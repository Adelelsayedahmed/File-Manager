#include "addonsbar.h"

addOnsBar::addOnsBar(QWidget *parent)
    : QWidget{parent}
{
    layout=new QHBoxLayout(this);
    toolbar = new QToolBar(this);
    QString style = "QToolBar {"
                    "    border: 2px solid black;"
                    "    border-top-left-radius: 5px;"
                    "    border-top-right-radius: 5px;"
                    "    padding: 10px;"
                    "}";

    toolbar->setStyleSheet(style);
    toolbar->setIconSize(QSize(32, 32));

    QString parentPath=QString::fromStdString(boost::filesystem::path(__FILE__).parent_path().string());
    qDebug() <<parentPath;
    QString path=parentPath + "/duplicatesIcon.png";
    QString name="duplicates";
    QPixmap image(path);
    QIcon icon(image);
    identifyDuplicatesAction = new QAction(icon, "duplicates", this);
    toolbar->addAction(identifyDuplicatesAction);
    setConnections();
    layout->addWidget(toolbar);

}
void addOnsBar::setConnections()
{
    connect(identifyDuplicatesAction, &QAction::triggered, this, &addOnsBar::identifyDuplicatesActionSlot);
}

void addOnsBar::identifyDuplicatesActionSlot()
{
    emit identifyDuplictesIconCLicked();
}
QAction* addOnsBar::addToTheBar(QString &path,QString& actionName)
{
    QPixmap image(path);
    QIcon icon(image);
    QAction *action = new QAction(icon, actionName, this);
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
