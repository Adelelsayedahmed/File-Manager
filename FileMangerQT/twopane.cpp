#include "twopane.h"

TwoPane::TwoPane(QWidget *parent):QWidget(parent)
{
    leftTable = std::unique_ptr<ExplorerMin>(new ExplorerMin());
    rightTable = std::unique_ptr<ExplorerMin>(new ExplorerMin());
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    QVBoxLayout *rightLayout = new QVBoxLayout(this);
    QVBoxLayout *leftLayout = new QVBoxLayout(this);

    leftBar = leftTable->initializeLocationBar();
    rightBar = rightTable->initializeLocationBar();
    leftLayout->addWidget(leftBar);
    leftLayout->addWidget(leftTable.get());

    rightLayout->addWidget(rightBar);
    rightLayout->addWidget(rightTable.get());
    hLayout->addLayout(leftLayout);
    //this has to be done otherwise the shortcuts will not be invoked.
    leftTable->setFocus();
    hLayout->addLayout(rightLayout);
    rightTable->setFocus();
    setupDragAndDrop(leftTable->table);
    setupDragAndDrop(rightTable->table);
}

TwoPane::~TwoPane()
{

}
void TwoPane::setupDragAndDrop(QTableView *tableView)
{
    tableView->setAcceptDrops(true);
    tableView->setDragEnabled(true);
    tableView->setDragDropMode(QAbstractItemView::DragDrop);
    tableView->setDropIndicatorShown(true);
    tableView->setDefaultDropAction(Qt::MoveAction);
//    tableView->setDragDropOverwriteMode(false);
}

void TwoPane::onDragEnter(QDragEnterEvent *)
{
    qInfo() << "drage";
}

void TwoPane::dropEvent(QDropEvent *event)
{
    qInfo() << "drop";

}

