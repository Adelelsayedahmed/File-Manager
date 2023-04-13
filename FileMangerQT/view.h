#ifndef VIEW_H
#define VIEW_H
#include <QFileSystemModel>
#include <QDesktopServices>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE

class View : public QMainWindow
{
    Q_OBJECT
private:
    QFileSystemModel* fileSystemModel;
public:
    View(QWidget *parent = nullptr);
    void TreeView();
    void TableView(const QModelIndex &index);
    ~View();

private slots:
    void on_treeView_clicked(const QModelIndex &index);

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::View *ui;
};
#endif // VIEW_H
