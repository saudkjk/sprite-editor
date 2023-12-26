// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A7
// Style reviewed by: Sam Bennett
// Style violations:  none

#ifndef RESIZEPOPUP_H
#define RESIZEPOPUP_H

#include <QDialog>

namespace Ui {
class ResizePopup;
}

class ResizePopup : public QDialog
{
    Q_OBJECT

public:
    explicit ResizePopup(QWidget *parent = nullptr);
    ~ResizePopup();

signals:
    void resize(int, int);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ResizePopup *ui;
};

#endif // RESIZEPOPUP_H
