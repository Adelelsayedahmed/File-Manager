#include "controller.h"

Controller::Controller()
{

}


Controller::Controller(View *view)
{
    dView = view;
    mRegisterSignals();
}



void Controller::mRegisterSignals()
{
//    QObject::connect(dView, &View::copyFile, this, &Controller::paste);
    QObject::connect(dView, &View::delFile, this, &Controller::del);
    QObject::connect(dView, &View::cutFile, this, &Controller::cutFile);
    QObject::connect(dView, &View::renameFileViewSignal, this, &Controller::renameFileControllerSlot);
    QObject::connect(dView, &View::batchRenameViewSignal, this, &Controller::batchRenamingControllerSlot);
    QObject::connect(dView, &View::propertiesOfFile,this,&Controller::propertiesOfFile);



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
    if (!fs::exists(source_path)) {
        qInfo() << "Source file does not exist!\n" ;
        return ;
    }
    if(action == CopyCutAction::Copy)
    {
        try {
            destination_path = destination_path / source_path.filename();
            if (fs::exists(destination_path)) {
                qInfo() << "Destination already exists!\n";
                return ;
            }
            if (fs::is_directory(source_path))
            {
                fs::copy(source_path, destination_path, fs::copy_options::recursive);
            }
            else
            {
                fs::copy_file(source_path, destination_path);
            }
            return ;
        }
        catch (const std::exception& ex) {
            qInfo() << "Error: "  ;
            std::cout<<destination_path;
        }
    }
    else if(action == CopyCutAction::Cut)
    {
        destination_path = destination_path / m_cutPath.filename();
        pasteFromCut(destination_path);
    }
}
void Controller::pasteFromCut(fs::path destination_path)
{
    try {
        if (fs::exists(destination_path)) {
            qInfo() << "Destination already exists!\n";
            return;
        }

        if (m_cutPath.empty()) {
            return; // Nothing to paste
        }

        fs::rename(m_cutPath, destination_path);
        m_cutPath.clear();

    } catch (const std::exception& ex) {
        qInfo() << "Error: " << ex.what() << '\n';
    }
}

void Controller::del(fs::path filePath)
{
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

void Controller::cutFile(const fs::path &path)
{
    m_cutPath = path;
}

void Controller::propertiesOfFile(const fs::path &path)
{
    qDebug() <<"here in the properties slot of controller";
       statistics *statObj = new statistics;

        pieChartPageWidget *pieChartWidget = new pieChartPageWidget(dView);
       PropertiesPageWidget* propertiesWidget = new PropertiesPageWidget(dView, statObj, pieChartWidget);
        qDebug() << path.string();
        propertiesWidget->path=path;

        propertiesWidget->showPropertiesWindow();

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







void Controller::SearchForFileByName(std::string starting_point_drictory_path , std::string file_name , std::vector<std::string>& file_paths)
{
    for (const auto & file: std::filesystem::directory_iterator(starting_point_drictory_path)) {

        if(file.is_regular_file())
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

