#include "searchfilewidget.h"
#include <QHeaderView>
#include <QBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QStandardItemModel>
#include <QMessageBox>


searchfilewidget::searchfilewidget(QWidget *parent)
    : QWidget{parent}
{

    this->allocateWidget();
    this->initiateSearchFilePage();
    this->mRegisterSignals();
   // searchString  = "adel" ;

}


void searchfilewidget::recieveSearchContentMapFromCont(const std::multimap<int, std::string>&result)
{
    clearResultTable();
    fillResultTableModel(result);
}

void searchfilewidget::onAddPathButton()
{
    searchPopUp->show();
}

void searchfilewidget::CallSearchContentBE()
{
    this->clearResultTable();
    this->fillPathVector();
    if (isValidEnteredString() == true && filePaths.empty() == false) // check the the Entered String and paths
    {
        emit searchContentPathsSignal(filePaths, searchString);
        //this->clearPathsTable();
    }
    else if (!isValidEnteredString()) {
        this->raiseEmptyStringError();
    }
    else if (filePaths.empty()) {
        this->raiseEmptyPathsError();
    }

}

void searchfilewidget::recieveFilePathFromPopUp(QString lineValue)
{
    // check the valid path
    this->fillPathTableModel(lineValue);

}

void searchfilewidget::onRemovePathButton()
{
    QItemSelectionModel *selectionModel = tablePathsWidget->selectionModel();
    QModelIndexList selectedRows = selectionModel->selectedRows();

    for (int i = selectedRows.size() - 1; i >= 0; i--) {
        QModelIndex index = selectedRows.at(i);
        tablePathsWidget->model()->removeRow(index.row());
    }

    qInfo()<<"removed\n";
}

void searchfilewidget::fillResultTableModel(const std::multimap<int, std::string>&result)
{
    // Iterate through the map and add each key-value pair to the table
    for (const auto& pair : result) {
        int row = tableResultWidget->rowCount();
        tableResultWidget->insertRow(row);
        QTableWidgetItem* l_item = new QTableWidgetItem(QString::number(pair.first));
        QTableWidgetItem* r_item = new QTableWidgetItem(QString::fromStdString(pair.second));
        l_item->setTextAlignment(Qt::AlignCenter); // center align the contents of the item
        tableResultWidget->setItem(row, 0, l_item);
        tableResultWidget->setItem(row, 1, r_item);
    }

}

void searchfilewidget::fillPathTableModel(const QString &lineValue)
{
    int row = tablePathsWidget->rowCount();
    tablePathsWidget->insertRow(row);
    QTableWidgetItem* item = new QTableWidgetItem(lineValue);
    tablePathsWidget->setItem(row,0,item);

}

void searchfilewidget::raiseEmptyStringError()
{
    QMessageBox::warning( this,"Error", QString::fromStdString("enter a non empty search string"));

}

void searchfilewidget::raiseEmptyPathsError()
{
    QMessageBox::warning( this,"Error", QString::fromStdString("enter at least file path"));

}


void searchfilewidget::fillPathVector()
{
    filePaths.clear();
    QStringList paths;

    for (int row = 0; row < tablePathsWidget->model()->rowCount(); ++row) {
        QModelIndex index = tablePathsWidget->model()->index(row, 0);
        QString path = tablePathsWidget->model()->data(index).toString();
        paths << path;
    }

    for (QString path : paths) {
        filePaths.push_back(path.toStdString());
    }

}

void searchfilewidget::clearResultTable()
{
      tableResultWidget->setRowCount(0);
}

void searchfilewidget::clearPathsTable()
{
      tablePathsWidget->setRowCount(0);
}

void searchfilewidget::mRegisterSignals()
{
      connect(searchButton,&QPushButton::clicked , this , &searchfilewidget::CallSearchContentBE);
      connect(addPathButton,&QPushButton::clicked,this,&searchfilewidget::onAddPathButton);
      connect(searchPopUp , &rename_widget::new_file_name_button_clicked,this ,&searchfilewidget::recieveFilePathFromPopUp);
      connect(removePathButton,&QPushButton::clicked , this , &searchfilewidget::onRemovePathButton);
}

bool searchfilewidget::isValidEnteredString()
{
      bool returnFlag = true ;
      QString temp = searchLine->text() ;
      if ( temp.isEmpty() )
      {
        returnFlag =  false ;
      }
      else
      {
        this->searchString = temp.toStdString();
      }
      return returnFlag ;
}


void searchfilewidget::initiateSearchFilePage()
{
    searchLine->setPlaceholderText("search here");
    searchLine->setAlignment(Qt::AlignCenter);

    // Set the headers for the table
    tableResultWidget->setHorizontalHeaderLabels({"Line Number", "File Path"});
    tablePathsWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("File Path"));

    // Set the size policy for the table widget
    tableResultWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    tablePathsWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Set the width of the columns
    tableResultWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    tableResultWidget->setColumnWidth(0, 100); // left column
    tableResultWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch); // right column

    tablePathsWidget->setColumnWidth(0, 400);

    // Create a horizontal layout for the button and add the button to it

    addPathButton->setStyleSheet("background-color: green");

    removePathButton->setEnabled(true);
    removePathButton->setStyleSheet("background-color: red");

    button_layout->addWidget(addPathButton);
    button_layout->addWidget(removePathButton);
    lineButtonHlayout->addWidget(searchButton);
    lineButtonHlayout->addWidget(searchLine);
    hLayOut->addLayout(button_layout);
    hLayOut->addWidget(tablePathsWidget);

    // Create a vertical layout and add the button layout and table widget to it

    layout->addLayout(hLayOut);
    layout->addLayout(lineButtonHlayout);

    // Add the table widget and center the layout vertically and horizontally
    layout->addWidget(tableResultWidget);
    layout->setAlignment(Qt::AlignCenter);

}

void searchfilewidget::allocateWidget()
{
    // Create a new QTableWidget with two column
    tableResultWidget = new QTableWidget(0, 2, this);
    tablePathsWidget  = new QTableWidget(0,1,this);
    //tablePathsWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tablePathsWidget->horizontalHeader()->setStyleSheet("QHeaderView::section { border: 1px solid black; }");
   // tablePathsWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    searchLine = new QLineEdit(this);
    hLayOut = new QHBoxLayout();
    button_layout = new QVBoxLayout();
    lineButtonHlayout = new QHBoxLayout();
    addPathButton= new QPushButton("add path", this);
    removePathButton = new QPushButton("remove path",this);
    searchButton= new QPushButton("search", this);
    layout = new QVBoxLayout(this);
    searchPopUp = new rename_widget("add","please enter a valid file path","\tfile path\t");
}

searchfilewidget::~searchfilewidget()
{
    delete tableResultWidget ;
    delete tablePathsWidget ;
    delete searchLine ;
    delete hLayOut ;
    delete button_layout ;
    delete lineButtonHlayout ;
    delete addPathButton ;
    delete removePathButton ;
    delete searchButton ;
    delete layout ;
    delete searchPopUp ;
}

