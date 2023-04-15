#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    statistics statObj;
   std::unordered_map<std::string, int> statsMap=statObj.directoryFilesSizes(statistics::getCurrentPath());
    for (const auto& pair : statsMap) {
        qDebug() << pair.first.c_str() << ": " << pair.second;
    }
   // PieChart::chartProperties prop={"Sizes of files","Arial",true,"KB",false,true,true};
    PieChart::chartProperties prop("Sizes of files");

    new PieChart(ui->gridLayoutWidget,statsMap,prop);


}

MainWindow::~MainWindow()
{
    delete ui;
}

