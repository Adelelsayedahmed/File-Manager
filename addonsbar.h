#ifndef ADDONSBAR_H
#define ADDONSBAR_H

#include <QWidget>
#include <QToolBar>
#include <QGridLayout>
#include <QMessageBox>
class addOnsBar : public QWidget
{
    Q_OBJECT
public:
    explicit addOnsBar(QWidget *parent = nullptr);

    QAction* addToTheBar(QString &path,QString& actionName);

    void connectAction(QAction *action, const QObject *receiver, const char *slot);

public slots:
//    void showDuplicatesMessage();

private:
    QToolBar *toolbar;
signals:

};

#endif // ADDONSBAR_H
