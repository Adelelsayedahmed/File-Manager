#include "explorermin.h"
#include <QBoxLayout>

ExplorerMin::ExplorerMin(QWidget *parent): QWidget(parent)
{
     QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    fileSystemModel = new QFileSystemModel(this);
    QWidget* tableWidget = new QWidget;
    table = new QTableView(tableWidget);
    index = fileSystemModel->setRootPath(QString());
    QObject::connect(table,SIGNAL(doubleClicked(QModelIndex)),table,SLOT(setRootIndex(QModelIndex)));
    layout->addWidget(ShowTableView());
}
QTableView* ExplorerMin::ShowTableView()
{
    table->setModel(fileSystemModel);
    table->setRootIndex(index);
    table->setColumnWidth(0,250);
    table->setColumnWidth(3,250);
    table->horizontalScrollBar();
    table->setMinimumHeight(120);
    //    table->setMinimumWidth(2000);
    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
//    table->verticalHeader()->hide();
    return table;
}
