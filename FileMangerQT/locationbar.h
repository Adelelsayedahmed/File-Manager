<<<<<<< Updated upstream
//#ifndef LOCATIONBAR_H
//#define LOCATIONBAR_H

//#include <QWidget>
//#include <QLineEdit>
//#include <QCompleter>
//#include <QFileSystemModel>

//class LocationBar : public QWidget
//{
//    Q_OBJECT
//public:
//    explicit LocationBar(QFileSystemModel model, QWidget *parent = nullptr);
//    QLineEdit  *locationBar;
//    QCompleter *completer;
//    QModelIndex dIndex;
//    QString dFilePath;

//public slots:
//    void locationBarChanged(QModelIndex index);

//signals:
//    void locationBarClicked(QString filepath);

//};

//#endif // LOCATIONBAR_H
=======
#ifndef LOCATIONBAR_H
#define LOCATIONBAR_H

#include <QWidget>
#include <QLineEdit>
#include <QCompleter>
#include <QFileSystemModel>

class LocationBar : public QWidget
{
    Q_OBJECT
public:
    explicit LocationBar(QFileSystemModel *model, QString path, QWidget *parent = nullptr);
    QLineEdit *locationBar;
    QCompleter *completer;
    QModelIndex dIndex;
    QFileSystemModel *dModel;

//slots:

signals:

};

#endif // LOCATIONBAR_H
>>>>>>> Stashed changes
