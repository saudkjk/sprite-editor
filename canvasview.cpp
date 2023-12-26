// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A7
// Style reviewed by: Saoud Aldowaish
// Style violations:  none

#include "canvasview.h"

#include <QBoxLayout>
#include <QMouseEvent>

#include <cmath>

///
/// \brief Controller for Canvas Window
///
CanvasView::CanvasView(QWidget *parent)
    : QWidget{parent}
{
    setMouseTracking(true);
}

///
/// \brief Connects this class to a model object so the model class can handle logic
/// \param model
///
void CanvasView::connectModel(CanvasModel* model) {
    connect(this, &CanvasView::handleTool, model, &CanvasModel::handleTool);
    connect(model, &CanvasModel::redrawCanvas, this, &CanvasView::redrawCanvas);

    // necessary to show canvas before any drawing
    currentImage = QPixmap(1, 1);
    currentImage.fill();
    update();
    repaint();
}

///
/// \brief Sends a signal that the user pressed the mouse
/// \param event - user pressed mouse
///
void CanvasView::mousePressEvent(QMouseEvent* event) {
    handleAllMouseEvents(event);
    emit handleTool(mousePosition);
}

///
/// \brief Sends a signal that the user moved the mouse
/// \param event - user moved mouse
///
void CanvasView::mouseMoveEvent(QMouseEvent* event) {
    handleAllMouseEvents(event);

    if(event->buttons() != Qt::NoButton) {
        emit handleTool(mousePosition);
    }
}

///
/// \brief Used to emit the coordinates where the users cursor is
/// \param event - mouse move or click
///
void CanvasView::handleAllMouseEvents(QMouseEvent* event) {
    // calcluate UV coordinates of click based on widget size

    QPointF clickPointPx = event->position();
    mousePosition.setX(clickPointPx.x() / this->width());
    mousePosition.setY(clickPointPx.y() / this->height());

    QPoint positionOnImage(mousePosition.x() * currentImage.width(), mousePosition.y() * currentImage.height());
    emit cursorPosition(positionOnImage);
    update();
    repaint();
}

///
/// \brief Handles paint event on canvas
/// \param event
///
void CanvasView::paintEvent(QPaintEvent* event) {
    QRect target(0, 0, this->width(), this->height());
    QRect source(0, 0, currentImage.width(), currentImage.height());

    QPainter painter(this);
    painter.drawPixmap(target, currentImage, source);

    int highlightWidth = this->width() / currentImage.width();
    int highlightHeight = this->height() / currentImage.height();

    int highlightX = std::round((int)(currentImage.width() * mousePosition.x()) * (qreal) this->width() / (qreal) currentImage.width());
    int highlightY = std::round((int)(currentImage.height() * mousePosition.y()) * (qreal) this->height() / (qreal) currentImage.height());

    painter.fillRect(highlightX, highlightY, highlightWidth, highlightHeight, QColor(128, 128, 128, 128));
}

///
/// \brief Redraw the canvas with image
/// \param image
///
void CanvasView::redrawCanvas(QPixmap image) {
    currentImage = image;
    update();
    repaint();
}
