
#ifndef EXPLORERMIN_H
#define EXPLORERMIN_H

#include <QObject>
#include <QTableView>
#include <QTreeView>
#include <QModelIndex>
#include <QFileSystemModel>
#include <QFormLayout>
#include <QShortcut>
#include <QMenu>
#include <QContextMenuEvent>
#include "Actions.h"
#include <filecontentview.h>
#include "ui_filecontentview.h"
#include "searchwindow.h"
#include "searchbar.h"


class ExplorerMin:public QWidget
{
    Q_OBJECT
public:
    ExplorerMin(QString rootPath =  QString(),QWidget *parent = nullptr);
protected:
    SearchBar *search;
    QTableView *table;
    QFormLayout *layout;
    QFileSystemModel* fileSystemModel;
    QModelIndex index;
    CopyCutAction action;
    QString filePath;
    QString sourceFilePathCopy;
    FileContentView *contentUi;
    void onTableViewClicked(QModelIndex index);
    void registerSignals();



    QTableView* ShowTableView();
public slots:
    void on_tableView_clicked(const QModelIndex &index);
    void onCopy();
    void onPaste();
    void onDel();
    void onCut();
    void onProperties();
    void onRenameFilesViewSlot();
    void onCompress();
    void onDeCompress();
    void onCompressHere();
    void onDecompressHere();
    void onBatchRenameViewSlot();

    void folderClicked(QString filepath);
    void SearchWindowCreatedSlot(SearchWindow *window);
signals:
    void copyFile(std::string source_path, std::string destination_path, CopyCutAction action);
    void delFile(std::string filePath);
    void cutFile(std::string filePath);
    void propertiesOfFile(std::string filePath);
    void renameFileViewSignal(std::string filePath , const std::string newFileName);
    void batchRenameViewSignal(std::vector< std::string>& oldPaths,const std::string &newBaseName);
    void SearchWindowCreated(SearchWindow *window);
    void locationChanged(QString filepath, QString filename);

protected slots:
    void contextMenuEvent(QContextMenuEvent *event);
    void on_tableView_doubleClicked(QModelIndex index);
};

#endif // EXPLORERMIN_H
