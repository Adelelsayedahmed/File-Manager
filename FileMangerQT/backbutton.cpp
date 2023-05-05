#include "backbutton.h"

BackButton::BackButton(QWidget *parent)
    : QWidget{parent}
{

    backButton = new QPushButton(this);

    QString parentPath=QString::fromStdString(boost::filesystem::path(__FILE__).parent_path().string());
    parentPath +="/up-arrow.png";
    QPixmap image(parentPath);
    QIcon icon(image);
    backButton->setIcon(icon);
    backButton->setCursor(Qt::PointingHandCursor);

    connect(backButton, &QPushButton::pressed, this, &BackButton::backButtonPressed);

}

void BackButton::backButtonPressed()
{
    emit backButtonPressedSignal();
}

