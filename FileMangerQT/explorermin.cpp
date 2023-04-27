#include "explorermin.h"
#include <QBoxLayout>
#include <QPushButton>
#include "fileoperations.h"
#include <QThread>
ExplorerMin::ExplorerMin(QString rootPath, QWidget *parent): QWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    layout = new QFormLayout(this);
    layout->setContentsMargins(0,0,0,0);
    fileSystemModel = new QFileSystemModel(this);
    QWidget* tableWidget = new QWidget;
    table = new QTableView(tableWidget);
    index = fileSystemModel->setRootPath(rootPath);
    registerSignals();
    layout->addRow("",ShowTableView());
     QThread* thread = new QThread(this);
     FileOperations * object = new FileOperations();
    object->moveToThread(thread);
    connect(this, &ExplorerMin::copyFile, object, &FileOperations::paste, Qt::QueuedConnection);
}



void ExplorerMin::registerSignals()
{
    QObject::connect(table,SIGNAL(doubleClicked(QModelIndex)),table,SLOT(setRootIndex(QModelIndex)));
//    QObject::connect(table,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(on_tableView_doubleClicked(QModelIndex)));

    QObject::connect(table, SIGNAL(clicked(QModelIndex)), this, SLOT(on_tableView_clicked(QModelIndex)));

    /*Register shortcusts*/
    QShortcut *shortcutCopy = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_C), this);
    shortcutCopy->setContext(Qt::ApplicationShortcut);


    QShortcut *shortcutPaste = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_V), this);
    QShortcut *shortcutDel = new QShortcut(QKeySequence(Qt::Key_Delete), this);
    QShortcut *shortcutCut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_X), this);

    QObject::connect(shortcutCopy, &QShortcut::activated, this, &ExplorerMin::onCopy);
    QObject::connect(shortcutPaste, &QShortcut::activated, this, &ExplorerMin::onPaste);
    QObject::connect(shortcutDel, &QShortcut::activated, this, &ExplorerMin::onDel);
    QObject::connect(shortcutCut, &QShortcut::activated, this, &ExplorerMin::onCut);
}
QTableView* ExplorerMin::ShowTableView()
{
    table->setModel(fileSystemModel);
    table->setRootIndex(index);
    table->setColumnWidth(0,250);
    table->setColumnWidth(3,250);
    table->horizontalScrollBar();
    table->setMinimumHeight(120);
    //    table->setMinimumWidth(2000);
    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //    table->verticalHeader()->hide();
    return table;
}

void ExplorerMin::contextMenuEvent(QContextMenuEvent *event)
{
    qInfo() << "right click pressed";
    QMenu menu(this);
    QAction *cutAction = menu.addAction(tr("Cut"));
    QAction *copyAction = menu.addAction(tr("Copy"));
    QAction *pasteAction = menu.addAction(tr("Paste"));
    QAction *delAction = menu.addAction(tr("Delete"));
    //    QAction *compressAction = menu.addAction(tr("Compress"));
    //    QAction *decompressAction = menu.addAction(tr("Decompress"));
    //    QAction *renameAction = menu.addAction(tr("Rename"));
    //    QAction *batchRenameAction = menu.addAction(tr("Batch renaming"));
    //    QAction *PropertiesAction= menu.addAction(tr("properties"));

    //    if ( isMultipleSelected() )
    //    {
    //        batchRenameAction->setEnabled(true);
    //        renameAction->setEnabled(false);
    //    }
    //    else
    //    {
    //        batchRenameAction->setEnabled(false);
    //        renameAction->setEnabled(true);
    //    }
    connect(copyAction, &QAction::triggered, this, &ExplorerMin::onCopy);
    connect(pasteAction, &QAction::triggered, this, &ExplorerMin::onPaste);
    connect(delAction, &QAction::triggered, this, &ExplorerMin::onDel);
    connect(cutAction, &QAction::triggered, this, &ExplorerMin::onCut);
    //    connect(compressAction, &QAction::triggered, this, &ExplorerMin::onCompress);
    //    connect(decompressAction, &QAction::triggered, this, &ExplorerMin::onDeCompress);

    //    connect(renameAction,&QAction::triggered, this, &ExplorerMin::onRenameFilesViewSlot );
    //    connect(batchRenameAction,&QAction::triggered, this, &ExplorerMin::onBatchRenameViewSlot );

    //    connect(PropertiesAction, &QAction::triggered, this, &ExplorerMin::onProperties);

    menu.exec(event->globalPos());
}

void ExplorerMin::on_tableView_clicked(const QModelIndex &index)
{
    this->index = index;
}
void ExplorerMin::onCopy()
{
    qInfo() << "Copying";
    sourceFilePathCopy = fileSystemModel->filePath(index);
    action = CopyCutAction::Copy;
}

void ExplorerMin::onPaste()
{

    std::string dest =  fileSystemModel->filePath(index).toStdString();
    qInfo()<<sourceFilePathCopy.toStdString();
    emit copyFile(sourceFilePathCopy.toStdString(),dest,action);
        QThread* thread = findChild<QThread*>(); // Get the thread associated with this object
        thread->start();
    qInfo()<< "pasting";
}

void ExplorerMin::onDel()
{
    filePath = fileSystemModel->filePath(index);
    emit delFile(filePath.toStdString());
}

void ExplorerMin::onCut()
{
    action = CopyCutAction::Cut;
    filePath = fileSystemModel->filePath(index);
    emit cutFile(filePath.toStdString());
}

void ExplorerMin::onProperties()
{
    qDebug() << "here in the properties slot of the view class";
    filePath = fileSystemModel->filePath(index);
    qDebug() << filePath.toStdString();
    emit propertiesOfFile(filePath.toStdString());
}

void ExplorerMin::onRenameFilesViewSlot()
{
    filePath = fileSystemModel->filePath(index);
    emit renameFileViewSignal(filePath.toStdString() , "New_name");
}
void ExplorerMin::onCompress()
{
    qInfo() << "line 122";
    //    CustomTwoPathWidget *customWidget = new CustomTwoPathWidget(COMPRESS);
    //    customWidget->show();
}

void ExplorerMin::onDeCompress()
{
    //    CustomTwoPathWidget *customWidget = new CustomTwoPathWidget(DECOMPRESS);
    //    customWidget->show();
}

void ExplorerMin::onCompressHere()
{

}

void ExplorerMin::onDecompressHere()
{

}
void ExplorerMin::onBatchRenameViewSlot()
{

    //    std::vector< std::string> oldPaths ;
    //    std::string newBaseName = "newfile_";

    ////    QItemSelectionModel *selectionModel = ui->treeView->selectionModel();
    ////    QModelIndexList indexes = selectionModel->selection().indexes();

    ////    foreach (QModelIndex index, indexes)
    ////    {
    ////        qInfo() << "In veiew " << index ;
    ////        oldPaths.push_back(fileSystemModel->filePath(index).toStdString());
    ////    }

    //    emit batchRenameViewSignal(oldPaths,newBaseName);
    //    /*emit with old paths*/
}
void ExplorerMin:: on_tableView_doubleClicked(QModelIndex index)
{
    filePath = fileSystemModel->filePath(index);
    qInfo() << filePath;
    qInfo() << "tableView double clicked";
    // Open the file and read its contents
    contentUi->file = new QFile (filePath);
    if (!contentUi->file->open(QIODevice::ReadWrite))
        return;
    QString fileContents = contentUi->file->readAll();
    qInfo() << "tableView double clicked";

    //        file.close();
    //| QIODevice::Text

    // Display the contents of the file in a QTextEdit widget
    contentUi->ui->textEdit->clear();
    contentUi->ui->textEdit->setPlainText(fileContents);
    contentUi->show();
}
