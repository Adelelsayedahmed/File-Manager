#ifndef UTILITIES_H
#define UTILITIES_H

#include <QDebug>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <filesystem>
#include <unistd.h>
namespace fs = boost::filesystem;
class utilities
{
public:
    static void del(fs::path filePath);
    static std::string removeNameFromPath(std::string path);
    static void pasteToUndoCut(fs::path source_path, fs::path destination_path);
    static void CreateDirectory(const fs::path &myPath);
};

#endif // UTILITIES_H
