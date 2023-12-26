// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A7
// Style reviewed by: Dillon Otto
// Style violations:  none

#include "preview.h"
#include "ui_preview.h"
#include <QTimer>
#include <QDebug>

///
/// \brief View class for the Preview window
///
Preview::Preview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Preview)
{
    ui->setupUi(this);
    model = new PreviewModel();
    connect(ui->fpsSlider, &QSlider::valueChanged, model, &PreviewModel::setFps);
    connect(model, &PreviewModel::sendFrame, this, &Preview::displayFrame);
}

///
/// \brief Used to connect CanvasModel and PreviewModel
/// \param canvasModel
///
void Preview::connectCanvasModel(CanvasModel* canvasModel) {
    connect(canvasModel, &CanvasModel::framesUpdated, model, &PreviewModel::updateFrames);
    model->updateFrames(canvasModel->getFrames());
}

///
/// \brief Destructor for Preview
///
Preview::~Preview()
{
    delete ui;
}

///
/// \brief Update fps value input from user
/// \param fps
///
void Preview::on_fpsSlider_valueChanged(int fps)
{
    emit fpsChanged(fps);
    ui->fps->setText(QStringLiteral(" %1 fps").arg(fps));
}

///
/// \brief Used to show frame emitted by previewModel
/// \param frame
///
void Preview::displayFrame(QPixmap frame) {
    if(ui->toggleSize->isChecked()) {
        ui->previewLabel->setPixmap(frame);
    }

    else {
        ui->previewLabel->setPixmap(frame.scaled(ui->previewLabel->frameSize(), Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}
