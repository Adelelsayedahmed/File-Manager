#include "locationbar.h"

LocationBar::LocationBar(QWidget *parent)
    : QWidget{parent}
{
    layout =  new QHBoxLayout(this);
    locationBar = new  QLineEdit(this);
    layout->addWidget(locationBar);
}

void LocationBar::initialize(QFileSystemModel *model, QModelIndex index)
{
    //  Set model of completer
    dModel = new QFileSystemModel(model);
    dModel->setFilter(QDir::Dirs);
    dModel->setRootPath(dModel->filePath(index));
    currentRoot = dModel->filePath(index);
    completer = new QCompleter(model);
    completer->setCompletionMode(QCompleter::PopupCompletion);

    //    Assign completer to location bar
    locationBar->setCompleter(completer);

    locationBar->setText(model->filePath(index));


    //    Connect signals
    connect(locationBar,  SIGNAL(returnPressed()), this, SLOT(validatePath()));
    connect(completer, QOverload<const QString &>::of(&QCompleter::activated),this, &LocationBar::validatePath);

}

void LocationBar::locationChanged(QString filepath)
{
    //   This needs to be connected with a signal sending the new file path when location changes
    //   Change line edit text and root path of model
    locationBar->setText(filepath);
    dModel->setRootPath(filepath);
    currentRoot = filepath;
}

void LocationBar::validatePath()
{
    //    This validates the path entered when the user clicks on the popup OR presses enter when the location bar is selected
    //    The signal emitted contains the validated path
    QDir dir(dModel->rootDirectory());
    if(dir.exists(locationBar->text()))
    {
        qDebug() <<locationBar->text()<<" exists!";
        emit validPath(locationBar->text());

    }
    else
        qDebug() <<"Invalid!!";
}


