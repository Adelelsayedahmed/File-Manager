#ifndef EXPLORER_H
#define EXPLORER_H
#include "qtreeview.h"
#include <QMainWindow>
#include  <QWidget>
#include <QTableView>
#include <QFormLayout>
#include <QFileSystemModel>
#include <QDesktopServices>
#include "view.h"
class Explorer: public QWidget
{
    Q_OBJECT
    public:
    Explorer(QWidget *parent = nullptr);
    QTreeView* ShowTreeView();

   private:
    QTreeView *tree;
    QTableView *table;
    QFileSystemModel* fileSystemModel;
    QModelIndex index;
private slots:
    QTableView* ShowTableView();

};

#endif // EXPLORER_H
