#include "undobatchrenaming.h"
#include <QDebug>
#include <iostream>
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
            qInfo()  <<"Undo batch renaming in file path ";
            qInfo()  <<i;
            std::string str=utilities::removeNameFromPath(oldPaths[i])+newNames[i];
            std::cerr << str;
            qInfo()<<'\n';
            fs::rename(utilities::removeNameFromPath(oldPaths[i])+newNames[i],oldPaths[i]);
        }
        catch (const std::exception& ex) {
        std::cerr << "Error renaming file in Undo: " << ex.what() << std::endl;    }
    }
}
