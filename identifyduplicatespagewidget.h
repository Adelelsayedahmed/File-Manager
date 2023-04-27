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
#include <QItemSelection>
#include <QMessageBox>
#include <QMenu>
#include "identifyduplicates.h"

class IdentifyDuplicatesPageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IdentifyDuplicatesPageWidget(QWidget *parent = nullptr,IdentifyDuplicates* duplicatesObj=nullptr);

    void setTheTable(std::vector<std::vector<std::string>> duplicates);

private:
    IdentifyDuplicates* duplicatesObj;

    QGridLayout *gridLayout;

    QLabel *pathsLabel;

    QPushButton *addButton;

    QPushButton *removeButton;

    QPushButton *identifyDuplicatesButton;

    QTableView *pathsTableView;

    QStandardItemModel *pathsTableModel;

    QTableView *duplicatesTableView;

    QStandardItemModel *duplicatesTableModel;

    QLineEdit* pathLineEdit;

    QDialog* Addpopup;

    std::vector<boost::filesystem::path> searchingPaths;

    std::vector<std::vector<std::string>> duplicates;

    void fillTheModel(QStandardItemModel *model,std::vector<std::vector<std::string>> duplicates);

    QDialog* createAddPopupWindow();

    QMenu menu;

    QAction *deleteAction;

    QModelIndex selectedDuplicateIndex;

    void initializeThePage();

    void initializeTables();

    void setPageConnections();

public slots:
    void showAddPopupWindow();

    void addButtonClicked();

    void duplicatesSlot();

    void updateDuplicatesTableSlot();

    void rowSelected(const QItemSelection& selected, const QItemSelection& deselected);

    void removeSelectedRow();

    void showMenu(const QModelIndex &index);

    void deleteSlot();
signals:

    void updateDuplicatesTable();

};

#endif // IDENTIFYDUPLICATESPAGEWIDGET_H