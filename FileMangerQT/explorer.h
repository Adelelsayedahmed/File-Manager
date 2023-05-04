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
#include <QSortFilterProxyModel>
#include<thread>
#include "statistics.h"
class DirectoryOnlyFilterProxyModel : public QSortFilterProxyModel
{
public:
    DirectoryOnlyFilterProxyModel(QObject *parent = nullptr)
        : QSortFilterProxyModel(parent)
    {
    }

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override
    {
        QFileSystemModel *source_model = dynamic_cast<QFileSystemModel *>(sourceModel());
        QModelIndex source_index = source_model->index(source_row, 0, source_parent);
        if (source_model->isDir(source_index)) {
            return true;
        }
        return false;
    }
};

#include "explorermin.h"
class Explorer: public ExplorerMin
{
    Q_OBJECT
public:
    Explorer(QString rootPath = QString(), QWidget *parent = nullptr);
    QTreeView* ShowTreeView(const QString &rootPath);
    QLabel* numFilesValueLabel;
    QLabel* sizeValueLabel ;
    void footer_size(std::string s);
    void footer_item(std::string s);
    DirectoryOnlyFilterProxyModel *proxy_model;

    ~Explorer();
protected slots:
    void on_treeView_clicked(const QModelIndex &index);
    void  ShowTableView(QModelIndex index1);
    void footer_update(const QModelIndex &index);
private:
    QTreeView *tree;
    void registerSignals();
    void expandPath(const QString &path);

};
#endif // EXPLORER_H
