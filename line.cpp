#include "line.h"
//添加此行用于UTF-8另存
void Line::paint(QPainter &painter) {
    painter.drawLine(start, end);
}

QString Line::toString() const {
    return QString("Line,%1,%2,%3,%4")
    .arg(start.x()).arg(start.y())
        .arg(end.x()).arg(end.y());
}

void Line::fromString(const QString &data) {
    auto parts = data.split(',');
    if (parts.size() == 5 && parts[0] == "Line") {
        start.setX(parts[1].toInt());
        start.setY(parts[2].toInt());
        end.setX(parts[3].toInt());
        end.setY(parts[4].toInt());
    }
}
