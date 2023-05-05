#include "searchfilewidget.h"

#include <QBoxLayout>

searchfilewidget::searchfilewidget(QWidget *parent)
    : QWidget{parent}
{
    // Create a new QTableWidget with two column
    tableWidget = new QTableWidget(0, 2, this);
    // Set the headers for the table
    tableWidget->setHorizontalHeaderLabels({"Line Number", "File Path"});

    // Set the size policy for the table widget
    tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Set the width of the columns
    tableWidget->setColumnWidth(0, 100); // left column
    tableWidget->setColumnWidth(1, 300); // right column

    // Set the size policy for the table widget
    tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Create a vertical layout and add the table widget to it
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(tableWidget);

    // Center the layout vertically and horizontally
    layout->setAlignment(Qt::AlignCenter);
}

void searchfilewidget::recieveSearchContentMapFromCont(std::map<int, std::string> result)
{
    // Clear the existing rows in the table
    tableWidget->setRowCount(0);

    // Iterate through the map and add each key-value pair to the table
    for (const auto& pair : result) {
        int row = tableWidget->rowCount();
        tableWidget->insertRow(row);
        tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(pair.first)));
        tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(pair.second)));
    }
}


