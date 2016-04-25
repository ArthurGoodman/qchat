#include "serverwindow.h"
#include "ui_serverwindow.h"

#include <QtWidgets>

ServerWindow::ServerWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::ServerWindow) {
    ui->setupUi(this);

    server = new Server(ui->console);
    server->start(port);
}

ServerWindow::~ServerWindow() {
    delete ui;

    delete server;
}

void ServerWindow::keyPressEvent(QKeyEvent *e) {
    switch (e->key()) {
    case Qt::Key_Escape:
        close();
        break;
    }
}
