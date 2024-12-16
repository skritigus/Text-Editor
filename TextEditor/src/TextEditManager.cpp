#include "TextEditManager.h"
#include "Exceptions.h"
#include <QTextTable>
#include <QMessageBox>
#include <QMenu>
#include <QTextBlock>
#include <QContextMenuEvent>

TextEditManager* TextEditManager::instance = nullptr;

TextEditManager::TextEditManager()
{
    highlighter = new WrongWordHighlighter(dictionary, document());

    setContextMenuPolicy(Qt::CustomContextMenu);
    textEditContextMenu->addAction(tr("Добавить в словарь"), this, &TextEditManager::addMissingWord);
    textEditContextMenu->addAction(tr("Удалить из словаря"), this, &TextEditManager::deleteWord);
    textEditContextMenu->addSeparator();
    textEditContextMenu->addAction(tr("Вставить таблицу"), tableManager, &TableManager::showCreateTableDialog);

    addTableCellsMenu->addAction(tr("Слева"), this, &TextEditManager::insertColumnLeft);
    addTableCellsMenu->addAction(tr("Справа"), this, &TextEditManager::insertColumnRight);
    addTableCellsMenu->addAction(tr("Сверху"), this, &TextEditManager::insertRowAbove);
    addTableCellsMenu->addAction(tr("Снизу"), this, &TextEditManager::insertRowBelow);

    deleteTableCellsMenu->addAction(tr("Строку"), this, &TextEditManager::deleteRow);
    deleteTableCellsMenu->addAction(tr("Столбец"), this, &TextEditManager::deleteColumn);

    connect(this, &TextEditManager::rightButtonClicked, this, &TextEditManager::showTextEditContextMenu);
    connect(tableManager, &TableManager::tableCreated, this, &TextEditManager::insertTable);
}

TextEditManager::~TextEditManager()
{
    delete highlighter;
    delete dictionary;
    delete textEditContextMenu;
}

TextEditManager* TextEditManager::getInstance()
{
    if(!instance)
    {
        instance = new TextEditManager;
    }
    return instance;
}

void TextEditManager::showTextEditContextMenu(const QPoint &pos)
{
    if(textCursor().currentTable() != nullptr && !isTableMenusAdded)
    {
        textEditContextMenu->addMenu(addTableCellsMenu);
        textEditContextMenu->addMenu(deleteTableCellsMenu);
        isTableMenusAdded = true;
    }
    else
    {
        if(textCursor().currentTable() == nullptr && isTableMenusAdded)
        {
            textEditContextMenu->removeAction(addTableCellsMenu->menuAction());
            textEditContextMenu->removeAction(deleteTableCellsMenu->menuAction());
            isTableMenusAdded = false;
        }
    }
    textEditContextMenu->popup(mapToGlobal(pos));
}

void TextEditManager::setTextEditFontStyle(const FontStyle& style)
{
    setCurrentFont(style.getFont());
    setAlignment(style.getAlign());
    setTextColor(style.getTextColor());
    setTextBackgroundColor(style.getBackgroundColor());
    emit styleChanged(style);
}

void TextEditManager::setTextEditContent(QString text)
{
    setHtml(text);
}

void TextEditManager::setTextEditFont(const QFont& font)
{
    if(QFontDatabase::hasFamily(font.family()))
    {
        setFontFamily(font.family());
    }
}

void TextEditManager::addMissingWord()
{
    QTextCursor cursor = textCursor();
    cursor.select(QTextCursor::WordUnderCursor);
    QString word = cursor.selectedText();

    try
    {
        dictionary->addNode(word);
        highlighter->rehighlight();
    } catch (AddExistingException& ex)
    {
        QMessageBox::warning(nullptr, "Ошибка", ex.getMessage(), QMessageBox::Ok);
    }
}

void TextEditManager::deleteWord()
{
    QTextCursor cursor = textCursor();
    cursor.select(QTextCursor::WordUnderCursor);
    QString word = cursor.selectedText();

    try
    {
        dictionary->deleteNode(word);
        highlighter->rehighlight();
    } catch (DeleteNonExistingException& ex)
    {
        QMessageBox::warning(nullptr, "Ошибка", ex.getMessage(), QMessageBox::Ok);
    }
}

void TextEditManager::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::RightButton && !isReadOnly())
    {
        QTextCursor cursor = cursorForPosition(event->pos());
        setTextCursor(cursor);
        emit rightButtonClicked(event->pos());
        return;
    }
    QTextEdit::mousePressEvent(event);
}

void TextEditManager::deleteRow()
{
    tableManager->deleteRow(textCursor());
}

void TextEditManager::deleteColumn()
{
    tableManager->deleteColumn(textCursor());
}

void TextEditManager::insertRowAbove()
{
    QTextCursor cursor = textCursor();

    tableManager->insertRowAbove(cursor);

    cursor.insertText(" ");
    setTextCursor(cursor);
    cursor.deletePreviousChar();
    setTextCursor(cursor);
}

void TextEditManager::insertRowBelow()
{
    tableManager->insertRowBelow(textCursor());
}

void TextEditManager::insertColumnLeft()
{
    tableManager->insertColumnLeft(textCursor());
}

void TextEditManager::insertColumnRight()
{
    tableManager->insertColumnRight(textCursor());
}

void TextEditManager::mergeCells()
{
    tableManager->mergeCells(textCursor());
}

void TextEditManager::splitCells()
{
    tableManager->splitCells(textCursor());
}

void TextEditManager::insertTable(const int& rows, const int& columns, const QTextTableFormat& format)
{
    textCursor().insertTable(rows, columns, format);
}
