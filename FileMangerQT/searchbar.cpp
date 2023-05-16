#include "searchbar.h"

SearchBar::SearchBar(QWidget *parent)
    : QWidget{parent}
{
    layout = new QHBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    findButton = new QPushButton(this);
    searchBar = new QLineEdit(this);
    bar = new LocationBar(this);
//    bar->locationBar = new  QLineEdit(this);
//    searchBar->resize(300,25);
    backButton = new QPushButton(this);

    QString parentPath=QString::fromStdString(boost::filesystem::path(__FILE__).parent_path().string());
    parentPath +="/up-arrow.png";
    QPixmap image(parentPath);
    QIcon icon(image);
    backButton->setIcon(icon);

    layout->insertWidget(0,backButton);
    layout->insertWidget(1,bar);
    layout->insertWidget(2,searchBar);
    layout->insertWidget(3,findButton);

    findButton->setText("Search");
    findButton->setCursor(Qt::PointingHandCursor);

    connect(findButton, &QPushButton::pressed, this, &SearchBar::on_findButton_pressed);
    connect(backButton, &QPushButton::pressed, this, &SearchBar::backButtonPressed);
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
