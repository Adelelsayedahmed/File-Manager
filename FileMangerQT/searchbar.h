#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include "searchwindow.h"
#include <QWidget>
#include <boost/filesystem.hpp>
#include "locationbar.h"


class SearchBar : public QWidget
{
    Q_OBJECT
public:
    explicit SearchBar(QWidget *parent = nullptr);
    QPushButton *backButton;
    LocationBar *bar;

protected:
    QHBoxLayout *layout;
    QPushButton *findButton;
    QLineEdit *searchBar;
    QString dfilePath;

public slots:
    void locationChanged(QString filepath, QString filename);
    void backButtonPressed();
    void initializeLocationBarModel(QFileSystemModel *model, QModelIndex index);

private slots:
    void on_findButton_pressed();

signals:
    void SearchWindowCreated(SearchWindow *search);
    void backButtonPressedSignal();
    void changeLocationBar(QString filepath);
};


#endif // SEARCHBAR_H
