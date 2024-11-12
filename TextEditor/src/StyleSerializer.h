#ifndef STYLESERIALIZER_H
#define STYLESERIALIZER_H

#include "FontStyle.h"
#include "List.h"
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>

class StyleSerializer
{
public:
    static QJsonObject styleToJson(const FontStyle& style);
    static QJsonObject stylesArrayToJson(const List<FontStyle>& styles);

    static FontStyle styleFromJson(const QJsonObject& json);
    static List<FontStyle> stylesArrayFromJson(const QJsonObject& jsonArray);
};

#endif // STYLESERIALIZER_H
