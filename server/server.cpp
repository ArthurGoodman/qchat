#include "server.h"

Server::Server(IConsole *console)
    : console(console) {
    tcpServer = new QTcpServer(this);
    connect(tcpServer, QTcpServer::newConnection, this, Server::newConnection);
}

Server::~Server() {
    delete tcpServer;
}

void Server::start(ushort port) {
    tcpServer->listen(QHostAddress::Any, port);

    if (!tcpServer->isListening())
        console->write("Failed to start server.", Qt::red);
    else
        console->write("Server is started and listening to port " + QString::number(port) + ".", Qt::green);
}

void Server::newConnection() {
    qDebug() << tcpServer->nextPendingConnection();
}
