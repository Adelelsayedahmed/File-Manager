#ifndef ADDONSBAR_H
#define ADDONSBAR_H

#include <QWidget>
#include <QToolBar>
#include <QGridLayout>
#include <QMessageBox>
#include <boost/filesystem.hpp>

class addOnsBar : public QWidget
{
    Q_OBJECT
public:
    explicit addOnsBar(QWidget *parent = nullptr);

    QAction* addToTheBar(QString &path,QString& actionName);

    void connectAction(QAction *action, const QObject *receiver, const char *slot);

    QAction* identifyDuplicatesAction;



public slots:
    void identifyDuplicatesActionSlot();

//    void showDuplicatesMessage();

private:
    void setConnections();
    QToolBar *toolbar;
    QHBoxLayout *layout;
signals:
    void identifyDuplictesIconCLicked();
};

#endif // ADDONSBAR_H
