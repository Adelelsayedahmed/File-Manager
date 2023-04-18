#ifndef VIEW_H
#define VIEW_H
#include <QFileSystemModel>
#include <QDesktopServices>
#include <QMainWindow>
#include <filecontentview.h>
#include "ui_filecontentview.h"
#include <stdio.h>
#include "customtwopathwidget.h"
QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE
enum class CopyCutAction {
    Copy,
    Cut,
    CopyDirectory
};

class View : public QMainWindow
{
    Q_OBJECT
private:
     Ui::View *ui;
    QFileSystemModel* fileSystemModel;
    void mRegisterSignals();
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
//    void on_treeView_pressed(const QModelIndex &index);
    void on_lineEditPath_textEdited(const QString &arg1);
    void on_tableView_doubleClicked(const QModelIndex &index);
    void contextMenuEvent(QContextMenuEvent *event);
    void onRename();
    void onCompress();
    void onDeCompress();
    void onCompressHere();
    void onDecompressHere();

signals:
    void copyFile(std::string source_path, std::string destination_path, CopyCutAction action);
    void delFile(std::string filePath);
    void cutFile(std::string filePath);
    void renameFile(std::string filePath , const std::string newFileName);
};

#endif // VIEW_H
