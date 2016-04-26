#include "server.h"

Server::Server(IConsole *console)
    : console(console) {
    tcpServer = new QTcpServer(this);
    connect(tcpServer, SIGNAL(newConnection()), SLOT(clientConnected()));
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

void Server::clientConnected() {
    QTcpSocket *client = tcpServer->nextPendingConnection();
    connect(client, SIGNAL(disconnected()), SLOT(clientDisconnected()));
    connect(client, SIGNAL(disconnected()), client, SLOT(deleteLater()));

    console->write("Client connected.");
}

void Server::clientDisconnected() {
    QTcpSocket *socket = (QTcpSocket *)sender();

    console->write("Client disconnected.");
}
