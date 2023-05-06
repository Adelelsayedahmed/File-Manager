#include "view.h"
#include "controller.h"
#include <QApplication>
#include <string>
#include <vector>
#include <QDir>
#include <QLatin1String>
int main(int argc, char *argv[])
{
    QString filePath = QDir::currentPath();

    qInfo() <<filePath;
    QApplication a(argc, argv);
    QFile styleSheetFile("../FileMangerQT/QSS/MacOS.qss");

    if (!styleSheetFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Handle the error if the file cannot be opened
        qDebug() << "Failed to open file:" ;
    }

    QString stylesheet = QLatin1String(styleSheetFile.readAll()) ;
    qInfo()<<stylesheet;
    a.setStyleSheet(stylesheet);;
    View w;
    Controller c(&w);
    w.show();


    std::vector<std::string> filePaths;


    // Add some dummy file paths to the vector
//    filePaths.push_back("/home/adel/playing/file1.txt");
//    filePaths.push_back("/home/adel/playing/file2.txt");
//    c.searchInMultiplefiles(filePaths,"adel");











    return a.exec();
}
