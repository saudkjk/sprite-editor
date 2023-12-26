// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A7
// Style reviewed by: Andrew Sumsion
// Style violations:  none

#include "framelistview.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

///
/// \brief Shows all frames in sprite and allows user to delete and add frames
///
FrameListView::FrameListView(QWidget *parent)
    : QWidget{parent}
{
    scrollParent = new QWidget();
    QVBoxLayout* scrollLayout = new QVBoxLayout(scrollParent);
    scrollLayout->setSpacing(0);

    scrollArea = new QScrollArea();
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(scrollParent);

    scrollParent->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    plusButton = new QPushButton("+");
    minusButton = new QPushButton("-");
    buttonLayout->addWidget(plusButton);
    buttonLayout->addWidget(minusButton);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(scrollArea);
    layout->addLayout(buttonLayout);

    this->show();
}

///
/// \brief Used to connect this class to a CanvasModel object
/// \param model
///
void FrameListView::connectModel(CanvasModel* model) {
    this->model = model;
    connect(model, &CanvasModel::updateFrameCount, this, &FrameListView::updateFrameCount);

    connect(plusButton, &QPushButton::clicked, model, &CanvasModel::insertFrame);
    connect(minusButton, &QPushButton::clicked, model, &CanvasModel::deleteFrame);
}

///
/// \brief Used to update how many frames are in the frame list
/// \param count
///
void FrameListView::updateFrameCount(int count) {
    for(FrameListItem* item : listItems) {
        delete item;
    }
    listItems.clear();

    for(int i = 0; i < count; i++) {
        FrameListItem* item = new FrameListItem(i, scrollParent);
        scrollParent->layout()->addWidget(item);
        listItems.push_back(item);

        connect(model, &CanvasModel::redrawPreview, item, &FrameListItem::redrawPreview);
        connect(model, &CanvasModel::highlightSelectedFrame, item, &FrameListItem::highlightSelectedFrame);
        connect(item, &FrameListItem::changeCurrentFrame, model, &CanvasModel::changeCurrentFrame);
    }

    scrollParent->update();
    scrollArea->update();

    this->update();
    this->show();
}
