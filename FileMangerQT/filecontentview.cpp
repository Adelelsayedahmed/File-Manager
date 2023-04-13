#include "filecontentview.h"
#include "ui_filecontentview.h"
#include <QDebug>

FileContentView::FileContentView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileContentView)
{
    ui->setupUi(this);
    mRegisterSignals();
}

FileContentView::~FileContentView()
{
    delete ui;
}

void FileContentView::on_saveAction_triggered()
{
    // Write the contents of the QTextEdit widget to the file
//    QTextStream out(file);

//    out << ui->textEdit->toPlainText();
//    // Close the file
//    file->close();

    saveFile();
}
void FileContentView::saveFile()
{
    if (!file->isOpen())
        return;
    if(ui->textEdit->document()->isModified())
    {
        QString existingText = "";
        if (file->size() > 0) {
            file->seek(0);
            QByteArray byteArray = file->readAll();
            existingText = QString(byteArray);
        }

        QString newText = ui->textEdit->toPlainText();

        QString diff = "";
        int start = 0;
        int length = qMin(existingText.length(), newText.length());
        for (int i = 0; i < length; i++) {
            if (existingText.mid(i, 1) != newText.mid(i, 1)) {
                diff += newText.mid(start, i - start);
                start = i;
            }
        }
        diff += newText.mid(start);

        file->resize(0);
        file->write(diff.toUtf8());
    }

}

void FileContentView::closeEvent(QCloseEvent *event)
{
    if (ui->textEdit->document()->isModified()) {
        QMessageBox::StandardButton reply = QMessageBox::question(
            this, "Save Changes",
            "Do you want to save changes ?",
            QMessageBox::Save | QMessageBox::Cancel | QMessageBox::Ignore
            );

        if (reply == QMessageBox::Save) {
            saveFile();

        } else if (reply == QMessageBox::Cancel) {
            event->ignore();
            return;
        } else {
            event->accept();
        }
    }
    // Call file.close() when the window is closed
    if (file->isOpen()) {
        file->close();
    }

    delete file;
    event->accept();
}

void FileContentView::mRegisterSignals()
{
    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this);
    QObject::connect(shortcut, &QShortcut::activated, this, &FileContentView::on_saveAction_triggered);
}


