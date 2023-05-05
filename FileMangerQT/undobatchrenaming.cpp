#include "undobatchrenaming.h"
UndoBatchRenaming::UndoBatchRenaming(std::vector<std::string> &oldPaths, std::vector<std::string> &newNames)
{
    this->oldPaths=oldPaths;
    this->newNames=newNames;
}

void UndoBatchRenaming::undo()
{
    for(int i=0;i<newNames.size();i++){
        try
        {
            fs::rename(Undo::removeNameFromPath(oldPaths[i])+newNames[i],oldPaths[i]);
        }
        catch (const std::exception& ex) {
        std::cerr << "Error renaming file in Undo: " << ex.what() << std::endl;    }
    }
}
