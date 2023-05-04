#include "backbutton.h"

BackButton::BackButton(QWidget *parent)
    : QWidget{parent}
{
    button = new QPushButton(this);

    QString parentPath=QString::fromStdString(boost::filesystem::path(__FILE__).parent_path().string());
    parentPath +="/Backincon.png";
    QPixmap image(parentPath);
    QIcon icon(image);
    button->setIcon(icon);
    connect(button, &QPushButton::pressed, this, &BackButton::backButtonPressed);
//    this->show();
}

void BackButton::backButtonPressed()
{
    emit backButtonPressedSignal();
}

