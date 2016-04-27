#ifndef ICONSOLE_H
#define ICONSOLE_H

#include <QString>
#include <QColor>

class IConsole {
public:
    virtual ~IConsole();

    virtual void write(const QString &text, const QColor &color = Qt::lightGray) = 0;
    virtual void writeLine(const QString &text, const QColor &color = Qt::lightGray) = 0;
};

#endif // ICONSOLE_H
