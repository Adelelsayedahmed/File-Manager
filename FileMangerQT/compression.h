#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <vector>
#include <string>
#include <iostream>
#include <thread>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <fstream>

class compression
{
public:
    compression();
    void batchCompress(std::vector< std::string>& Paths);
    void batchDecompress(std::vector< std::string>& Paths);

private :
   void batchCompressionWorkFunction(unsigned workCount , unsigned startIndex , std::vector< std::string>& Paths );
   void batchDecompressionWorkFunction(unsigned workCount , unsigned startIndex , std::vector< std::string>& Paths );
   void compress_file_here(const std::string& input_file_path);
   void decompress_file_here( const std::string& input_file_path);
   void decompress_file(const std::string& input_file_path, const std::string& output_file_path);
   void compress_file(const std::string& input_file_path, const std::string& output_file_path);
};

#endif // COMPRESSION_H
