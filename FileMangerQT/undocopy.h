#ifndef UNDOCOPY_H
#define UNDOCOPY_H
#include "undo.h"
#include "utilities.h"
#include "vector"
class UndoCopy:public Undo
{
    std::vector<fs::path> paths;
public:
    UndoCopy(std::vector<fs::path>& paths);
    virtual  void undo() override;
};

#endif // UNDOCOPY_H
