// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A7
// Style reviewed by: Andrew Sumsion
// Style violations:  none

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "canvasmodel.h"
#include "preview.h"
#include "resizepopup.h"

#include <QMainWindow>
#include <QColorDialog>
//#include <QFileDialog>
#include <QJsonDocument>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
public slots:
    void colorChanged(QColor color);
    void colorButtonClicked(bool checked);
    void cursorPosition(QPoint position);
    void save();
    void load();
    void importPNG();
    void exportPNG();

signals:
    void saveToFileSig(QString filename);
    void loadFromFileSig(QString filename);
    void exportPNGSig(QString filename);
    void importPNGSig(QString filename);
    void connectPreview(CanvasModel* model);

private slots:
    void on_showPreviewButton_clicked();
    void on_resizeButton_clicked();

private:
    Ui::MainWindow *ui;
    CanvasModel* canvasModel;
    QColorDialog* colorDialog;
    Preview* preview;
    ResizePopup* resize;
};
#endif // MAINWINDOW_H
