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
     rename_widget(std::string buttonValueF , std::string lineValueF , std::string errorValueF);
    ~rename_widget();
private :
    QLineEdit *file_name_edit;
    QPushButton *okButton;
    QLabel *warningLabel;
    std::string buttonValue ;
    std::string errorValue ;
    std::string lineValue ;


private slots:
    void onOkClicked() ;
signals :
    void new_file_name_button_clicked(QString lineValue);

};

#endif // RENAME_WIDGET_H
