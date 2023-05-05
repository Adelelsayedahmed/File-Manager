#include "backbutton.h"

BackButton::BackButton(QWidget *parent)
    : QWidget{parent}
{
<<<<<<< Updated upstream
    button = new QPushButton(this);

    QString parentPath=QString::fromStdString(boost::filesystem::path(__FILE__).parent_path().string());
    parentPath +="/Backincon.png";
    QPixmap image(parentPath);
    QIcon icon(image);
    button->setIcon(icon);
    connect(button, &QPushButton::pressed, this, &BackButton::backButtonPressed);
//    this->show();
=======
    backButton = new QPushButton(this);

    QString parentPath=QString::fromStdString(boost::filesystem::path(__FILE__).parent_path().string());
    parentPath +="/up-arrow.png";
    QPixmap image(parentPath);
    QIcon icon(image);
    backButton->setIcon(icon);
    backButton->setCursor(Qt::PointingHandCursor);

    connect(backButton, &QPushButton::pressed, this, &BackButton::backButtonPressed);

>>>>>>> Stashed changes
}

void BackButton::backButtonPressed()
{
    emit backButtonPressedSignal();
}

<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
