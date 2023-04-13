#ifndef VIEW_H
#define VIEW_H
#include <QFileSystemModel>
#include <QDesktopServices>
#include <QMainWindow>
#include <filecontentview.h>
#include "ui_filecontentview.h"
#include <stdio.h>
QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE

class View : public QMainWindow
{
    Q_OBJECT
private:
     Ui::View *ui;
    QFileSystemModel* fileSystemModel;
    void mRegisterSignals();
    QModelIndex index;

    QString filePath;
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
signals:
    void copyFile(std::string source_path, std::string destination_path);
    void delFile(std::string filePath);
    void cutFile(std::string filePath);
};
#endif // VIEW_H
