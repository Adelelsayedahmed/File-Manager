#ifndef PROPERTIESPAGEWIDGET_H
#define PROPERTIESPAGEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QDialog>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QCoreApplication>
#include <QFileInfo>
#include <boost/filesystem.hpp>
#include "statistics.h"
#include <PiechartWidget.h>
#include "piechartpagewidget.h"

class PropertiesPageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PropertiesPageWidget(QWidget *parent = nullptr,statistics *statsObj=nullptr,pieChartPageWidget *pieChartWidget = nullptr);

    void showPropertiesWindow();

    QPushButton *statisticsButton;

    boost::filesystem::path path;

private:

    QWidget *parent;

    statistics *statsObj;


    pieChartPageWidget *piechartpagewidget;

    QDialog *propertiesWindow;

    QGridLayout *layout;

    QLabel *iconLabel ;

signals:

public slots:
    void showStatistics();
};

#endif // PROPERTIESPAGEWIDGET_H
