#include "mainwindow.h"
#include <QToolBar>
#include <QPushButton>
#include <QPainter>
#include <QPen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Paint");
    resize(400, 300);

    canvas = QImage(size(), QImage::Format_RGB32);
    canvas.fill(Qt::white);

    QToolBar *toolbar = addToolBar("Tools");

    QPushButton *penBtn = new QPushButton("Pen", this);
    QPushButton *eraserBtn = new QPushButton("Eraser", this);
    QPushButton *clearBtn = new QPushButton("Clear", this);

    toolbar->addWidget(penBtn);
    toolbar->addWidget(eraserBtn);
    toolbar->addWidget(clearBtn);

    connect(penBtn, &QPushButton::clicked, this, [this](){
        currentTool = Tool::Pen;
    });

    connect(eraserBtn, &QPushButton::clicked, this, [this](){
        currentTool = Tool::Eraser;
    });

    connect(clearBtn, &QPushButton::clicked, this, [this](){
        canvas.fill(Qt::white);
        update();
    });
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if ((event->buttons() & Qt::LeftButton) && currentTool != Tool::None) {
        QPainter painter(&canvas);

        if (currentTool == Tool::Pen) {
            painter.setPen(QPen(Qt::black, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        } else if (currentTool == Tool::Eraser) {
            painter.setPen(QPen(Qt::white, 16, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        }

        painter.drawLine(lastPoint, event->pos());
        lastPoint = event->pos();

        update();
    }
}

void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawImage(0, 0, canvas);
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