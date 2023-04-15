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
    statistics();

    std::unordered_map<std::string,int> directoryFilesSizes(const path& directortyPath);

    std::unordered_map<std::string,int> directoryFilesTypes(const path& directortyPath);

    static path getCurrentPath();

    uintmax_t directory_size(const path& directory_path);

    int convertToKB(uintmax_t bytes);

};

#endif // STATISTICS_H
