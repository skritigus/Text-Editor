#include "FontStyleManager.h"
#include <QStringBuilder>
#include <QFile>
#include <QMessageBox>
#include <QJsonDocument>
#include "FileManager.h"
#include <QMouseEvent>

FontStyleManager* FontStyleManager::instance = nullptr;

FontStyleManager::FontStyleManager()
{
    FileManager::loadStyles(styles);

    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedSize(150, 45);
    setFlow(QListView::LeftToRight);

    insertItem(0, "Добавить...");
    for(ListIterator<FontStyle> it = styles.begin(styles.getLast()), end = styles.end(nullptr); it != end; --it)
    {
        insertItem(0, it->getData().getFont().styleName());
    }

    connect(fontStyleEditor, &FontStyleDialog::styleAdded, this, &FontStyleManager::addFontStyle);
    connect(fontStyleEditor, &FontStyleDialog::styleEdited, this, &FontStyleManager::editFontStyle);
    connect(fontStyleEditor, &FontStyleDialog::styleDeleted, this, &FontStyleManager::deleteFontStyle);

    connect(this, &FontStyleManager::itemClicked, this, &FontStyleManager::setFontStyle);
}

FontStyleManager::~FontStyleManager()
{
    FileManager::saveStyles(styles);
}

FontStyleManager* FontStyleManager::getInstance()
{
    if(!instance)
    {
        instance = new FontStyleManager;
    }
    return instance;
}

List<FontStyle>& FontStyleManager::getStyles()
{
    return styles;
}

void FontStyleManager::addFontStyle(FontStyle& style)
{
    styles.pushFront(style);
    insertItem(0, style.getFont().styleName());
}

void FontStyleManager::editFontStyle(FontStyle& style)
{
    int index = currentRow();
    styles[index] = std::move(style);
}

void FontStyleManager::deleteFontStyle()
{
    int index = currentRow();
    styles.deleteByIndex(index);
    takeItem(index);
}

void FontStyleManager::setFontStyle(QListWidgetItem* item)
{
    if(item->text() == "Добавить...")
    {
        fontStyleEditor->showToAddStyle();
    }
    else
    {
        emit fontStyleChosen(getCurrentStyle());
    }
}

FontStyle& FontStyleManager::getCurrentStyle()
{
    return getStyles()[currentRow()];
}

void FontStyleManager::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::RightButton && itemAt(event->pos()) != nullptr && itemAt(event->pos())->text() != "Добавить...")
    {
        fontStyleEditor->showToEditStyle(getStyles()[row(itemAt(event->pos()))]);
        return;
    }
    QListWidget::mousePressEvent(event);
}
