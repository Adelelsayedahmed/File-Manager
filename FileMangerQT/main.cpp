#include "view.h"
#include "controller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    View w;
    Controller c(&w);
    w.show();
    return a.exec();
}
