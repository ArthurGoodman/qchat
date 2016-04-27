#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>

#include "client.h"

namespace Ui {
class ClientWindow;
}

class ClientWindow : public QMainWindow {
    Q_OBJECT

    Client *client;

public:
    explicit ClientWindow(Client *client, QWidget *parent = 0);
    ~ClientWindow();

private slots:
    void on_sendButton_clicked();
    void on_messageEdit_returnPressed();

protected:
    void keyPressEvent(QKeyEvent *e);

private:
    Ui::ClientWindow *ui;
};

#endif // CLIENTWINDOW_H
