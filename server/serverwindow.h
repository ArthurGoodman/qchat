#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QMainWindow>

#include "server.h"

namespace Ui {
class ServerWindow;
}

class ServerWindow : public QMainWindow {
    Q_OBJECT

    static const ushort port = 43567;

    Server *server;

public:
    explicit ServerWindow(QWidget *parent = 0);
    ~ServerWindow();

protected:
    void keyPressEvent(QKeyEvent *e);

private:
    Ui::ServerWindow *ui;
};

#endif // SERVERWINDOW_H
