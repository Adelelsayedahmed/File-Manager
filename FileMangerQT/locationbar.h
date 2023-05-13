#ifndef LOCATIONBAR_H
#define LOCATIONBAR_H

#include <QWidget>
#include <QLineEdit>
#include <QCompleter>
#include <QFileSystemModel>
#include <QShortcut>


class LocationBar : public QWidget
{
    Q_OBJECT
public:
    explicit LocationBar(QWidget *parent = nullptr);

private:
    QLineEdit *locationBar;
    QCompleter *completer;
    QFileSystemModel *dModel;
    QString currentRoot;

public slots:
    void initialize(QFileSystemModel *model, QModelIndex index);
    void locationChanged(QString filepath);
    void validatePath();
signals:
    void validPath(QString path);

};

#endif // LOCATIONBAR_H
