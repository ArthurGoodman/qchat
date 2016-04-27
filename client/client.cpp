#include "client.h"

#include <QtWidgets>

#include "clientwindow.h"

Client::Client(QString username)
    : username(username), console(0) {
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(connected()), SLOT(connected()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));
    connect(tcpSocket, SIGNAL(disconnected()), SLOT(disconnected()));
    connect(tcpSocket, SIGNAL(readyRead()), SLOT(readyRead()));
}

Client::~Client() {
    delete tcpSocket;
}

void Client::setConsole(IConsole *console) {
    this->console = console;
}

void Client::connectToServer(QHostAddress address, ushort port) {
    tcpSocket->connectToHost(address, port);
}

void Client::login(QString username) {
    QJsonObject obj;
    obj["command"] = "login";
    obj["username"] = username;

    QJsonDocument doc(obj);
    tcpSocket->write(doc.toJson());
}

void Client::sendMessage(QString message) {
    QJsonObject obj;
    obj["command"] = "broadcast";
    obj["message"] = message;

    QJsonDocument doc(obj);
    tcpSocket->write(doc.toJson());
}

void Client::connected() {
    ClientWindow *window = new ClientWindow(this);
    window->show();

    login(username);
}

void Client::disconnected() {
    reportError("Disconnected from server.");
}

void Client::socketError(QAbstractSocket::SocketError error) {
    switch (error) {
    case QAbstractSocket::RemoteHostClosedError:
        break;

    case QAbstractSocket::HostNotFoundError:
        reportError("Host not found.");
        break;

    case QAbstractSocket::ConnectionRefusedError:
        reportError("Connection refused.");
        break;

    default:
        reportError(tcpSocket->errorString());
    }
}

void Client::readyRead() {
    processCommand(tcpSocket->readAll());
}

void Client::processCommand(QString command) {
    console->writeLine(command);

    QJsonDocument doc = QJsonDocument::fromJson(command.toUtf8());
    QJsonObject obj = doc.object();
}

void Client::reportError(QString message) {
    if (console != 0)
        console->writeLine(message, Qt::red);
    else
        QMessageBox::critical(0, "Error", message);
}
