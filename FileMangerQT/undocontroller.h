#ifndef UNDOCONTROLLER_H
#define UNDOCONTROLLER_H
#include "undo.h"
#include "deque"
#include <QDebug>
#define MAX_NUMBER_OF_OPERATIONS 10

class UndoController
{
private:
    static const int max_number_of_actions_supported_for_undo;
    std::deque<Undo *> undoActions;
public:
    UndoController();
    void addActions(Undo * undo);
    void undo();
    static const int get_max_number_of_actions_supported_for_undo();

};

#endif // UNDOCONTROLLER_H
