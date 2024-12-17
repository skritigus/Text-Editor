#ifndef TEXTCOLORBUTTON_H
#define TEXTCOLORBUTTON_H

#include "AbstractColorButton.h"

class TextColorButton : public AbstractColorButton
{
public:
    explicit TextColorButton(QWidget* parent = nullptr);

    void createIcon() override;

    void resetColor() override;
};

#endif // TEXTCOLORBUTTON_H
