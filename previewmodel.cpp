// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A7
// Style reviewed by: Saoud Aldowaish
// Style violations:  none

#include "previewmodel.h"
#include "qtimer.h"

///
/// \brief Model class for the Preview Window
///
PreviewModel::PreviewModel(QObject *parent)
    : QObject{parent}
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &PreviewModel::refresh);
    timer->start(1000);
}

///
/// \brief Used to change fps and restart timer to adhere to that new fps
///
void PreviewModel::setFps(int newFps) {
    fps = newFps;

    timer->stop();
    timer->start(1000 / fps);
}

///
/// \brief Return int stored in fps
///
int PreviewModel::getFps() {
    return fps;
}

///
/// \brief Updates stored frames with new frames
/// \param newFrames - the new frames to be stored
///
void PreviewModel::updateFrames(vector<QPixmap> newFrames) {
    frames = newFrames;
}

///
/// \brief Timeout method attached to timer that sends next frame to Preview
///
void PreviewModel::refresh() {
    if(frames.size() == 0) return;

    if(currentFrame >= (int)frames.size()) {
        currentFrame = 0;
    }

    emit sendFrame(frames[currentFrame]);

    currentFrame++;
}
