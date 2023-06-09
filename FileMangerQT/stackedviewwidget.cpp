#include "stackedviewwidget.h"


stackedviewwidget::stackedviewwidget(QWidget *parent)
{
    // Create the stacked widget
        stackedWidget = new QStackedWidget(this);

        // Create the explorer widget and add it to the stacked widget
        explorer = new Explorer("", this);
        stackedWidget->addWidget(explorer);


        // Create the identify duplicates widget and add it to the stacked widget
        duplicatesPage=new IdentifyDuplicatesPageWidget(this);
        stackedWidget->addWidget(duplicatesPage);

        // Create the two pane widget and add it to the stacked widget
        twoPane = new TwoPane(this);
        stackedWidget->addWidget(twoPane);

        // Create the search files content page
        file_search_wedge_obj = new searchfilewidget(this);
        stackedWidget->addWidget(file_search_wedge_obj);



        // Connect the next and previous buttons to the slots that change the current index of the stacked widget


        // Add the stacked widget and buttons to the layout of the stacked view widget
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(stackedWidget);


        connect(file_search_wedge_obj,&searchfilewidget::searchContentPathsSignal,this,&stackedviewwidget::recieveFromContentSearchWedgit);

}

void stackedviewwidget::nextPane()
{
    int index = stackedWidget->currentIndex();
        emit indexAboutToChange(index);
        index++;
        if (index >= stackedWidget->count()){
            index = 0;
        }

              emit currentIndexChanged(index);
        stackedWidget->setCurrentIndex(index);
}

void stackedviewwidget::previousPane()
{
    int index = stackedWidget->currentIndex();
        emit indexAboutToChange(index);
        index--;
        if (index < 0){
           index = stackedWidget->count() - 1;
        }

       emit currentIndexChanged(index);
        stackedWidget->setCurrentIndex(index);
}

void stackedviewwidget::recieveFromContentSearchWedgit(const std::vector<std::string> &filePaths, const std::string &searchString)
{
    emit passingContentSearchToView(filePaths , searchString);
}
void stackedviewwidget::switchToIndex(int index)
{
       if (index >= 0 && index < stackedWidget->count()) {
           int oldIndex=stackedWidget->currentIndex();
           emit indexAboutToChange(oldIndex);//hard coded
           emit currentIndexChanged(index);// hard coded
           stackedWidget->setCurrentIndex(index);
       }
}
