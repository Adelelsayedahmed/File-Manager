#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include <QObject>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include "Actions.h"
#include <QDebug>
#include <iostream>
#include "compression.h"
#include "undo.h"
#include "undocopy.h"
#include "undocut.h"
#include"undobatchrenaming.h"
#include "undocontroller.h"
#include "undodelete.h"
#include "undocreatedirectory.h"
#include "undocreatefile.h"
#include "contentfilessearch.h"
#include <filesystem>
namespace fs = boost::filesystem;

class FileOperations: public QObject
{
public:
    FileOperations();
    ~FileOperations();
    void paste(fs::path source_path, fs::path destination_path, CopyCutAction action);
    void del(fs::path filePath);
    void d(fs::path p);
    void cutFile(const fs::path &path);
    void renameFile(const boost::filesystem::path &path ,const std::string& newFileName );
    void batchRenameFile( std::vector< std::string>& oldPaths,const std::string &newBaseName);
    void batchCompression(std::vector< std::string>& Paths);
    void batchDecompression(std::vector< std::string>& Paths);
    void SearchForFileByName(std::string starting_point_drictory_path , std::string file_name , std::vector<std::string>& file_paths);
    void createFile(const std::string& filename);
    void createDirectory(const std::string& dirname);
    std::multimap<int, std::string> SearchContentInFiles(const std::vector<std::string> &filePaths, const std::string &searchStr);
    void setUndoController(UndoController *undoController);
    static const std::string& getDeletePath();
private:
    compression* compressionOperationsObj ;
    contentFilesSearch* contFileSearchObj ;
    fs::path m_cutPath;
    void pasteFromCut(fs::path destination_path);
    std::string removeNameFromPath(std::string path);
    void copy_directory(const fs::path &source_path, const fs::path &destination_path);
    UndoController * undoController;
    bool Delete=0;
    static std::string path_for_delete;
};
#endif // FILEOPERATIONS_H
