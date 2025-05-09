#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPoint>
#include <QPainter>
#include <vector>
#include "line.h"
#include "rect.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void saveShapesToFile();
    void loadShapesFromFile();
    void selectDrawLine();
    void selectDrawRectangle();

private:
    Ui::MainWindow *ui;
    std::vector<Shape*> shapes; // 存储所有形状
    QPoint startPoint; // 起点
    QPoint endPoint;   // 终点
    bool isDrawing;    // 是否正在绘制
    enum DrawMode { None, LineMode, RectMode } drawMode; // 绘图模式
};

#endif // MAINWINDOW_H
