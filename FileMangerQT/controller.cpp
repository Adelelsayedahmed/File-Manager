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
