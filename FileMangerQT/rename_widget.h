#ifndef RENAME_WIDGET_H
#define RENAME_WIDGET_H

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

class rename_widget : public QWidget
{
     Q_OBJECT
public:
    rename_widget();
    QLineEdit *file_name_edit;
    QPushButton *okButton;
    QLabel *warningLabel;


private slots:
    void onOkClicked() ;
signals :
    void new_file_name_button_clicked(QString new_file_name);

};

#endif // RENAME_WIDGET_H
