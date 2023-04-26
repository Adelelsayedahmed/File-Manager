#include "integrate.h"

integrate::integrate(QObject *parent,statistics *statsObj,pieChartPageWidget *pieChartWidget)
    : QObject{parent}
{
    this->parent=parent;
    this->statsObj=statsObj;
    this->pieChartWidget=pieChartWidget;
}
void integrate::showStatistics()
{

std::unordered_map<std::string, int> sizesMap=statsObj->directoryFilesSizes(statistics::getCurrentPath());

PieChartWidget::chartProperties sizesChartprop("Sizes of files","Arial",true,"KB",false,true,true);
new PieChartWidget(pieChartWidget->returnTabs(0),sizesMap,sizesChartprop);

std::unordered_map<std::string, int> typesMap=statsObj->directoryFilesTypes(statistics::getCurrentPath());

PieChartWidget::chartProperties typesprop("Types of files","Arial",true," items",false,true,true);
new PieChartWidget(pieChartWidget->returnTabs(1),typesMap,typesprop);

pieChartWidget->show();

}
