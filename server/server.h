#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork>

#include "../common/iconsole.h"

class Server : public QObject {
    Q_OBJECT

    IConsole *console;
    QTcpServer *tcpServer;

    QMap<QString, QTcpSocket *> userSocket;
    QMap<QTcpSocket *, QString> socketUser;

public:
    Server(IConsole *console);
    ~Server();

    void start(ushort port);

private slots:
    void clientConnected();
    void clientDisconnected();
    void readyRead();

private:
    void processCommand(QTcpSocket *client, QString command);

    void broadcast(QString message, QTcpSocket *except = 0);

    void accept(QTcpSocket *client);
    void reject(QTcpSocket *client);

    void noSuchUser(QTcpSocket *client);

    void reportUsers(QTcpSocket *client);
};

#endif // SERVER_H
