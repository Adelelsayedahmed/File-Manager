#include "piechart.h"


PieChart::PieChart(QWidget *parent,std::unordered_map<std::string, int>& statsMap,PieChart::chartProperties& prop)
    : QWidget{parent}
{



    QChartView* chartView=createTheChartView(statsMap,prop);
    chartView->setParent(parent);

}

QPieSeries* PieChart::fillPieSeries(std::unordered_map<std::string,int> statsMap)
{


    QPieSeries *series=new QPieSeries();
    for ( auto& pair : statsMap) {
         QPieSlice *slice =series->append(QString::fromStdString(pair.first),pair.second);
          slice->setLabelVisible(false);
    }

    return series;
}


QChart* PieChart::initializeTheChart(QPieSeries* series,QString chartTitle)
{
    QChart *chart=new QChart();
    chart->addSeries(series);
    chart->setTitle(chartTitle);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setVisible(true);

    return chart;
}

QChartView* PieChart::createTheChartView(std::unordered_map<std::string, int> statsMap,struct chartProperties& chartProperties)
{
    QPieSeries* series=fillPieSeries(statsMap);
    QChartView *chartView=new QChartView(initializeTheChart(series,chartProperties.chartTitle));
    chartView->setMouseTracking(chartProperties.mouseTracking);
    chartView->setRenderHint(QPainter::Antialiasing,chartProperties.renderHint_Antialiasing);
    QFont font(chartProperties.fontType);
    if(series->count()>=8){

          font.setPointSize(8);
    }
    chartView->chart()->legend()->setFont(font);
    if(chartProperties.showValue){
    for (QPieSlice *slice : series->slices()) {
          slice->setLabel(QString("%1: %2%3").arg(slice->label()).arg(slice->value()).arg(chartProperties.addToValue));
    }
    }
    if(chartProperties.setSpecialColors){
    int i = 0;
    for (QPieSlice *slice : series->slices()) {
    slice->setColor(QColor::fromHsv((i * 255) / series->count(), 255, 255));
    ++i;
    }
    }
    chartView->resize(800, 600);
    QObject::connect(series, &QPieSeries::hovered, this, &PieChart::hoveringSlot);


    return chartView;
}

void PieChart::hoveringSlot(QPieSlice *slice, bool state){
    if (slice) {
          if (state) {
              if(slice->label().length()>=9){
              QFont font = slice->labelFont();
              font.setPointSize(8);
              slice->setLabelFont(font);
              }
              slice->setLabelVisible(true);
              slice->setExploded(true);

          } else {
              slice->setExploded(false);
              slice->setLabelVisible(false);
          }
    }
}

