#include "customtable.h"

CustomTable::CustomTable(QWidget *parent) : QTableView(parent)
{
    // Constructor implementation
}

void CustomTable::dragEnterEvent(QDragEnterEvent *event)
{
    qInfo()<<"drag";
}

void CustomTable::dropEvent(QDropEvent *event)
{
    qInfo()<<"drop";
}
