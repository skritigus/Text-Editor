#ifndef FONTSTYLE_H
#define FONTSTYLE_H

#include <QFont>
#include <QColor>

class FontStyle
{
    QFont font;
    QColor textColor;
    QColor backgroundColor;
    Qt::Alignment align;

public:
    FontStyle() = default;
    FontStyle (QFont font, QColor textColor, QColor backgroundColor, Qt::Alignment align) :
        font(font), textColor(textColor), backgroundColor(backgroundColor), align(align) {}
    FontStyle(const FontStyle& style) = default;
    FontStyle (FontStyle&& other) noexcept :
        font(other.font), textColor(other.textColor), backgroundColor(other.backgroundColor), align(other.align) {};

    QFont getFont() const;
    QColor getTextColor() const;
    QColor getBackgroundColor() const;
    Qt::Alignment getAlign() const;

    void setFont(QFont newFont);
    void setTextColor(QColor newTextColor);
    void setBackgroundColor(QColor newBackgroundColor);
    void setAlign(Qt::Alignment newAlign);

    FontStyle& operator=(FontStyle&& other) noexcept
    {
        if (this != &other)
        {
            font = other.font;
            textColor = other.textColor;
            backgroundColor = other.backgroundColor;
            align = other.align;
        }

        return *this;
    }

    FontStyle& operator=(const FontStyle& other) = default;

    bool operator==(const FontStyle& other) const
    {
        if(font == other.font && textColor == other.textColor &&
            backgroundColor == other.backgroundColor && align == other.align)
        {
            return true;
        }
        return false;
    }
};

#endif // FONTSTYLE_H
