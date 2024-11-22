#include "FontStyle.h"

QFont FontStyle::getFont() const
{
    return font;
}

QColor FontStyle::getTextColor() const
{
    return textColor;
}

QColor FontStyle::getBackgroundColor() const
{
    return backgroundColor;
}

Qt::Alignment FontStyle::getAlign() const
{
    return align;
}

void FontStyle::setFont(const QFont& newFont)
{
    font = newFont;
}

void FontStyle::setTextColor(const QColor& newTextColor)
{
    textColor = newTextColor;
}

void FontStyle::setBackgroundColor(const QColor& newBackgroundColor)
{
    backgroundColor = newBackgroundColor;
}

void FontStyle::setAlign(const Qt::Alignment& newAlign)
{
    align = newAlign;
}
