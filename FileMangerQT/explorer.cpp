
#include "explorer.h"
#include <QObject>
#include <QLabel>


Explorer::Explorer(QString rootPath, QWidget *parent ): ExplorerMin(rootPath,parent)

{
    proxy_model = new DirectoryOnlyFilterProxyModel(this);
    proxy_model->setSourceModel(fileSystemModel);
    tree = new QTreeView(this);
    layout->insertRow(0,topBar);
    layout->insertRow(1, search);
    layout->insertRow(2,ShowTreeView(rootPath),table);

// Create the footer widget
    QWidget* footerWidget = new QWidget(this);

    // Create labels for number of files and size
    QLabel* numFilesLabel = new QLabel("Number of files: ", footerWidget);
    QLabel* numFilesValueLabel = new QLabel("0", footerWidget);

    QLabel* sizeLabel = new QLabel("Size: ", footerWidget);
    QLabel* sizeValueLabel = new QLabel("0", footerWidget);

    // Set alignment for the labels in footer widget
    numFilesLabel->setAlignment(Qt::AlignCenter);
    sizeLabel->setAlignment(Qt::AlignCenter);

    // Create a layout for the labels
    QHBoxLayout* footerLayout = new QHBoxLayout(footerWidget);
    footerLayout->addWidget(numFilesLabel);
    footerLayout->addWidget(numFilesValueLabel);
    //footerLayout->addStretch(); // Add stretch to make size label right-aligned
    footerLayout->addWidget(sizeLabel);
    footerLayout->addWidget(sizeValueLabel);

    // Set a minimum height and border for the footer widget
    footerWidget->setMinimumHeight(30);
    // footerWidget->setStyleSheet("border-top: 1px solid black;");


//    QVBoxLayout* mainLayout = new QVBoxLayout(this);
//    mainLayout->addLayout(layout);
//    mainLayout->addWidget(footerWidget, 0, Qt::AlignBottom);

    // Set the layout of the CustomTwoPathWidget to the main layout
//    setLayout(mainLayout);
    layout->addRow(footerWidget);
    footerWidget->setLayout(layout);
    layout->setFormAlignment(Qt::AlignBottom);

    registerSignals();

}
void Explorer::registerSignals()
{
    QObject::connect(tree,SIGNAL(clicked(QModelIndex)),this,SLOT(ShowTableView(QModelIndex)));
//    QObject::connect(tree,SIGNAL(clicked(QModelIndex)),table,SLOT(setRootIndex(QModelIndex)));
    QObject::connect(tree, SIGNAL(clicked(QModelIndex)), this, SLOT(on_treeView_clicked(QModelIndex)));

}

Explorer::~Explorer()
{
    delete tree;
}


QTreeView* Explorer::ShowTreeView(const QString &rootPath)
{
    tree->setModel(proxy_model);
tree->setRootIndex(proxy_model->mapFromSource(fileSystemModel->index("/")));
    tree->horizontalScrollBar();
    tree->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //hide the columns we don't want
    for (int i=1; i<4; ++i) tree->hideColumn(i);
    tree->setColumnWidth(0, 500);
    tree->show();
    tree->setMinimumHeight(120);
    return tree;
}
void Explorer::ShowTableView(QModelIndex index1)
{
    table->setModel(fileSystemModel);
//    table->setRootIndex(index);
    table->setColumnWidth(0,250);
    table->setColumnWidth(3,250);
    table->horizontalScrollBar();
    table->setMinimumHeight(120);
    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    table->verticalHeader()->hide();
    QString path = fileSystemModel->filePath(proxy_model->mapToSource(index1));
    table->setRootIndex(fileSystemModel->index(path));
//    emit locationChanged(fileSystemModel->filePath(index), fileSystemModel->fileName(index));
}

void Explorer::on_treeView_clicked(const QModelIndex &index1)
{
    this->index = index;
    emit locationChanged(fileSystemModel->filePath(proxy_model->mapToSource(index1)), fileSystemModel->filePath(proxy_model->mapToSource(index1)));
}

