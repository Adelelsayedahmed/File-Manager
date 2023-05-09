#include "utilities.h"
void utilities::del(boost::filesystem::path filePath)
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

std::string utilities::removeNameFromPath(std::string path)
{

    size_t found = path.find_last_of("/\\");
    if (found != std::string::npos) {
        return path.substr(0, found+1);
    }
    return path;

}

void utilities::pasteToUndoCut(boost::filesystem::path source_path, boost::filesystem::path destination_path)
{

    if (!fs::exists(source_path)) {
        qInfo() << "Source file does not exist!\n" ;
        return ;
    }
    destination_path = destination_path / source_path.filename();
    try {
        if (fs::exists(destination_path)) {
            qInfo() << "Destination already exists!\n";
            return;
        }

        if (source_path.empty()) {
            return; // Nothing to paste
        }

        fs::rename(source_path, destination_path);
        source_path.clear();
    }
    catch (const std::exception& ex) {
        qInfo() << "Error: " << ex.what() << '\n';
    }

}

void utilities::CreateDirectory(const boost::filesystem::path &myPath)
{

    qDebug()<< myPath.string()<<"path in create directory\n";
    bool success ;
    try{
        success = boost::filesystem::create_directory(myPath);
        qInfo()<< "Directory creation success and path :";
        qDebug()<< myPath.string();
    }
    catch (const std::exception& ex)
    {
        qInfo() << "Error creating directory";
    }

}
