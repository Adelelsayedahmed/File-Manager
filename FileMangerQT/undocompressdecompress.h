#ifndef UNDOCOMPRESSDECOMPRESS_H
#define UNDOCOMPRESSDECOMPRESS_H
#include "undo.h"
#include "utilities.h"
class undoCompressDecompress :public Undo
{
public:
    undoCompressDecompress(std::string &path);
     virtual  void undo() override;
private:
    std::string path;
};

#endif // UNDOCOMPRESSDECOMPRESS_H
