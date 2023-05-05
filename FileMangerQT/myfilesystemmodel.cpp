#include "myfilesystemmodel.h"
#include <QMimeData>
#include <QUrl>
#include <QFileInfo>

MyFileSystemModel::MyFileSystemModel(QObject *parent)
    : QFileSystemModel(parent)
{
}

Qt::DropActions MyFileSystemModel::supportedDropActions() const
{
    return Qt::CopyAction;
}

bool MyFileSystemModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
//    qInfo()<<"file system";

    if (action == Qt::CopyAction && data->hasUrls()) {
        QList<QUrl> urls = data->urls();
        foreach (QUrl url, urls) {
            QString filePath = url.toLocalFile();
            QFileInfo fileInfo(filePath);
            if (fileInfo.isFile()) {
                // Insert the file into the model
                QFileSystemModel::dropMimeData(data, action, row, column, parent);
                return true;
            }
        }
    }
    return false;
}
Qt::ItemFlags MyFileSystemModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QFileSystemModel::flags(index);
    flags |= Qt::ItemIsDropEnabled;
    return flags;
}
