#include "fileoperations.h"

FileOperations::FileOperations()
{

}
void FileOperations::paste(fs::path source_path, fs::path destination_path, CopyCutAction action)
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
void FileOperations::cutFile(const fs::path &path)
{
    m_cutPath = path;
}
