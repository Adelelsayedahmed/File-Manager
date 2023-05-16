#ifndef LOCATIONBAR_H
#define LOCATIONBAR_H
#include <QWidget>
#include <QLineEdit>
#include <QCompleter>
#include <QFileSystemModel>
#include <QShortcut>
#include  <QHBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>
#include <boost/filesystem.hpp>
class LocationBar : public QWidget
{
    Q_OBJECT
public:
    explicit LocationBar(QWidget *parent = nullptr);
    QLineEdit *locationBar;
    QPushButton *backButton;
private:
    QCompleter *completer;
    QFileSystemModel *dModel;
    QString currentRoot;
    QHBoxLayout *layout;

public slots:
    void initialize(QFileSystemModel *model, QModelIndex index);
    void locationChanged(QString filepath);
    void validatePath();
    void backButtonPressed();
signals:
    void validPath(QString path);
    void sigBackButtonPressed();

};

#endif // LOCATIONBAR_H
