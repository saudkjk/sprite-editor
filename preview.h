// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A7
// Style reviewed by: Dillon Otto
// Style violations:  none

#ifndef PREVIEW_H
#define PREVIEW_H

#include <QWidget>
#include "canvasmodel.h"
#include "previewmodel.h"

namespace Ui {
class Preview;
}

class Preview : public QWidget
{
    Q_OBJECT

public:
    explicit Preview(QWidget *parent = nullptr);
    void connectCanvasModel(CanvasModel*);
    ~Preview();

signals:
    void fpsChanged(int);

private slots:
    void on_fpsSlider_valueChanged(int value);
    void displayFrame(QPixmap);

private:
    Ui::Preview *ui;
    PreviewModel* model;
};

#endif // PREVIEW_H
