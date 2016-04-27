#include "utility.h"

#include <QCryptographicHash>
#include <QDataStream>

uint Utility::hash(const QString &str) {
    QByteArray hash = QCryptographicHash::hash(QByteArray::fromRawData((const char *)str.utf16(), str.length() * 2), QCryptographicHash::Md5);

    Q_ASSERT(hash.size() == 16);

    QDataStream stream(&hash, QIODevice::ReadOnly);

    uint a, b;
    stream >> a >> b;

    return a ^ b;
}

QColor Utility::colorString(const QString &str) {
    return QColor::fromHsv(hash(str) % 360, 255, 255);
}
