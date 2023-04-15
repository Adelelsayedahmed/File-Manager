#include "explorer.h"
#include <QObject>

Explorer::Explorer(QWidget *parent ): QWidget(parent)

{

     fileSystemModel = new QFileSystemModel(this);
     tree = new QTreeView(this);
     table = new QTableView(this);
     QFormLayout *form = new QFormLayout(this);
     form->addRow(ShowTreeView(),ShowTableView());
     index = fileSystemModel->setRootPath(QString());
     QObject::connect(tree,SIGNAL(doubleClicked(QModelIndex)),table,SLOT(setRootIndex(QModelIndex)));
     QObject::connect(table,SIGNAL(doubleClicked(QModelIndex)),table,SLOT(setRootIndex(QModelIndex)));

}
QTreeView* Explorer::ShowTreeView()
{
    tree->setModel(fileSystemModel);
    tree->setRootIndex(fileSystemModel->setRootPath(QString()));
    tree->horizontalScrollBar();
    tree->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //hide the columns we don't want
    for (int i=1; i<4; ++i) tree->hideColumn(i);
    tree->setColumnWidth(0, 500);
    tree->show();
    tree->setMinimumHeight(120);

    return tree;
}

QTableView* Explorer::ShowTableView()
{

    table->setModel(fileSystemModel);
    table->setRootIndex(index);
    table->setColumnWidth(0,250);
    table->setColumnWidth(3,250);
    table->horizontalScrollBar();
    table->setMinimumHeight(120);
//    table->setMinimumWidth(2000);
    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    table->verticalHeader()->hide();
    return table;

}
