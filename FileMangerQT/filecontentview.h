#ifndef FILECONTENTVIEW_H
#define FILECONTENTVIEW_H

#include <QDialog>
#include <QFile>
#include <QCloseEvent>
#include <QShortcut>
#include <QMessageBox>
namespace Ui {
class FileContentView;
}

class FileContentView : public QDialog
{
    Q_OBJECT

public:
    explicit FileContentView(QWidget *parent = nullptr);
    ~FileContentView();
    Ui::FileContentView *ui;
    QFile *file;
public slots:
    void on_saveAction_triggered();
    void closeEvent(QCloseEvent *event);
private:
    void mRegisterSignals();
    void saveFile();
};

#endif // FILECONTENTVIEW_H
