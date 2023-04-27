#include "view.h"
#include "./ui_view.h"
#include "controller.h"
#include<QThread>
void View::mRegisterSignals()
{
//    QShortcut *shortcutCopy = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_C), this);
//    QShortcut *shortcutPaste = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_V), this);
//    QShortcut *shortcutDel = new QShortcut(QKeySequence(Qt::Key_Delete), this);
//    QShortcut *shortcutCut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_X), this);

//    QObject::connect(shortcutCopy, &QShortcut::activated, this, &View::onCopy);
//    QObject::connect(shortcutPaste, &QShortcut::activated, this, &View::onPaste);
//    QObject::connect(shortcutDel, &QShortcut::activated, this, &View::onDel);
//    QObject::connect(shortcutCut, &QShortcut::activated, this, &View::onCut);

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

//    QThread* thread = new QThread(this);
//    Controller* object = new Controller();
//    object->moveToThread(thread);
//    connect(this, &View::copyFile, object, &Controller::paste, Qt::QueuedConnection);

    explorer = new Explorer("/home/ziad",this);
    ui->formLayout->addWidget(explorer);
       this->setCentralWidget(explorer);
}


View::~View()
{
    delete ui;
}









//bool View::isMultipleSelected(){
////    QItemSelectionModel *selectionModel = ui->treeView->selectionModel();
////    QModelIndexList selectedIndexes = selectionModel->selectedIndexes();
////    if (selectedIndexes.length() == 1) {
////        return false ;
////    } else if (selectedIndexes.length() > 1) {
////        return true ;
////    }

//}
