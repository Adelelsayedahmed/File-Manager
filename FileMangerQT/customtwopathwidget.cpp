
#include "customtwopathwidget.h"

CustomTwoPathWidget::CustomTwoPathWidget(int num,QWidget *parent)
    : QWidget{parent}
{

    // Create a button to open the file dialog

    QPushButton *dst_button = new QPushButton("Browse Destination Directory ");
    action_button = new QPushButton("ActionName");
    if (!num)
    action_button->setText("compress");
    else
    action_button->setText("Decompress");
    QLineEdit *fileNameLineEdit = new QLineEdit();
    fileNameLineEdit->setPlaceholderText("Entre File Name");
    connect(dst_button, &QPushButton::clicked, this, &CustomTwoPathWidget::browseDirectory);
    connect(action_button, &QPushButton::clicked, this, &CustomTwoPathWidget::action_method);
    // Create a layout to hold the button
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(dst_button);
    layout->addWidget(fileNameLineEdit);
    layout->addWidget(action_button);
    setLayout(layout);

}

void CustomTwoPathWidget::  browseDirectory()
{
    // Open a file dialog to allow the user to select a directory
    QString directory = QFileDialog::getExistingDirectory(this, tr("Open Directory"), QDir::homePath());

    // If a directory was selected, do something with it
    if (!directory.isEmpty()) {
        // Do something with the selected directory
        // ...
    }
}

void CustomTwoPathWidget::  browseFile()
{
    // Open a file dialog to allow the user to select a directory
   QString fileName = QFileDialog::getOpenFileName(nullptr, "Open File");

    // If a directory was selected, do something with it
    if (!fileName.isEmpty()) {
        // Do something with the selected directory
        // ...
    }

}

void CustomTwoPathWidget::action_method()
{

}


