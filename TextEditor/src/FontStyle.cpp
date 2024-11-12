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

QFlags<Qt::AlignmentFlag> FontStyle::getAlign() const
{
    return align;
}

void FontStyle::setFont(QFont newFont)
{
    font = newFont;
}

void FontStyle::setTextColor(QColor newTextColor)
{
    textColor = newTextColor;
}

void FontStyle::setBackgroundColor(QColor newBackgroundColor)
{
    backgroundColor = newBackgroundColor;
}

void FontStyle::setAlign(QFlags<Qt::AlignmentFlag> newAlign)
{
    align = newAlign;
}
