#include "identifyduplicatespagewidget.h"

IdentifyDuplicatesPageWidget::IdentifyDuplicatesPageWidget(QWidget *parent,IdentifyDuplicates* duplicatesObj)
    : QWidget{parent}
{
    this->duplicatesObj=duplicatesObj;

    initializeThePage();

    setPageConnections();

    showThePage();


}

void IdentifyDuplicatesPageWidget::initializeThePage()
{

    gridLayout = new QGridLayout(this);

    pathsLabel=new QLabel;
    pathsLabel->setText("searching paths");
    pathsLabel->setFixedSize(110,35);

    gridLayout->addWidget(pathsLabel,0,1);

    addButton=new QPushButton("add path");
    addButton->setFixedSize(100,30);
    addButton->setStyleSheet("background-color: green");

    gridLayout->addWidget(addButton,1,0);

    removeButton=new QPushButton("remove path");
    removeButton->setFixedSize(100,30);
    removeButton->setEnabled(false);
    removeButton->setStyleSheet("background-color: #f0f0f0; color: #808080;");

    gridLayout->addWidget(removeButton,2,0);

    initializeTables();

}
void IdentifyDuplicatesPageWidget::showThePage()
{
    dialog=new QDialog(this);
    dialog->setMinimumSize(750,650);
    dialog->setLayout(gridLayout);
    dialog->show();
}
void IdentifyDuplicatesPageWidget::initializeTables()
{
    pathsTableView= new QTableView(this);

    pathsTableModel= new QStandardItemModel();
    pathsTableModel->setColumnCount(1);
    pathsTableModel->setHeaderData(0,Qt::Horizontal,"paths");
    pathsTableView->setModel(pathsTableModel);
    pathsTableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    pathsTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    gridLayout->addWidget(pathsTableView, 1, 1, 3, gridLayout->columnCount()-1);

    identifyDuplicatesButton=new QPushButton("check duplicates");
    identifyDuplicatesButton->setFixedSize(120,30);

    gridLayout->addWidget(identifyDuplicatesButton, gridLayout->rowCount(),2 , 1, 1);

    duplicatesTableView= new QTableView(this);

    duplicatesTableModel= new QStandardItemModel();
    duplicatesTableModel->setColumnCount(1);
    duplicatesTableModel->setHeaderData(0,Qt::Horizontal,"file/directory name");
    //duplicatesTableModel->setHeaderData(1,Qt::Horizontal,"file/directory size");

    duplicatesTableView->setModel(duplicatesTableModel);
    duplicatesTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    duplicatesTableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    duplicatesTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QHeaderView* verticalHeader = duplicatesTableView->verticalHeader();
    verticalHeader->setVisible(false);
    //duplicatesTableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);


    gridLayout->addWidget(duplicatesTableView,5,1,gridLayout->rowCount(),gridLayout->columnCount()-1);
}
void IdentifyDuplicatesPageWidget::setPageConnections()
{
    connect(addButton, SIGNAL(clicked()), this, SLOT(showAddPopupWindow()));
    connect(identifyDuplicatesButton, SIGNAL(clicked()), this, SLOT(duplicatesSlot()));
    connect(this, &IdentifyDuplicatesPageWidget::removedItem, this, &IdentifyDuplicatesPageWidget::duplicatesSlot);
    connect(this, &IdentifyDuplicatesPageWidget::updateDuplicatesTable, this, &IdentifyDuplicatesPageWidget::updateDuplicatesTableSlot);
    connect(pathsTableView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &IdentifyDuplicatesPageWidget::rowSelected);
    connect(removeButton, &QPushButton::clicked, this, &IdentifyDuplicatesPageWidget::removeSelectedRow);
    connect(duplicatesTableView, QOverload<const QModelIndex &>::of(&QTableView::clicked), this, &IdentifyDuplicatesPageWidget::showMenu);

}
QDialog* IdentifyDuplicatesPageWidget::createAddPopupWindow()
{
    Addpopup = new QDialog(this);
    Addpopup->setWindowTitle("add path");
    Addpopup->setFixedSize(400, 200);

    QLabel* titleLabel = new QLabel("path",Addpopup );

    QPushButton* addButton = new QPushButton("add", Addpopup);
    addButton->setFixedSize(100,50);

    pathLineEdit = new QLineEdit(Addpopup);
    pathLineEdit->setPlaceholderText("Write the path here");

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
    if(duplicatesObj->checkPathValidation(duplicatesObj->convertStringToPath(path.toStdString()))){
        searchingPaths.push_back(duplicatesObj->convertStringToPath(path.toStdString()));
        QString itemData = QString::fromStdString(path.toStdString()) ;
        QStandardItem *item = new QStandardItem(itemData);
        pathsTableModel->appendRow(item);
        pathsTableView->setModel(pathsTableModel);
        Addpopup->close();
    }
    else
    {
     QMessageBox::critical(this, "Error", "The path is not valid.");
    }


}

void IdentifyDuplicatesPageWidget::setTheTable(std::vector<std::vector<std::string>> duplicates)
{
    fillTheModel(duplicatesTableModel,duplicates);
    duplicatesTableView->setModel(duplicatesTableModel);
}

void IdentifyDuplicatesPageWidget::fillTheModel(QStandardItemModel *model,std::vector<std::vector<std::string>> duplicates)
{
    model->removeRows(0, model->rowCount());
    std::vector<QColor> colors = {QColor("#1f77b4"), QColor("#ff7f0e"), QColor("#2ca02c"), QColor("#d62728"), QColor("#9467bd"), QColor("#8c564b"), QColor("#e377c2"), QColor("#7f7f7f"), QColor("#bcbd22"), QColor("#17becf")};

    // Map to keep track of the color assigned to each group of duplicates
    std::unordered_map<std::string, QColor> colorMap;

    for (int i = 0; i < duplicates.size(); ++i) {
     std::string groupId = duplicates[i][0]; // The first element of the group is used as the group ID

     // Check if the group already has a color assigned
     QColor groupColor;
     if (colorMap.count(groupId) == 0) {
         // Assign the next available color from the color palette
         groupColor = colors[i % colors.size()];
         colorMap[groupId] = groupColor;
     } else {
         groupColor = colorMap[groupId];
     }

     for (int j = 0; j < duplicates[i].size(); ++j) {
         QString itemData = QString::fromStdString(duplicates[i][j]);
         QStandardItem *item = new QStandardItem(itemData);
         item->setBackground(QBrush(groupColor)); // Set the background color to the color assigned to the group
         model->appendRow(item);
     }
    }
}

void IdentifyDuplicatesPageWidget::showAddPopupWindow()
{
    QDialog* Addpopup =createAddPopupWindow();
    Addpopup->show();
}


void IdentifyDuplicatesPageWidget::duplicatesSlot()
{
   duplicates= duplicatesObj->checkDuplication(searchingPaths);
    emit updateDuplicatesTable();
}

void IdentifyDuplicatesPageWidget::updateDuplicatesTableSlot()
{
    setTheTable(duplicates);
}

void IdentifyDuplicatesPageWidget::rowSelected(const QItemSelection& selected, const QItemSelection& deselected)
{
     if (!deselected.isEmpty())
    {
        removeButton->setStyleSheet("background-color: #f0f0f0; color: #808080;");
        removeButton->setEnabled(false);
    }
    else
    {
        removeButton->setStyleSheet("background-color: red;");
        removeButton->setEnabled(!selected.isEmpty());
    }
}
void IdentifyDuplicatesPageWidget::removeSelectedRow()
{
    QModelIndexList selectedRows = pathsTableView->selectionModel()->selectedRows();
    if (selectedRows.size() > 0) {
        int row = selectedRows[0].row();
        searchingPaths.erase(searchingPaths.begin() + row);
        pathsTableModel->removeRow(row);
        removeButton->setEnabled(false);
    }
}

void IdentifyDuplicatesPageWidget::showMenu(const QModelIndex &index)
{
    if (index.isValid() && index.model() == duplicatesTableModel)
    {
        QString value = duplicatesTableModel->data(duplicatesTableModel->index(index.row(), 0)).toString();
        if (value != "" && value !="Duplicates") // replace with the value you want to exclude
        {
        menu.clear();
        selectedDuplicateIndex = index;
        deleteAction = menu.addAction("delete the selected item");
        connect(deleteAction, &QAction::triggered, this, &IdentifyDuplicatesPageWidget::deleteSlot);
        menu.exec(duplicatesTableView->viewport()->mapToGlobal(duplicatesTableView->visualRect(index).center()));
        }
    }
}

void IdentifyDuplicatesPageWidget::deleteSlot()
{
    if (selectedDuplicateIndex.isValid())
    {
        QString filePath = selectedDuplicateIndex.data().toString();
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Delete item?", "Do you want to delete the file/directory \"" + filePath + "\"?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            boost::filesystem::remove_all(boost::filesystem::path(filePath.toStdString()));
            duplicatesTableModel->removeRow(selectedDuplicateIndex.row());
            selectedDuplicateIndex = QModelIndex();
            emit removedItem();
        }
    }
}
