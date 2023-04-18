#ifndef PIECHARTWIDGET_H
#define PIECHARTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QtCharts/QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <unordered_map>
#include <string>
#include <QString>


class PieChartWidget : public QWidget
{
    Q_OBJECT
public:

    // Structure that holds chart properties such as title, font type, and whether to show values or not
    struct chartProperties{
        QString chartTitle;
        QString fontType;
        bool showValue;
        QString addToValue;
        bool setSpecialColors;
        bool mouseTracking;
        bool renderHint_Antialiasing;


        /* struct constructor
           takes every value to be set
                                             */
        chartProperties(QString title, QString font = "Arial", bool showVal = false,
                        QString addToVal = "", bool setSpecColors = false, bool mouseTrack = true,
                        bool antialias = true)
            : chartTitle(title), fontType(font), showValue(showVal), addToValue(addToVal),
            setSpecialColors(setSpecColors), mouseTracking(mouseTrack),
            renderHint_Antialiasing(antialias)
        {}

    };

    // Constructor that takes a parent widget, a map of statistics to display, and chart properties
    explicit PieChartWidget(QWidget *parent ,std::unordered_map<std::string, int>& statsMap,PieChartWidget::chartProperties& prop);

private:

    // Function that fills a QPieSeries with the data from a given stats map and returns a pointer to the series
    QPieSeries * fillPieSeries(std::unordered_map<std::string,int> statsMap);

    // Function that initializes a QChart with a given QPieSeries and title and returns a pointer to the chart
    QChart* initializeTheChart(QPieSeries* series,QString chartTitle);

    // Function that sets properties of a QPieSeries
    void setupPieSeriesProperties(QPieSeries* &series,struct chartProperties& chartProperties);

    // Function that sets properties of a QChartView
    void setupChartViewProperties(QChartView* &chartView,struct chartProperties& chartProperties);

    // Function that creates a QChartView with a given stats map and chart properties and returns a pointer to the view
    QChartView* createTheChartView(std::unordered_map<std::string, int> statsMap,struct chartProperties& chartProperties);

signals:


private slots:

    // Slot function that is called when a slice is hovered over or not hovered over
    void hoveringSlot(QPieSlice *slice, bool state);

};


#endif // PIECHARTWIDGET_H
