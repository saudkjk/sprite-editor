// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A7
// Style reviewed by: Sam Bennett
// Style violations:  none

#include "canvasmodel.h"

#include <QPainter>
#include <QDebug>

///
/// \brief Model class to handle logic of the canvas
///
CanvasModel::CanvasModel(QObject *parent)
    : QObject{parent}
{

}

///
/// \brief Changes color of pixels to be added
///
void CanvasModel::changeColor(const QColor& color) {
    this->color = color;
}

///
/// \brief Changes the frame to display on canvas
/// \param index of the frame to change to
///
void CanvasModel::changeCurrentFrame(int index) {
    this->currentFrameIndex = index;
    emit redrawCanvas(frames[currentFrameIndex]);
    emit highlightSelectedFrame(currentFrameIndex);
}

///
/// \brief Changes selected tool
/// \param tool to change to
///
void CanvasModel::changeTool(ToolType tool) {
    this->currentTool = tool;
}

///
/// \brief Changes brush size
/// \param size of new brush
///
void CanvasModel::changeBrushSize(int size) {
    this->brushSize = size;
}

///
/// \brief Used to draw onto canvas at a point with any selected tool
/// \param uv - point to draw to
///
void CanvasModel::handleTool(QPointF uv) {
    QPoint location;
    location.setX((int) (uv.x() * frameWidth));
    location.setY((int) (uv.y() * frameHeight));

    switch(currentTool) {
    case TOOL_PEN:
        handlePen(location);
        break;
    case TOOL_BUCKET:
        handleBucket(location);
        break;
    case TOOL_DROPPER:
        handleDropper(location);
        break;
    default:
        // ???
        break;
    }

    emit redrawCanvas(frames[currentFrameIndex]);
    emit redrawPreview(currentFrameIndex, frames[currentFrameIndex]);
    emit framesUpdated(frames);
}

///
/// \brief Adds a new blank frame into frames vector
///
void CanvasModel::insertFrame() {
    QPixmap newFrame(frameWidth, frameHeight);
    newFrame.fill();

    if(currentFrameIndex + 1 >= (int)frames.size()) {
        frames.push_back(newFrame);
    }
    else {
        frames.insert(frames.begin() + currentFrameIndex + 1, newFrame);
    }

    emit updateFrameCount(frames.size());
    redrawAllPreviews();

    changeCurrentFrame(currentFrameIndex + 1);
}

///
/// \brief Deletes frame at currentFrameIndex in frames vector
///
void CanvasModel::deleteFrame() {
    if(frames.size() == 1) {
        // clear the first frame if only one is left
        frames[0].fill();
    }
    else {
        frames.erase(frames.begin() + currentFrameIndex);
        if(currentFrameIndex + 1 >= (int)frames.size()) {
            currentFrameIndex = frames.size() - 1;
        }
    }

    emit updateFrameCount(frames.size());
    redrawAllPreviews();

    changeCurrentFrame(currentFrameIndex);
}

///
/// \brief Resizes canvas with new dimensions
/// \param width - new width of canvas
/// \param height - new height of canvas
///
void CanvasModel::resizeCanvas(int width, int height) {
    // create frames of new size and draw old frames on them without scaling
    for(size_t i = 0; i < frames.size(); i++) {
        QPixmap oldImage = frames[i];
        QPixmap newImage(width, height);
        newImage.fill();

        QRect oldImageSize = QRect(0, 0, frameWidth, frameHeight);

        QPainter painter(&newImage);
        painter.drawPixmap(oldImageSize, oldImage, oldImageSize);

        frames[i] = newImage;
    }

    frameWidth = width;
    frameHeight = height;

    emit redrawCanvas(frames[currentFrameIndex]);
    redrawAllPreviews();
}

///
/// \brief Draws on canvas at location with stored brushsize and color
/// \param location
///
void CanvasModel::handlePen(QPoint location) {
    QPainter painter(&frames[currentFrameIndex]);
    QPen pen;
    pen.setColor(color);
    pen.setWidth(brushSize);
    painter.setPen(pen);

    painter.drawPoint(location);
}

///
/// \brief Replaces the selected color with the color of the pixel at the provided location
/// \param location
///
void CanvasModel::handleDropper(QPoint location) {
    QImage image = frames[currentFrameIndex].toImage();
    QColor replaceColor = image.pixelColor(location);

    changeColor(replaceColor);
    emit changedColor(replaceColor);
}

///
/// \brief Replaces every pixel with the same color of location within a boundary
/// \param location
///
void CanvasModel::handleBucket(QPoint location) {
    // we convert the pixmap to an image for this operation
    // because we need to read and write pixel-by-pixel
    QImage image = frames[currentFrameIndex].toImage();
    QColor replaceColor = image.pixelColor(location);


    if(color == replaceColor) {
        // if we start trying to replace a blob of our current color
        // with its own color, it will double back on itself and keep
        // recursing forever. instead, just cancel the operation if
        // this is the case. this is functionally exactly the same,
        // and it allows us to use the color of the pixel to determine
        // whether it has been visited.
        return;
    }

    vector<QPoint> dfsStack;
    dfsStack.push_back(location);

    // depth first search, marking pixels visited by setting their color
    while(!dfsStack.empty()) {
        QPoint point = dfsStack.back();
        dfsStack.pop_back();

        if (point.x() < 0              || point.y() < 0 ||
            point.x() >= image.width() || point.y() >= image.height()) {
            // out of bounds of the image
            continue;
        }

        QColor oldColor = image.pixelColor(point);
        if(oldColor != replaceColor) {
            // not the color that needs to be replaced, edge reached
            continue;
        }

        image.setPixelColor(point, color);

        dfsStack.push_back(QPoint(point.x() + 1, point.y()    ));
        dfsStack.push_back(QPoint(point.x() - 1, point.y()    ));
        dfsStack.push_back(QPoint(point.x(),     point.y() + 1));
        dfsStack.push_back(QPoint(point.x(),     point.y() - 1));
    }

    // convert back to pixmap and update
    frames[currentFrameIndex] = QPixmap::fromImage(image);
}

///
/// \brief Used to signal when to update frames and previews
///
void CanvasModel::redrawAllPreviews() {
    for(size_t i = 0; i < frames.size(); i++) {
        emit redrawPreview(i, frames[i]);
    }

    emit framesUpdated(frames);
}

///
/// \brief Returns frames vector
///
vector<QPixmap>& CanvasModel::getFrames() {
    return frames;
}

///
/// \brief saves sprite as JSON format into file
/// \param filename
///
void CanvasModel::saveToFile(QString filename) {
      QFile f(filename);
      f.open(QIODevice::WriteOnly);
      QTextStream str(&f);

      int height = this->frameHeight;
      int width = this->frameWidth;
      int numberOfFrames = this->frames.size();
      str << "{" << Qt::endl;
      str << "    \"height\": " << height << "," << Qt::endl;
      str << "    \"width\": " << width << "," << Qt::endl;
      str << "    \"numberOfFrames\": " << numberOfFrames << "," << Qt::endl;
      str << "    \"frames\": {" << Qt::endl;
      for (int frameIndex = 0; frameIndex < numberOfFrames; frameIndex++)
      {
          std::string currentFrame = "frame" + std::to_string(frameIndex);
          QImage currentFrameImage = frames[frameIndex].toImage();
          str << "            \"" << QString::fromStdString(currentFrame) << "\"" << ":  [";
          for (int y = 0; y < height; y++)
          {
              str << Qt::endl << "                     [";
              for (int x = 0; x < width; x++)
              {
                  QColor c = QColor::fromRgba(currentFrameImage.pixel(x, y));
                  str << "[" << c.red() << ",";
                  str << c.green() << ",";
                  str << c.blue() << ",";
                  str << c.alpha() << "]";
                  if (x != width - 1)
                      str << ", ";
              }
              str << "]";
              if(y != height - 1)
                  str << ", ";
          }
          str << "]";
          if(frameIndex != numberOfFrames - 1)
              str << ", ";
          str << Qt::endl;
      }
      str << "       }" << Qt::endl << "}" << Qt::endl;
}

///
/// \brief Loads JSON format file into sprite
/// \param filename
///
void CanvasModel::loadFromFile(QString filename) {

     QFile f(filename);
     if(!f.open(QIODevice::ReadOnly))
         return;

     // read file content
     QTextStream str(&f);
     QString JSONString = str.readAll();

     // get JSON object from string
     QByteArray br = JSONString.toUtf8();
     QJsonDocument doc = QJsonDocument::fromJson(br);
     QJsonObject JSON = doc.object();

    // get the default format for conversion between image and pixmap
    QImage::Format bestFormat = QPixmap(1, 1).toImage().format();

    // clean up old frames
    // maybe we should add a warning here that existing changes will be overwritten?
    frames.clear();
    this->currentFrameIndex = 0;

    // change frame width and height
    this->frameWidth = JSON["width"].toInt();
    this->frameHeight = JSON["height"].toInt();
    int numberOfFrames = JSON["numberOfFrames"].toInt();
    QJsonObject frames = JSON["frames"].toObject();
    for (int frameIndex = 0; frameIndex < numberOfFrames; frameIndex++) {
        QImage image(frameWidth, frameHeight, bestFormat);

        std::string  currentFrame = "frame"  + std::to_string(frameIndex);
        QJsonArray frameArray = frames[QString::fromStdString(currentFrame)].toArray();
        for (int y = 0; y < frameHeight; y++) {
            for (int x = 0; x < frameWidth; x++) {
                QColor currColor;
                currColor.setRed(frameArray[y][x][0].toInt());   // gets red color from pixel at x,y
                currColor.setGreen(frameArray[y][x][1].toInt()); // gets green color from pixel at x,y
                currColor.setBlue(frameArray[y][x][2].toInt());  // gets blue color from pixel at x,y
                currColor.setAlpha(frameArray[y][x][3].toInt()); // gets alpha from pixel at x,y
                image.setPixelColor(x, y, currColor);
            }
        }
        this->frames.push_back(QPixmap::fromImage(image));
    }
    emit redrawCanvas(this->frames[currentFrameIndex]);
    emit updateFrameCount(frames.size());
    redrawAllPreviews();
}

///
/// \brief Saves current frame into file as PNG
/// \param filename
///
void CanvasModel::saveCurrentFrameAsPNG(QString filename) {
    QFile f(filename);
    f.open(QIODevice::WriteOnly);
    QPixmap image = this->frames[currentFrameIndex];
    QImage currentFrameImage = image.scaled(this->frameHeight, this->frameWidth, Qt::KeepAspectRatio, Qt::FastTransformation).toImage();
    currentFrameImage.save(&f, "PNG");
}

///
/// \brief Loads a PNG image from file as a new frame
/// \param filename
///
void CanvasModel::loadPNGToNewFrame(QString filename) {
    QFile f(filename);
    if(!f.open(QIODevice::ReadOnly))
        return;

    QImage image;
    image.load(&f, "PNG"); //load the content of the file to the image

    QImage scaledImage = image.scaled(frameWidth, frameHeight);
    this->frames.push_back(QPixmap::fromImage(scaledImage));

    emit redrawCanvas(this->frames[currentFrameIndex]);
    emit updateFrameCount(frames.size());
    redrawAllPreviews();
}
