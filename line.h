#ifndef LINE_H
#define LINE_H
//添加此行用于UTF-8另存
#include "shape.h"
#include <QPoint>

class Line : public Shape
{
public:
    void paint(QPainter &painter) override;
    QString toString() const override; // 实现 toString 方法
    void fromString(const QString &data) override; // 实现 fromString 方法

    void setStart(const QPoint &point) { start = point; }
    void setEnd(const QPoint &point) { end = point; }

private:
    QPoint start;
    QPoint end;
};

#endif // LINE_H
