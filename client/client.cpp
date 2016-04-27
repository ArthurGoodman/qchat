#include "client.h"

#include <QtWidgets>

#include "clientwindow.h"
#include "../common/utility.h"

Client::Client()
    : console(0) {
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

void Client::login() {
    QJsonObject obj;
    obj["command"] = "login";
    obj["username"] = username;

    QJsonDocument doc(obj);
    tcpSocket->write(doc.toJson());
}

void Client::sendMessage(QString message) {
    if (message == "\\users") {
        QJsonObject obj;
        obj["command"] = "users";

        QJsonDocument doc(obj);
        tcpSocket->write(doc.toJson());
    } else if (message[0] == '@') {
        QRegExp regExp("^@([a-zA-Z]+)");
        regExp.indexIn(message);

        QString recipient = regExp.cap(1);

        if (recipient.isEmpty())
            reportError("Invalid username.");
        else if (regExp.matchedLength() == message.length())
            reportError("Empty message.");
        else {
            QJsonObject obj;
            obj["command"] = "private";
            obj["username"] = username;
            obj["recipient"] = recipient;
            obj["message"] = message.mid(regExp.matchedLength() + 1).trimmed();

            QJsonDocument doc(obj);
            tcpSocket->write(doc.toJson());

            writePrivateMessage(obj);
        }
    } else {
        QJsonObject obj;
        obj["command"] = "broadcast";
        obj["username"] = username;
        obj["message"] = message;

        QJsonDocument doc(obj);
        tcpSocket->write(doc.toJson());

        writeMessage(obj);
    }
}

void Client::setUsername(const QString &username) {
    this->username = username;
}

QString Client::getUsername() {
    return username;
}

void Client::connected() {
    emit connectedToServer();
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
    //    if (console)
    //        console->writeLine(command.simplified());

    QJsonDocument doc = QJsonDocument::fromJson(command.toUtf8());
    QJsonObject obj = doc.object();

    if (obj["command"].toString() == "login") {
        console->write(obj["username"].toString(), Utility::colorString(obj["username"].toString()));
        console->writeLine(" joined the conversation.");
    } else if (obj["command"].toString() == "broadcast") {
        writeMessage(obj);
    } else if (obj["command"].toString() == "private") {
        writePrivateMessage(obj);
    } else if (obj["command"].toString() == "leave") {
        console->write(obj["username"].toString(), Utility::colorString(obj["username"].toString()));
        console->writeLine(" has left the conversation.");
    } else if (obj["command"].toString() == "accept") {
        emit accepted();
    } else if (obj["command"].toString() == "reject") {
        emit rejected();
    } else if (obj["command"].toString() == "no_such_user") {
        reportError("No such user.");
    } else if (obj["command"].toString() == "users") {
        QStringList users = obj["users"].toString().split(',');

        console->writeLine("Users:");

        foreach (QString user, users)
            console->writeLine(user, Utility::colorString(user));
    }
}

void Client::reportError(QString message) {
    if (console != 0)
        console->writeLine(message, Qt::red);
    else
        QMessageBox::critical(0, "Error", message);
}

void Client::writeMessage(const QJsonObject &obj) {
    console->timestamp();
    console->write(obj["username"].toString(), Utility::colorString(obj["username"].toString()));
    console->writeLine(": " + obj["message"].toString());
}

void Client::writePrivateMessage(const QJsonObject &obj) {
    console->timestamp();
    console->write(obj["username"].toString(), Utility::colorString(obj["username"].toString()));
    console->write(" -> ");
    console->write(obj["recipient"].toString(), Utility::colorString(obj["recipient"].toString()));
    console->writeLine(": " + obj["message"].toString());
}
