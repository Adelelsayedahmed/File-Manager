#include "controller.h"

Controller::Controller()
{

}


Controller::Controller(View *view)
{
    dView = view;
    mRegisterSignals();
    fileOperations = new FileOperations();
}



void Controller::mRegisterSignals()
{
    QObject::connect(dView->stackedview->explorer, &ExplorerMin::copyFile, this, &Controller::paste);
    QObject::connect(dView->stackedview->explorer, &ExplorerMin::delFile, this, &Controller::del);
    QObject::connect(dView->stackedview->explorer, &ExplorerMin::cutFile, this, &Controller::cutFile);
    QObject::connect(dView->stackedview->explorer, &ExplorerMin::renameFileViewSignal, this, &Controller::renameFileControllerSlot);
    QObject::connect(dView->stackedview->explorer, &ExplorerMin::batchRenameViewSignal, this, &Controller::batchRenamingControllerSlot);
    QObject::connect(dView->stackedview->explorer, &ExplorerMin::propertiesOfFile,this,&Controller::propertiesOfFile);
    QObject::connect(dView->stackedview->explorer, &ExplorerMin::SearchWindowCreated, this, &Controller::SearchWindowCreated);
    QObject::connect(dView->stackedview->explorer, &ExplorerMin::identifyDuplictesIconCLicked, this, &Controller::Controller::identifyDuplicates);

    QObject::connect(dView->stackedview->explorer, &ExplorerMin::batchCompressViewSignal, this, &Controller::Controller::batchCompressControllerSlot);
    QObject::connect(dView->stackedview->explorer, &ExplorerMin::batchDecompressViewSignal, this, &Controller::Controller::batchDecompressControllerSlot);


}


Controller::~Controller()
{
    delete dView;
    delete fileOperations;
    delete dWindow;
}
/**
 * @brief Pastes a file or folder from the source path to the destination path.
 *
 * If the action is set to Copy, the file or folder at the source path is copied to the
 * destination path. If the action is set to Cut, the file or folder at the source path is
 * moved to the destination path. If the file or folder already exists at the destination path
 * during a Copy action, the function returns without pasting the file or folder.
 *
 * @param source_path The path of the file or folder to be pasted.
 * @param destination_path The path to where the file or folder should be pasted.
 * @param action The action to be performed: Copy or Cut.
 */

void Controller::paste(fs::path source_path, fs::path destination_path, CopyCutAction action)
{
    std::thread t(&FileOperations::paste, fileOperations, source_path, destination_path, action);
    t.detach();

}


void Controller::del(fs::path filePath)
{
        std::thread t(&FileOperations::del, fileOperations, filePath);
        t.detach();
}

void Controller::cutFile(const fs::path &path)
{
        std::thread t(&FileOperations::cutFile, fileOperations, path);
        t.join();
}

void Controller::propertiesOfFile(const fs::path &path)
{/*
        statistics *statObj = new statistics;

        pieChartPageWidget *pieChartWidget = new pieChartPageWidget(dView->explorer);

        PropertiesPageWidget* propertiesWidget = new PropertiesPageWidget(dView->explorer, statObj, pieChartWidget);

        propertiesWidget->path=path;

        propertiesWidget->showPropertiesWindow();*/

}

std::string removeNameFromPath(std::string path) {
    size_t found = path.find_last_of("/\\");
    if (found != std::string::npos) {
        return path.substr(0, found+1);
    }
    return path;
}


void Controller::renameFileControllerSlot(const boost::filesystem::path &path ,const std::string& newFileName )
{

        std::thread t(&FileOperations::renameFile, fileOperations, path, newFileName);
        t.detach();
}


/*This function will be deleted from here and will be used in Fileoperations.cpp instead */
void Controller::addPaths(std::vector<std::string> oldPaths, std::vector<std::string> newPaths)
{
    paths.push(oldPaths);
    paths.push(newPaths);
}

void Controller::undoRename()
{
   std::vector<std::string> oldPaths=paths.top();
   paths.pop();
   std::vector<std::string> newPaths=paths.top();
   paths.pop();
   for(int i=0;i<oldPaths.size();i++){
        fs::rename(oldPaths[i],newPaths[i]);
    }
}

void Controller::batchRenamingControllerSlot( std::vector< std::string>& oldPaths,const std::string &newBaseName){
   fileOperations->batchRenameFile(oldPaths, newBaseName);

}

void Controller::identifyDuplicates()
{
   // IdentifyDuplicates* dupsObj=new IdentifyDuplicates;

  //  IdentifyDuplicatesPageWidget *pageWidget = new IdentifyDuplicatesPageWidget(dView->explorer,dupsObj);

}


void Controller::SearchWindowCreated(SearchWindow *search)
{
    dWindow = search;
    QObject::connect(dWindow, &SearchWindow::searchForFileByName, fileOperations, &FileOperations::SearchForFileByName);

}


void Controller::SearchForFileByName(std::string starting_point_directory_path, std::string file_name, std::vector<std::string>& file_paths)
{
    std::thread t(&FileOperations::SearchForFileByName, fileOperations, starting_point_directory_path, file_name, std::ref(file_paths));
    t.detach();

}


void Controller::batchCompressControllerSlot(std::vector<std::string> &Paths)
{
        std::thread t(&FileOperations::batchCompression, fileOperations, std::ref(Paths));
        t.detach();
}

void Controller::batchDecompressControllerSlot(std::vector<std::string> &Paths)
{
        std::thread t(&FileOperations::batchDecompression, fileOperations, std::ref(Paths));
        t.detach();
}

