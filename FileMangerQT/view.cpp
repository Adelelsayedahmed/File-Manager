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

QObject::connect(stackedview, &stackedviewwidget::passingContentSearchToView,this,&View::recieveContentSearchFromSv);

}

View::View(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::View)
{
ui->setupUi(this);


topBar = new addOnsBar(this);
stackedview = new stackedviewwidget(this);

QGridLayout* mainLayout = new QGridLayout(this);
mainLayout->addWidget(topBar, 0, 0);
mainLayout->addWidget(stackedview, 1, 0);

QWidget* centralWidget = new QWidget(this);
centralWidget->setLayout(mainLayout);
this->setCentralWidget(centralWidget);
mRegisterSignals();

}


View::~View()
{
delete ui;
}

void View::closeEvent(QCloseEvent *event)
{
    Undo::del(FileOperations::getDeletePath());
    qInfo()<<   "program ended\n";
}

void View::recieveContentSearchFromSv(const std::vector<std::string> &filePaths, const std::string &searchString)
{
    emit passingContentSearchFromSvtoController(filePaths,searchString);
}










