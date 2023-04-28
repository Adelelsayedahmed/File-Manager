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
//    void showDuplicatesMessage();

private:
    QToolBar *toolbar;
    QHBoxLayout *layout;
signals:

};

#endif // ADDONSBAR_H