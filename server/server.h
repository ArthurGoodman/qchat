#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork>

#include "../common/iconsole.h"

class Server : public QObject {
    Q_OBJECT

    IConsole *console;
    QTcpServer *tcpServer;

public:
    Server(IConsole *console);
    ~Server();

    void start(ushort port);

private slots:
    void clientConnected();
    void clientDisconnected();
};

#endif // SERVER_H
