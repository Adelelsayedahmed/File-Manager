#include "undocompressdecompress.h"

undoCompressDecompress::undoCompressDecompress(std::string &path)
{
    this->path=path;
}

void undoCompressDecompress::undo()
{
   utilities::del(this->path);
}
