#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>
#include <QString>
//添加此行用于UTF-8另存
class Shape
{
public:
    enum Code { Line, Rect }; // 添加枚举类型

    virtual ~Shape() {}
    virtual void paint(QPainter &painter) = 0;
    virtual QString toString() const = 0; // 转换为字符串
    virtual void fromString(const QString &data) = 0; // 从字符串解析

    void setStart(const QPoint &point) { start = point; }
    void setEnd(const QPoint &point) { end = point; }

protected:
    QPoint start;
    QPoint end;
};

#endif // SHAPE_H
