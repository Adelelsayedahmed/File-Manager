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
    void undoCut();
    void undoCopy();
    void undoBatchRename();
    void undoDeleteItems();
    std::string removeNameFromPath(std::string path);
public slots :
   // void undo();
    //void addActions(CopyCutAction action);
//    void addPaths_CUT(fs::path oldPath,fs::path newPath);
//    void addPaths_COPY(fs::path current_path);
//    void addPaths_BatchRename(std::vector<std::string> oldPaths, std::vector<std::string> newNames);
//    void addDeletedItems(DeletedItem deleted_item);
};

#endif // UNDO_H
