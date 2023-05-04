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

#ifndef CopyCutAction_H
#define CopyCutAction_H
enum class CopyCutAction {
    Copy,
    Cut,
    CopyDirectory,
    BatchRename,
    Delete
};
#endif
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
    Undo();
private:
    std::stack<std::vector<std::string>> paths_Bathc_Rename;
    std::stack<fs::path> paths_CUT_COPY;
    std::stack<CopyCutAction> actions;
    std::stack<DeletedItem> deleted_items;

    fs::path m_cutPath;

    void cutFile(const fs::path &path);
    void pasteFromCut(fs::path destination_path);
    void paste(fs::path source_path, fs::path destination_path, CopyCutAction action);
    void del(fs::path filePath);
    void undoCut();
    void undoCopy();
    void undoBatchRename();
    void undoDeleteItems();
    std::string removeNameFromPath(std::string path);
public slots :
    void undo();
    void addActions(CopyCutAction action);
    void addPaths_CUT(fs::path oldPath,fs::path newPath);
    void addPaths_COPY(fs::path current_path);
    void addPaths_BatchRename(std::vector<std::string> oldPaths, std::vector<std::string> newNames);
    void addDeletedItems(DeletedItem deleted_item);
};

#endif // UNDO_H
