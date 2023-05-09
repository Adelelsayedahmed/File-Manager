#ifndef UNDOCREATEFILE_H
#define UNDOCREATEFILE_H
#include "undo.h"
#include "utilities.h"
class UndoCreateFile:public Undo
{
private:
   fs::path p;
public:
    UndoCreateFile(const fs::path& p);
    virtual void undo();
};

#endif // UNDOCREATEFILE_H
