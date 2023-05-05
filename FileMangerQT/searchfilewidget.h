#ifndef SEARCHFILEWIDGET_H
#define SEARCHFILEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QTableWidget>
#include <map>
#include <QPushButton>
#include <QBoxLayout>
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
    private :
        void initiateSearchFilePage();
        void allocateWidget();

public:
    explicit searchfilewidget(QWidget *parent = nullptr);
    ~searchfilewidget();
    void recieveSearchContentMapFromCont(std::multimap<int, std::string> result);
signals:

};

#endif // SEARCHFILEWIDGET_H
