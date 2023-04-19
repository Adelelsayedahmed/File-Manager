#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    IdentifyDuplicates* dupsObj=new IdentifyDuplicates;

    IdentifyDuplicatesPageWidget *pageWidget = new IdentifyDuplicatesPageWidget(this,dupsObj);
    setCentralWidget(pageWidget);
    show();


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
//    PieChart::chartProperties sizesChartprop("Sizes of files","Arial",true,"KB",false,true,true);
////    PieChart::chartProperties prop("Sizes of files");



//    new PieChart(ui->tab_3,sizesMap,sizesChartprop);

//    std::unordered_map<std::string, int> typesMap=statObj.directoryFilesTypes(statistics::getCurrentPath());
//    PieChart::chartProperties typesprop("Types of files");
//    //PieChart::chartProperties typesprop("Types of files","Arial",true," items",false,true,true);
//    new PieChart(ui->tab_4,typesMap,typesprop);


}

MainWindow::~MainWindow()
{
    delete ui;
}

