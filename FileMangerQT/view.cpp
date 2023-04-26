#include "view.h"
#include "./ui_view.h"
#include "controller.h"
#include<QThread>
void View::mRegisterSignals()
{
    // create a QShortcut object for Ctrl+C
    QShortcut *shortcutCopy = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_C), this);
    // create a QShortcut object for Ctrl+V
    QShortcut *shortcutPaste = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_V), this);
    QShortcut *shortcutDel = new QShortcut(QKeySequence(Qt::Key_Delete), this);
    QShortcut *shortcutCut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_X), this);



    // connect the shortcuts to your copy and paste functions
    QObject::connect(shortcutCopy, &QShortcut::activated, this, &View::onCopy);
    QObject::connect(shortcutPaste, &QShortcut::activated, this, &View::onPaste);
    QObject::connect(shortcutDel, &QShortcut::activated, this, &View::onDel);
    QObject::connect(shortcutCut, &QShortcut::activated, this, &View::onCut);

//    connect(ui->tableView, &QTableView::customContextMenuRequested, this, &View::onCustomContextMenuRequested);
}

View::View(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::View)
{
    ui->setupUi(this);
    fileSystemModel = new QFileSystemModel(this);
    mRegisterSignals();
    //TreeView();
    contentUi = new FileContentView(this);

    QThread* thread = new QThread(this);
    Controller* object = new Controller();
    object->moveToThread(thread);
    connect(this, &View::copyFile, object, &Controller::paste, Qt::QueuedConnection);

    ExplorerMin *e = new ExplorerMin();
    ui->formLayout->addRow("dewwqwwwwwwwwwwwww",e);

}

//void View::TreeView()
//{


//    QModelIndex modelIndex = fileSystemModel->setRootPath(QDir::rootPath());
//    ui->treeView->setModel(fileSystemModel);
//    //    ui->treeView->horizontalScrollBar();
//    ui->treeView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //hide the columns we don't want
    /*The first column shows the names of the files and folders in the hierarchy.
     * The second column shows the size of the files in bytes.
     * The third column shows the type of the files (e.g. directory, file, symlink, etc.).
     * The fourth column shows the date and time when the files were last modified.
     */
//    for (int i=1; i<4; ++i) ui->treeView->hideColumn(i);
//    ui->treeView->header()->setStretchLastSection(true);
//    ui->treeView->setColumnWidth(0, 1000);

//    ui->treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);

//    // set the selection behavior to SelectItems
//    ui->treeView->setSelectionBehavior(QAbstractItemView::SelectItems);
//}

//    QModelIndex modelIndex = fileSystemModel->setRootPath(QDir::rootPath());
//    ui->treeView->setModel(fileSystemModel);
//    //    ui->treeView->horizontalScrollBar();
//    ui->treeView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
//    //hide the columns we don't want
//    /*The first column shows the names of the files and folders in the hierarchy.
//     * The second column shows the size of the files in bytes.
//     * The third column shows the type of the files (e.g. directory, file, symlink, etc.).
//     * The fourth column shows the date and time when the files were last modified.
//     */
//    for (int i=1; i<4; ++i) ui->treeView->hideColumn(i);
//    ui->treeView->header()->setStretchLastSection(true);
//    ui->treeView->setColumnWidth(0, 1000);

//}


View::~View()
{
    delete ui;
}



//void View::on_treeView_clicked(const QModelIndex &index)
//{
//    qInfo()<<"Clicked\n";
//    this->index = index;
//    ui->tableView->setModel(fileSystemModel);
//    ui->tableView->setRootIndex(index);
//    ui->tableView->verticalHeader()->setVisible(false);
//    ui->tableView->setColumnWidth(0,250);
//    ui->tableView->setColumnWidth(3,250);
//    ui->tableView->horizontalScrollBar();
//    ui->tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

//}


//void View::on_tableView_clicked(const QModelIndex &index)
//{
//    this->index = index;
//    qInfo()<<this->index<<"  ok \n";

//}

//void View::on_treeView_clicked(const QModelIndex &index)
//{

//    this->index = index;
//    ui->tableView->setModel(fileSystemModel);
//    ui->tableView->setRootIndex(index);
//    ui->tableView->verticalHeader()->setVisible(false);
//    ui->tableView->setColumnWidth(0,250);
//    ui->tableView->setColumnWidth(3,250);
//    ui->tableView->horizontalScrollBar();
//    ui->tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);


//}


//void View::on_tableView_clicked(const QModelIndex &index)
//{
//    this->index = index;
//}

void View::onCopy()
{
    qInfo() << "Copying";
    filePath = fileSystemModel->filePath(index);
    action = CopyCutAction::Copy;
}

void View::onPaste()
{

    std::string dest =  fileSystemModel->filePath(index).toStdString();
    emit copyFile(filePath.toStdString(),dest,action);
    QThread* thread = findChild<QThread*>(); // Get the thread associated with this object
    thread->start();
    qInfo()<< "thread started";

}

void View::onDel()
{
    filePath = fileSystemModel->filePath(index);
    emit delFile(filePath.toStdString());
}

void View::onCut()
{
    action = CopyCutAction::Cut;
    filePath = fileSystemModel->filePath(index);
    emit cutFile(filePath.toStdString());
}

void View::onProperties()
{
    qDebug() << "here in the properties slot of the view class";
    filePath = fileSystemModel->filePath(index);
     qDebug() << filePath.toStdString();
    emit propertiesOfFile(filePath.toStdString());
}

void View::onRenameFilesViewSlot()
{

    filePath = fileSystemModel->filePath(index);
    emit renameFileViewSignal(filePath.toStdString() , "New_name");
}

void View::onCompress()
{
    qInfo() << "line 122";
//    CustomTwoPathWidget *customWidget = new CustomTwoPathWidget(COMPRESS);
//    customWidget->show();
}

void View::onDeCompress()
{
//    CustomTwoPathWidget *customWidget = new CustomTwoPathWidget(DECOMPRESS);
//    customWidget->show();
}

void View::onCompressHere()
{

}

void View::onDecompressHere()
{

}

void View::onBatchRenameViewSlot()
{

    std::vector< std::string> oldPaths ;
    std::string newBaseName = "newfile_";

//    QItemSelectionModel *selectionModel = ui->treeView->selectionModel();
//    QModelIndexList indexes = selectionModel->selection().indexes();

//    foreach (QModelIndex index, indexes)
//    {
//        qInfo() << "In veiew " << index ;
//        oldPaths.push_back(fileSystemModel->filePath(index).toStdString());
//    }

    emit batchRenameViewSignal(oldPaths,newBaseName);
    /*emit with old paths*/
}



void View::on_lineEditPath_textEdited(const QString &arg1)
{

}
void View::on_tableView_doubleClicked(const QModelIndex &index)
{
//    qInfo() << "95";
//    this->index = index;
//    on_treeView_clicked(index);
//        // Get the path of the selected file

//    filePath = fileSystemModel->filePath(index);
//    qInfo() << filePath;
//    // Open the file and read its contents
//    contentUi->file = new QFile (filePath);
//    if (!contentUi->file->open(QIODevice::ReadWrite))
//        return;
//    QString fileContents = contentUi->file->readAll();
//    //        file.close();
//    //| QIODevice::Text

//    // Display the contents of the file in a QTextEdit widget
//    contentUi->ui->textEdit->clear();
//    contentUi->ui->textEdit->setPlainText(fileContents);
//    contentUi->show();
}

void View::contextMenuEvent(QContextMenuEvent *event)
{
    qInfo() << "right click pressed";
//    // Convert the position to global coordinates
//    QPoint globalPos = ui->tableView->viewport()->mapToGlobal(pos);

//    // Create a context menu
//    QMenu myContextMenu;
//    myContextMenu.addAction("Action 1");
//    myContextMenu.addAction("Action 2");

//    // Show the context menu at the global position
//    myContextMenu.exec(globalPos);
    QMenu menu(this);
    QAction *cutAction = menu.addAction(tr("Cut"));
    QAction *copyAction = menu.addAction(tr("Copy"));
    QAction *pasteAction = menu.addAction(tr("Paste"));
    QAction *delAction = menu.addAction(tr("Delete"));
    QAction *compressAction = menu.addAction(tr("Compress"));
    QAction *decompressAction = menu.addAction(tr("Decompress"));
    QAction *renameAction = menu.addAction(tr("Rename"));
    QAction *batchRenameAction = menu.addAction(tr("Batch renaming"));
    QAction *PropertiesAction= menu.addAction(tr("properties"));

    if ( isMultipleSelected() )
    {
        batchRenameAction->setEnabled(true);
        renameAction->setEnabled(false);
    }
    else
    {
        batchRenameAction->setEnabled(false);
        renameAction->setEnabled(true);
    }






    connect(copyAction, &QAction::triggered, this, &View::onCopy);
    connect(pasteAction, &QAction::triggered, this, &View::onPaste);
    connect(delAction, &QAction::triggered, this, &View::onDel);
    connect(cutAction, &QAction::triggered, this, &View::onCut);
    connect(compressAction, &QAction::triggered, this, &View::onCompress);
    connect(decompressAction, &QAction::triggered, this, &View::onDeCompress);

    connect(renameAction,&QAction::triggered, this, &View::onRenameFilesViewSlot );
    connect(batchRenameAction,&QAction::triggered, this, &View::onBatchRenameViewSlot );

    connect(PropertiesAction, &QAction::triggered, this, &View::onProperties);

    menu.exec(event->globalPos());
}

bool View::isMultipleSelected(){
//    QItemSelectionModel *selectionModel = ui->treeView->selectionModel();
//    QModelIndexList selectedIndexes = selectionModel->selectedIndexes();
//    if (selectedIndexes.length() == 1) {
//        return false ;
//    } else if (selectedIndexes.length() > 1) {
//        return true ;
//    }

}
