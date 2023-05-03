#ifndef CUSTOMTABLE_H
#define CUSTOMTABLE_H

#include <QObject>
#include <QTableView>
#include <QDebug>
#include <QWidget>
#include <QDropEvent>
#include <QMimeData>
#include <QFileSystemModel>
#include <QFileInfo>
#include <QDrag>
#include "Actions.h"
/**
 * @class CustomTable
 * @brief A custom table view that supports drag and drop operations.
 *
 * This class extends QTableView to provide support for drag and drop operations.
 * It also emits a 'paste' signal when a drop event occurs, which can be used to
 * handle pasting of files and folders.
 */
class CustomTable: public QTableView
{
    Q_OBJECT
public:
    CustomTable(QWidget *parent =  nullptr );
protected:
    QFileSystemModel *fileSystemModel;
//    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
private:
    QList<QUrl> sourceUrls;
 signals:
    void paste(std::string source_path, std::string destination_path, CopyCutAction action);
};

#endif // CUSTOMTABLE_H
