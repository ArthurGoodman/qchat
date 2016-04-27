#ifndef CONSOLE_H
#define CONSOLE_H

#include <QTextEdit>

#include "iconsole.h"

class Console : public QTextEdit, public IConsole {
public:
    Console(QWidget *parent = 0);

    void write(const QString &text, const QColor &color);
    void writeLine(const QString &text, const QColor &color);
};

#endif // CONSOLE_H
