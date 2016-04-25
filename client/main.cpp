#include <QApplication>

#include "connectdialog.h"
#include "client.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    ConnectDialog dialog;
    dialog.exec();

    if (dialog.result() == QDialog::Rejected)
        return 0;
    else {
        QHostAddress ipAddress = dialog.getIPAddress();

        Client *client = new Client;
        client->connectToServer(ipAddress, 43567);
    }

    return app.exec();
}
