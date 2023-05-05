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
                    "}"
                    "QToolButton {"
                    "    margin-right: 15px;"
                    "}";

    toolbar->setStyleSheet(style);

    QString parentPath=QString::fromStdString(boost::filesystem::path(__FILE__).parent_path().string());
//    qDebug() <<parentPath;
    QString path=parentPath + "/duplicatesIcon.png";
    QString name="duplicates";
    QPixmap image(path);
    QIcon icon(image);
    identifyDuplicatesAction = new QAction(icon, "duplicates", this);
    toolbar->addAction(identifyDuplicatesAction);

    toolbar->setIconSize(QSize(42, 42));

    createActions();

    for (auto& action : actions) {
        qDebug() << "here in for loop";
        toolbar->addAction(action);
    }
    disableAction(0);

    setConnections();
    layout->addWidget(toolbar);

}
void addOnsBar::createActions()
{
    QString parentPath = QString::fromStdString(boost::filesystem::path(__FILE__).parent_path().string());
    qDebug() << parentPath;

    QString path1 = parentPath + "/explorerIcon.png";
    QString name1 = "explorer";

    actions.append(addToTheBar(path1,name1));


    QString path2 = parentPath + "/duplicatesIcon.png";
    QString name2 = "identify duplicates";

    actions.append(addToTheBar(path2,name2));


    QString path3 = parentPath + "/twoPaneIcon.png";
    QString name3 = "two pane";

    actions.append(addToTheBar(path3,name3));


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
    connect(actions.at(0), &QAction::triggered, this, &addOnsBar::explorerActionSlot);

    connect(actions.at(1), &QAction::triggered, this, &addOnsBar::identifyDuplicatesActionSlot);

    connect(actions.at(2), &QAction::triggered, this, &addOnsBar::twoPaneActionSlot);

}
void addOnsBar::explorerActionSlot()
{
    emit explorerClicked();
}

void addOnsBar::identifyDuplicatesActionSlot()
{
    emit identifyDuplictesIconCLicked();
}


void addOnsBar::twoPaneActionSlot()
{
    emit twoPaneClicked();
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
