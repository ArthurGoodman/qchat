#include "client.h"

#include <QtWidgets>

Client::Client() {
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(connected()), SLOT(connected()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));
    connect(tcpSocket, SIGNAL(readyRead()), SLOT(readyRead()));
}

Client::~Client() {
    delete tcpSocket;
}

void Client::connectToServer(QHostAddress address, ushort port) {
    tcpSocket->connectToHost(address, port);
}

void Client::connected() {
    qDebug() << "connected";
}

void Client::socketError(QAbstractSocket::SocketError error) {
    switch (error) {
    case QAbstractSocket::RemoteHostClosedError:
        break;

    case QAbstractSocket::HostNotFoundError:
        QMessageBox::critical(0, "Error", "Host not found.");
        break;

    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::critical(0, "Error", "Connection refused.");
        break;

    default:
        QMessageBox::critical(0, "Error", tcpSocket->errorString());
    }
}

void Client::readyRead() {
    qDebug() << "readyRead";
}
