#ifndef UNDOCUT_H
#define UNDOCUT_H
#include "undo.h"
class UndoCut:public Undo
{
    fs::path source_path,dest_path;
public:
    UndoCut(fs::path& source_path,fs::path& dest_path);
    virtual  void undo() override;
};

#endif // UNDOCUT_H
