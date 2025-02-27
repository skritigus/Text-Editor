#include "StyleSerializer.h"
#include "AlignManager.h"
#include "Exceptions.h"
#include <algorithm>
#include <QJsonValue>
#include <QJsonArray>
#include <QMessageBox>

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

    auto write = [&jsonArray](Node<FontStyle>& style)
    {
        jsonArray.append(styleToJson(style.getData()));
    };

    std::for_each(styles.cbegin(), styles.cend(), write);

    json["styles"] = jsonArray;
    return json;
}

FontStyle StyleSerializer::styleFromJson(const QJsonObject& json)
{
    QFont font;
    QColor textColor;
    QColor backgroundColor;
    Qt::Alignment align;

    const QJsonValue name = json["name"];
    const QJsonValue fontFamily = json["font family"];

    const QJsonValue size = json["font size"];

    const QJsonValue bold = json["bold"];
    const QJsonValue italic = json["italic"];
    const QJsonValue underline = json["underline"];

    const QJsonValue textColorRed = json["text color red"];
    const QJsonValue textColorGreen = json["text color green"];
    const QJsonValue textColorBlue = json["text color blue"];

    const QJsonValue backgroundColorRed = json["background color red"];
    const QJsonValue backgroundColorGreen = json["background color green"];
    const QJsonValue backgroundColorBlue = json["background color blue"];

    const QJsonValue alignment = json["align"];

    if(!(name.isString() && fontFamily.isString() &&  size.isDouble() && bold.isBool() && italic.isBool() && underline.isBool() &&
        textColorRed.isDouble() && textColorGreen.isDouble() && textColorBlue.isDouble() && backgroundColorRed.isDouble() &&
        backgroundColorGreen.isDouble() && backgroundColorBlue.isDouble() && alignment.isDouble()))
    {
        throw InvalidTypeException("Данные повреждены. Все стили текста с поврежденными данными будут удалены");
    }

    font.setStyleName(name.toString());
    font.setFamily(fontFamily.toString());

    font.setPointSize(size.toInt());

    font.setBold(bold.toBool());
    font.setItalic(italic.toBool());
    font.setUnderline(underline.toBool());

    textColor.setRed(textColorRed.toInt());
    textColor.setGreen(textColorGreen.toInt());
    textColor.setBlue(textColorBlue.toInt());

    backgroundColor.setRed(backgroundColorRed.toInt());
    backgroundColor.setGreen(backgroundColorGreen.toInt());
    backgroundColor.setBlue(backgroundColorBlue.toInt());

    align = AlignManager::intToAlign(alignment.toInt());

    return FontStyle(font, textColor, backgroundColor, align);
}

List<FontStyle> StyleSerializer::stylesArrayFromJson(const QJsonObject& json)
{
    List<FontStyle> styles;
    bool wasWarningShown = false;

    if(const QJsonValue s = json["styles"]; s.isArray())
    {
        const QJsonArray jsonArray = s.toArray();

            for(const QJsonValue& styleJson : jsonArray)
            {
            try
            {
                FontStyle style = styleFromJson(styleJson.toObject());
                styles.pushBack(style);
            } catch(InvalidTypeException& ex)
            {
                if(!wasWarningShown)
                {
                    QMessageBox::warning(nullptr, "Ошибка", ex.getMessage(), QMessageBox::Ok);
                    wasWarningShown = true;
                }
            }
        }
    }

    return styles;
}
