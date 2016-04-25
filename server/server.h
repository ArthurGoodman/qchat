#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>

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
    void newConnection();
};

#endif // SERVER_H
