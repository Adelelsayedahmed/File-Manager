#ifndef STACKEDVIEWWIDGET_H
#define STACKEDVIEWWIDGET_H

#include "explorer.h"
#include "twopane.h"
#include "identifyduplicatespagewidget.h"

#include <QPushButton>
#include <QStackedWidget>
#include <QWidget>

class stackedviewwidget:public QWidget{
    Q_OBJECT
public:
    explicit stackedviewwidget(QWidget *parent = nullptr);
    QStackedWidget *stackedWidget;
    Explorer *explorer;
    TwoPane *twoPane;
    IdentifyDuplicatesPageWidget *duplicatesPage;
    QPushButton *nextButton;
    QPushButton *previousButton;

public slots:
    void switchToIndex(int index);

private slots:
    void nextPane();
    void previousPane();

private:

};

#endif // STACKEDVIEWWIDGET_H
