
#include "explorer.h"
#include <QObject>
#include <QLabel>
Explorer::Explorer(QString rootPath, QWidget *parent ): ExplorerMin(rootPath,parent)

{
    tree = new QTreeView(this);
    layout->insertRow(0,topBar);
    layout->insertRow(1, search);
    layout->insertRow(2,ShowTreeView(rootPath),table);

    registerSignals();

}
void Explorer::registerSignals()
{
    QObject::connect(tree,SIGNAL(doubleClicked(QModelIndex)),table,SLOT(setRootIndex(QModelIndex)));
    QObject::connect(tree,SIGNAL(clicked(QModelIndex)),table,SLOT(setRootIndex(QModelIndex)));
    QObject::connect(tree, SIGNAL(clicked(QModelIndex)), this, SLOT(on_treeView_clicked(QModelIndex)));

}

Explorer::~Explorer()
{
    delete tree;
}


QTreeView* Explorer::ShowTreeView(const QString &rootPath)
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

void Explorer::on_treeView_clicked(const QModelIndex &index)
{
    this->index = index;
    emit locationChanged(fileSystemModel->filePath(index), fileSystemModel->fileName(index));
}

