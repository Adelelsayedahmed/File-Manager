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
QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE


class View : public QMainWindow
{
    Q_OBJECT
private:
     Ui::View *ui;
    void mRegisterSignals();
    bool isMultipleSelected();
public:
    View(QWidget *parent = nullptr);
    void TreeView();
    ~View();
    Explorer *explorer;
    TwoPane *twoPane;
private slots:

//signals:

};

#endif // VIEW_H
