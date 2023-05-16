#include "undocontroller.h"
const int UndoController::max_number_of_actions_supported_for_undo = 10;
UndoController::UndoController()
{
}

void UndoController::addActions(Undo *undo)
{
    if(undoActions.size()==max_number_of_actions_supported_for_undo){
       undoActions.pop_front();
    }
    qInfo()  <<"add Undo in undo controller\n ";
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

const int UndoController::get_max_number_of_actions_supported_for_undo()
{
    return max_number_of_actions_supported_for_undo;
}
