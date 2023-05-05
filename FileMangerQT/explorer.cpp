
#include "explorer.h"
#include <QObject>
#include <QLabel>


Explorer::Explorer(QString rootPath, QWidget *parent ): ExplorerMin(rootPath,parent)
{
    proxy_model = new DirectoryOnlyFilterProxyModel(this);
    proxy_model->setSourceModel(fileSystemModel);
    tree = new QTreeView(this);
<<<<<<< Updated upstream

    layout->setContentsMargins(0,0,0,0);
    layout->insertRow(0,topBar);
    layout->insertRow(1, locationLayout);
    layout->insertRow(2,ShowTreeView(rootPath),table);
=======
   // layout->insertRow(0,topBar);
    layout->insertRow(0, location);
//    layout->insertRow(0,ShowTreeView(rootPath),table);
>>>>>>> Stashed changes

    // Create the footer widget
    QWidget* footerWidget = new QWidget(this);

    // Create labels for number of files and size
    QLabel* numFilesLabel = new QLabel("Number of files: ", footerWidget);
     numFilesValueLabel = new QLabel("0", footerWidget);

    QLabel* sizeLabel = new QLabel("Size: ", footerWidget);
     sizeValueLabel = new QLabel("0", footerWidget);

    // Set alignment for the labels in footer widget
    numFilesLabel->setAlignment(Qt::AlignLeft);
    numFilesValueLabel->setAlignment(Qt::AlignLeft);
    sizeLabel->setAlignment(Qt::AlignLeft);
    sizeValueLabel->setAlignment(Qt::AlignLeft);

    // Create a layout for the footer widget
    QHBoxLayout* footerLayout = new QHBoxLayout(footerWidget);
    footerLayout->addWidget(numFilesLabel);
    footerLayout->addWidget(numFilesValueLabel);
    footerLayout->addWidget(sizeLabel);
    footerLayout->addWidget(sizeValueLabel);
    footerLayout->addStretch(1);

    // Set a minimum height and border for the footer widget
    footerWidget->setMinimumHeight(30);
    // footerWidget->setStyleSheet("border-top: 1px solid black;");

    layout->addRow(footerWidget);
    // Set the layout of the footer widget to the footer layout
    footerWidget->setLayout(footerLayout);
    // Align the footer widget to the bottom of the layout
    layout->setFormAlignment(Qt::AlignBottom | Qt::AlignLeft);

    registerSignals();
}
void Explorer::registerSignals()
{
    QObject::connect(tree,SIGNAL(clicked(QModelIndex)),this,SLOT(ShowTableView(QModelIndex)));
       QObject::connect(table,SIGNAL(clicked(QModelIndex)),this,SLOT(footer_update(QModelIndex)));
//    QObject::connect(tree,SIGNAL(clicked(QModelIndex)),table,SLOT(setRootIndex(QModelIndex)));
    QObject::connect(tree, SIGNAL(clicked(QModelIndex)), this, SLOT(on_treeView_clicked(QModelIndex)));

}

Explorer::~Explorer()
{
    delete tree;
}

void Explorer:: footer_update(const QModelIndex &index1)
{
//    qInfo()<<"a";
//     table->setModel(fileSystemModel);
    // ppath is "" we need too eeedit path here

//    qInfo()<<"in table view selected "<<fileSystemModel->filePath(index1).toStdString();

   // qInfo()<<"in table view selected size:  ";

    std::thread t(&Explorer::footer_size, this, fileSystemModel->filePath(index1).toStdString());
    t.detach();
    std::thread t2(&Explorer::footer_item, this, fileSystemModel->filePath(index1).toStdString());
    t2.detach();
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

void Explorer::footer_size(std::string s)
{
<<<<<<< Updated upstream
    sizeValueLabel->setText("0");
//    qInfo()<<"in footer size function"<<s;
    boost::filesystem::path filePath = boost::filesystem::path(s);
    sizeValueLabel->setText(QString::number(statistics::convertToKB( statistics::directory_size(filePath))).append(" kb")) ;
=======
    sizeValueLabel->setText("...");

//    qInfo()<<"in footer size function"<<s;
    unsigned int size=0;
    QString appendingString;
    if(statistics::isFile(s))
    {
        size=statistics::convertToKB(statistics::getFile_size(s));
        appendingString=" KB";
    }
    else
    {
        size=statistics::convertToMB(statistics::directory_size(s));
        appendingString=" MB";
    }
    sizeValueLabel->setText(QString::number(size).append(appendingString)) ;

>>>>>>> Stashed changes
}

void Explorer::footer_item(std::string s)
{
    numFilesValueLabel->setText("0");
    boost::filesystem::path filePath = boost::filesystem::path(s);
      numFilesValueLabel->setText(QString::number(statistics::numberOfItems(filePath)));
}

void Explorer::on_treeView_clicked(const QModelIndex &index1)
{
    this->index = index1;
    std::thread t(&Explorer::footer_size, this, fileSystemModel->filePath(proxy_model->mapToSource(index1)).toStdString());
    t.detach();
    std::thread t2(&Explorer::footer_item, this, fileSystemModel->filePath(proxy_model->mapToSource(index1)).toStdString());
    t2.detach();
<<<<<<< Updated upstream
    emit locationChanged(fileSystemModel->filePath(proxy_model->mapToSource(index1)), fileSystemModel->fileName(proxy_model->mapToSource(index1)));
=======
    ExplorerMin::filepath = fileSystemModel->filePath(proxy_model->mapToSource(index1));
    emit backButtonPressedSignalFromTree();
    emit locationChanged(fileSystemModel->filePath(proxy_model->mapToSource(index1)), fileSystemModel->fileName(proxy_model->mapToSource(index1)));

>>>>>>> Stashed changes
}

