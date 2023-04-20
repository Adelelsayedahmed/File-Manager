#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /////identify duplicates main//////
////    IdentifyDuplicates* dupsObj=new IdentifyDuplicates;

////    IdentifyDuplicatesPageWidget *pageWidget = new IdentifyDuplicatesPageWidget(this,dupsObj);
////    setCentralWidget(pageWidget);
////    show();

    //controller of pie chart
////    pieChartPageWidget *pieChartWidget = new pieChartPageWidget(parent);
////    setCentralWidget(pieChartWidget);

////    statistics statObj;
////    std::unordered_map<std::string, int> sizesMap=statObj.directoryFilesSizes(statistics::getCurrentPath());

////    PieChartWidget::chartProperties sizesChartprop("Sizes of files","Arial",true,"KB",false,true,true);
////    new PieChartWidget(pieChartWidget->returnTabs(0),sizesMap,sizesChartprop);

////    std::unordered_map<std::string, int> typesMap=statObj.directoryFilesTypes(statistics::getCurrentPath());

////    PieChartWidget::chartProperties typesprop("Types of files","Arial",true," items",false,true,true);
////    new PieChartWidget(pieChartWidget->returnTabs(1),typesMap,typesprop);


    //setCentralWidget(pieChartWidget);


    //still needs to be adjusted
    statistics *statObj = new statistics;

    pieChartPageWidget *pieChartWidget = new pieChartPageWidget(parent);
    PropertiesPageWidget* propertiesWidget = new PropertiesPageWidget(parent, statObj, pieChartWidget);

    propertiesWidget->path=boost::filesystem::path("/home/fady/Documents/cheatsheet.pdf");

    // Create and show the properties page widget last
    propertiesWidget->showPropertiesWindow();




//    std::vector<boost::filesystem::path> paths;
//    paths.push_back(statistics::getCurrentPath());
//    paths.push_back(statistics::getCurrentPath().parent_path());
//    std::vector<std::vector<std::string>> duplicatesVector=dupsObj.checkDuplication(paths);
//    for (auto& stringVector : duplicatesVector) {
//        QString str;
//        for (auto& strValue : stringVector) {
//            str += QString::fromStdString(strValue) + " ";
//        }
//        qDebug() << str;
//    }

//    ui->tabWidget->setTabText(0,"sizes");
//    ui->tabWidget->setTabText(1,"types");

//    statistics statObj;
//  std::unordered_map<std::string, int> sizesMap=statObj.directoryFilesSizes(statistics::getCurrentPath());
////    for (const auto& pair : statsMap) {
////        qDebug() << pair.first.c_str() << ": " << pair.second;
////    }

    //PieChartWidget::chartProperties prop("Sizes of files");




//    PieChart::chartProperties typesprop("Types of files");
//    //PieChart::chartProperties typesprop("Types of files","Arial",true," items",false,true,true);
//    new PieChart(ui->tab_4,typesMap,typesprop);


}

MainWindow::~MainWindow()
{
    delete ui;
}

