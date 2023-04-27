#include "addonsbar.h"

addOnsBar::addOnsBar(QWidget *parent)
    : QWidget{parent}
{

    toolbar = new QToolBar(this);


}

QAction* addOnsBar::addToTheBar(QString &path,QString& actionName)
{
    QPixmap image(path);
    QIcon icon(image);
    QAction *action = new QAction(QIcon(path), actionName, this);
    toolbar->addAction(action);
    return action;

}
void addOnsBar::connectAction(QAction *action, const QObject *receiver, const char *slot)
{
    connect(action, SIGNAL(triggered()), receiver, slot);
}
//void addOnsBar::showDuplicatesMessage()
//{
//    QMessageBox::information(this, "Welcome", "Hello! You clicked the Duplicates action.");
//}
