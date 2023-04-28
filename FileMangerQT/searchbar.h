#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include "searchwindow.h"
#include <QWidget>
#include <boost/filesystem.hpp>
class SearchBar : public QWidget
{
    Q_OBJECT
public:
    explicit SearchBar(QWidget *parent = nullptr);
    QPushButton *backButton;

protected:
    QHBoxLayout *layout;
    QPushButton *findButton;
    QLineEdit *searchBar;
    QLineEdit  *locationBar;
    QString dfilePath;

public slots:
    void locationChanged(QString filepath, QString filename);
    void backButtonPressed();

private slots:
    void on_findButton_pressed();

signals:
    void SearchWindowCreated(SearchWindow *search);
    void backButtonPressedSignal();
};


#endif // SEARCHBAR_H
