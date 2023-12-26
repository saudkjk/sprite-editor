// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A7
// Style reviewed by: Sam Bennett
// Style violations:  none

#include "resizepopup.h"
#include "ui_resizepopup.h"

///
/// \brief Class used to implement resize window
///
ResizePopup::ResizePopup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResizePopup)
{
    ui->setupUi(this);
}

///
/// \brief Destructor
///
ResizePopup::~ResizePopup()
{
    delete ui;
}

///
/// \brief When user presses accept button this emits the input width and height
///
void ResizePopup::on_buttonBox_accepted()
{
    emit resize(ui->widthVal->value(), ui->heightVal->value());
}
