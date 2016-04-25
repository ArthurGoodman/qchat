#include "console.h"

Console::Console(QWidget *parent)
    : QTextEdit(parent) {
    setReadOnly(true);
    setFont(QFont("Consolas", 10));

    setStyleSheet("QTextEdit { background: #202020 }");
}

void Console::write(const QString &text, const QColor &color) {
    insertHtml("<font color=\"" + color.name() + "\">" + text + "</font><br>");
}
