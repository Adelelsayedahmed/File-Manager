#ifndef UNDOCONTROLLER_H
#define UNDOCONTROLLER_H
#include "undo.h"
#include "deque"
#define MAX_NUMBER_OF_OPERATIONS 10

class UndoController
{
    std::deque<Undo *> undoActions;
    int index=0;
public:
    UndoController();
    void addActions(Undo * undo);
    void undo();

};

#endif // UNDOCONTROLLER_H
