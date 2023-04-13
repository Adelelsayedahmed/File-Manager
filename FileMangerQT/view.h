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
    void on_treeView_pressed(const QModelIndex &index);

    void on_lineEditPath_textEdited(const QString &arg1);

signals:
    void copyFile(std::string source_path, std::string destination_path);

};
#endif // VIEW_H
//QFileSystemModel* fileSystemModel = new QFileSystemModel(this);
//QModelIndex modelIndex = fileSystemModel->setRootPath(QDir::rootPath());
//ui->treeView->setModel(fileSystemModel);
//ui->treeView->setColumnHidden(1,true);
//ui->treeView->setColumnHidden(2,true);
//ui->treeView->setColumnHidden(3,true);
//ui->treeView->header()->resizeSections(QHeaderView::Interactive);
//ui->treeView->header()->setStretchLastSection(true);
//ui->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
