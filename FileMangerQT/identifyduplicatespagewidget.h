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
#include "filecontentview.h"
#include "identifyduplicates.h"

class IdentifyDuplicatesPageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IdentifyDuplicatesPageWidget(QWidget *parent = nullptr);

    void setTheTable(std::vector<std::vector<std::string>> duplicates);

    void setDuplicatesObject(IdentifyDuplicates* duplicatesObj);


private:
    IdentifyDuplicates* duplicatesObj;

    QGridLayout *gridLayout;

    QDialog *dialog;

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

    QAction *openAction;

    QAction *deleteAction;

    FileContentView *contentUi;

    QModelIndex selectedDuplicateIndex;

    std::string toBeRemovedPath;

    void initializeThePage();

    void initializeTables();

    void setPageConnections();

    void showThePage();

    void duplicatesDeletion();


public slots:
    void showAddPopupWindow();

    void addButtonClicked();

    void duplicatesSlot();

    void duplicationInThread();

    void updateDuplicatesTableSlot();

    void rowSelected(const QItemSelection& selected, const QItemSelection& deselected);

    void removeSelectedRow();

    void showMenu(const QModelIndex &index);

    void deleteSlot();

    void openSlot(QString filePath);

signals:

    void updateDuplicatesTable();

    void removedItem();

};

#endif // IDENTIFYDUPLICATESPAGEWIDGET_H
