
#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QObject>
#include "view.h"
#include "searchwindow.h"
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <filesystem>
#include <QDebug>
#include <iostream>

#include <string>
#include <stack>
#include <vector>


namespace fs = boost::filesystem;
class Controller : public QObject
{
    Q_OBJECT
public:
    Controller();
    Controller(View* view);
    void addPaths(std::vector<std::string>oldPaths,std::vector<std::string> newPaths);

private:
    std::stack<std::vector<std::string>> paths;
    View *dView;
    SearchWindow *dSearchWindow;
    fs::path m_cutPath;
    fs::path m_tempCutPath;
    void pasteFromCut(fs::path destination_path);

    void mRegisterSignals();
public slots:
    void paste(fs::path source_path, fs::path destination_path, CopyCutAction action);
    void del(fs::path filePath);
    void cutFile(const boost::filesystem::path& path);
    void renameFileControllerSlot(const boost::filesystem::path &path , const std::string newFileName);
    void batchRenamingControllerSlot( std::vector< std::string>& oldPaths,const std::string& newBaseName);
    void undoRename();
    void searchWindwCreated(SearchWindow *search);
    void searchForFileByName(std::string starting_point_drictory_path , std::string file_name , std::vector<std::string>& file_paths);

};

#endif // CONTROLLER_H
