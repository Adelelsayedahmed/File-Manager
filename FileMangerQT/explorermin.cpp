#include "explorermin.h"
#include <QBoxLayout>
#include <QPushButton>
#include "fileoperations.h"
#include <QThread>

QString ExplorerMin::filepath;
ExplorerMin::ExplorerMin(QString rootPath, QWidget *parent): QWidget(parent)
{
    rename_widg_obj  = new rename_widget("rename","please enter a valid name","new name");
    batch_rename_widg_obj = new rename_widget("batch rename","please enter a valid base name","new base name");
    setFocusPolicy(Qt::StrongFocus);
    layout = new QFormLayout(this);
    layout->setContentsMargins(0,0,0,0);
    fileSystemModel = new MyFileSystemModel(this);
    QWidget* tableWidget = new QWidget;
    table = new CustomTable(tableWidget);
    index = fileSystemModel->setRootPath(rootPath);
    fileSystemModel->parent(index);
    search = new SearchBar(this);

  //  topBar = new addOnsBar(this);
   // identifyDuplicatesAction=topBar->identifyDuplicatesAction;

    registerSignals();
    layout->addRow("",ShowTableView());
     QThread* thread = new QThread(this);
     FileOperations * object = new FileOperations();
    object->moveToThread(thread);
    connect(this, &ExplorerMin::copyFile, object, &FileOperations::paste, Qt::QueuedConnection);
    contentUi = new FileContentView();
    backFilepath = fileSystemModel->filePath(index);
    emit locationChanged(fileSystemModel->filePath(index), fileSystemModel->fileName(index));
}



void ExplorerMin::registerSignals()
{
//    QObject::connect(table,SIGNAL(doubleClicked(QModelIndex)),table,SLOT(setRootIndex(QModelIndex)));
    QObject::connect(table,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(on_tableView_doubleClicked(QModelIndex)));

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

    QObject::connect(search, &SearchBar::SearchWindowCreated, this, &ExplorerMin::SearchWindowCreatedSlot);
    QObject::connect(this, &ExplorerMin::locationChanged, search, &SearchBar::locationChanged);
    QObject::connect(search,&SearchBar::backButtonPressedSignal,this,&ExplorerMin::BackButtonClicked);
  //  topBar->connectAction(identifyDuplicatesAction,this,SLOT(on_identifyDuplicatesIconClicked()));
    //QObject::connect(table,SIGNAL(doubleClicked),this,&ExplorerMin::BackButtonClicked);
    QObject::connect(rename_widg_obj,&rename_widget::new_file_name_button_clicked,this,&ExplorerMin::emitingRenameSlot);
    QObject::connect(batch_rename_widg_obj,&rename_widget::new_file_name_button_clicked,this,&ExplorerMin::emitingBatchRenameSlot);
}



ExplorerMin::~ExplorerMin()
{
    delete layout;
    delete fileSystemModel;
    delete contentUi;
    delete search;
    delete identifyDuplicatesAction;
    delete topBar;
    delete rename_widg_obj ;
    delete batch_rename_widg_obj ;
}

QTableView* ExplorerMin::ShowTableView()
{

    table->setModel(fileSystemModel);
    QItemSelectionModel* selectionModel = new QItemSelectionModel(fileSystemModel);
//    table->setSelectionModel(selectionModel);
//    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setRootIndex(index);
    table->setColumnWidth(0,250);
    table->setColumnWidth(3,150);
    table->setMinimumWidth(350);
    table->horizontalScrollBar();
    table->setMinimumHeight(120);
    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    table->verticalHeader()->hide();
    table->setSelectionBehavior(QAbstractItemView::SelectRows);

    //to make the tableView resizable
    for (int i = 0; i < table->horizontalHeader()->count(); ++i) {
        if (i == 0) {
            table->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
        } else {
            table->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Fixed);
        }
    }
    backFilepath=fileSystemModel->filePath(index);
    emit locationChanged(fileSystemModel->filePath(index), fileSystemModel->fileName(index));
    return table;
}

void ExplorerMin::contextMenuEvent(QContextMenuEvent *event)
{
    //disable right click in case it is pressed on empty area.
    QModelIndex ind = table->indexAt(event->pos());
    if(!ind.isValid())
    {
        event->ignore();
        return;
    }
    qInfo() << "right click pressed";
     qInfo() << fileSystemModel->filePath(table->currentIndex());
    // on_tableView_clicked(table->currentIndex());
   // emit locationChanged(fileSystemModel->filePath(table->currentIndex()), fileSystemModel->fileName(table->currentIndex()));
    qInfo()<< fileSystemModel->filePath(index);
    QMenu menu(this);
    QAction *cutAction = menu.addAction(tr("Cut"));
    QAction *copyAction = menu.addAction(tr("Copy"));
    QAction *pasteAction = menu.addAction(tr("Paste"));
    QAction *delAction = menu.addAction(tr("Delete"));
    QMenu *subMenu = new QMenu("Compression", this);

    compressAction= subMenu->addAction(tr("Compress"));
    //connect(compressAction, &QAction::triggered, this, &ExplorerMin::checkSelectedFileForCompression);

    decompressAction = subMenu->addAction(tr("Decompress"));
    //connect(decompressAction, &QAction::triggered, this, &ExplorerMin::checkSelectedFileForrdeCompression);
    QAction *batchCompressionAction = subMenu->addAction(tr("Batch Compression"));
    QAction *batchDecompressionAction = subMenu->addAction(tr("Batch Decompression"));

    menu.addMenu(subMenu);

    QMenu* renamingSubMenu = new QMenu("Renaming",this);

    QAction *renameAction = renamingSubMenu->addAction(tr("Rename"));
    QAction *batchRenameAction = renamingSubMenu->addAction(tr("Batch rename"));

    menu.addMenu((renamingSubMenu));

    QAction *PropertiesAction= menu.addAction(tr("properties"));

        if ( isMultipleSelected() )
        {
            batchRenameAction->setEnabled(true);
            renameAction->setEnabled(false);

            batchCompressionAction->setEnabled(true);
            compressAction->setEnabled(false);

            batchDecompressionAction->setEnabled(true);
            decompressAction->setEnabled(false);
        }
        else
        {
            batchRenameAction->setEnabled(false);
            renameAction->setEnabled(true);

            batchCompressionAction->setEnabled(false);
            compressAction->setEnabled(true);

            batchDecompressionAction->setEnabled(false);
            decompressAction->setEnabled(true);

        }
    connect(copyAction, &QAction::triggered, this, &ExplorerMin::onCopy);
    connect(pasteAction, &QAction::triggered, this, &ExplorerMin::onPaste);
    connect(delAction, &QAction::triggered, this, &ExplorerMin::onDel);
    connect(cutAction, &QAction::triggered, this, &ExplorerMin::onCut);
    //    connect(compressAction, &QAction::triggered, this, &ExplorerMin::onCompress);
    //    connect(decompressAction, &QAction::triggered, this, &ExplorerMin::onDeCompress);

        connect(batchCompressionAction,&QAction::triggered, this, &ExplorerMin::onBatchCompressViewSlot );
        connect(batchDecompressionAction,&QAction::triggered, this, &ExplorerMin::onBatchDecompressViewSlot );


        connect(renameAction,&QAction::triggered, this, &ExplorerMin::onRenameFilesViewSlot );
        connect(batchRenameAction,&QAction::triggered, this, &ExplorerMin::onBatchRenameViewSlot );

        connect(PropertiesAction, &QAction::triggered, this, &ExplorerMin::onProperties);

       // checkSelectedFileForCompression();


        menu.exec(event->globalPos());
}
void ExplorerMin::checkSelectedFileForCompression()
{

    // Get the path of the selected file
    QString filePath = fileSystemModel->filePath(index);
    qInfo()<<"AA";
    qInfo()<<filePath;
    // Enable the compress action if the file is a .txt file, otherwise disable it
    if (QFileInfo(filePath).suffix() == "txt")
    {qInfo()<<"in compress";
        compressAction->setEnabled(true);
     decompressAction->setEnabled(false);
    }

    else if ((QFileInfo(filePath).suffix() == "gz"))

    {
        qInfo()<<"in deecompress";
        compressAction->setEnabled(false);
     decompressAction->setEnabled(true);
    }

    else {qInfo()<<"innot ";
        compressAction->setEnabled(false);
             decompressAction->setEnabled(false);
    }
}

void ExplorerMin::BackButtonClickedFromTree()
{
    backFilepath = ExplorerMin::filepath;
}

void ExplorerMin::on_tableView_clicked(const QModelIndex &index)
{
    qInfo()<<index;
    //this->index = index;
    backFilepath=fileSystemModel->filePath(index);
    emit locationChanged(fileSystemModel->filePath(index), fileSystemModel->fileName(index));
    ///////////////////////
}
void ExplorerMin::onCopy()
{
    qInfo() << "Copying";
    sourceFilePathCopy = fileSystemModel->filePath(index);
    action = CopyCutAction::Copy;
}

void ExplorerMin::onPaste()
{
    if (!fileSystemModel->isDir(index))
    {
             index = index.parent();
    }
    std::string dest =  fileSystemModel->filePath(index).toStdString();
    qInfo()<<sourceFilePathCopy;
    emit copyFile(sourceFilePathCopy.toStdString(),dest,action);
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
    qDebug() << filePath;
    emit propertiesOfFile(filePath.toStdString());
}

void ExplorerMin::onRenameFilesViewSlot()
{
    rename_widg_obj->show();
}

void ExplorerMin:: emitingRenameSlot(QString newFileName){
    filePath = fileSystemModel->filePath(index);
    rename_widg_obj->hide() ;
    emit renameFileViewSignal(filePath.toStdString() , newFileName.toStdString());

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
    batch_rename_widg_obj->show();

}
void ExplorerMin::emitingBatchRenameSlot(QString newFileName)
{
    std::vector< std::string> oldPaths = getSelectedPaths();
    std::string newBaseName = newFileName.toStdString();
    batch_rename_widg_obj ->hide();
    emit batchRenameViewSignal(oldPaths,newBaseName);

}
void ExplorerMin:: on_tableView_doubleClicked(QModelIndex index)
{
    this->index = index;
    filePath = fileSystemModel->filePath(index);
    qInfo() << filePath;
    contentUi->file = new QFile (filePath);
    if (!contentUi->file->open(QIODevice::ReadWrite))
    {
        table->setRootIndex( index);
        return;
    }
    QString fileContents = contentUi->file->readAll();
    contentUi->ui->textEdit->clear();
    contentUi->ui->textEdit->setPlainText(fileContents);
    contentUi->show();
    backFilepath=fileSystemModel->filePath(index);
    emit locationChanged(fileSystemModel->filePath(index), fileSystemModel->fileName(index));

}

void ExplorerMin::BackButtonClicked()
{
    QString path = fileSystemModel->filePath(index);
    qInfo() << path;
    if (path == "/") folderClicked("");
    else if(path !="")
    {
        QStringList list1 = path.split('/');
        qInfo() << list1;
        path="/";
        if(list1.length() > 1)
        {
            for(int i = 1 ; i < list1.length()-2;i++)
            {

                path+=list1[i] + "/";
            }
            path+=list1[list1.length()-2];
        }
        folderClicked(path);
    }

}

void  ExplorerMin::folderClicked(QString returnedFilePath)
{
    //Get index of clicked folder
    this->backFilepath = returnedFilePath;
    this->index = fileSystemModel->index(returnedFilePath);

    //Open folder in tableView
    table->setModel(fileSystemModel);
    table->setRootIndex(index);
    table->setColumnWidth(0,250);
    table->setColumnWidth(3,250);
    table->horizontalScrollBar();
    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    table->verticalHeader()->hide();
    emit locationChanged(returnedFilePath, fileSystemModel->fileName(index));
//    ui->locationBar->setPlaceholderText(fileSystemModel->filePath(index));
//    ui->searchBar->clear();
//    ui->searchBar->setPlaceholderText("Search " + fileSystemModel->fileName(index));
}

void ExplorerMin::SearchWindowCreatedSlot(SearchWindow *window)
{
    QObject::connect(window, &SearchWindow::folderClicked, this, &ExplorerMin::folderClicked);
    emit SearchWindowCreated(window);
}
//void ExplorerMin::on_identifyDuplicatesIconClicked()
//{
//    emit identifyDuplictesIconCLicked();
//}

void ExplorerMin::onBatchCompressViewSlot()
{
    std::cout<<"onBatchCompressViewSlot"<<std::endl ;
    std::vector< std::string> Paths  = getSelectedPaths();
    emit batchCompressViewSignal(Paths);
}

void ExplorerMin::onBatchDecompressViewSlot()
{
    std::vector< std::string> Paths  = getSelectedPaths();
    emit batchDecompressViewSignal(Paths);
}


bool ExplorerMin::isMultipleSelected(){
    QItemSelectionModel *selectionModel = this->table->selectionModel();
    QModelIndexList selectedIndexes = selectionModel->selectedIndexes();
    QSet<int> selectedRows;
    for (const QModelIndex &index : selectedIndexes) {
        selectedRows.insert(index.row());
    }
    if (selectedRows.size() == 1) {
        return false;
    } else if (selectedRows.size() > 1) {
        return true;
    }
}


std::vector<std::string> ExplorerMin::getSelectedPaths() {
    std::vector< std::string> oldPaths ;
    QItemSelectionModel *selectionModel = table->selectionModel();
    QModelIndexList indexes = selectionModel->selection().indexes();

    foreach (QModelIndex index, indexes)
    {
        oldPaths.push_back(fileSystemModel->filePath(index).toStdString());
    }

    return oldPaths ;


}
