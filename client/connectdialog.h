#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include <QtNetwork>

#include "client.h"

namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QDialog {
    Q_OBJECT

    Client *client;
    bool connected;

public:
    explicit ConnectDialog(QWidget *parent = 0);
    ~ConnectDialog();

    QHostAddress getIPAddress();
    QString getUsername();

private slots:
    void on_connectButton_clicked();
    void on_closeButton_clicked();

    void connectedToServer();
    void accepted();
    void rejected();

private:
    Ui::ConnectDialog *ui;
};

#endif // CONNECTDIALOG_H
