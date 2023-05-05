#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include "searchwindow.h"
#include <QWidget>
<<<<<<< Updated upstream
=======
#include <boost/filesystem.hpp>
#include "backbutton.h"
#include "locationbar.h"
>>>>>>> Stashed changes

class SearchBar : public QWidget
{
    Q_OBJECT
public:
    explicit SearchBar(QWidget *parent = nullptr);
<<<<<<< Updated upstream
=======
    BackButton *back;
//    LocationBar *locationBar;

>>>>>>> Stashed changes

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
<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
};


#endif // SEARCHBAR_H
