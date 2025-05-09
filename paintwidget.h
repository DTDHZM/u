#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H
//添加此行用于UTF-8另存
#include <QWidget>
#include <QList>
#include "shape.h"

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = nullptr);
    ~PaintWidget(); // 添加析构函数

public slots:
    void setCurrentShape(Shape::Code s) { currShapeCode = s; }

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;

private:
    Shape::Code currShapeCode;
    Shape *currentShape;
    bool isDrawing;
    QList<Shape*> shapes;
};

#endif // PAINTWIDGET_H
