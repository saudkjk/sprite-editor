// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A7
// Style reviewed by: Saoud Aldowaish
// Style violations:  none

#ifndef CANVASVIEW_H
#define CANVASVIEW_H

#include "canvasmodel.h"

#include <QWidget>
#include <QGraphicsView>

class CanvasView : public QWidget
{
    Q_OBJECT
private:
    // stored here to be drawn in the paint event
    QPixmap currentImage;
    QPointF mousePosition;

    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);

    void handleAllMouseEvents(QMouseEvent* event);

public:
    explicit CanvasView(QWidget *parent = nullptr);
    void connectModel(CanvasModel* model);

signals:
    void handleTool(QPointF location);
    void cursorPosition(QPoint position);

public slots:
    void redrawCanvas(QPixmap image);

};

#endif // CANVASVIEW_H
