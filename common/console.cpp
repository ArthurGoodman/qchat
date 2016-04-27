#include "console.h"

#include <QTime>

Console::Console(QWidget *parent)
    : QTextEdit(parent) {
    setReadOnly(true);
    setFont(QFont("Consolas", 10));

    setStyleSheet("QTextEdit { background: #202020 }");
}

void Console::write(const QString &text, const QColor &color) {
    moveCursor(QTextCursor::End);

    QTextCharFormat format = currentCharFormat();
    format.setForeground(color);
    setCurrentCharFormat(format);

    insertPlainText(text);
}

void Console::writeLine(const QString &text, const QColor &color) {
    write(text, color);

    insertPlainText("\n");
}

void Console::timestamp() {
    write(QTime::currentTime().toString("hh:mm") + " ", Qt::darkGray);
}
