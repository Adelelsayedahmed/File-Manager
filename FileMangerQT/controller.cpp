#include "controller.h"
Controller::Controller(View *view)
{
    dView = view;
    mRegisterSignals();
}

void Controller::mRegisterSignals()
{
    QObject::connect(dView, &View::copyFile, this, &Controller::paste);
    QObject::connect(dView, &View::delFile, this, &Controller::delFile);
    QObject::connect(dView, &View::cutFile, this, &Controller::cutFile);
}

void Controller::paste(fs::path source_path, fs::path destination_path, CopyCutAction action)
{
    if(action == CopyCutAction::Copy)
    {
        try {
            fs::path pathObj(source_path);
            std::string directoryName = pathObj.filename().string();
            destination_path = destination_path / directoryName;
            // Check if source file exists
            if (!fs::exists(source_path)) {
                qInfo() << "Source file does not exist!\n" ;
                return ;
            }
            if (fs::is_directory(source_path))
            {
//                if (!fs::create_directory(destination_path)) {
//                    throw std::runtime_error("Failed to create destination directory");
//                }
                try {
                    fs::copy(source_path, destination_path, fs::copy_options::recursive);
                }
                catch (std::exception& e) { // Not using fs::filesystem_error since std::bad_alloc can throw too.
                    // Handle exception or use error code overload of fs::copy.
                }

            }
            else
            {
                destination_path = destination_path / source_path.filename();
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
        if (fs::is_directory(filePath))
        {
            try {
                fs::remove_all(filePath);
                qInfo() << "directory deleted successfully!";
            } catch (const std::exception& ex) {
                std::cerr << "Error deleting directory: " << ex.what() << std::endl;
            }
        }
        else
        {
            fs::remove(filePath);
            qInfo() << "File deleted successfully!";
        }


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
