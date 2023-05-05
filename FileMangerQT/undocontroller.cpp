#include "undocontroller.h"

UndoController::UndoController()
{
}

void UndoController::addActions(Undo *undo)
{
    if(undoActions.size()==10){
       undoActions.pop_front();
    }
    undoActions.push_back(undo);
}

void UndoController::undo()
{
    if(!undoActions.empty()){
        Undo * undo=undoActions.back();
        undoActions.pop_back();
        undo->undo();
    }
}
