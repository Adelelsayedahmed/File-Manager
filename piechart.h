#ifndef PIECHART_H
#define PIECHART_H

#include <QObject>
#include <QWidget>
#include <QtCharts/QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <unordered_map>
#include <string>
#include <QString>


class PieChart : public QWidget
{
    Q_OBJECT
public:
    struct chartProperties{
        QString chartTitle;
        QString fontType;
        bool showValue;
        QString addToValue;
        bool setSpecialColors;
        bool mouseTracking;
        bool renderHint_Antialiasing;

        /* struct constructor
           provide it's default properties
                                             */
        chartProperties(QString title)
            : chartTitle(title), fontType("Arial"), showValue(false), addToValue("")
            , setSpecialColors(false), mouseTracking(true), renderHint_Antialiasing(true)  {}

    };

    explicit PieChart(QWidget *parent ,std::unordered_map<std::string, int>& statsMap,PieChart::chartProperties& prop);

    QPieSeries * fillPieSeries(std::unordered_map<std::string,int> statsMap);

    QChart* initializeTheChart(QPieSeries* series,QString chartTitle);

    QChartView* createTheChartView(std::unordered_map<std::string, int> statsMap,struct chartProperties& chartProperties);

signals:


private slots:
    void hoveringSlot(QPieSlice *slice, bool state);

};


#endif // PIECHART_H
