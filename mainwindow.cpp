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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    isDrawing(false),
    drawMode(None)
{
    ui->setupUi(this);



    // 添加“文件“
    QMenu *fileMenu = menuBar()->addMenu(tr("文件"));
    QAction *saveAction = new QAction(tr("保存"), this);
    QAction *openAction = new QAction(tr("打开"), this);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveShapesToFile);
    connect(openAction, &QAction::triggered, this, &MainWindow::loadShapesFromFile);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(openAction);

    // 添加“绘图”
    QMenu *drawMenu = menuBar()->addMenu(tr("绘图"));
    QAction *drawLineAction = new QAction(tr("画线"), this);
    QAction *drawRectAction = new QAction(tr("画矩形"), this);
    connect(drawLineAction, &QAction::triggered, this, &MainWindow::selectDrawLine);
    connect(drawRectAction, &QAction::triggered, this, &MainWindow::selectDrawRectangle);
    drawMenu->addAction(drawLineAction);
    drawMenu->addAction(drawRectAction);
}

MainWindow::~MainWindow()
{
    // 清理动态分配的形状
    for (Shape *shape : shapes) {
        delete shape;
    }
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // 绘制所有形状
    for (Shape *shape : shapes) {
        shape->paint(painter);
    }

    // 绘制正在创建的形状
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

        // 根据当前模式创建形状
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

        // 更新绘图
        update();
    }
}

void MainWindow::saveShapesToFile()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("保存文件"), "", tr("Text Files (*.txt)"));
    if (filePath.isEmpty()) return;

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("错误"), tr("无法保存文件"));
        return;
    }

    QTextStream out(&file);
    out.setCodec("UTF-8"); // 设置保存为 UTF-8 编码

    for (Shape *shape : shapes) {
        out << shape->toString() << "\n"; // 调用 toString 方法
    }

    file.close();
    QMessageBox::information(this, tr("成功"), tr("文件已保存"));
}

void MainWindow::loadShapesFromFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("打开文件"), "", tr("Text Files (*.txt)"));
    if (filePath.isEmpty()) return;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("错误"), tr("无法打开文件"));
        return;
    }

    QTextStream in(&file);
    in.setCodec("UTF-8"); // 设置读取为 UTF-8 编码

    // 清空现有形状
    for (Shape *shape : shapes) {
        delete shape;
    }
    shapes.clear();

    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.startsWith("Line")) {
            Line *lineShape = new Line();
            lineShape->fromString(line); // 调用 fromString 方法
            shapes.push_back(lineShape);
        } else if (line.startsWith("Rect")) {
            Rect *rectShape = new Rect();
            rectShape->fromString(line); // 调用 fromString 方法
            shapes.push_back(rectShape);
        }
    }

    file.close();

    // 更新绘图
    update();

    // 重置绘图模式，允许新增绘制
    drawMode = None;
    QMessageBox::information(this, tr("成功"), tr("文件已加载"));
}

void MainWindow::selectDrawLine()
{
    drawMode = LineMode;
}

void MainWindow::selectDrawRectangle()
{
    drawMode = RectMode;
}
