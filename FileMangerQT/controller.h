#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "view.h"
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <filesystem>
#include <QDebug>
#include <iostream>
namespace fs = boost::filesystem;
class Controller : public QObject
{
    Q_OBJECT
public:
    Controller(View* view);

private:
    View *dView;
    fs::path m_cutPath;
    fs::path m_tempCutPath;

    void mRegisterSignals();
public slots:
    void paste(fs::path source_path, fs::path destination_path, CopyCutAction action);
    void delFile(fs::path filePath);
    void cutFile(const boost::filesystem::path& path);
    void renameFile(const boost::filesystem::path &path , const std::string newFileName);
};

#endif // CONTROLLER_H
