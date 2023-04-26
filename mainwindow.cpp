#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /////identify duplicates main//////
    ///
    IdentifyDuplicates* dupsObj=new IdentifyDuplicates;

    IdentifyDuplicatesPageWidget *pageWidget = new IdentifyDuplicatesPageWidget(this,dupsObj);
    setCentralWidget(pageWidget);
    show();


    //setCentralWidget(pieChartWidget);


/// controller for properties window
 ///   statistics *statObj = new statistics;

///    pieChartPageWidget *pieChartWidget = new pieChartPageWidget(parent);
///    PropertiesPageWidget* propertiesWidget = new PropertiesPageWidget(parent, statObj, pieChartWidget);
                // take the path from the selection and pass it
///    propertiesWidget->path=boost::filesystem::path("/home/fady/Documents/cheatsheet.pdf");

///    propertiesWidget->showPropertiesWindow();




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
//    for (const auto& pair : statsMap) {
//        qDebug() << pair.first.c_str() << ": " << pair.second;
//    }

    //PieChartWidget::chartProperties prop("Sizes of files");




//    PieChart::chartProperties typesprop("Types of files");
//    //PieChart::chartProperties typesprop("Types of files","Arial",true," items",false,true,true);
//    new PieChart(ui->tab_4,typesMap,typesprop);


}

MainWindow::~MainWindow()
{
    delete ui;
}

