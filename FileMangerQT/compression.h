#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <vector>
#include <string>
#include <iostream>
#include <thread>

class compression
{
public:
    compression();
    void batchCompress(std::vector< std::string>& Paths);
    void batchDecompress(std::vector< std::string>& Paths);

private :
   void batchCompressionWorkFunction(unsigned workCount , unsigned startIndex , std::vector< std::string>& Paths );
   void batchDecompressionWorkFunction(unsigned workCount , unsigned startIndex , std::vector< std::string>& Paths );
};

#endif // COMPRESSION_H
