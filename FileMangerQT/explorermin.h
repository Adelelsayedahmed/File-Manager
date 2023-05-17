
#ifndef EXPLORERMIN_H
#define EXPLORERMIN_H
#include<QHeaderView>
#include <QObject>
#include <QTableView>
#include <QTreeView>
#include <QModelIndex>
#include <QFileSystemModel>
#include <QFormLayout>
#include <QShortcut>
#include <QMenu>
#include <QContextMenuEvent>
#include "Actions.h"
#include <filecontentview.h>
#include "ui_filecontentview.h"
#include "searchwindow.h"
#include "searchbar.h"
#include "addonsbar.h"
#include"statistics.h"
#include<QString>

#include <QDragEnterEvent>
#include <QDropEvent>

#include <QAbstractItemView>
#include "customtable.h"
#include "myfilesystemmodel.h"
#include "rename_widget.h"
class ExplorerMin:public QWidget
{
    Q_OBJECT
private :
    rename_widget* rename_widg_obj;
    rename_widget* batch_rename_widg_obj;
    rename_widget *createFileWidget;
    rename_widget *createDirectoryWidget;
    bool isMultipleSelected();
    bool hasGzExtension(const std::string& path);
    std::vector<std::string> getSelectedPaths();
    bool newDirectoryEnteredFlag = false;
public:
    ExplorerMin(QString rootPath =  QString(),QWidget *parent = nullptr);
    QAction *compressAction ;
    QAction *decompressAction;
    QString backFilepath;
    static QString filepath;
    CustomTable *table;
    LocationBar *bar;
    ~ExplorerMin();
protected:
    addOnsBar* topBar;
    QAction* identifyDuplicatesAction;
    SearchBar *search;
protected:

    QFormLayout *layout;
    MyFileSystemModel* fileSystemModel;
    QModelIndex index;
    QModelIndex upBouttonIndex;
    CopyCutAction action;
    QString filePath;
    QString sourceFilePathCopy;

    FileContentView *contentUi;
    void onTableViewClicked(QModelIndex index);
    void registerSignals();


    QTableView* ShowTableView();
public slots:
    void on_tableView_clicked(const QModelIndex &index);
    void onCopy();
    void onPaste();
    void onDel();
    void onCut();
    void onUndo();
    void onCreatingFile();
    void onCreatingFolder();

    void onProperties();

    void onRenameFilesViewSlot();
    void onBatchRenameViewSlot();
    void emitingRenameSlot(QString newFileName) ;
    void emitingBatchRenameSlot(QString newFileName);
    void emittingCreatingFile(QString filename);
    void emittingCreatingFolder(QString dirname);
    void onCompress();
    void onDeCompress();



    void folderClicked(QString filepath);
    void SearchWindowCreatedSlot(SearchWindow *window);
    void BackButtonClicked();
  //  void on_identifyDuplicatesIconClicked();

    void onBatchCompressViewSlot();
    void onBatchDecompressViewSlot ();
    void onCompressHere();
    void onDecompressHere();
    void BackButtonClickedFromTree();

    LocationBar* initializeLocationBar();


signals:
    void copyFile(std::string source_path, std::string destination_path, CopyCutAction action);
    void delFile(std::string filePath);
    void cutFile(std::string filePath);
    void undoAction();
    void createFile(std::string filePath);
    void createFolder(const std::string& dirname);
    void propertiesOfFile(std::string filePath);
    void renameFileViewSignal(std::string filePath , const std::string newFileName);
    void batchRenameViewSignal(std::vector< std::string>& oldPaths,const std::string &newBaseName);
    void SearchWindowCreated(SearchWindow *window);
    void locationChanged(QString filepath, QString filename);
    void folderChanged(QString filepath);
    void backButtonPressedSignalFromTree();
    void batchCompressViewSignal(std::vector< std::string>&Paths);
    void batchDecompressViewSignal(std::vector< std::string>&Paths);
    void context_menu(QModelIndex index);
    void compresshere( std::string & path);
    void decompresshere(std::string & path);

protected slots:
    void contextMenuEvent(QContextMenuEvent *event);
    void on_tableView_doubleClicked(QModelIndex index);
    void checkSelectedFileForCompression();


};

#endif // EXPLORERMIN_H
