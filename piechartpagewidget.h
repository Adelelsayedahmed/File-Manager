#ifndef PIECHARTPAGEWIDGET_H
#define PIECHARTPAGEWIDGET_H

#include <QWidget>
#include <QTabWidget>

class pieChartPageWidget : public QWidget
{
    Q_OBJECT
public:
    QWidget *parent;

    explicit pieChartPageWidget(QWidget *parent = nullptr);

    QWidget* returnTabs(int index);

    QTabWidget *tabWidget;

    QWidget *sizesTab;

    QWidget *typesTab;

signals:

};

#endif // PIECHARTPAGEWIDGET_H
