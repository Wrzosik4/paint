#include "mainwindow.h"
#include <QToolBar>
#include <QPushButton>
#include <QPainter>
#include <QPen>
#include <QButtonGroup>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Paint");
    resize(600, 500);

    canvas = QImage(size(), QImage::Format_RGB32);
    canvas.fill(Qt::white);

    QToolBar *toolbar = new QToolBar("Tools", this);
    addToolBar(Qt::LeftToolBarArea, toolbar);

    QPushButton *penBtn = new QPushButton("Pen", this);
    QPushButton *eraserBtn = new QPushButton("Eraser", this);
    QPushButton *clearBtn = new QPushButton("Clear", this);
    QPushButton *circleBtn = new QPushButton("Circle", this);
    QPushButton *rectangleBtn = new QPushButton("Rectangle", this);
    QPushButton *lineBtn = new QPushButton("Line", this);

    penBtn->setCheckable(true);
    eraserBtn->setCheckable(true);
    circleBtn->setCheckable(true);
    rectangleBtn->setCheckable(true);
    lineBtn->setCheckable(true);


    toolbar->addWidget(penBtn);
    toolbar->addWidget(eraserBtn);
    toolbar->addWidget(circleBtn);
    toolbar->addWidget(rectangleBtn);
    toolbar->addWidget(lineBtn);
    toolbar->addWidget(clearBtn);

    connect(penBtn, &QPushButton::clicked, this, [this, penBtn, eraserBtn, circleBtn, rectangleBtn, lineBtn](){
        if (penBtn->isChecked()) {
            eraserBtn->setChecked(false);
            circleBtn->setChecked(false);
            rectangleBtn->setChecked(false);
            lineBtn->setChecked(false);
            currentTool = Tool::Pen;
        } else {
            currentTool = Tool::None;
        }
    });

    connect(eraserBtn, &QPushButton::clicked, this, [this, penBtn, eraserBtn, circleBtn, rectangleBtn, lineBtn](){
        if (eraserBtn->isChecked()) {
            penBtn->setChecked(false);
            circleBtn->setChecked(false);
            rectangleBtn->setChecked(false);
            lineBtn->setChecked(false);
            currentTool = Tool::Eraser;
        } else {
            currentTool = Tool::None;
        }
    });

    connect(circleBtn, &QPushButton::clicked, this, [this, penBtn, eraserBtn, circleBtn, rectangleBtn, lineBtn](){
        if (circleBtn->isChecked()) {
            penBtn->setChecked(false);
            eraserBtn->setChecked(false);
            rectangleBtn->setChecked(false);
            lineBtn->setChecked(false);
            currentTool = Tool::Circle;
        } else {
            currentTool = Tool::None;
        }
    });

    connect(rectangleBtn, &QPushButton::clicked, this, [this, penBtn, eraserBtn, circleBtn, rectangleBtn, lineBtn](){
        if (rectangleBtn->isChecked()) {
            penBtn->setChecked(false);
            eraserBtn->setChecked(false);
            circleBtn->setChecked(false);
            lineBtn->setChecked(false);
            currentTool = Tool::Rectangle;
        } else {
            currentTool = Tool::None;
        }
    });

    connect(lineBtn, &QPushButton::clicked, this, [this, penBtn, eraserBtn, circleBtn, rectangleBtn, lineBtn](){
        if (lineBtn->isChecked()) {
            penBtn->setChecked(false);
            eraserBtn->setChecked(false);
            circleBtn->setChecked(false);
            rectangleBtn->setChecked(false);
            currentTool = Tool::Line;
        } else {
            currentTool = Tool::None;
        }
    });

    connect(clearBtn, &QPushButton::clicked, this, [this](){
        canvas.fill(Qt::white);
        update();
    });
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        currentPoint = event->pos();
        isDrawing = true;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
if ((event->buttons() & Qt::LeftButton) && isDrawing) {
        if (currentTool == Tool::Pen || currentTool == Tool::Eraser) {
            QPainter painter(&canvas);
            if (currentTool == Tool::Pen) {
                painter.setPen(QPen(Qt::black, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            } else {
                painter.setPen(QPen(Qt::white, 16, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            }
            painter.drawLine(lastPoint, event->pos());
            lastPoint = event->pos();
        } else if (currentTool == Tool::Circle || currentTool == Tool::Rectangle || currentTool == Tool::Line){
            currentPoint = event->pos();
        }
        update();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && isDrawing) {
        isDrawing = false;

        if (currentTool == Tool::Circle || currentTool == Tool::Rectangle || currentTool == Tool::Line) {
            QPainter painter(&canvas);
            painter.setPen(QPen(Qt::black, 3, Qt::SolidLine));
            painter.setBrush(Qt::NoBrush);
            
            QRect rect = QRect(lastPoint, event->pos()).normalized();

            if (currentTool == Tool::Circle) {
                painter.drawEllipse(rect);
            } else if (currentTool == Tool::Rectangle) {
                painter.drawRect(rect);
            } else if (currentTool == Tool::Line) {
                painter.drawLine(lastPoint, event->pos());
            }

            update();
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    
    painter.drawImage(0, 0, canvas);

    if (isDrawing && (currentTool == Tool::Circle || currentTool == Tool::Rectangle || currentTool == Tool::Line)) {
        painter.setPen(QPen(Qt::blue, 2, Qt::DashLine)); 
        painter.setBrush(Qt::NoBrush);
        QRect rect = QRect(lastPoint, currentPoint).normalized();

        if (currentTool == Tool::Circle){
            painter.drawEllipse(rect);
        } else if (currentTool == Tool::Rectangle){
            painter.drawRect(rect);
        } else if (currentTool == Tool::Line) {
            painter.drawLine(lastPoint, currentPoint);
        }
    }
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    if (width() > canvas.width() || height() > canvas.height()) {
        QImage newCanvas(size(), QImage::Format_RGB32);
        newCanvas.fill(Qt::white);

        QPainter painter(&newCanvas);
        painter.drawImage(0, 0, canvas);
        canvas = newCanvas;
    }
    QMainWindow::resizeEvent(event);
}