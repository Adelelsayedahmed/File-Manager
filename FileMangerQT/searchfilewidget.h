#ifndef SEARCHFILEWIDGET_H
#define SEARCHFILEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QTableWidget>
#include <map>
#include <QPushButton>
#include <QBoxLayout>
#include <string>
#include <vector>
#include "rename_widget.h"

class searchfilewidget : public QWidget
{
    Q_OBJECT
private :
        QTableWidget* tableResultWidget;
        QTableWidget* tablePathsWidget;
        QPushButton * addPathButton;
        QPushButton * searchButton;
        QPushButton * removePathButton;
        QLineEdit   * searchLine;
        QVBoxLayout * layout ;
        QVBoxLayout * button_layout ;
        QHBoxLayout * lineButtonHlayut ;
        QHBoxLayout * lineButtonHlayout ;
        QHBoxLayout * hLayOut ;
        rename_widget* searchPopUp ;


        std::vector<std::string> filePaths;
        std::string searchString ;

    private :
        void initiateSearchFilePage();
        void allocateWidget();
        void fillResultTableModel(const std::multimap<int, std::string>&result);
        void fillPathVector();
        void clearResultTable();
        void clearPathsTable();
        void mRegisterSignals();
        bool isValidEnteredString();
        void fillPathTableModel(const QString &lineValue);
        void raiseEmptyStringError();
        void raiseEmptyPathsError();

public:
    explicit searchfilewidget(QWidget *parent = nullptr);
    ~searchfilewidget();
    void recieveSearchContentMapFromCont(const std::multimap<int, std::string>& result);

private slots :
    void onAddPathButton();
    void CallSearchContentBE();
    void recieveFilePathFromPopUp(QString lineValue);
    void onRemovePathButton();
signals:
    void searchContentPathsSignal(const std ::vector<std::string> &filePaths ,const std::string &searchString);

};

#endif // SEARCHFILEWIDGET_H
