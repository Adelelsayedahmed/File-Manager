#include "undocreatedirectory.h"
undocreateDirectory::undocreateDirectory(const fs::path& p)
{
    this->p = p;
}

void undocreateDirectory::undo()
{
     utilities::del(p);
}
