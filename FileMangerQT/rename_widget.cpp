#include "rename_widget.h"
#include <iostream>
#include <QBoxLayout>
#include <QMessageBox>

rename_widget::rename_widget(std::string buttonValueF , std::string lineValueF ,std::string errorValueF):buttonValue(buttonValueF), lineValue(errorValueF),errorValue(lineValueF)
{

    file_name_edit = new QLineEdit(this);
    file_name_edit->setPlaceholderText(QString::fromStdString(lineValue));
    okButton = new QPushButton(QString::fromStdString(buttonValue),this);
    warningLabel = new QLabel("",this);

    connect(okButton, &QPushButton::clicked, this, &rename_widget::onOkClicked);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(file_name_edit);
    layout->addWidget(okButton);
    layout->addWidget(warningLabel);

}

rename_widget::~rename_widget()
{
    std::cout <<"Destructor is called\n";
    delete file_name_edit ;
    delete okButton  ;
    delete warningLabel ;
    std::cout.flush();
}



void rename_widget::onOkClicked()
{
    QString name = file_name_edit->text();
    if (name.isEmpty())
    {
        QMessageBox::warning( this,"Error", QString::fromStdString(errorValue));
    } else {

        QString new_file_name  = file_name_edit->text();
        emit new_file_name_button_clicked(new_file_name);
    }
}
