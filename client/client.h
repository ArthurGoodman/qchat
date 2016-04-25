#ifndef CLIENT_H
#define CLIENT_H

#include <QtNetwork>

class Client : public QObject {
    Q_OBJECT

    QTcpSocket *tcpSocket;

public:
    Client();
    ~Client();

    void connectToServer(QHostAddress address, ushort port);

private slots:
    void connected();
    void socketError(QAbstractSocket::SocketError error);
    void readyRead();
};

#endif // CLIENT_H
