#include "propertiespagewidget.h"

PropertiesPageWidget::PropertiesPageWidget(QWidget *parent,statistics* statsObj,pieChartPageWidget *pieChartWidget )
    : QWidget{parent}
{

    this->parent=parent;
   this->statsObj=statsObj;
    this->pieChartWidget=pieChartWidget;

   propertiesWindow = new QDialog(this);




}
void PropertiesPageWidget::showPropertiesWindow()
{
    propertiesWindow->setWindowTitle("Properties");
    propertiesWindow->setFixedSize(400, 400);

    layout = new QGridLayout(propertiesWindow);
    propertiesWindow->setLayout(layout);

    QString name;
    QString size;
    QString extension;


    iconLabel = new QLabel(propertiesWindow);
    QString parentPath=QString::fromStdString(boost::filesystem::path(__FILE__).parent_path().string());
    if(boost::filesystem::is_regular_file(path))
    {
        iconLabel->setPixmap(QPixmap( parentPath + "/fileIcon.png"));
        name=QString::fromStdString(path.filename().string());
        size=QString::fromStdString(std::to_string(boost::filesystem::file_size(path)/1000)+" KB");
        extension=QString::fromStdString(path.extension().string());
    }else
    {
        iconLabel->setPixmap(QPixmap( parentPath + "/directoryIcon.png"));
        name=QString::fromStdString(path.filename().string());
        size=QString::fromStdString(std::to_string(statistics::directory_size(path)/1000)+" KB");
        extension="directory";

        statisticsButton = new QPushButton("Statistics", propertiesWindow);
       connect(statisticsButton, &QPushButton::clicked, this, &PropertiesPageWidget::showStatistics);

        layout->addWidget(statisticsButton, 7, 1, 1, 1);

    }

    layout->addWidget(iconLabel, 1, 1, 1, 1);

    // Add the labels
    QLabel *nameLabel = new QLabel("Name:", propertiesWindow);
    QLabel *sizeLabel = new QLabel("Size:", propertiesWindow);
    QLabel *extensionLabel = new QLabel("Type:", propertiesWindow);

   QLabel *nameValueLabel = new QLabel("  "+name, propertiesWindow);
    QLabel *sizeValueLabel = new QLabel("  "+size, propertiesWindow);
    QLabel *extensionValueLabel = new QLabel("  "+extension, propertiesWindow);

    layout->addWidget(nameLabel, 3, 1,1,1);
    layout->addWidget(nameValueLabel, 3, 2,1,1);
    layout->addWidget(sizeLabel, 4, 1,1,1);
    layout->addWidget(sizeValueLabel, 4, 2,1,1);
    layout->addWidget(extensionLabel, 5, 1,1,1);
    layout->addWidget(extensionValueLabel, 5, 2,1,1);





    propertiesWindow->show();
}


void PropertiesPageWidget::showStatistics()
{

    std::unordered_map<std::string, int> sizesMap=statsObj->directoryFilesSizes(path);

    PieChartWidget::chartProperties sizesChartprop("Sizes of files","Arial",true,"KB",false,true,true);
    new PieChartWidget(pieChartWidget->returnTabs(0),sizesMap,sizesChartprop);

    std::unordered_map<std::string, int> typesMap=statsObj->directoryFilesTypes(path);

    PieChartWidget::chartProperties typesprop("Types of files","Arial",true," items",false,true,true);
    new PieChartWidget(pieChartWidget->returnTabs(1),typesMap,typesprop);

    pieChartWidget->show();

}
