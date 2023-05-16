#ifndef TWOPANE_H
#define TWOPANE_H

#include "explorermin.h"
class TwoPane:public QWidget
{
     Q_OBJECT
public:
    TwoPane(QWidget *parent = nullptr);
    ~TwoPane();
public:
    std::unique_ptr<ExplorerMin> leftTable;
    std::unique_ptr<ExplorerMin> rightTable;
    LocationBar  *leftBar;
    LocationBar *rightBar;

private slots:
    void onDragEnter(QDragEnterEvent*);
    void dropEvent(QDropEvent* event) ;
private:
    void setupDragAndDrop(QTableView *tableView);
};

#endif // TWOPANE_H
