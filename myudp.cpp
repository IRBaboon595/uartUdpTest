#include "myudp.h"

myUDP::myUDP(QObject *parent) : QObject(parent)
{
    // create a QUDP socket
    socket = new QUdpSocket(this);
    QHostAddress myPC;
    myPC.setAddress("192.168.1.46");
    // The most common way to use QUdpSocket class is
    // to bind to an address and port using bind()
    // bool QAbstractSocket::bind(const QHostAddress & address,
    //     quint16 port = 0, BindMode mode = DefaultForPlatform)
    socket->bind(myPC, 22);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void myUDP::HelloUDP()
{
    QByteArray Data;
    Data.append("Hello from UDP");
    QHostAddress iPhone;
    iPhone.setAddress("192.168.1.59");
    // Sends the datagram datagram
    // to the host address and at port.
    // qint64 QUdpSocket::writeDatagram(const QByteArray & datagram,
    //                      const QHostAddress & host, quint16 port)
    socket->writeDatagram(Data, iPhone, 4023);
}

void myUDP::readyRead()
{
    // when data comes in
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    // qint64 QUdpSocket::readDatagram(char * data, qint64 maxSize,
    //                 QHostAddress * address = 0, quint16 * port = 0)
    // Receives a datagram no larger than maxSize bytes and stores it in data.
    // The sender's host address and port is stored in *address and *port
    // (unless the pointers are 0).

    socket->readDatagram(buffer.data(), buffer.size(),
                         &sender, &senderPort);

    qDebug() << "Message from: " << sender.toString();
    qDebug() << "Message port: " << senderPort;
    qDebug() << "Message: " << buffer;
    HelloUDP();
}
