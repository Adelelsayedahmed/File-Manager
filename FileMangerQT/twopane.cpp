#include "twopane.h"

TwoPane::TwoPane(QWidget *parent):QWidget(parent)
{
    leftTable = new ExplorerMin();
    rightTable = new ExplorerMin();
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->addWidget(leftTable);
    hLayout->addWidget(rightTable);
    leftTable->table->setAcceptDrops(true);
    leftTable->table->setDragEnabled(true);
    leftTable->table->setDragDropMode(QAbstractItemView::DragDrop);
    leftTable->table->setDropIndicatorShown(true);
    leftTable->table->setDefaultDropAction(Qt::CopyAction);
    // Connect signals to slots

    rightTable->table->setAcceptDrops(true);
    rightTable->table->setDragEnabled(true);
    rightTable->table->setDragDropMode(QAbstractItemView::DragDrop);

    rightTable->table->setDropIndicatorShown(true);
    rightTable->table->setDefaultDropAction(Qt::CopyAction);

}

void TwoPane::onDragEnter(QDragEnterEvent *)
{
    qInfo() << "drage";
}

void TwoPane::onDrop(QDropEvent *)
{
    qInfo() << "drop";
}
