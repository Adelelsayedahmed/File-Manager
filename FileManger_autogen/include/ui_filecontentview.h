/********************************************************************************
** Form generated from reading UI file 'filecontentview.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILECONTENTVIEW_H
#define UI_FILECONTENTVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_FileContentView
{
public:
    QTextEdit *textEdit;

    void setupUi(QDialog *FileContentView)
    {
        if (FileContentView->objectName().isEmpty())
            FileContentView->setObjectName("FileContentView");
        FileContentView->resize(863, 544);
        textEdit = new QTextEdit(FileContentView);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(0, 10, 861, 531));

        retranslateUi(FileContentView);

        QMetaObject::connectSlotsByName(FileContentView);
    } // setupUi

    void retranslateUi(QDialog *FileContentView)
    {
        FileContentView->setWindowTitle(QCoreApplication::translate("FileContentView", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FileContentView: public Ui_FileContentView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILECONTENTVIEW_H
