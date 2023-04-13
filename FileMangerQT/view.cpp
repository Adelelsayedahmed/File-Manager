#include "view.h"
#include "./ui_view.h"

View::View(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::View)
{
    ui->setupUi(this);
    fileSystemModel = new QFileSystemModel(this);
    TreeView();
}

void View::TreeView()
{
    ui->treeView->setModel(fileSystemModel);
    ui->treeView->setRootIndex(fileSystemModel->setRootPath(QString()));
    ui->treeView->horizontalScrollBar();
    ui->treeView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //hide the columns we don't want
    for (int i=1; i<4; ++i) ui->treeView->hideColumn(i);
    ui->treeView->header()->setStretchLastSection(true);
    ui->treeView->setColumnWidth(0, 500);
}

void View::TableView(const QModelIndex &index)
{
    ui->tableView->setModel(fileSystemModel);
    ui->tableView->setRootIndex(index);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setColumnWidth(0,250);
    ui->tableView->setColumnWidth(3,250);
    ui->tableView->horizontalScrollBar();
    ui->tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

View::~View()
{
    delete ui;
}


void View::on_treeView_clicked(const QModelIndex &index)
{
    TableView(index);
}


void View::on_tableView_clicked(const QModelIndex &index)
{
    TableView(index);

}

