// Group: Null
// Names: Andrew Sumsion, Dillon Otto, Sam Bennett, Saoud Aldowaish
// Course: CS3505
// Assignment: A7
// Style reviewed by: Dillon Otto
// Style violations:  none

#include "toolbarview.h"

#include <QBoxLayout>
#include <QMouseEvent>

///
/// \brief Constructor -- creates UI and sets default toolbar state
/// \param parent
///
ToolbarView::ToolbarView(QWidget *parent)
    : QWidget{parent}
{
        // layout UI
        mainLayout = new QVBoxLayout(this);

        pencilButton = new QPushButton("Pen");
        bucketButton = new QPushButton("Bucket");
        dropperButton = new QPushButton("Dropper");

        toolButtons.push_back(pencilButton);
        toolButtons.push_back(bucketButton);
        toolButtons.push_back(dropperButton);

        QSizePolicy policy(QSizePolicy::Minimum, QSizePolicy::Minimum);

        // configure and add each button
        for(auto toolButton : toolButtons)
        {
            toolButton->setFlat(true);
            toolButton->setSizePolicy(policy);
            toolButton->setStyleSheet( QString("QPushButton {background-color: grey; border: none;}"
                                               "QPushButton:pressed {background-color: DarkGrey;}"
                                               "QPushButton[blinking=\"true\"] {background-color: rgb(150,150,255);}"));
            mainLayout->addWidget(toolButton);
        }



        // set pencil as active
        setTool(0);

        // connect buttons
        connect(pencilButton, SIGNAL(clicked()), this, SLOT(pencilPressed()));
        connect(bucketButton, SIGNAL(clicked()), this, SLOT(bucketPressed()));
        connect(dropperButton, SIGNAL(clicked()), this, SLOT(dropperPressed()));

}

///
/// \brief Destructor cleans up UI components
///
ToolbarView::~ToolbarView()
{
    delete mainLayout;
    delete pencilButton;
    delete bucketButton;
    delete dropperButton;
}
///
/// \brief Connects the toolbar view to a canvas model
/// \param model
///
void ToolbarView::connectModel(CanvasModel* model) {
    connect(this, &ToolbarView::changeTool, model, &CanvasModel::changeTool);
}

///
/// \brief Pencil tool button callback
///
void ToolbarView::pencilPressed()
{
     setTool(0);
     emit changeTool(ToolType::TOOL_PEN);
}

///
/// \brief Bucket tool button callback
///
void ToolbarView::bucketPressed()
{
     setTool(1);
     emit changeTool(ToolType::TOOL_BUCKET);
}

///
/// \brief Dropper tool button callback
///
void ToolbarView::dropperPressed()
{
     setTool(2);
     emit changeTool(ToolType::TOOL_DROPPER);
}

///
/// \brief Sets the UI so the specified tool is selected and the others are unselected
/// \param tool
///
void ToolbarView::setTool(int tool)
{
    int i = 0;
    for(auto toolButton : toolButtons)
    {
        if(i == tool)
        {
            toolButton->setEnabled(false);
        }
        else
        {
            toolButton->setEnabled(true);
        }
        i++;
    }
}
