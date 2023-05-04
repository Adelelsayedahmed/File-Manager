#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QObject>
#include "view.h"
//#include <PiechartWidget.h>
#include "statistics.h"
//#include "propertiespagewidget.h"
//#include "piechartpagewidget.h"
#include "identifyduplicates.h"
#include "identifyduplicatespagewidget.h"
#include "searchwindow.h"

#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <filesystem>
#include <QDebug>
#include <iostream>

#include <string>
#include <stack>
#include <vector>
#include "fileoperations.h"
#include<thread>
#include "customtable.h"

namespace fs = boost::filesystem;
class Controller : public QObject
{
    Q_OBJECT
public:
    Controller();
    Controller(View* view);
    void addPaths(std::vector<std::string>oldPaths,std::vector<std::string> newPaths);
     ~Controller();
private:
    std::stack<std::vector<std::string>> paths;
    View *dView;
    fs::path m_cutPath;
    fs::path m_tempCutPath;
    FileOperations *fileOperations;
    SearchWindow *dWindow;
    void pasteFromCut(fs::path destination_path);
    void mRegisterSignals();



public slots:
    void paste(fs::path source_path, fs::path destination_path, CopyCutAction action);
    void del(fs::path filePath);
    void cutFile(const boost::filesystem::path& path);

    void propertiesOfFile(const fs::path &path);
    void identifyDuplicates();


    void renameFileControllerSlot(const boost::filesystem::path &path , const std::string& newFileName);
    void batchRenamingControllerSlot( std::vector< std::string>& oldPaths,const std::string& newBaseName);

    void undoRename();

//    void renameFile(const boost::filesystem::path &path , const std::string newFileName);
    void SearchWindowCreated(SearchWindow *window);
    void SearchForFileByName(std::string starting_point_drictory_path , std::string file_name , std::vector<std::string>& file_paths);

    void batchCompressControllerSlot( std::vector< std::string>&Paths);
    void batchDecompressControllerSlot( std::vector< std::string>&Paths);

    void StackedWidgetSwitchedDisable(int index);
    void StackedWidgetSwitchedEnable(int index);


};

#endif // CONTROLLER_H
