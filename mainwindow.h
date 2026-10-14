#pragma once

#include <QMainWindow>
#include <QImage>
#include <QPoint>
#include <QPushButton>
#include <QMouseEvent>
#include <QPaintEvent>

enum Tool {
    None,
    Pen,
    Eraser
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

private:
    Tool currentTool = Tool::None;
    QPoint lastPoint;
    QImage canvas;
};