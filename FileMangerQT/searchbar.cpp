#include "searchbar.h"

SearchBar::SearchBar(QWidget *parent)
    : QWidget{parent}
{
    layout = new QHBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    findButton = new QPushButton(this);
    searchBar = new QLineEdit(this);
    locationBar = new QLineEdit(this);

    layout->addWidget(locationBar);
    layout->addWidget(searchBar);
    layout->addWidget(findButton);

    findButton->setText("Search");
    findButton->setCursor(Qt::PointingHandCursor);

    connect(findButton, &QPushButton::pressed, this, &SearchBar::on_findButton_pressed);

}

void SearchBar::locationChanged(QString filepath, QString filename)
{
    dfilePath = filepath;
    searchBar->clear();
    searchBar->setPlaceholderText("Search " + filename);
    locationBar->setPlaceholderText(filepath);
}


void SearchBar::on_findButton_pressed()
{
    SearchWindow *window = new SearchWindow(this);
    emit SearchWindowCreated(window);

    //Set file path to search in and show results
    window->show();
    window->search(dfilePath, searchBar->text());


}
