#include "locationbar.h"

LocationBar::LocationBar(QWidget *parent)
    : QWidget{parent}
{
    locationBar = new QLineEdit(parent);
}

void LocationBar::initialize(QFileSystemModel *model, QModelIndex index)
{
    dModel = new QFileSystemModel(model);
    dModel->setFilter(QDir::Dirs);
    dModel->setRootPath(dModel->filePath(index));

    currentRoot = dModel->filePath(index);
    completer = new  QCompleter(model, this);
    completer->setCompletionMode(QCompleter::PopupCompletion);

    locationBar->setText(model->filePath(index));
    locationBar->setCompleter(completer);

    QShortcut *validate = new QShortcut(QKeySequence("Return"), locationBar);
    QObject::connect(validate, SIGNAL(activated()), this, SLOT(validatePath()));
    connect(completer, QOverload<const QString &>::of(&QCompleter::activated),this, &LocationBar::validatePath);

}

void LocationBar::locationChanged(QString filepath)
{
    locationBar->setText(filepath);
    dModel->setRootPath(filepath);
    currentRoot = filepath;
}

void LocationBar::validatePath()
{
//    QString current;
//    current = dModel->rootPath();
//    current = current
    QDir dir(dModel->rootDirectory());
    if(dir.exists(locationBar->text()))
    {
        qDebug() <<locationBar->text()<<" exists!";
        emit validPath(locationBar->text());

    }
    else
        qDebug() <<"Invalid!!";
}


