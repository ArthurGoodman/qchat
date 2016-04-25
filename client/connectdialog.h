#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include <QtNetwork>

namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QDialog {
    Q_OBJECT

public:
    explicit ConnectDialog(QWidget *parent = 0);
    ~ConnectDialog();

    QHostAddress getIPAddress();
    QString getUsername();

private slots:
    void on_connectButton_clicked();
    void on_closeButton_clicked();

private:
    Ui::ConnectDialog *ui;
};

#endif // CONNECTDIALOG_H
