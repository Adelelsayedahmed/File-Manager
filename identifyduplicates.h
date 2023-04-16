#ifndef IDENTIFYDUPLICATES_H
#define IDENTIFYDUPLICATES_H


#include <boost/filesystem.hpp>
#include <unordered_map>
#include <string>
#include <statistics.h>

using namespace boost::filesystem;

class IdentifyDuplicates
{
public:

    //default constructor
    IdentifyDuplicates();

    // function to return a vector of vector of strings containing the suspected duplicates files/directories paths
    std::vector<std::vector<std::string>> checkDuplication(const std::vector<path>& paths);

private:

    // function to generate a unique number for each file/directory
    int fileDuplicationHash(int size,std::string extension);

    // function takes a map and convert it to vector of vectors
    std::vector<std::vector<std::string>> convertMapToVectorOfVectors(std::unordered_map<int, std::vector<path>>& elementsMap);


};

#endif // IDENTIFYDUPLICATES_H
