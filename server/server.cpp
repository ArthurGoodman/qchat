#include "server.h"

#include <QtWidgets>

#include "../common/utility.h"

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

    QJsonObject obj;
    obj["command"] = "leave";
    obj["username"] = username;

    QJsonDocument doc(obj);
    broadcast(doc.toJson());
}

void Server::readyRead() {
    QTcpSocket *client = (QTcpSocket *)sender();
    processCommand(client, client->readAll());
}

void Server::processCommand(QTcpSocket *client, QString command) {
    console->writeLine(command.simplified());

    QJsonDocument doc = QJsonDocument::fromJson(command.toUtf8());
    QJsonObject obj = doc.object();

    if (obj["command"].toString() == "login") {
        if (userSocket.keys().contains(obj["username"].toString())) {
            reject(client);
        } else {
            accept(client);

            userSocket[obj["username"].toString()] = client;
            socketUser[client] = obj["username"].toString();

            broadcast(command, client);
        }
    } else if (obj["command"].toString() == "broadcast") {
        broadcast(command, client);
    } else if (obj["command"].toString() == "private") {
        if (!userSocket.keys().contains(obj["recipient"].toString()))
            noSuchUser(client);
        else if (userSocket[obj["recipient"].toString()] != client) {
            userSocket[obj["recipient"].toString()]->write(command.toUtf8());
        }
    } else if (obj["command"].toString() == "users") {
        reportUsers(client);
    }
}

void Server::broadcast(QString message, QTcpSocket *except) {
    foreach (QTcpSocket *socket, socketUser.keys())
        if (socket != except)
            socket->write(message.toUtf8());
}

void Server::accept(QTcpSocket *client) {
    QJsonObject obj;
    obj["command"] = "accept";

    QJsonDocument doc(obj);
    client->write(doc.toJson());
}

void Server::reject(QTcpSocket *client) {
    QJsonObject obj;
    obj["command"] = "reject";

    QJsonDocument doc(obj);
    client->write(doc.toJson());
}

void Server::noSuchUser(QTcpSocket *client) {
    QJsonObject obj;
    obj["command"] = "no_such_user";

    QJsonDocument doc(obj);
    client->write(doc.toJson());
}

void Server::reportUsers(QTcpSocket *client) {
    QString users = "";

    foreach (QString user, userSocket.keys()) {
        if (!users.isEmpty())
            users += ",";

        users += user;
    }

    QJsonObject obj;
    obj["command"] = "users";
    obj["users"] = users;

    QJsonDocument doc(obj);
    client->write(doc.toJson());
}
