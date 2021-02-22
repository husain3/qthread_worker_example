#ifndef MYUDP_H
#define MYUDP_H

#include <QObject>
#include <QUdpSocket>

class MyUDP : public QObject
{
    Q_OBJECT
public:
    MyUDP(QObject *parent) :
        QObject(parent)
    {
        // create a QUDP socket
        socket = new QUdpSocket(this);

        socket->bind(QHostAddress::LocalHost, 27150);

        connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    }

signals:

public slots:
    void readyRead() {
        // when data comes in
        QByteArray buffer;
        buffer.resize(socket->pendingDatagramSize());

        QHostAddress sender;
        quint16 senderPort;

        socket->readDatagram(buffer.data(), buffer.size(),
                             &sender, &senderPort);

        qDebug() << "Message from: " << sender.toString();
        qDebug() << "Message port: " << senderPort;
        qDebug() << "Message: " << buffer;
    }

private:
    QUdpSocket *socket;

};

#endif // MYUDP_H
