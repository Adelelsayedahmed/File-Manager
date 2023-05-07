#ifndef STATISTICS_H
#define STATISTICS_H

#include <boost/filesystem.hpp>
#include <unordered_map>
#include <string>
#include <QDebug>

#include "conversions.h"
using namespace boost::filesystem;

class statistics
{
public:

    // default constructor
    statistics();

    // function to return map of file names and sizes of files in a directory
    std::unordered_map<std::string,uintmax_t> directoryFilesSizes(const path& directortyPath);

    // function to return map of file types and count of each type in a directory
    std::unordered_map<std::string,uintmax_t> directoryFilesTypes(const path& directortyPath);

    // static function to get the current directory path
    static path getCurrentPath();

    // static function to get the size of a directory
    static uintmax_t directory_size(std::string directory_path);

    // static function to get the number of files/directories in a given path
    static int numberOfItems(std::string& givenPath);

    // static function to detemine the selected path is file or not
    static bool isFile(std::string givenPath);

    //static function to determine the size of a selected path
    static uintmax_t getFile_size(std::string& givenPath);




};

#endif // STATISTICS_H
