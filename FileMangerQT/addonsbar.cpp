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
    toolbar->setIconSize(QSize(40, 40));

    createActions();

    for (auto& action : actions) {
        qDebug() << "here in for loop";
        toolbar->addAction(action);
    }

    setConnections();
    layout->addWidget(toolbar);

}
void addOnsBar::createActions()
{
    QString parentPath = QString::fromStdString(boost::filesystem::path(__FILE__).parent_path().string());
    qDebug() << parentPath;

    QString path = parentPath + "/duplicatesIcon.png";
    QString name = "identify duplicates";

    actions.append(addToTheBar(path,name));


    // add two pane and explorer actions here
}

void addOnsBar::disableAction(int index)
{
    actions.at(index)->setEnabled(false);
}
void addOnsBar::enableAction(int index)
{
    actions.at(index)->setEnabled(true);
}
void addOnsBar::setConnections()
{
    connect(actions.at(0), &QAction::triggered, this, &addOnsBar::identifyDuplicatesActionSlot);
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
