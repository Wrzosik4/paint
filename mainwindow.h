#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPoint>
#include <QPushButton>
#include <QMouseEvent>
#include <QPaintEvent>

enum Tool {
    None,
    Pen,
    Eraser,
    Circle,
    Rectangle,
    Line
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Tool currentTool = Tool::None;
    QPoint lastPoint;
    QImage canvas;
    QPoint currentPoint;
    bool isDrawing = false;
};

#endif