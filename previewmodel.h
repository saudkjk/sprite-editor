// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A7
// Style reviewed by: Saoud Aldowaish
// Style violations:  none

#ifndef PREVIEWMODEL_H
#define PREVIEWMODEL_H

#include <QObject>
#include "canvasmodel.h"

class PreviewModel : public QObject
{
    Q_OBJECT
public:
    explicit PreviewModel(QObject *parent = nullptr);
    void connectModel(CanvasModel*);
    int getFps();

signals:
    void sendFrame(QPixmap);

public slots:
    void updateFrames(vector<QPixmap>);
    void refresh();
    void setFps(int);

private:
    int fps = 1;
    vector<QPixmap> frames;
    QTimer* timer;
    int currentFrame = 0;
};

#endif // PREVIEWMODEL_H
