#include "undorename.h"
void UndoRename::undo()
{
    fs::rename(utilities::removeNameFromPath(oldPath)+newName,oldPath);
}

UndoRename::UndoRename(const std::string &oldPath,const std::string &newName)
{
    this->oldPath=oldPath;
    this->newName=newName;
}
