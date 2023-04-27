#ifndef EXPLORER_H
#define EXPLORER_H
#include "qtreeview.h"
#include <QMainWindow>
#include  <QWidget>
#include <QTableView>
#include <QFormLayout>
#include <QFileSystemModel>
#include <QDesktopServices>

#include <QHeaderView>
#include "explorermin.h"
class Explorer: public ExplorerMin
{
    Q_OBJECT
public:
    Explorer(QString rootPath = QString(), QWidget *parent = nullptr);
    QTreeView* ShowTreeView(const QString &rootPath);

protected slots:
    void on_treeView_clicked(const QModelIndex &index);
private:
    QTreeView *tree;
    void registerSignals();
    void expandPath(const QString &path);
};
#endif // EXPLORER_H
