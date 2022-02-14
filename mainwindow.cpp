#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    hostIPAddr = getHostIP();
    hostPort = 22;
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress(hostIPAddr), hostPort);
    //hostPort = ui->udpPortLineEdit->text().toUInt();

    COM = new QSerialPort(this);
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        ui->com_combobox->addItem(info.portName());

    connect(COM, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(ui->com_button, SIGNAL(clicked(bool)), this, SLOT(connectCOM()));
    connect(ui->echo_button, SIGNAL(clicked(bool)), this, SLOT(getEcho()));
    connect(timer_echo, SIGNAL(timeout()), this, SLOT(timer_echo_timeout()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(udpRead()));
}

/**************************************** Service Functions ****************************************/

void MainWindow::connectCOM(void)
{
    if(COM->portName() != ui->com_combobox->currentText())
    {
        COM->close();
        COM->setPortName(ui->com_combobox->currentText());
    }

    COM->setBaudRate(QSerialPort::Baud115200, QSerialPort::AllDirections);
    COM->setDataBits(QSerialPort::Data8);
    COM->setParity(QSerialPort::NoParity);
    COM->setStopBits(QSerialPort::OneStop);
    COM->setFlowControl(QSerialPort::NoFlowControl);
    COM->setReadBufferSize(0);
    if(COM->open(QSerialPort::ReadWrite))
    {
        ui->comstate_label->setText("<FONT COLOR=#008000>Opened</FONT>");
        com_mode = 1;
        ui->com_button->setText("Close port");
    }
    else
    {
        COM->close();
        ui->comstate_label->setText("<FONT COLOR=red>Closed</FONT>");
        ui->com_button->setText("Open port");
        com_mode = 0;
    }
}

QString MainWindow::getHostIP()
{
    QUdpSocket tempSock;
    QString localIP="127.0.0.1";    //fall back
    QString googleDns = "8.8.8.83";  //try google DNS or sth. else reliable first
    tempSock.connectToHost(googleDns, 53);
    if (tempSock.waitForConnected(3000))
    {
        localIP = tempSock.localAddress().toString();
    }
    else
    {
        foreach (const QHostAddress &address, QNetworkInterface::allAddresses())
        {
            QString guessedGatewayAddress = address.toString().section( ".",0,2 ) + ".1";

            if (address.protocol() == QAbstractSocket::IPv4Protocol
                    && address != QHostAddress(QHostAddress::LocalHost)
                    )
            {
                tempSock.connectToHost(guessedGatewayAddress, 53);
                if (tempSock.waitForConnected(3000))
                {
                    localIP = tempSock.localAddress().toString();
                    break;
                }
            }
        }
    }


    return localIP;
}

/***************************************** Control Functions *********************************************/

void MainWindow::getEcho(void)
{
    QByteArray ba_1;
    char len = 0x06;
    char crc = 0;
    char echo = ECHO;
    ba_1.append(SYNCHRO);
    ba_1.append(char(0x00));
    ba_1.append(len);
    ba_1.append(UART_ADDR);
    ba_1.append(echo);
    for(int i = 0; i < ba_1.size(); i++)
    {
        crc ^= ba_1.at(i);
    }
    ba_1.append(crc);
    if(COM->write(ba_1) != -1)
    {
        COM->waitForBytesWritten(200);
        COM->waitForReadyRead(300);
    }
}

void MainWindow::timer_echo_timeout()
{
    ui->service_message->setText("Empty");
}

void MainWindow::on_com_refresh_button_clicked()
{
    ui->com_combobox->clear();
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        ui->com_combobox->addItem(info.portName());
}

void MainWindow::readData(void)
{
    char temp = 0;
    bool trigger = true;
    std_union len;
    len.istd = 0;
    qDebug() << "ReadyRead_Got";
    ba.append(COM->readAll());
    qDebug() << ba.size();

    int idx = ba.indexOf(SYNCHRO, 0);
    if(idx >= 0)
    {
        qDebug() << "Synchro byte found";
        if(idx > 0)
        {
            ba.remove(0,idx);
            idx = 0;
        }
        while((ba.size() >= 6) && (trigger))
        {
            qDebug() << "Potential parcel len achieved";
            len.cstd[1] = uint8_t(ba[1]);
            len.cstd[0] = uint8_t(ba[2]);
            qDebug() << len.istd;
            temp = ba[3];
            if(temp == UART_ADDR)
            {
                qDebug() << "Address achieved";
                for(int i = 0; i < len.istd; i++)
                {
                    CRC ^= ba[i];
                }
                if(CRC == 0)
                {
                    qDebug() << "XOR approved";
                    temp = ba[4];
                    switch (temp)
                    {
                    case ECHO:
                        ui->service_message->setText("Echo Got");
                        timer_echo->start(1000);
                        uart_command = 0;
                        break;
                    case SUPPLY_CTRL:

                        break;
                    default:
                        ui->uartMessage->setText(ba.toHex());
                        uart_command = 255;
                        break;
                    }
                    trigger = false;
                    ba.clear();
                }
                else
                {
                    qDebug() << "XOR error";
                    idx = ba.indexOf(SYNCHRO, 1);
                    int bad_len = idx;
                    ba.remove(0, bad_len);
                }

            }
            else
            {
                qDebug() << "Address error";
                idx = ba.indexOf(SYNCHRO, 1);
                int bad_len = idx;
                ba.remove(0, bad_len);
            }
        }
    }
    else
    {
        qDebug() << "No Synchro";
        ba.clear();
    }
    CRC = 0;
}

void MainWindow::on_sendButton_clicked()
{
    QString *string = new QString(ui->uartMessage->text());
    QString tempString;
    QStringList *stringList = new QStringList;
    int u = 0;
    bool check = true;
    QByteArray ba_1;
    ba_1.clear();
    tempString.clear();
    stringList->clear();
    int idx_1 = string->indexOf('$', 0);
    int idx_2 = string->indexOf('$', idx_1 + 1);
    while((idx_2 - idx_1) > 3)
    {
        string->remove(0, idx_2);
        idx_1 = string->indexOf('$', 0);
        idx_2 = string->indexOf('$', idx_1 + 1);
    }

    if(idx_1 != -1)
    {
        do
        {
            string->remove(0, idx_1 + 1);
            if((idx_2 - idx_1) == 3)
            {
                tempString.append(string->at(0));
                tempString.append(string->at(1));
                tempString.toInt(&check, 16);
                if(check == false)
                    tempString.clear();
                string->remove(0, 1);
                string->remove(0, 1);
            }
            else if((idx_2 - idx_1) == 2)
            {
                tempString.append(string->at(0));
                tempString.toInt(&check, 16);
                if(check == false)
                    tempString.clear();
                string->remove(0, 1);
            }
            stringList->append(tempString);
            tempString.clear();
            idx_1 = string->indexOf('$', 0);
            idx_2 = string->indexOf('$', idx_1 + 1);
            while((idx_2 - idx_1) > 3)
            {
                string->remove(0, idx_2);
                idx_1 = string->indexOf('$', 0);
                idx_2 = string->indexOf('$', idx_1 + 1);
            }
            if(idx_2 == -1)
                idx_2 = string->size();
            //qDebug() << stringList->at(u);
            //u++;
        }
        while(idx_1 != -1);
        for (int i = 0; i < stringList->size(); i++) {
            ba_1.append(stringList->at(i).toInt(nullptr, 16));
        }
    }
    else
    {
        ba_1.append(string->toUtf8());
    }

    //qDebug() << ba_1.toHex();

    if(COM->write(ba_1) != -1)
    {
        COM->waitForBytesWritten(200);
        COM->waitForReadyRead(300);
    }

}

void MainWindow::on_udpSendButton_clicked()
{
    QByteArray Data;
    Data.append(ui->udpDataLineEdit->text());

    socket->writeDatagram(Data, QHostAddress(clientIPAddr), clientPort);
}

void MainWindow::on_setSocketButton_clicked()
{
    clientPort = ui->udpPortLineEdit->text().toUInt();
    clientIPAddr = ui->ip4LineEdit_3->text()+ '.' + ui->ip4LineEdit_2->text() + '.' + ui->ip4LineEdit_1->text() + '.' + ui->ip4LineEdit_0->text();

    qDebug() << clientPort << clientIPAddr;
}

void MainWindow::udpRead()
{
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    socket->readDatagram(buffer.data(), buffer.size(),
                         &sender, &senderPort);

    qDebug() << "Message from: " << sender.toString();
    qDebug() << "Message port: " << senderPort;
    qDebug() << "Message: " << buffer;

    ui->udpDataLabel->setText(QString::fromStdString(buffer.toStdString()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
