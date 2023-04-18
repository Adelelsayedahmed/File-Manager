#include "controller.h"
#include <string>
Controller::Controller(View *view)
{
    dView = view;
    mRegisterSignals();
}

void Controller::mRegisterSignals()
{
//    connect(dView->contentUi->ui->saveAction &QAction::triggered, this, &FileContentView::on_saveAction_triggered);
    QObject::connect(dView, &View::copyFile, this, &Controller::copyFile);
    QObject::connect(dView, &View::delFile, this, &Controller::delFile);
    QObject::connect(dView, &View::cutFile, this, &Controller::cutFile);
    QObject::connect(dView, &View::renameFileViewSignal, this, &Controller::renameFileControllerSlot);
    QObject::connect(dView, &View::batchRenameViewSignal, this, &Controller::batchRenamingControllerSlot);



}

void Controller::copyFile(fs::path source_path, fs::path destination_path, CopyCutAction action)
{
    if(action == CopyCutAction::Copy)
    {
        try {
            destination_path = destination_path / source_path.filename();
            // Check if source file exists
            if (!fs::exists(source_path)) {
                qInfo() << "Source file does not exist!\n" ;
                return ;
            }
            std::cout << destination_path;
            // Check if destination file exists
            if (fs::exists(destination_path)) {
                qInfo() << "Destination file already exists!\n";
                return ;
            }

            // Copy the file
            fs::copy_file(source_path, destination_path);

            std::cout << destination_path;
            qInfo() << "File copied successfully.\n";
            return ;
        }
        catch (const std::exception& ex) {
            qInfo() << "Error: " ;
        }
    }
    else if(action == CopyCutAction::Cut)
    {
        if (m_cutPath.empty()) {
            return; // Nothing to paste
        }
            boost::filesystem::rename(m_cutPath, destination_path / m_cutPath.filename());
            m_cutPath.clear();
    }

}

void Controller::delFile(boost::filesystem::path filePath)
{
    if (!fs::exists(filePath))
    {
        qInfo() << "File does not exist!";
        return ;
    }
    try
    {
        // Remove the file
        fs::remove(filePath);
        qInfo() << "File deleted successfully!";
    }
    catch (fs::filesystem_error const &e)
    {
        qInfo() << "Error deleting file: ";
    }
}

void Controller::cutFile(const boost::filesystem::path &path)
{
    m_cutPath = path;
//    m_tempCutPath = path.parent_path() / (path.filename().string() + ".tmp");
//    fs::copy(path, m_tempCutPath);
//    delFile(path);
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


void Controller::batchRenamingControllerSlot( std::vector< boost::filesystem::path>& oldPaths,const std::string &newBaseName){
    unsigned int counter = 1 ;
    std::string tempName ;
    for ( auto & path : oldPaths)
    {
        tempName = newBaseName ;
        Controller::renameFileControllerSlot(path,tempName.append(std::to_string(counter++)));
    }

}

