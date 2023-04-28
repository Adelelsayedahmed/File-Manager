#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include "searchwindow.h"
#include <QWidget>

class SearchBar : public QWidget
{
    Q_OBJECT
public:
    explicit SearchBar(QWidget *parent = nullptr);

protected:
    QHBoxLayout *layout;
    QPushButton *findButton;
    QLineEdit *searchBar;
    QLineEdit  *locationBar;
    QString dfilePath;

public slots:
    void locationChanged(QString filepath, QString filename);

private slots:
    void on_findButton_pressed();
signals:
    void SearchWindowCreated(SearchWindow *search);
};


#endif // SEARCHBAR_H
