#ifndef BACKGROUNDCOLORBUTTON_H
#define BACKGROUNDCOLORBUTTON_H

#include "AbstractColorButton.h"

class BackgroundColorButton : public AbstractColorButton
{
    Q_OBJECT

public:
    BackgroundColorButton(QWidget* parent = nullptr);

    void createIcon() override;

    void resetColor() override;
};

#endif // BACKGROUNDCOLORBUTTON_H
