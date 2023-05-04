#ifndef BACKBUTTON_H
#define BACKBUTTON_H
#include <QWidget>
#include <QPushButton>
#include <boost/filesystem.hpp>

class BackButton : public QWidget
{
    Q_OBJECT
public:
    explicit BackButton(QWidget *parent = nullptr);

protected:
    QPushButton *button;

public slots:
    void backButtonPressed();

signals:
    void backButtonPressedSignal();
};

#endif // BACKBUTTON_H
