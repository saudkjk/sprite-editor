// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A7
// Style reviewed by: Dillon Otto
// Style violations:  none

#include "framelistitem.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

///
/// \brief Controller for a frame in the frame list at an index
/// \param index
///
FrameListItem::FrameListItem(int index, QWidget *parent)
    : QWidget{parent},
      index(index)
{
    QWidget* wrapper = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(wrapper);

    imageLabel = new QLabel();
    nameLabel = new QLabel(QString("Frame %1").arg(index + 1));

    layout->addWidget(imageLabel);
    layout->addWidget(nameLabel);

    QVBoxLayout* outerLayout = new QVBoxLayout(this);
    outerLayout->addWidget(wrapper);

    this->show();
}

///
/// \brief Redraws preview of a frame in the frame list
/// \param frameIndex
/// \param image
///
void FrameListItem::redrawPreview(int frameIndex, QPixmap image) {
    if(index != frameIndex) {
        return;
    }

    int w = 50;
    int h = 50;

    imageLabel->setPixmap(image.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

///
/// \brief Highlists frame in frame list at frameIndex
/// \param frameIndex
///
void FrameListItem::highlightSelectedFrame(int frameIndex) {
    if(frameIndex == index) {
        this->setStyleSheet("background-color: #b9b9b9");
    }
    else {
        this->setStyleSheet("");
    }
}

///
/// \brief Changes current frame
/// \param event - mouse pressed
///
void FrameListItem::mousePressEvent(QMouseEvent* event) {
    emit changeCurrentFrame(index);
}
