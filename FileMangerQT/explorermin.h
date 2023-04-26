#ifndef EXPLORERMIN_H
#define EXPLORERMIN_H

#include <QObject>
#include <QTableView>
#include <QTreeView>
#include <QModelIndex>
#include <QFileSystemModel>
class ExplorerMin:public QWidget
{
    Q_OBJECT
public:
    ExplorerMin(QWidget *parent = nullptr);

private:
    QTableView *table;
    QFileSystemModel* fileSystemModel;
    QModelIndex index;
    QTableView* ShowTableView();
};

#endif // EXPLORERMIN_H
