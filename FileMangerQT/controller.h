#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "view.h"
#include <boost/filesystem.hpp>
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

    void mRegisterSignals();
public slots:
    void copyFile(fs::path source_path, fs::path destination_path);
    void delFile(fs::path filePath);
};

#endif // CONTROLLER_H
