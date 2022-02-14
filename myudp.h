#ifndef MYUDP_H
#define MYUDP_H

#include <QObject>
#include <QByteArray>
#include <QDebug>
#include <QUdpSocket>
#include <QHostAddress>
#include <QHostInfo>

class myUDP : public QObject
{
    Q_OBJECT
public:
    explicit myUDP(QObject *parent = nullptr);

    void HelloUDP();

signals:

public slots:
    void readyRead();

private:
    QUdpSocket *socket;

};

#endif // MYUDP_H
