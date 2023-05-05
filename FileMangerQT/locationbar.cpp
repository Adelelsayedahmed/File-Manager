#include "locationbar.h"

LocationBar::LocationBar(QFileSystemModel *model, QString path, QWidget *parent)
    : QWidget{parent}
{
    locationBar = new QLineEdit(this);
    dModel = model;
    dIndex = dModel->setRootPath(path);
    completer = new QCompleter(model, this);

    locationBar->setPlaceholderText(path);
    completer->setCompletionMode(QCompleter::PopupCompletion);

}

