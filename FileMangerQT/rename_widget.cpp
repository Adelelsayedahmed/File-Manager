#include "rename_widget.h"

#include <QBoxLayout>
#include <QMessageBox>

rename_widget::rename_widget()
{
    file_name_edit = new QLineEdit(this);
    file_name_edit->setPlaceholderText("Enter file name");
    okButton = new QPushButton("OK",this);
    warningLabel = new QLabel("",this);

    connect(okButton, &QPushButton::clicked, this, &rename_widget::onOkClicked);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(file_name_edit);
    layout->addWidget(okButton);
    layout->addWidget(warningLabel);

}



void rename_widget::onOkClicked()
{
    QString name = file_name_edit->text();
    if (name.isEmpty())
    {
        QMessageBox::warning( this,"Error", "Please enter the new name.");
    } else {

        QString new_file_name  = file_name_edit->text();
        emit new_file_name_button_clicked(new_file_name);
    }
}
