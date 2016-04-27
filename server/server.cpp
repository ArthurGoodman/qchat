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
    connect(client, SIGNAL(readyRead()), SLOT(readyRead()));

    console->write("Client connected.");
}

void Server::clientDisconnected() {
    QTcpSocket *client = (QTcpSocket *)sender();

    QString username = socketUser[client];

    socketUser.remove(client);
    userSocket.remove(username);

    console->write(username + " disconnected.");
}

void Server::readyRead() {
    QTcpSocket *client = (QTcpSocket *)sender();
    processCommand(client->readAll());
}

void Server::processCommand(QString command) {
    console->write(command);
}
