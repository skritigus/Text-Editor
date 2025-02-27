#ifndef ABSTRACTCOLORBUTTON_H
#define ABSTRACTCOLORBUTTON_H

#include <QPushButton>
#include <QColorDialog>

class AbstractColorButton : public QPushButton
{
    Q_OBJECT

    QColorDialog* colorDialog = new QColorDialog;

signals:
    void colorReseted(const QColor& color);

public:
    QColor color;

    explicit AbstractColorButton(QWidget *parent = nullptr);
    ~AbstractColorButton();

    virtual void createIcon() = 0;
    void createColorRectangleIcon();

    void changeRectangleColor(const QColor& newColor);
    virtual void resetColor() = 0;

    QColorDialog* getColorDialog();
    void showColorDialog();
};

#endif // ABSTRACTCOLORBUTTON_H
