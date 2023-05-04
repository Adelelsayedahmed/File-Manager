#ifndef VIEW_H
#define VIEW_H
#include <QFileSystemModel>
#include <QDesktopServices>
#include <QMainWindow>
#include <filecontentview.h>
#include "ui_filecontentview.h"
#include <stdio.h>
#include "customtwopathwidget.h"
#include "vector"
#include <boost/filesystem.hpp>
#include <explorer.h>
#include "explorermin.h"
#include "twopane.h"
#include "stackedviewwidget.h"
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
    QVector<QModelIndex> indexVector;
    QModelIndex index;

    CopyCutAction action;
public:
    View(QWidget *parent = nullptr);
    void TreeView();
    ~View();
    FileContentView *contentUi;
//  Explorer *explorer;
    stackedviewwidget * stackedview;
private slots:

//signals:

};

#endif // VIEW_H
