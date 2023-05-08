#include "undocreatefile.h"

UndoCreateFile::UndoCreateFile(const fs::path& p)
{
    this->p = p;
}

void UndoCreateFile::undo()
{
    Undo::del(p);
}
