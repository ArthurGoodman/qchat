#ifndef UTILITY_H
#define UTILITY_H

#include <QString>
#include <QColor>

class Utility {
public:
    static uint hash(const QString &str);
    static QColor colorString(const QString &str);
};

#endif // UTILITY_HD
