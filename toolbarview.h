// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A7
// Style reviewed by: Dillon Otto
// Style violations:  none

#ifndef TOOLBARVIEW_H
#define TOOLBARVIEW_H

#include "canvasmodel.h"

#include <QWidget>
#include <QGraphicsView>
#include <QtWidgets>

class ToolbarView : public QWidget
{

Q_OBJECT

private:
    QVBoxLayout *mainLayout;
    QLabel *firstLabel;
    vector<QPushButton*> toolButtons;
    QPushButton *pencilButton;
    QPushButton *bucketButton;
    QPushButton *dropperButton;

    void setTool(int tool);

public:
    explicit ToolbarView(QWidget *parent = nullptr);
    ~ToolbarView();
    void connectModel(CanvasModel* model);

signals:
    void changeTool(ToolType tool);

private slots:
    void pencilPressed();
    void bucketPressed();
    void dropperPressed();

};

#endif // TOOLBARVIEW_H
