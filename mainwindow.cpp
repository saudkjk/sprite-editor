// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A7
// Style reviewed by: Andrew Sumsion
// Style violations:  none

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPalette>
#include <iostream>

///
/// \brief Used to control the Main Window
///
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    canvasModel = new CanvasModel();
    ui->canvasView->connectModel(canvasModel);
    ui->frameListView->connectModel(canvasModel);
    ui->toolbarView->connectModel(canvasModel);
    canvasModel->insertFrame();

    preview = new Preview();
    preview->connectCanvasModel(canvasModel);

    colorDialog = new QColorDialog(Qt::black, this);
    connect(colorDialog, &QColorDialog::colorSelected, this, &MainWindow::colorChanged);
    connect(colorDialog, &QColorDialog::colorSelected, canvasModel, &CanvasModel::changeColor);

    ui->colorPickerButton->setStyleSheet("background-color: black");
    connect(ui->colorPickerButton, &QPushButton::clicked, this, &MainWindow::colorButtonClicked);

    ui->brushSizeSpinBox->setMinimum(1);
    connect(ui->brushSizeSpinBox, &QSpinBox::valueChanged, canvasModel, &CanvasModel::changeBrushSize);

    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::save);
    connect(this, &MainWindow::saveToFileSig, canvasModel, &CanvasModel::saveToFile);

    connect(ui->loadButton, &QPushButton::clicked, this, &MainWindow::load);
    connect(this, &MainWindow::loadFromFileSig, canvasModel, &CanvasModel::loadFromFile);

    connect(ui->exportPNGButton, &QPushButton::clicked, this, &MainWindow::exportPNG);
    connect(this, &MainWindow::exportPNGSig, canvasModel, &CanvasModel::saveCurrentFrameAsPNG);

    connect(ui->importPNGButton, &QPushButton::clicked, this, &MainWindow::importPNG);
    connect(this, &MainWindow::importPNGSig, canvasModel, &CanvasModel::loadPNGToNewFrame);

    resize = new ResizePopup();
    connect(resize, &ResizePopup::resize, canvasModel, &CanvasModel::resizeCanvas);

    connect(canvasModel, &CanvasModel::changedColor, this, &MainWindow::colorChanged);
    connect(ui->canvasView, &CanvasView::cursorPosition, this, &MainWindow::cursorPosition);
}

///
/// \brief Destructor
///
MainWindow::~MainWindow()
{
    delete ui;
    delete canvasModel;
    delete colorDialog;
}

///
/// \brief change selected color
/// \param color - new color
///
void MainWindow::colorChanged(QColor color)
{
    QString stylesheet = QString("background-color: %1").arg(color.name());
    ui->colorPickerButton->setStyleSheet(stylesheet);
}

///
/// \brief Opens color dialog when color button is clicked
/// \param checked
///
void MainWindow::colorButtonClicked(bool checked)
{
    colorDialog->open();
}

///
/// \brief Displays cursor position as X: Y:
/// \param position
///
void MainWindow::cursorPosition(QPoint position) {
    ui->cursorPositionLabel->setText(QString("X: %1 Y: %2").arg(position.x()).arg(position.y()));
}

///
/// \brief Saves current sprite in JSON format
///
void MainWindow::save()
{
    QString filename = QFileDialog::getSaveFileName(0, "Save ssp file", QDir::currentPath(), "SSP file (*.ssp)");
    emit saveToFileSig(filename);
}

///
/// \brief Loads a saved sprite
///
void MainWindow::load()
{
    QString filename = QFileDialog::getOpenFileName(this, "Load file", QDir::currentPath(), "sprite sheet project file (*.ssp)");
    emit loadFromFileSig(filename);
}

///
/// \brief Export current frame as png
///
void MainWindow::exportPNG ()
{
    QString filename = QFileDialog::getSaveFileName(0, "Import as png", QDir::currentPath(), "PNG file (*.png)");
    emit exportPNGSig(filename);
}

///
/// \brief import png as QPixmap frame
///
void MainWindow::importPNG()
{
    QString filename = QFileDialog::getOpenFileName(this, "Export as png", QDir::currentPath(), "PNG file (*.png)");
    emit importPNGSig(filename);
}

///
/// \brief Show preview window when Preview button is clicked
///
void MainWindow::on_showPreviewButton_clicked()
{
    preview->show();
}

///
/// \brief Show resize popup when resize button is clicked
///
void MainWindow::on_resizeButton_clicked()
{
    resize->show();
}

