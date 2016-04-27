#include "clientwindow.h"
#include "ui_clientwindow.h"

#include <QtWidgets>

ClientWindow::ClientWindow(Client *client, QWidget *parent)
    : QMainWindow(parent), client(client), ui(new Ui::ClientWindow) {
    ui->setupUi(this);

    client->setConsole(ui->console);

    ui->messageEdit->setFont(QFont("Consolas", 10));

    setWindowTitle("Client - " + client->getUsername());
}

ClientWindow::~ClientWindow() {
    delete ui;
}

void ClientWindow::on_sendButton_clicked() {
    if (ui->messageEdit->text().isEmpty())
        return;

    client->sendMessage(ui->messageEdit->text());
    ui->messageEdit->clear();
}

void ClientWindow::on_messageEdit_returnPressed() {
    on_sendButton_clicked();
}

void ClientWindow::keyPressEvent(QKeyEvent *e) {
    switch (e->key()) {
    case Qt::Key_Escape:
        close();
        break;
    }
}
