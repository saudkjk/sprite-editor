// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A7
// Style reviewed by: Sam Bennett
// Style violations:  none

#ifndef CANVASMODEL_H
#define CANVASMODEL_H

#include "enumtypes.h"

#include <QObject>
#include <QPixmap>
#include <QColor>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFileDialog>

#include <vector>
using std::vector;

class CanvasModel : public QObject
{
    Q_OBJECT
private:
    // the current brush color
    QColor color = Qt::black;
    // the dimension of the square brush
    int brushSize = 1;
    ToolType currentTool = TOOL_PEN;

    int frameWidth = 100;
    int frameHeight = 100;

    vector<QPixmap> frames;
    int currentFrameIndex = -1;

    void handlePen(QPoint location);
    void handleBucket(QPoint location);
    void handleDropper(QPoint location);
    void handleBucketRecursive(QImage& image, QPoint location, const QColor& replaceColor);

    void redrawAllPreviews();
    QJsonObject getJSON2();

public:
    explicit CanvasModel(QObject *parent = nullptr);
    vector<QPixmap>& getFrames();

signals:
    void redrawPreview(int frameIndex, QPixmap image);
    void redrawCanvas(QPixmap image);
    void updateFrameCount(int count);
    void highlightSelectedFrame(int frameIndex);
    void framesUpdated(vector<QPixmap> frames);

    // unused so far, meant for telling the view how big the image is
    // might not be necessary
    void updateCanvasSize(int width, int height);

    void changedColor(QColor color);

public slots:
    void changeColor(const QColor& color);
    void changeCurrentFrame(int index);
    void changeTool(ToolType tool);
    void changeBrushSize(int size);

    // note: location is floats between 0 and 1 rather than actual coordinates
    void handleTool(QPointF location);

    void insertFrame();
    void deleteFrame();

    void resizeCanvas(int width, int height);

    void saveToFile(QString filename);
    void loadFromFile(QString filename);
    void saveCurrentFrameAsPNG(QString filename);
    void loadPNGToNewFrame(QString filename);
};

#endif // CANVASMODEL_H
