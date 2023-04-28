#ifndef TWOPANE_H
#define TWOPANE_H

#include "explorermin.h"
class TwoPane:public QWidget
{
     Q_OBJECT
public:
    TwoPane(QWidget *parent = nullptr);
private:
    ExplorerMin *leftTable = nullptr;
    ExplorerMin *rightTable = nullptr;
};

#endif // TWOPANE_H
