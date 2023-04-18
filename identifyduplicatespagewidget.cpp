#include "identifyduplicatespagewidget.h"

IdentifyDuplicatesPageWidget::IdentifyDuplicatesPageWidget(QWidget *parent)
    : QWidget{parent}
{
    QGridLayout *gridLayout = new QGridLayout(this);

    QLabel *pathsLabel=new QLabel;
    pathsLabel->setText("searching paths");
    pathsLabel->setFixedSize(110,35);

    gridLayout->addWidget(pathsLabel,0,1);

    QPushButton *addButton=new QPushButton("add path");
    addButton->setFixedSize(100,30);
    addButton->setStyleSheet("background-color: green");

    gridLayout->addWidget(addButton,1,0);

    QPushButton *removeButton=new QPushButton("remove path");
    removeButton->setFixedSize(100,30);
    removeButton->setStyleSheet("background-color: red");

    gridLayout->addWidget(removeButton,2,0);

    pathsBrowser=new QTextBrowser;

    qDebug() << gridLayout->columnCount();
    gridLayout->addWidget(pathsBrowser, 1, 1, 3, gridLayout->columnCount()-1);

    QPushButton *identifyDuplicatesButton=new QPushButton("check duplicates");
    identifyDuplicatesButton->setFixedSize(120,30);

    gridLayout->addWidget(identifyDuplicatesButton, gridLayout->rowCount(),2 , 1, 1);

    duplicatesTableView= new QTableView(this);

    duplicatesTableModel= new QStandardItemModel();
    duplicatesTableModel->setColumnCount(2);
    duplicatesTableModel->setHeaderData(0,Qt::Horizontal,"file/directory name");
    duplicatesTableModel->setHeaderData(1,Qt::Horizontal,"file/directory size");

    duplicatesTableView->setModel(duplicatesTableModel);
    duplicatesTableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    duplicatesTableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);

    qDebug() << gridLayout->columnCount();
    qDebug() << gridLayout->rowCount();
    gridLayout->addWidget(duplicatesTableView,5,1,gridLayout->rowCount(),gridLayout->columnCount()-1);
    qDebug() << gridLayout->columnCount();
    qDebug() << gridLayout->rowCount();

//connect the add button to the showAddpopup window
    connect(addButton, SIGNAL(clicked()), this, SLOT(showAddPopupWindow()));

}
QDialog* IdentifyDuplicatesPageWidget::createAddPopupWindow()
{
    Addpopup = new QDialog(this);
    Addpopup->setWindowTitle("add");
    Addpopup->setFixedSize(400, 200);

    QLabel* titleLabel = new QLabel("path",Addpopup );

    QPushButton* addButton = new QPushButton("add", Addpopup);
    addButton->setFixedSize(100,50);

    pathLineEdit = new QLineEdit(Addpopup);

    connect(addButton, SIGNAL(clicked()), this, SLOT(addButtonClicked()));

    QGridLayout* layout = new QGridLayout(Addpopup);
    layout->addWidget(titleLabel,2,0,1,1);
    qDebug() << layout->columnCount();
    qDebug() << layout->rowCount();
    layout->addWidget(pathLineEdit,1,1,layout->rowCount(),3);
    layout->addWidget(addButton,layout->rowCount(),2,1,1);
    Addpopup->setLayout(layout);
    return Addpopup;
}
void IdentifyDuplicatesPageWidget::addButtonClicked()
{
    QString path = pathLineEdit->text();
    searchingPaths.push_back(path.toStdString());
    pathsBrowser->append(path);
    Addpopup->close();
}
void IdentifyDuplicatesPageWidget::setTheTable(std::vector<std::vector<std::string>> duplicates)
{
    fillTheModel(duplicatesTableModel,duplicates);
    duplicatesTableView->setModel(duplicatesTableModel);
}

void IdentifyDuplicatesPageWidget::fillTheModel(QStandardItemModel *model,std::vector<std::vector<std::string>> duplicates)
{
    for (int i = 0; i < duplicates.size(); ++i) {
        for (int j = 0; j < duplicates[i].size(); ++j) {
            QString itemData = QString::fromStdString(duplicates[i][j]) ;
            QStandardItem *item = new QStandardItem(itemData);
            model->setItem(i, j, item);
        }
    }
}

void IdentifyDuplicatesPageWidget::showAddPopupWindow()
{
    QDialog* Addpopup =createAddPopupWindow();
    Addpopup->show();
}


