#ifndef IDENTIFYDUPLICATESPAGEWIDGET_H
#define IDENTIFYDUPLICATESPAGEWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextBrowser>
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QDialog>
#include <QLineEdit>
class IdentifyDuplicatesPageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IdentifyDuplicatesPageWidget(QWidget *parent = nullptr);

    void setTheTable(std::vector<std::vector<std::string>> duplicates);

private:
    QTableView *duplicatesTableView;

    QStandardItemModel *duplicatesTableModel;

    void fillTheModel(QStandardItemModel *model,std::vector<std::vector<std::string>> duplicates);

    QDialog* createAddPopupWindow();

    QLineEdit* pathLineEdit;

    QDialog* Addpopup;

    std::vector<std::string> searchingPaths;

    QTextBrowser *pathsBrowser;

public slots:
    void showAddPopupWindow();

    void addButtonClicked();
signals:


};

#endif // IDENTIFYDUPLICATESPAGEWIDGET_H
