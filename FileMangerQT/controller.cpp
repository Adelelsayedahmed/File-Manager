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
//    QObject::connect(dView->explorer, &ExplorerMin::copyFile, this, &Controller::paste);
    QObject::connect(dView->explorer, &ExplorerMin::delFile, this, &Controller::del);
    QObject::connect(dView->explorer, &ExplorerMin::cutFile, this, &Controller::cutFile);
    QObject::connect(dView->explorer, &ExplorerMin::renameFileViewSignal, this, &Controller::renameFileControllerSlot);
    QObject::connect(dView->explorer, &ExplorerMin::batchRenameViewSignal, this, &Controller::batchRenamingControllerSlot);
    QObject::connect(dView->explorer, &ExplorerMin::propertiesOfFile,this,&Controller::propertiesOfFile);
    QObject::connect(dView->explorer, &ExplorerMin::SearchWindowCreated, this, &Controller::SearchWindowCreated);
    QObject::connect(dView->explorer, &ExplorerMin::identifyDuplictesIconCLicked, this, &Controller::Controller::identifyDuplicates);

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
    fileOperations->paste(source_path, destination_path, action);
}


void Controller::del(fs::path filePath)
{
    fileOperations->del(filePath);
}

void Controller::cutFile(const fs::path &path)
{
   fileOperations->cutFile(path);
}

void Controller::propertiesOfFile(const fs::path &path)
{
//        statistics *statObj = new statistics;

//        pieChartPageWidget *pieChartWidget = new pieChartPageWidget(dView->explorer);

//        PropertiesPageWidget* propertiesWidget = new PropertiesPageWidget(dView->explorer, statObj, pieChartWidget);

//        propertiesWidget->path=path;

//        propertiesWidget->showPropertiesWindow();

}

std::string removeNameFromPath(std::string path) {
    size_t found = path.find_last_of("/\\");
    if (found != std::string::npos) {
        return path.substr(0, found+1);
    }
    return path;
}


void Controller::renameFileControllerSlot(const boost::filesystem::path &path ,const std::string newFileName )
{
    qInfo() << "File path = " << QString::fromStdString(path.string()) <<"  " << QString::fromStdString(newFileName);
    std::string temp_path = removeNameFromPath(path.string());
    std::string new_path_str  = temp_path + newFileName ;

    qInfo() << "File path = " << QString::fromStdString(temp_path) << QString::fromStdString(new_path_str);
    fs::path new_path_p(new_path_str);
    try
    {
        fs::rename(path,new_path_p);
    }
    catch (const std::exception& ex) {
    std::cerr << "Error renaming file: " << ex.what() << std::endl;    }

}

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
    unsigned int counter = 1 ;

    /*to be used by wafyola*/
    std::vector< std::string> new_paths ;
    std::string tempName ;
    for ( auto & path : oldPaths)
    {
        tempName = newBaseName ;
        Controller::renameFileControllerSlot(path,tempName.append(std::to_string(counter)));
        new_paths.push_back(tempName.append(std::to_string(counter)));
        counter++;
    }
    addPaths( oldPaths,new_paths);
}

void Controller::identifyDuplicates()
{
//    IdentifyDuplicates* dupsObj=new IdentifyDuplicates;

//    IdentifyDuplicatesPageWidget *pageWidget = new IdentifyDuplicatesPageWidget(dView->explorer,dupsObj);

}


void Controller::SearchWindowCreated(SearchWindow *search)
{
    dWindow = search;
    QObject::connect(dWindow, &SearchWindow::searchForFileByName, this, &Controller::SearchForFileByName);

}


void Controller::SearchForFileByName(std::string starting_point_drictory_path , std::string file_name , std::vector<std::string>& file_paths)
{
    for (const auto & file: std::filesystem::directory_iterator(starting_point_drictory_path)) {

//      if(file.is_regular_file())
        {
            std::string searchbyname = file.path();
            if(searchbyname.find(file_name)!= std::string::npos)
                file_paths.push_back(searchbyname);
        }
    }
    for (const auto & file: std::filesystem::directory_iterator(starting_point_drictory_path)) {

        if(file.is_directory())
        {
           SearchForFileByName(file.path() , file_name , file_paths);
        }
    }
}

