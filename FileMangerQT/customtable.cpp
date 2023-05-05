#include "customtable.h"

CustomTable::CustomTable(QWidget *parent) : QTableView(parent)
{
    fileSystemModel = new QFileSystemModel(this);
    fileSystemModel->setRootPath(QDir::rootPath());
    setModel(fileSystemModel);
    setAcceptDrops(true);
}

void CustomTable::dragEnterEvent(QDragEnterEvent *event)
{

    qInfo()<<"drag";

    sourceUrls = event->mimeData()->urls();
    for (const QUrl & url : sourceUrls )
    {
        qInfo() << url.toLocalFile();
    }
    event->acceptProposedAction();
    const QMimeData* mimeData = event->mimeData();
    qDebug() << "MIME types: " << mimeData->formats();
}
void CustomTable::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();
    // Check if there is a file list in the mime data
        QString targetPath;
    QModelIndex targetIndex;
        if (mimeData->hasUrls()) {
            QList<QUrl> targetUrls = mimeData->urls();
            //loop in case multiple selection

            //        if (targetUrls.count() == 1)
            {
                if(!indexAt(event->pos()).isValid())
                    targetPath = fileSystemModel->filePath(rootIndex());
                else
                {
                     targetIndex = indexAt(event->pos());

                    if (!fileSystemModel->isDir(targetIndex))
                    {
                        targetIndex = targetIndex.parent();
                    }
                    targetPath = fileSystemModel->filePath(targetIndex);
                }

                for (const QUrl &url : sourceUrls)
                {
//                    qInfo()<<"copying";
//                    qInfo()<<url.toLocalFile().toStdString();
//                    qInfo()<< "pasting";
//                    qInfo()<<targetPath;
//                    qInfo() << fileSystemModel->filePath( targetIndex).toStdString();
                    emit paste(url.toLocalFile().toStdString(), targetPath.toStdString(), CopyCutAction::Copy);
                }

            }
            event->acceptProposedAction();
        }
}

void CustomTable::CustomTable::dragLeaveEvent(QDragLeaveEvent *event)
{
    qInfo() << "Drag left";
    event->accept();
}
