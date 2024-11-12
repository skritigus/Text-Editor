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

    QFont getFont() const;
    QColor getTextColor() const;
    QColor getBackgroundColor() const;
    Qt::Alignment getAlign() const;

    void setFont(QFont newFont);
    void setTextColor(QColor newTextColor);
    void setBackgroundColor(QColor newBackgroundColor);
    void setAlign(Qt::Alignment newAlign);

    FontStyle& operator=(const FontStyle& other) = default;
};

#endif // FONTSTYLE_H
