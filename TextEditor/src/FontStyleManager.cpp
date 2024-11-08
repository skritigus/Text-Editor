#include "FontStyleManager.h"
#include <QStringBuilder>
#include <QFile>
#include <QMessageBox>
#include "FontStyle.h"
#include "List.h"
#include "StyleSerializer.h"

FontStyleManager::FontStyleManager()
{
    loadStyles();
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedSize(150, 45);
    setFlow(QListView::LeftToRight);
    insertItem(0, "Добавить...");
    for(ListIterator<FontStyle> it = styles.begin(styles.getLast()), end = styles.end(nullptr); it != end; --it)
    {
        insertItem(0, it->getData().getFont().styleName());
    }
}

List<FontStyle>& FontStyleManager::getStyles()
{
    return styles;
}

void FontStyleManager::loadStyles()
{
    QFile file("FontStyles.json");

    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(nullptr, "Error", "Failed to read file");
        return;
    }

    QByteArray stylesObject;

    while (!file.atEnd())
    {
        stylesObject = stylesObject % file.readLine();
    }

    QJsonDocument jsonDoc = QJsonDocument::fromJson(stylesObject);

    styles = StyleSerializer::stylesArrayFromJson(jsonDoc.object());

    file.close();
}

void FontStyleManager::saveStyles() const
{
    QFile file("FontStyles.json");

    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(nullptr, "Error", "Failed to save file");
        return;
    }

    QJsonObject stylesObject = StyleSerializer::stylesArrayToJson(styles);

    file.write(QJsonDocument(stylesObject).toJson());

    file.close();
}

void FontStyleManager::addFontStyle(FontStyle& style)
{
    styles.pushFront(style);
    insertItem(0, style.getFont().styleName());
}

void FontStyleManager::editFontStyle(FontStyle& style)
{
    int index = currentRow();
    styles[index].getData() = std::move(style);
}

void FontStyleManager::deleteFontStyle()
{
    int index = currentRow();
    styles.deleteByIndex(index);
    takeItem(index);
}
