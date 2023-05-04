#include "fileoperations.h"

FileOperations::FileOperations()
{

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
