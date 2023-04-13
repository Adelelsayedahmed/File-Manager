#include "controller.h"
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
//    QObject::connect(dView, &View::cutFile, this, &Controller::cutFile);

}

void Controller::copyFile(fs::path source_path, fs::path destination_path)
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
    m_tempCutPath = path.parent_path() / (path.filename().string() + ".tmp");
    boost::filesystem::copy(path, m_tempCutPath);
    boost::filesystem::remove(path);
}
