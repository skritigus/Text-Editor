#include "BackgroundColorButton.h"
#include <QPainter>
#include <QDialogButtonBox>

BackgroundColorButton::BackgroundColorButton(QWidget* parent) : AbstractColorButton(parent)
{
    getColorDialog()->setWindowTitle("Выберите цвет заднего фона");
    createIcon();
}

void BackgroundColorButton::createIcon()
{
    QPixmap pixmap = icon().pixmap(35);
    QPainter painter(&pixmap);

    painter.drawPixmap(0, 0, QPixmap("icons/backgroundColorIcon.png"));
    painter.end();

    setIcon(QIcon(pixmap));
}

void BackgroundColorButton::resetColor()
{
    changeRectangleColor(Qt::transparent);
    getColorDialog()->close();
    emit colorReseted(color);
}
