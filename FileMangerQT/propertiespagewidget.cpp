#include "propertiespagewidget.h"


PropertiesPageWidget::PropertiesPageWidget(QWidget *parent,statistics* statsObj,pieChartPageWidget *pieChartWidget )
    : QWidget{parent}
{

    this->parent=parent;
   this->statsObj=statsObj;
   // this->piechartpagewidget=pieChartWidget;

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
    QString dateModified;

    iconLabel = new QLabel(propertiesWindow);
    QString parentPath=QString::fromStdString(boost::filesystem::path(__FILE__).parent_path().string());
    if(boost::filesystem::is_regular_file(path))
    {
        iconLabel->setPixmap(QPixmap( parentPath + "/fileIcon.png"));
        name=QString::fromStdString(path.filename().string());
        size=QString::fromStdString(std::to_string(boost::filesystem::file_size(path)/1024)+" KB");
        extension=QString::fromStdString(path.extension().string());

        boost::posix_time::ptime modifiedTime = boost::posix_time::from_time_t(last_write_time(path));
        dateModified = QString::fromStdString(boost::posix_time::to_simple_string(modifiedTime));


    }else
    {
        iconLabel->setPixmap(QPixmap( parentPath + "/directoryIcon.png"));
        name=QString::fromStdString(path.filename().string());
        size=QString::fromStdString(std::to_string(statistics::directory_size(path.string())/1024)+" KB");
        extension="directory";

        statisticsButton = new QPushButton("Charts representation", propertiesWindow);
       connect(statisticsButton, &QPushButton::clicked, this, &PropertiesPageWidget::showStatistics);
        dateModified=getDirectoryLastModifiedTime(path.string());
        layout->addWidget(statisticsButton, 8, 1, 1, 1);

    }
    if(extension==""){
        extension="file";
    }

    layout->addWidget(iconLabel, 1, 1, 1, 1);

    // Add the labels
    QLabel *nameLabel = new QLabel("Name:", propertiesWindow);
    QLabel *sizeLabel = new QLabel("Size:", propertiesWindow);
    QLabel *extensionLabel = new QLabel("Type:", propertiesWindow);
    QLabel *dateLabel = new QLabel("date modified:", propertiesWindow);

   QLabel *nameValueLabel = new QLabel("  "+name, propertiesWindow);
    QLabel *sizeValueLabel = new QLabel("  "+size, propertiesWindow);
    QLabel *extensionValueLabel = new QLabel("  "+extension, propertiesWindow);
    QLabel *dateValueLabel = new QLabel("  "+dateModified, propertiesWindow);


    layout->addWidget(nameLabel, 3, 1,1,1);
    layout->addWidget(nameValueLabel, 3, 2,1,1);
    layout->addWidget(sizeLabel, 4, 1,1,1);
    layout->addWidget(sizeValueLabel, 4, 2,1,1);
    layout->addWidget(extensionLabel, 5, 1,1,1);
    layout->addWidget(extensionValueLabel, 5, 2,1,1);
    layout->addWidget(dateLabel, 6, 1,1,1);
    layout->addWidget(dateValueLabel, 6, 2,1,1);




    propertiesWindow->show();
}
void PropertiesPageWidget::showStatisticsThreaded()
{
    std::thread statsThread(&PropertiesPageWidget::showStatistics, this);
    statsThread.detach();
}

void PropertiesPageWidget::showStatistics()
{

    std::unordered_map<std::string, int> sizesMap=statsObj->directoryFilesSizes(path);
    piechartpagewidget= new pieChartPageWidget(this);
    PieChartWidget::chartProperties sizesChartprop("Sizes of files/directories","Arial",true,"KB",false,true,true);
    new PieChartWidget(piechartpagewidget->returnTabs(0),sizesMap,sizesChartprop);

    std::unordered_map<std::string, int> typesMap=statsObj->directoryFilesTypes(path);

    PieChartWidget::chartProperties typesprop("Types of files/directories","Arial",true," items",false,true,true);
    new PieChartWidget(piechartpagewidget->returnTabs(1),typesMap,typesprop);



        QDialog* dialog = new QDialog(this);
        dialog->setWindowTitle("Charts");
        dialog->setMinimumSize(840, 800);
        dialog->setLayout(new QGridLayout(dialog));
            dialog->layout()->addWidget(piechartpagewidget);
        dialog->show();

}

QString PropertiesPageWidget::getDirectoryLastModifiedTime(const std::string& dirPath)
{
        boost::filesystem::path path(dirPath);
        boost::system::error_code error;
        auto lastWriteTime = boost::filesystem::last_write_time(path, error);

        if (error) {
        return QString(); // error occurred, return empty QString
        }

        boost::posix_time::ptime lastWritePtime = boost::posix_time::from_time_t(lastWriteTime);
        lastWritePtime = lastWritePtime + boost::posix_time::time_duration(0,0,0,0); // adjust for local time zone
        std::string lastWriteStr = boost::posix_time::to_simple_string(lastWritePtime);
        return QString::fromStdString(lastWriteStr);
}
