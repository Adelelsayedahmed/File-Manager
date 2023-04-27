#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <PiechartWidget.h>
#include "statistics.h"
#include "identifyduplicates.h"
#include "identifyduplicatespagewidget.h"
#include "propertiespagewidget.h"
#include "piechartpagewidget.h"
#include "addonsbar.h"
#include <QToolBar>
#include <QAction>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGridLayout *gridLayout;
};
#endif // MAINWINDOW_H