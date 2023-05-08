#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QObject>
#include "view.h"
#include <PiechartWidget.h>
#include "statistics.h"
#include "propertiespagewidget.h"
#include "piechartpagewidget.h"
#include "identifyduplicates.h"
#include "identifyduplicatespagewidget.h"
#include "searchwindow.h"
#include "Constants.h"

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
#include "undocontroller.h"
#include "undo.h"
#include "undorename.h"
#include "customtable.h"

namespace fs = boost::filesystem;
class Controller : public QObject
{
    Q_OBJECT
public:
    Controller();
    Controller(View* view);
     ~Controller();
private:
    View *dView;
    fs::path m_cutPath;
    fs::path m_tempCutPath;
    FileOperations *fileOperations;
    SearchWindow *dWindow;
    void pasteFromCut(fs::path destination_path);
    void mRegisterSignals();
    UndoController* undoController;


public slots:
    void paste(fs::path source_path, fs::path destination_path, CopyCutAction action);
    void del(fs::path filePath);
    void cutFile(const boost::filesystem::path& path);
    void createFile(const std::string& filename);
    void createDirectory(const std::string& dirname);

    void propertiesOfFile(const fs::path &path);
    void identifyDuplicates();

    void undoAction();
    void twoPaneSlot();
    void explorerSlot();
    void searchByContentSlot();

    void renameFileControllerSlot(const boost::filesystem::path &path , const std::string& newFileName);
    void batchRenamingControllerSlot( std::vector< std::string>& oldPaths,const std::string& newBaseName);

//    void renameFile(const boost::filesystem::path &path , const std::string newFileName);
    void SearchWindowCreated(SearchWindow *window);
    void SearchForFileByName(std::string starting_point_drictory_path , std::string file_name , std::vector<std::string>& file_paths);

    void batchCompressControllerSlot( std::vector< std::string>&Paths);
    void batchDecompressControllerSlot( std::vector< std::string>&Paths);


    void StackedWidgetSwitchedDisable(int index);
    void StackedWidgetSwitchedEnable(int index);
    void searchInMultiplefiles(const std::vector<std::string>& filePaths, const std::string& searchStr);





};

#endif // CONTROLLER_H
