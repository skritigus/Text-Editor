#include "TextColorButton.h"
#include <QPainter>

TextColorButton::TextColorButton(QWidget* parent) : AbstractColorButton(parent)
{
    getColorDialog()->setWindowTitle("Выберите цвет текса");
    createIcon();
}

void TextColorButton::createIcon()
{
    QPixmap pixmap = icon().pixmap(35);
    QPainter painter(&pixmap);
    QFont font("Arial", 20, QFont::Bold);

    painter.setFont(font);
    painter.setPen(Qt::white);
    painter.drawText(pixmap.rect(), Qt::AlignCenter, "A");
    painter.end();

    setIcon(QIcon(pixmap));
}

void TextColorButton::resetColor()
{
    changeRectangleColor(Qt::white);
    getColorDialog()->close();
    emit colorReseted(color);
}
