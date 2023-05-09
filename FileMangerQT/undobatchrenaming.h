#ifndef UNDOBATCHRENAMING_H
#define UNDOBATCHRENAMING_H
#include "utilities.h"
#include "undo.h"
#include "vector"
class UndoBatchRenaming :public Undo
{
    std::vector<std::string> oldPaths,newNames;
public:
    UndoBatchRenaming(std::vector<std::string>&oldPaths, std::vector<std::string>&newNames);
    virtual  void undo() override;
};

#endif // UNDOBATCHRENAMING_H
