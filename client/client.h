#ifndef CLIENT_H
#define CLIENT_H

#include <QtNetwork>

#include "../common/Iconsole.h"

class Client : public QObject {
    Q_OBJECT

    QTcpSocket *tcpSocket;
    QString username;

    IConsole *console;

public:
    Client(QString username);
    ~Client();

    void setConsole(IConsole *console);

    void connectToServer(QHostAddress address, ushort port);

    void login(QString username);
    void sendMessage(QString message);

private slots:
    void connected();
    void disconnected();
    void socketError(QAbstractSocket::SocketError error);
    void readyRead();

private:
    void processCommand(QString command);
    void reportError(QString message);
};

#endif // CLIENT_H
