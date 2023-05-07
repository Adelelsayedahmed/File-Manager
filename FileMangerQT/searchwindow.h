#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QMainWindow>
#include "filecontentview.h"
#include "ui_filecontentview.h"


namespace Ui {
class SearchWindow;
}

class SearchWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SearchWindow(QWidget *parent = nullptr);
    void search(QString filepath, QString  filename);
    ~SearchWindow();
    FileContentView *contentUi;

private slots:
    void on_tableWidget_cellDoubleClicked(int row, int column);

private:
    Ui::SearchWindow *ui;
    QString dfilePath;

signals:
     void searchForFileByName(std::string starting_point_drictory_path , std::string file_name , std::vector<std::string>& file_paths);
     void folderClicked(QString filePath);
};

#endif // SEARCHWINDOW_H
