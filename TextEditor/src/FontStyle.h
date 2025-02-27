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
    FontStyle (const QFont& font, const QColor& textColor, const QColor& backgroundColor, const Qt::Alignment& align) :
        font(font), textColor(textColor), backgroundColor(backgroundColor), align(align) {}
    FontStyle(const FontStyle& other) = default;
    FontStyle (FontStyle&& other) noexcept :
        font(other.font), textColor(other.textColor), backgroundColor(other.backgroundColor), align(other.align) {};

    QFont getFont() const;
    QColor getTextColor() const;
    QColor getBackgroundColor() const;
    Qt::Alignment getAlign() const;

    void setFont(const QFont& newFont);
    void setTextColor(const QColor& newTextColor);
    void setBackgroundColor(const QColor& newBackgroundColor);
    void setAlign(const Qt::Alignment& newAlign);

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
};

#endif // FONTSTYLE_H
