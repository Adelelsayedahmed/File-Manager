#include "piechartpagewidget.h"

pieChartPageWidget::pieChartPageWidget(QWidget *parent)
    : QWidget{parent}
{
    this->parent=parent;
    tabWidget = new QTabWidget(this);
    tabWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    tabWidget->setMinimumSize(800, 800);

     sizesTab = new QWidget();
    tabWidget->addTab(sizesTab, tr("sizes"));

    typesTab = new QWidget();
    tabWidget->addTab(typesTab, tr("types"));
}

QWidget* pieChartPageWidget::returnTabs(int index)
{
    if (index >= 0 && index < tabWidget->count()) {

        return tabWidget->widget(index);
    }
    return nullptr;
}
