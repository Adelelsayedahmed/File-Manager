#ifndef INTEGRATE_H
#define INTEGRATE_H

#include <QObject>
#include "statistics.h"
#include <PiechartWidget.h>
#include "piechartpagewidget.h"
#include <QMainWindow>


class integrate : public QObject
{
    Q_OBJECT
public:
    explicit integrate(QObject *parent = nullptr,statistics *statsObj=nullptr,pieChartPageWidget *pieChartWidget = nullptr);
private:
    QMainWindow* mainWindow;
    QObject *parent;
    statistics *statsObj;
    pieChartPageWidget *pieChartWidget;
signals:
public slots:
    void showStatistics();
};

#endif // INTEGRATE_H
