#include "AbstractColorButton.h"
#include <QPainter>
#include <QDialogButtonBox>

AbstractColorButton::AbstractColorButton(QWidget* parent) : QPushButton(parent)
{
    QPushButton* resetButton = new QPushButton("Нет Цвета");
    QDialogButtonBox* buttonBox = getColorDialog()->findChild<QDialogButtonBox*>();
    buttonBox->addButton(resetButton, QDialogButtonBox::ResetRole);
    colorDialog->setStyleSheet("QSpinBox {width: 60px;}");

    createColorRectangleIcon();

    connect(this, &QPushButton::clicked, this, &AbstractColorButton::showColorDialog);
    connect(colorDialog, &QColorDialog::colorSelected, this, &AbstractColorButton::changeRectangleColor);
    connect(resetButton, &QPushButton::clicked, this, &AbstractColorButton::resetColor);
}

AbstractColorButton::~AbstractColorButton()
{
    delete colorDialog;
}

void AbstractColorButton::createColorRectangleIcon()
{
    QPixmap pixmap(35, 35);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    QRect rect(5, 30, 25, 3);
    painter.setBrush(Qt::black);
    painter.drawRect(rect);
    painter.end();

    setIcon(QIcon(pixmap));
}

void AbstractColorButton::changeRectangleColor(const QColor& color)
{
    QPixmap pixmap = icon().pixmap(35);
    QPainter painter(&pixmap);

    QRect rect(5, 30, 25, 3);
    painter.setBrush(color);
    painter.drawRect(rect);
    painter.end();

    setIcon(QIcon(pixmap));
    this->color = color;
}

void AbstractColorButton::showColorDialog()
{
    colorDialog->exec();
}

QColorDialog* AbstractColorButton::getColorDialog()
{
    return colorDialog;
}
