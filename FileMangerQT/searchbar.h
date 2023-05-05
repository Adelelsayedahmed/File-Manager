#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include "searchwindow.h"
#include <QWidget>
#include "backbutton.h"


class SearchBar : public QWidget
{
    Q_OBJECT
public:
    explicit SearchBar(QWidget *parent = nullptr);

    BackButton *back;
//    LocationBar *locationBar;


protected:
    QHBoxLayout *layout;
    QPushButton *findButton;
    QLineEdit *searchBar;
    QString dfilePath;
    QLineEdit *locationBar;

public slots:
    void locationChanged(QString filepath, QString filename);

private slots:
    void on_findButton_pressed();

signals:
    void SearchWindowCreated(SearchWindow *search);

};


#endif // SEARCHBAR_H
