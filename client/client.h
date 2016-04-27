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
    Client();
    ~Client();

    void setConsole(IConsole *console);

    void connectToServer(QHostAddress address, ushort port);

    void login();
    void sendMessage(QString message);

    void setUsername(const QString &username);
    QString getUsername();

private slots:
    void connected();
    void disconnected();
    void socketError(QAbstractSocket::SocketError error);
    void readyRead();

private:
    void processCommand(QString command);
    void reportError(QString message);
    void writeMessage(const QJsonObject &obj);
    void writePrivateMessage(const QJsonObject &obj);

signals:
    void connectedToServer();
    void accepted();
    void rejected();
};

#endif // CLIENT_H
