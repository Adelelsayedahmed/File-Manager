#ifndef BACKBUTTON_H
#define BACKBUTTON_H
<<<<<<< Updated upstream
#include <QWidget>
#include <QPushButton>
=======
#include <QPushButton>
#include <QWidget>
>>>>>>> Stashed changes
#include <boost/filesystem.hpp>

class BackButton : public QWidget
{
    Q_OBJECT
public:
    explicit BackButton(QWidget *parent = nullptr);
<<<<<<< Updated upstream

protected:
    QPushButton *button;
=======
    QPushButton *backButton;
>>>>>>> Stashed changes

public slots:
    void backButtonPressed();

signals:
    void backButtonPressedSignal();
<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
};

#endif // BACKBUTTON_H
