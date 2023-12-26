// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A7
// Style reviewed by: Dillon Otto
// Style violations:  none

#ifndef FRAMELISTITEM_H
#define FRAMELISTITEM_H

#include <QLabel>
#include <QWidget>

class FrameListItem : public QWidget
{
    Q_OBJECT

private:
    int index;
    QLabel* imageLabel;
    QLabel* nameLabel;

    void mousePressEvent(QMouseEvent* event);

public:
    explicit FrameListItem(int index, QWidget *parent = nullptr);

signals:
    void changeCurrentFrame(int index);

public slots:
    void redrawPreview(int frameIndex, QPixmap image);
    void highlightSelectedFrame(int frameIndex);
};

#endif // FRAMELISTITEM_H
