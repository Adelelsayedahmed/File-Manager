#ifndef UNDO_H
#define UNDO_H
#include <iostream>
#include <QObject>
#include <QDebug>

#include<stack>
#include <vector>
#include <string>

#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <filesystem>

namespace fs = boost::filesystem;
#define PATH "/Recycle Bin"

//enum class CopyCutAction{
//    Copy,
//    Cut,
//    CopyDirectory,
//    BatchRename,
//    Delete
//};

#ifndef DeletedItem_H
#define DeletedItem_H
struct DeletedItem {
    fs::path path;
    std::string contents;
};
#endif
class Undo : public QObject
{
    Q_OBJECT
public:
    virtual void undo()=0;

private:
    std::stack<std::vector<std::string>> paths_Bathc_Rename;
    std::stack<fs::path> paths_CUT_COPY;
    //std::stack<CopyCutAction> actions;
    std::stack<DeletedItem> deleted_items;

    fs::path m_cutPath;

    void cutFile(const fs::path &path);
    void pasteFromCut(fs::path destination_path);
    //void paste(fs::path source_path, fs::path destination_path, CopyCutAction action);
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
    bool success = boost::filesystem::create_directory(myPath);
    if (success) {
        std::cout << "Directory created successfully!" << std::endl;
    } else {
        std::cout << "Directory creation failed." << std::endl;
    }
}


    void undoCut();
    void undoCopy();
    void undoBatchRename();
    void undoDeleteItems();
   // std::string removeNameFromPath(std::string path);
public slots :
   // void undo();
    //void addActions(CopyCutAction action);
//    void addPaths_CUT(fs::path oldPath,fs::path newPath);
//    void addPaths_COPY(fs::path current_path);
//    void addPaths_BatchRename(std::vector<std::string> oldPaths, std::vector<std::string> newNames);
//    void addDeletedItems(DeletedItem deleted_item);
};

#endif // UNDO_H
