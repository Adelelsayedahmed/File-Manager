#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include <QObject>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include "Actions.h"
#include <QDebug>
#include <iostream>
#include "compression.h"
#include <filesystem>
namespace fs = boost::filesystem;

class FileOperations: public QObject
{
public:
    FileOperations();
    ~FileOperations();
    void paste(fs::path source_path, fs::path destination_path, CopyCutAction action);
    void del(fs::path filePath);
    void cutFile(const fs::path &path);
    void renameFile(const boost::filesystem::path &path ,const std::string& newFileName );
    void batchRenameFile( std::vector< std::string>& oldPaths,const std::string &newBaseName);
    void batchCompression(std::vector< std::string>& Paths);
    void batchDecompression(std::vector< std::string>& Paths);
    void SearchForFileByName(std::string starting_point_drictory_path , std::string file_name , std::vector<std::string>& file_paths);

private:
    compression* compressionOperationsObj ;
    fs::path m_cutPath;
    void pasteFromCut(fs::path destination_path);
    void addPaths(std::vector<std::string> oldPaths, std::vector<std::string> newPaths);
    std::string removeNameFromPath(std::string path);
};
#endif // FILEOPERATIONS_H
