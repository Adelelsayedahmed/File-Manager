#include "twopane.h"

TwoPane::TwoPane(QWidget *parent):QWidget(parent)
{
    leftTable = std::unique_ptr<ExplorerMin>(new ExplorerMin("/home/ziad"));
    rightTable = std::unique_ptr<ExplorerMin>(new ExplorerMin("/home/ziad"));
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->addWidget(leftTable.get());
    hLayout->addWidget(rightTable.get());
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

