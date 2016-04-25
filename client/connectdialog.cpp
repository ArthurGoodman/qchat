#include "connectdialog.h"
#include "ui_connectdialog.h"

#include <QtWidgets>

ConnectDialog::ConnectDialog(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::ConnectDialog) {
    ui->setupUi(this);

    ui->ipAddressEdit->setFont(QFont("Consolas", 10));
    ui->ipAddressEdit->setInputMask("000.000.000.000");

    ui->usernameEdit->setFont(QFont("Consolas", 10));
    ui->usernameEdit->setValidator(new QRegExpValidator(QRegExp("[a-z]*")));
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

    if(getUsername().isEmpty()) {
        QMessageBox::critical(0, "Error", "Invalid username.");
        return;
    }

    accept();
}

void ConnectDialog::on_closeButton_clicked() {
    reject();
}
