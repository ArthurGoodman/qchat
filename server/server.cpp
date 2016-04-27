#include "server.h"

#include <QtWidgets>

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
        console->writeLine("Failed to start server.", Qt::red);
    else
        console->writeLine("Server is started.", Qt::green);
}

void Server::clientConnected() {
    QTcpSocket *client = tcpServer->nextPendingConnection();
    connect(client, SIGNAL(disconnected()), SLOT(clientDisconnected()));
    connect(client, SIGNAL(disconnected()), client, SLOT(deleteLater()));
    connect(client, SIGNAL(readyRead()), SLOT(readyRead()));

    console->writeLine("Client connected.");
}

void Server::clientDisconnected() {
    QTcpSocket *client = (QTcpSocket *)sender();

    QString username = socketUser[client];

    socketUser.remove(client);
    userSocket.remove(username);

    console->writeLine(username + " disconnected.");
}

void Server::readyRead() {
    QTcpSocket *client = (QTcpSocket *)sender();
    processCommand(client, client->readAll());
}

void Server::processCommand(QTcpSocket *client, QString command) {
    console->writeLine(command);

    QJsonDocument doc = QJsonDocument::fromJson(command.toUtf8());
    QJsonObject obj = doc.object();

    if (obj["command"].toString() == "login") {
        userSocket[obj["username"].toString()] = client;
        socketUser[client] = obj["username"].toString();
    } else if (obj["command"].toString() == "broadcast") {
        foreach (QTcpSocket *socket, socketUser.keys())
            socket->write(command.toUtf8());
    }
}
