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
enum class CopyCutAction {
    Copy,
    Cut,
    CopyDirectory
};
class ExplorerMin:public QWidget
{
    Q_OBJECT
public:
    ExplorerMin(QString rootPath =  QString(),QWidget *parent = nullptr);
protected:
    QTableView *table;
    QFormLayout *layout;
    QFileSystemModel* fileSystemModel;
    QModelIndex index;
    CopyCutAction action;
    QString filePath;

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
signals:
    void copyFile(std::string source_path, std::string destination_path, CopyCutAction action);
    void delFile(std::string filePath);
    void cutFile(std::string filePath);
    void propertiesOfFile(std::string filePath);
    void renameFileViewSignal(std::string filePath , const std::string newFileName);
    void batchRenameViewSignal(std::vector< std::string>& oldPaths,const std::string &newBaseName);
protected slots:
    void contextMenuEvent(QContextMenuEvent *event);
};

#endif // EXPLORERMIN_H
