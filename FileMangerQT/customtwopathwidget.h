
#ifndef CUSTOMTWOPATHWIDGET_H
#define CUSTOMTWOPATHWIDGET_H
#define COMPRESS 0
#define DECOMPRESS 1

#include <QWidget>
#include <QFileDialog>
#include <QDir>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include<QString>
class CustomTwoPathWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomTwoPathWidget(int num = 0,QWidget *parent = nullptr );

protected:
    QPushButton *action_button ;

private slots:
    void browseDirectory() ;
    void browseFile();
 void action_method()  ;



signals:

};

#endif // CUSTOMTWOPATHWIDGET_H
