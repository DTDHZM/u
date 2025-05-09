#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QFont>
#include <QLocale>
#include <QTranslator>
#include <QIcon> // Required for using icons
#include <QToolBar> // Required for using toolbar

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    isDrawing(false),
    drawMode(None)
{
    ui->setupUi(this);

    // 添加“文件”菜单
    QMenu *fileMenu = menuBar()->addMenu(tr("文件"));
    QAction *saveAction = new QAction(tr("保存"), this);
    QAction *openAction = new QAction(tr("打开"), this);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveShapesToFile);
    connect(openAction, &QAction::triggered, this, &MainWindow::loadShapesFromFile);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(openAction);

    // 添加工具栏
    QToolBar *toolBar = addToolBar(tr("工具栏"));

    // 添加“画线”按钮
    QAction *drawLineAction = new QAction(QIcon(":/line.png"), tr("画线"), this);

    connect(drawLineAction, &QAction::triggered, this, &MainWindow::selectDrawLine);
    toolBar->addAction(drawLineAction);

    // 添加“画矩形”按钮
    QAction *drawRectAction = new QAction(QIcon(":/rect.png"), tr("画矩形"), this);

    connect(drawRectAction, &QAction::triggered, this, &MainWindow::selectDrawRectangle);
    toolBar->addAction(drawRectAction);
}

MainWindow::~MainWindow()
{
    // 清理动态分配的形状
    for (Shape *shape : shapes) {
        delete shape;
    }
    delete ui;
}

// 其他绘图功能保持不变
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // 绘制所有形状
    for (Shape *shape : shapes) {
        shape->paint(painter);
    }

    if (isDrawing) {
        painter.setPen(Qt::DashLine);
        if (drawMode == LineMode) {
            painter.drawLine(startPoint, endPoint);
        } else if (drawMode == RectMode) {
            painter.drawRect(QRect(startPoint, endPoint));
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && drawMode != None) {
        startPoint = event->pos();
        isDrawing = true;
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && isDrawing) {
        endPoint = event->pos();
        isDrawing = false;

        if (drawMode == LineMode) {
            Line *line = new Line();
            line->setStart(startPoint);
            line->setEnd(endPoint);
            shapes.push_back(line);
        } else if (drawMode == RectMode) {
            Rect *rect = new Rect();
            rect->setStart(startPoint);
            rect->setEnd(endPoint);
            shapes.push_back(rect);
        }

        update();
    }
}

void MainWindow::saveShapesToFile()
{
    // 保存文件功能
}

void MainWindow::loadShapesFromFile()
{
    // 打开文件功能
}

void MainWindow::selectDrawLine()
{
    drawMode = LineMode;
}

void MainWindow::selectDrawRectangle()
{
    drawMode = RectMode;
}
