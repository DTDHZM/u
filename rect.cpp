#include "rect.h"
//添加此行用于UTF-8另存
void Rect::paint(QPainter &painter) {
    painter.drawRect(QRect(start, end));
}

QString Rect::toString() const {
    return QString("Rect,%1,%2,%3,%4")
    .arg(start.x()).arg(start.y())
        .arg(end.x()).arg(end.y());
}

void Rect::fromString(const QString &data) {
    auto parts = data.split(',');
    if (parts.size() == 5 && parts[0] == "Rect") {
        start.setX(parts[1].toInt());
        start.setY(parts[2].toInt());
        end.setX(parts[3].toInt());
        end.setY(parts[4].toInt());
    }
}
