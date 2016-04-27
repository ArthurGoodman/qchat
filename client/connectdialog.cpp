#include "connectdialog.h"
#include "ui_connectdialog.h"

#include <QtWidgets>

#include "client.h"
#include "clientwindow.h"

ConnectDialog::ConnectDialog(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::ConnectDialog) {
    ui->setupUi(this);

    ui->ipAddressEdit->setFont(QFont("Consolas", 10));
    ui->ipAddressEdit->setInputMask("000.000.000.000");

    ui->usernameEdit->setFont(QFont("Consolas", 10));
    ui->usernameEdit->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z]*")));

    connected = false;

    client = new Client;
    connect(client, SIGNAL(connectedToServer()), SLOT(connectedToServer()));
    connect(client, SIGNAL(accepted()), SLOT(accepted()));
    connect(client, SIGNAL(rejected()), SLOT(rejected()));
}

ConnectDialog::~ConnectDialog() {
    delete ui;
}

QHostAddress ConnectDialog::getIPAddress() {
    return QHostAddress(ui->ipAddressEdit->text());
}

QString ConnectDialog::getUsername() {
    return ui->usernameEdit->text();
}

void ConnectDialog::on_connectButton_clicked() {
    if (getIPAddress().isNull()) {
        QMessageBox::critical(0, "Error", "Invalid IP address.");
        return;
    }

    if (getUsername().isEmpty()) {
        QMessageBox::critical(0, "Error", "Invalid username.");
        return;
    }

    if (!connected) {
        client->connectToServer(getIPAddress(), 43567);
    } else {
        client->setUsername(getUsername());
        client->login();
    }
}

void ConnectDialog::on_closeButton_clicked() {
    reject();
}

void ConnectDialog::connectedToServer() {
    connected = true;

    client->setUsername(getUsername());
    client->login();
}

void ConnectDialog::accepted() {
    qDebug() << "accepted";

    ClientWindow *window = new ClientWindow(client);
    window->show();

    accept();
}

void ConnectDialog::rejected() {
    qDebug() << "rejected";

    QMessageBox::critical(0, "Error", "Username is already in use.");
}
