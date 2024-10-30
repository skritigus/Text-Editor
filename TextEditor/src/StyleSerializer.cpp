#include "StyleSerializer.h"
#include "AlignManager.h"

QJsonObject StyleSerializer::styleToJson(const FontStyle& style)
{
    QJsonObject json;
    QFont font = style.getFont();
    QColor textColor = style.getTextColor();
    QColor backgroundColor = style.getBackgroundColor();

    json["name"] = font.styleName();
    json["font family"] = font.family();
    json["font size"] = font.pointSize();

    json["bold"] = font.bold();
    json["italic"] = font.italic();
    json["underline"] = font.underline();

    json["text color red"] = textColor.red();
    json["text color green"] = textColor.green();
    json["text color blue"] = textColor.blue();

    json["background color red"] = backgroundColor.red();
    json["background color green"] = backgroundColor.green();
    json["background color blue"] = backgroundColor.blue();

    json["align"] = AlignManager::alignToInt(style.getAlign());

    return json;
}

QJsonObject StyleSerializer::stylesArrayToJson(const List<FontStyle>& styles)
{
    QJsonObject json;
    QJsonArray jsonArray;

    for(ListIterator<FontStyle> it = styles.cbegin(), end = styles.cend(); it != end; ++it)
    {
        jsonArray.append(styleToJson(it->getData()));
    }

    json["styles"] = jsonArray;
    return json;
}

FontStyle StyleSerializer::styleFromJson(const QJsonObject& json)
{
    QFont font;
    QColor textColor;
    QColor backgroundColor;
    Qt::Alignment align;

    if(const QJsonValue n = json["name"]; n.isString())
    {
        font.setStyleName(n.toString());
    }

    if(const QJsonValue f = json["font family"]; f.isString())
    {
        font.setFamily(f.toString());
    }

    if(const QJsonValue s = json["font size"]; s.isDouble())
    {
        font.setPointSize(s.toInt());
    }

    if(const QJsonValue b = json["bold"]; b.isBool())
    {
        font.setBold(b.toBool());
    }
    if(const QJsonValue i = json["italic"]; i.isBool())
    {
        font.setItalic(i.toBool());
    }
    if(const QJsonValue u = json["underline"]; u.isBool())
    {
        font.setUnderline(u.toBool());
    }

    if(const QJsonValue tc = json["text color red"]; tc.isDouble())
    {
        textColor.setRed(tc.toInt());
    }
    if(const QJsonValue tc = json["text color green"]; tc.isDouble())
    {
        textColor.setGreen(tc.toInt());
    }
    if(const QJsonValue tc = json["text color blue"]; tc.isDouble())
    {
        textColor.setBlue(tc.toInt());
    }

    if(const QJsonValue bc = json["background color red"]; bc.isDouble())
    {
        backgroundColor.setRed(bc.toInt());
    }
    if(const QJsonValue bc = json["background color green"]; bc.isDouble())
    {
        backgroundColor.setGreen(bc.toInt());
    }
    if(const QJsonValue bc = json["background color blue"]; bc.isDouble())
    {
        backgroundColor.setBlue(bc.toInt());
    }

    if(const QJsonValue a = json["align"]; a.isDouble())
    {
        align = AlignManager::intToAlign(a.toInt());
    }

    return FontStyle(font, textColor, backgroundColor, align);
}

List<FontStyle> StyleSerializer::stylesArrayFromJson(const QJsonObject& json)
{
    List<FontStyle> styles;

    if(const QJsonValue s = json["styles"]; s.isArray())
    {
        const QJsonArray jsonArray = s.toArray();
        for(const QJsonValue& styleJson : jsonArray)
        {
            FontStyle style = styleFromJson(styleJson.toObject());
            styles.pushBack(style);
        }
    }

    return styles;
}
