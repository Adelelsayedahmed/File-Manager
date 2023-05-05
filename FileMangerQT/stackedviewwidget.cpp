#include "stackedviewwidget.h"


stackedviewwidget::stackedviewwidget(QWidget *parent)
{
    // Create the stacked widget
        stackedWidget = new QStackedWidget(this);

        // Create the explorer widget and add it to the stacked widget
        explorer = new Explorer("", this);
        stackedWidget->addWidget(explorer);

        // Create the two pane widget and add it to the stacked widget
        twoPane = new TwoPane(this);
        stackedWidget->addWidget(twoPane);

        // Create the identify duplicates widget and add it to the stacked widget
        duplicatesPage=new IdentifyDuplicatesPageWidget(this);
        stackedWidget->addWidget(duplicatesPage);


        // Create the next and previous buttons
        nextButton = new QPushButton("Next", this);
        previousButton = new QPushButton("Previous", this);

        // Connect the next and previous buttons to the slots that change the current index of the stacked widget
        connect(nextButton, &QPushButton::clicked, this, &stackedviewwidget::nextPane);
        connect(previousButton, &QPushButton::clicked, this, &stackedviewwidget::previousPane);

        // Add the stacked widget and buttons to the layout of the stacked view widget
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(stackedWidget);
        QHBoxLayout *buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(previousButton);
        buttonLayout->addWidget(nextButton);
        layout->addLayout(buttonLayout);
}

void stackedviewwidget::nextPane()
{
    int index = stackedWidget->currentIndex();
        index++;
        if (index >= stackedWidget->count())
            index = 0;
        stackedWidget->setCurrentIndex(index);
}

void stackedviewwidget::previousPane()
{
    int index = stackedWidget->currentIndex();
       index--;
       if (index < 0)
           index = stackedWidget->count() - 1;
       stackedWidget->setCurrentIndex(index);
}
void stackedviewwidget::switchToIndex(int index)
{
       if (index >= 0 && index < stackedWidget->count()) {
           stackedWidget->setCurrentIndex(index);
       }
}
