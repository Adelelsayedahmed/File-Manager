#include "undocontroller.h"

UndoController::UndoController()
{
}

void UndoController::addActions(Undo *undo)
{
    if(undoActions.size()==10){
       undoActions.pop_front();
    }
    qInfo()  <<"add Undo\n ";
    undoActions.push_back(undo);
}

void UndoController::undo()
{   qInfo() << "in undo controller " << '\n';
    if(!undoActions.empty()){
        Undo * undo=undoActions.back();
        undoActions.pop_back();
        qInfo() << "before undo" << '\n';
        undo->undo();
        qInfo() << "after undo" << '\n';
    }
    else
     qInfo() << "undoActions is empty" << '\n';
}
