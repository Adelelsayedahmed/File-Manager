#ifndef UNDO_H
#define UNDO_H
#include <iostream>
#include <QObject>
#include <QDebug>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <filesystem>
#include <unistd.h>
namespace fs = boost::filesystem;
class Undo
{
public:
    virtual void undo()=0;

private:
    fs::path m_cutPath;
public:
    static void del(fs::path filePath){
       if (!fs::exists(filePath))
       {
           qInfo() << "File does not exist!";
           return ;
       }
       try
       {
           if (fs::is_directory(filePath))
           {

               fs::remove_all(filePath);
               qInfo() << "directory deleted successfully!";
           }
           else
           {
               fs::remove(filePath);
               qInfo() << "File deleted successfully!";
           }
       }
       catch (const std::exception& ex)
       {
           qInfo() << "Error deleting";
       }
    }
static std::string removeNameFromPath(std::string path) {
    size_t found = path.find_last_of("/\\");
    if (found != std::string::npos) {
        return path.substr(0, found+1);
    }
    return path;
 }

static void pasteToUndoCut(fs::path source_path, fs::path destination_path)
{
    if (!fs::exists(source_path)) {
        qInfo() << "Source file does not exist!\n" ;
        return ;
    }
     destination_path = destination_path / source_path.filename();
    try {
        if (fs::exists(destination_path)) {
            qInfo() << "Destination already exists!\n";
            return;
        }

        if (source_path.empty()) {
            return; // Nothing to paste
        }

        fs::rename(source_path, destination_path);
        source_path.clear();
    }
    catch (const std::exception& ex) {
        qInfo() << "Error: " << ex.what() << '\n';
    }
}
static void CreateDirectory(const fs::path &myPath){
    qDebug()<< myPath.string()<<"path in create directory\n";
    bool success ;
    try{
        success = boost::filesystem::create_directory(myPath);
        qInfo()<< "Directory creation success and path :";
        qDebug()<< myPath.string();
    }
    catch (const std::exception& ex)
    {
        qInfo() << "Error creating directory";
    }
}
};
#endif // UNDO_H
