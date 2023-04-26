#include "PiechartWidget.h"


PieChartWidget::PieChartWidget(QWidget *parent,std::unordered_map<std::string, int>& statsMap,PieChartWidget::chartProperties& prop)
    : QWidget{parent}
{
   // Create the QChartView object and set its parent to this widget
    QChartView* chartView=createTheChartView(statsMap,prop);
    chartView->setParent(parent);

}

QPieSeries* PieChartWidget::fillPieSeries(std::unordered_map<std::string,int> statsMap)
{
    // Create the QPieSeries object and fill it with data from statsMap
    QPieSeries *series=new QPieSeries();
    for ( auto& pair : statsMap) {
         QPieSlice *slice =series->append(QString::fromStdString(pair.first),pair.second);
          slice->setLabelVisible(false);
    }

    return series;
}

void PieChartWidget::setupPieSeriesProperties(QPieSeries* &series,struct chartProperties& chartProperties)
{
    // Set up properties of the QPieSeries object based on chartProperties
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
}

void PieChartWidget::setupChartViewProperties(QChartView* &chartView,struct chartProperties& chartProperties)
{
    // Set up properties of the QChartView object based on chartProperties
    chartView->setRenderHint(QPainter::Antialiasing,chartProperties.renderHint_Antialiasing);
    chartView->resize(800, 600);

    // Make the chart track the Mouse movement for detecting the hovering.
    chartView->setMouseTracking(chartProperties.mouseTracking);


}

QChart* PieChartWidget::initializeTheChart(QPieSeries* series,QString chartTitle)
{
    // Initializes and Setup the chart
    QChart *chart=new QChart();

    // Add the Pie Series to the chart.
    chart->addSeries(series);

    // Set the title of the chart.
    chart->setTitle(chartTitle);

    // Make the chart dynamically animated.
    chart->setAnimationOptions(QChart::AllAnimations);

    if(series->count()>10){
          chart->legend()->setVisible(false);
    }else{

          chart->legend()->setVisible(true);
    }

    return chart;
}

QChartView* PieChartWidget::createTheChartView(std::unordered_map<std::string, int> statsMap,struct chartProperties& chartProperties)
{
    // Fill the pie series with the statistics map data.
    QPieSeries* series=fillPieSeries(statsMap);

    // Create the chart view widget and initialize it with the pie series and chart title.
    QChartView *chartView=new QChartView(initializeTheChart(series,chartProperties.chartTitle));

    // Set up the properties of the chart view based on the chart properties.
    setupChartViewProperties(chartView,chartProperties);

    // Select the font for the chart.
    QFont font(chartProperties.fontType);

    qDebug() << series->count();
    // Set the font size of the chart
    if(series->count()>=7){
          font.setPointSize(8);
    }
    chartView->chart()->legend()->setFont(font);


    // Customize the pie series by setting its properties.
    setupPieSeriesProperties(series,chartProperties);

    // Connect the hovered signal of the pie series to the hoveringSlot function.
    QObject::connect(series, &QPieSeries::hovered, this, &PieChartWidget::hoveringSlot);


    return chartView;
}

void PieChartWidget::hoveringSlot(QPieSlice *slice, bool state){
    if (slice) {
          if (state) {

              // If the label text is too long, reduce its font size.
              if(slice->label().length()>=9){
              QFont font = slice->labelFont();
              font.setPointSize(8);
              slice->setLabelFont(font);
              }

              // Show the label and explode it.
              slice->setLabelVisible(true);
              slice->setExploded(true);

          } else {

              // Fade the label and shrink it.
              slice->setExploded(false);
              slice->setLabelVisible(false);
          }
    }
}

