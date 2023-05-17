#include "searchbar.h"

SearchBar::SearchBar(QWidget *parent)
    : QWidget{parent}
{
    layout = new QHBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    findButton = new QPushButton(this);
    searchBar = new QLineEdit(this);
    bar = new LocationBar(this);
    backButton = new QPushButton(this);



    layout->insertWidget(0,bar);
    layout->insertWidget(1,searchBar);
    layout->insertWidget(2,findButton);

    findButton->setText("Search");
    findButton->setCursor(Qt::PointingHandCursor);

    connect(findButton, &QPushButton::pressed, this, &SearchBar::on_findButton_pressed);
    connect(bar, &LocationBar::sigBackButtonPressed, this, &SearchBar::backButtonPressed);
    connect(this, &SearchBar::changeLocationBar, bar, &LocationBar::locationChanged);

}


void SearchBar::initializeLocationBarModel(QFileSystemModel *model, QModelIndex index)
{
   bar->initialize(model, index);
}

void SearchBar::locationChanged(QString filepath, QString filename)
{
    dfilePath = filepath;
    searchBar->clear();
    searchBar->setPlaceholderText("Search " + filename);
    emit changeLocationBar(filepath);
}

void SearchBar::backButtonPressed()
{
    emit backButtonPressedSignal();
}


void SearchBar::on_findButton_pressed()
{
    SearchWindow *window = new SearchWindow(this);
    emit SearchWindowCreated(window);

    //Set file path to search in and show results
    window->search(dfilePath, searchBar->text());
}
