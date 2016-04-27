#include <QApplication>

#include "connectdialog.h"
#include "client.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    ConnectDialog dialog;
    dialog.exec();

    if (dialog.result() == QDialog::Rejected)
        return 0;

    return app.exec();
}
