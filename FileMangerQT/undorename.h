#ifndef UNDORENAME_H
#define UNDORENAME_H
#include "undo.h"
#include"utilities.h"
class UndoRename:public Undo
{
    std::string oldPath,newName;
public:
    virtual  void undo() override;
    UndoRename(const std::string& oldPaths,const std::string& newName);
};

#endif // UNDORENAME_H
