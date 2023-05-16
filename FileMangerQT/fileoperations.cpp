#include "fileoperations.h"

FileOperations::FileOperations()
{
    compressionOperationsObj = new compression ();
}

FileOperations::~FileOperations()
{
    delete compressionOperationsObj ;
    delete contFileSearchObj ;
}

void FileOperations::copy_directory(const fs::path& source_path, const fs::path& destination_path)
{
    // Create destination directory if it does not already exist
    if (!fs::exists(destination_path))
    {
        fs::create_directories(destination_path);
    }

    // Copy all files in the source directory to the destination directory
    for (const auto& entry : fs::directory_iterator(source_path))
    {
        const fs::path& source_sub_path = entry.path();
        const fs::path& destination_sub_path = destination_path / source_sub_path.filename();
        /*
         * this condition is made in case we are trying to copy a folder
         * inside another folder where they both have the same name so
         * we have to prevent the infinite loop
         */
        if(source_sub_path == destination_path)
            continue;
        if (fs::is_directory(source_sub_path))
        {
            // Recursively copy subdirectory
            copy_directory(source_sub_path, destination_sub_path);
        }
        else
        {
            // Copy file to destination directory
            fs::copy_file(source_sub_path, destination_sub_path);

        }
    }
}
std::string FileOperations::path_for_delete="";
void FileOperations::paste(fs::path source_path, fs::path destination_path, CopyCutAction action)
{
    qInfo()<<source_path.string();
    if (!fs::exists(source_path)) {
        qInfo() << "Source file does not exist!\n" ;
        return ;
    }
    if(action == CopyCutAction::Copy)
    {
        Undo * undo;
        std::vector<fs::path> paths;
        try {
            destination_path = destination_path / source_path.filename();
            if (fs::exists(destination_path)) {
                qInfo()<< destination_path.c_str();
                qInfo() << "Destination already exists!!\n";
                return ;
            }
            if (fs::is_directory(source_path))
            {
                qInfo()<<"destination is:";
                qInfo()<< destination_path.c_str();
                if (!fs::exists(destination_path))
                {
                    copy_directory(source_path,destination_path);
                }

            }
            else
            {
                fs::copy_file(source_path, destination_path);
            }
            paths.push_back(destination_path);
            undo= new UndoCopy(paths);
            undoController->addActions(undo);
            return ;
        }
        catch (const std::exception& ex) {
            qInfo() << "Error: " << ex.what();
            std::cout << "Destination path: " << destination_path << std::endl;
        }
    }
    else if(action == CopyCutAction::Cut)
    {
        if(Delete==true){
            fs::path  temp_path = path_for_delete / m_cutPath.filename();
            fs::path temp_source= m_cutPath;
            pasteFromCut(temp_path);
            Undo* undo =new undoDelete(temp_source,temp_path);
            undoController->addActions(undo);
        }
        else{
            //cut operation
            fs::path  temp_path = destination_path / m_cutPath.filename();
            fs::path temp_source= m_cutPath;
            pasteFromCut(temp_path);
            Undo* undo =new UndoCut(temp_source,temp_path);
            undoController->addActions(undo);
        }
    }
}
void FileOperations::pasteFromCut(fs::path destination_path)
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
void FileOperations::del(fs::path filePath)
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

void FileOperations::d(boost::filesystem::path p)
{
    Delete=true;
    std::string home_dir = std::getenv("HOME");
    if (home_dir.empty()) {
        std::cerr << "Error: could not get home directory path for user " << home_dir << '\n';
        return;
    }
    else{
        path_for_delete = home_dir +"/Recycle bin";
        qInfo()<< path_for_delete << "in fucntion d\n";
        utilities::CreateDirectory(path_for_delete);
        cutFile(p);
        paste(p,path_for_delete,CopyCutAction::Cut);
    }
    Delete=false;
}
void FileOperations::cutFile(const fs::path &path)
{
    m_cutPath = path;
}


void FileOperations:: SearchForFileByName(std::string starting_point_drictory_path , std::string file_name , std::vector<std::string>& file_paths)
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

void FileOperations::createFile(const std::string &filename)
{
    // Set the path and filename of the new file
    fs::path filepath(filename);

    // Create a new output file stream with the specified file path
    std::ofstream ofs(filepath);

    // Check if the file was successfully opened
    if (!ofs.is_open()) {
        throw std::runtime_error("Failed to create file: " + filename);
    }
    Undo *undoCreatefile = new UndoCreateFile(filepath);
    undoController->addActions(undoCreatefile );
    // Close the file stream
    ofs.close();
}

void FileOperations::createDirectory(const std::string& dirname) {
    // Set the path and directory name
    boost::filesystem::path dirpath(dirname);

    // Check if the directory already exists
    if (boost::filesystem::exists(dirpath)) {
        throw std::runtime_error("Directory already exists: " + dirname);
    }

    // Create the directory
    if (!boost::filesystem::create_directory(dirpath)) {
        throw std::runtime_error("Failed to create directory: " + dirname);
    }
    Undo *undoCreateDirectory = new undocreateDirectory(dirpath);
    undoController->addActions(undoCreateDirectory);
}
void FileOperations::renameFile(const boost::filesystem::path &path ,const std::string& newFileName ){
   // new_paths.push_back(newFileName);()
    qInfo() << "File path = " << QString::fromStdString(path.string()) <<"  " << QString::fromStdString(newFileName);
    std::string temp_path = removeNameFromPath(path.string());
    std::string new_path_str  = temp_path + newFileName ;

    qInfo() << "File path = " << QString::fromStdString(temp_path) << QString::fromStdString(new_path_str);
    fs::path new_path_p(new_path_str);
    try
    {
        fs::rename(path,new_path_p);
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Error renaming file: " << ex.what() << std::endl;
    }

}


void FileOperations::batchRenameFile( std::vector< std::string>& oldPaths,const std::string &newBaseName){
    unsigned int counter = 1 ;

    /*to be used by wafyola*/
    std::vector< std::string> new_names ;
    std::string tempName ;
    for ( auto & path : oldPaths)
    {
        tempName = newBaseName ;
        FileOperations::renameFile(path,tempName.append(std::to_string(counter)));
        new_names.push_back(tempName);
        counter++;
    }
    qInfo()  <<"Creating batch rename\n ";
    Undo *undo  = new UndoBatchRenaming(oldPaths,new_names);
    undoController->addActions(undo);
}

void FileOperations::compresshere(std::string &Paths)
{
    std::string path= compressionOperationsObj->compress_file_here(Paths);
    qDebug()<<"come back final in file operation"<<path;
    Undo *undo  = new undoCompressDecompress(path);
    undoController->addActions(undo);

}

void FileOperations::decompresshere(std::string &Paths)
{
   std::string path= compressionOperationsObj->decompress_file_here(Paths);
    Undo *undo  = new undoCompressDecompress(path);
    undoController->addActions(undo);
}

void FileOperations::batchCompression(std::vector<std::string> &Paths)
{
    compressionOperationsObj->batchCompress(Paths);
}

void FileOperations::batchDecompression(std::vector<std::string> &Paths)
{
    compressionOperationsObj->batchDecompress(Paths);
}

std::multimap<int, std::string> FileOperations::SearchContentInFiles(const std::vector<std::string> &filePaths, const std::string &searchStr)
{
    std::multimap<int, std::string> resultMap = contFileSearchObj->searchInMultiplefiles(filePaths,searchStr);
    return resultMap ;
}

void FileOperations::setUndoController(UndoController *undoController)
{
     this->undoController=undoController;
}

const std::string &FileOperations::getDeletePath()
{
     return path_for_delete;
}


std::string FileOperations:: removeNameFromPath(std::string path) {
    size_t found = path.find_last_of("/\\");
    if (found != std::string::npos) {
        return path.substr(0, found+1);
    }
    return path;
}
