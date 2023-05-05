#ifndef SEARCHFILEWIDGET_H
#define SEARCHFILEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QTableWidget>
#include <map>

class searchfilewidget : public QWidget
{
    Q_OBJECT
private :
        QTableWidget* tableWidget;
public:
    explicit searchfilewidget(QWidget *parent = nullptr);
    void recieveSearchContentMapFromCont(std::map<int, std::string> result);
signals:

};

#endif // SEARCHFILEWIDGET_H
