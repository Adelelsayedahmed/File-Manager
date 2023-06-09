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
    void mRegisterSignals();
    QVector<QModelIndex> indexVector;
    QModelIndex index;

    CopyCutAction action;
    bool isMultipleSelected();
public:
    addOnsBar* topBar;
    View(QWidget *parent = nullptr);
    void TreeView();
    ~View();
    FileContentView *contentUi;
//  Explorer *explorer;
    stackedviewwidget * stackedview;
    public slots:
    void closeEvent(QCloseEvent *event);
private slots:
        void recieveContentSearchFromSv(const std ::vector<std::string> &filePaths ,const std::string &searchString);
signals:
      void passingContentSearchFromSvtoController(const std ::vector<std::string> &filePaths ,const std::string &searchString);
};

#endif // VIEW_H
