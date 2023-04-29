#ifndef CUSTOMTABLE_H
#define CUSTOMTABLE_H

#include <QObject>
#include <QTableView>
#include <QDebug>
#include <QWidget>
class CustomTable: public QTableView
{
    Q_OBJECT
public:
    CustomTable(QWidget *parent =  nullptr );
protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
};

#endif // CUSTOMTABLE_H
