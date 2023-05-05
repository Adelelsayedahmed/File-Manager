#include "view.h"
#include "controller.h"
#include <QApplication>
#include <string>
#include <vector>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    View w;
    Controller c(&w);
    w.show();


    std::vector<std::string> filePaths;


//    // Add some dummy file paths to the vector
//    filePaths.push_back("/home/adel/playing/file1.txt");
//    filePaths.push_back("/home/adel/playing/file2.txt");

//    c.searchInMultiplefiles(filePaths,"adel");







    return a.exec();
}
