// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A7
// Style reviewed by: Andrew Sumsion
// Style violations:  none

#ifndef FRAMELISTVIEW_H
#define FRAMELISTVIEW_H

#include "canvasmodel.h"
#include "framelistitem.h"

#include <QWidget>
#include <QScrollArea>
#include <QPushButton>

#include <vector>
using std::vector;

class FrameListView : public QWidget
{
    Q_OBJECT
private:
    CanvasModel* model;
    QScrollArea* scrollArea;
    QWidget* scrollParent;
    vector<FrameListItem*> listItems;

    QPushButton* plusButton;
    QPushButton* minusButton;

public:
    explicit FrameListView(QWidget *parent = nullptr);

    void connectModel(CanvasModel* model);

signals:


public slots:
    void updateFrameCount(int count);
};

#endif // FRAMELISTVIEW_H
