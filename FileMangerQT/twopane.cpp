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
    leftTable->table->setDropIndicatorShown(true);
    leftTable->table->setDefaultDropAction(Qt::MoveAction);

    rightTable->table->setAcceptDrops(true);
    rightTable->table->setDragEnabled(true);
    rightTable->table->setDropIndicatorShown(true);
    rightTable->table->setDefaultDropAction(Qt::MoveAction);

}
