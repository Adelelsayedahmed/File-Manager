#include "searchwindow.h"
#include "ui_searchwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QFileInfo>

#define NO_OF_FIELDS 2
#define EMPTY 0
#define NAME_COLUMN 0
#define TYPE_COLUMN 1

SearchWindow::SearchWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SearchWindow)
{
    ui->setupUi(this);  

     //Disable edit of results table
      ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

      QStringList labels;

      //Set table labels and dimensions
      labels <<"Path"<<"Type";
      ui->tableWidget->setColumnCount(NO_OF_FIELDS);
      ui->tableWidget->setColumnWidth(0,650);
      ui->tableWidget->setColumnWidth(1,150);
      ui->tableWidget->setHorizontalHeaderLabels(labels);



}

void SearchWindow::search(QString filepath, QString filename)
{
    //Set fillepath to search in
    dfilePath = filepath;

     //Initialize search parameters
     std::string path = dfilePath.toStdString();
     std::string file_name = filename.toStdString();
     std::vector<std::string> file_paths;

     QString temp;

     //Emit search signal
     emit searchForFileByName(path, file_name, file_paths);
     qDebug() <<file_paths.size();


     if( file_paths.size()> EMPTY )
     {   //Set number of results in table
         ui->tableWidget->setRowCount(file_paths.size());

         //Loop over table cells
         for( int rowIndex = 0; rowIndex < ui->tableWidget->rowCount(); rowIndex++)
         {
              temp = QString::fromStdString(file_paths[rowIndex]);

              for( int columnIndex = 0; columnIndex < NO_OF_FIELDS; columnIndex++)
              {

                  QTableWidgetItem *tempItem = new QTableWidgetItem();

                  //Set result name
                  if(columnIndex == NAME_COLUMN)
                  {
                      tempItem->setText(temp);
                      ui->tableWidget->setItem(rowIndex, NAME_COLUMN, tempItem);
                  }

                  //Set result type
                  if(columnIndex == TYPE_COLUMN)
                  {
                      QFileInfo file(temp);

                      //Check if result type is folder or file
                      if(file.isDir())
                          tempItem->setText("Folder");
                      else
                         tempItem->setText(file.suffix() + " File");

                      //Insert item in table
                      ui->tableWidget->setItem(rowIndex, TYPE_COLUMN, tempItem);
                  }


              }
         }
         this->show();
     }

     //If no results returned
     else
        { QMessageBox msg;
          msg.setText("No Results found.");
          msg.exec();;
      }

}

SearchWindow::~SearchWindow()
{
    delete ui;
}

void SearchWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    //Check is cell clicked is a file or folder to open
    //If cell clicked is a type, do nothing
    if(column == NAME_COLUMN)
    {
        //Get filepath
        QString filePath = ui->tableWidget->item(row,  NAME_COLUMN)->text();

       //If cell clicked is folder
        if(ui->tableWidget->item(row, TYPE_COLUMN)->text() == "Folder")
        {
            this->hide();
            emit folderClicked(filePath);
        }

        //If cell clicked is file
        else
        {
            //Open file in content view
            contentUi = new FileContentView(this);
            contentUi->file = new QFile (filePath);
            if (!contentUi->file->open(QIODevice::ReadWrite))
                return;
            QString fileContents = contentUi->file->readAll();

            contentUi->ui->textEdit->clear();
            contentUi->ui->textEdit->setPlainText(fileContents);
            contentUi->show();
        }
    }


}

