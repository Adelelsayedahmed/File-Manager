#ifndef UNDODELETE_H
#define UNDODELETE_H
#include "undo.h"

class undoDelete:public Undo
{
    fs::path old_path,new_path;

public:
    undoDelete(fs::path& old_path,fs::path& new_path);
    virtual  void undo() override;
};

#endif // UNDODELETE_H
