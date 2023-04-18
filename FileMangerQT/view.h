#ifndef VIEW_H
#define VIEW_H
#include <QFileSystemModel>
#include <QDesktopServices>
#include <QMainWindow>
#include <filecontentview.h>
#include "ui_filecontentview.h"
#include <stdio.h>
#include "vector"
#include <boost/filesystem.hpp>
QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE
enum class CopyCutAction {
    Copy,
    Cut
};

class View : public QMainWindow
{
    Q_OBJECT
private:
     Ui::View *ui;
    QFileSystemModel* fileSystemModel;
    void mRegisterSignals();
    QVector<QModelIndex> indexVector;
    QModelIndex index;
    QString filePath;
    CopyCutAction action;
public:
    View(QWidget *parent = nullptr);
    void TreeView();
    ~View();
    FileContentView *contentUi;
private slots:
    void on_treeView_clicked(const QModelIndex &index);
    void on_tableView_clicked(const QModelIndex &index);
    void onCopy();
    void onPaste();
    void onDel();
    void onCut();
    void on_treeView_pressed(const QModelIndex &index);

    void on_lineEditPath_textEdited(const QString &arg1);
    void on_tableView_doubleClicked(const QModelIndex &index);
    void contextMenuEvent(QContextMenuEvent *event);
    void onRenameFilesViewSlot();
    void onBatchRenameViewSlot();
signals:
    void copyFile(std::string source_path, std::string destination_path, CopyCutAction action);
    void delFile(std::string filePath);
    void cutFile(std::string filePath);
    void renameFileViewSignal(std::string filePath , const std::string newFileName);
    void batchRenameViewSignal(std::vector< std::string>& oldPaths,const std::string &newBaseName);
};

#endif // VIEW_H
