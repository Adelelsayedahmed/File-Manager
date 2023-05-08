#ifndef UNDOCREATEDIRECTORY_H
#define UNDOCREATEDIRECTORY_H
#include "undo.h"

class undocreateDirectory:public Undo
{
private:
    fs::path p;
public:
    undocreateDirectory(const fs::path& p);
    virtual void undo();
};

#endif // UNDOCREATEDIRECTORY_H
