#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    COM = new QSerialPort(this);
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        ui->com_combobox->addItem(info.portName());

    connect(COM, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(ui->com_button, SIGNAL(clicked(bool)), this, SLOT(connectCOM()));
    connect(ui->echo_button, SIGNAL(clicked(bool)), this, SLOT(getEcho()));
    connect(timer_echo, SIGNAL(timeout()), this, SLOT(timer_echo_timeout()));
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

MainWindow::~MainWindow()
{
    delete ui;
}
