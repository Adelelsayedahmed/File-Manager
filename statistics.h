#ifndef STATISTICS_H
#define STATISTICS_H

#include <boost/filesystem.hpp>
#include <unordered_map>
#include <string>
#include <QDebug>

using namespace boost::filesystem;

class statistics
{
public:

    // default constructor
    statistics();

    // function to return map of file names and sizes of files in a directory
    std::unordered_map<std::string,int> directoryFilesSizes(const path& directortyPath);

    // function to return map of file types and count of each type in a directory
    std::unordered_map<std::string,int> directoryFilesTypes(const path& directortyPath);

    // static function to get the current directory path
    static path getCurrentPath();

    // static function to get the size of a directory
    static uintmax_t directory_size(const path& directory_path);

private:
    // function to convert from bytes to kilo bytes
    int convertToKB(uintmax_t bytes);

};

#endif // STATISTICS_H
