#ifndef TEXTEDITMANAGER_H
#define TEXTEDITMANAGER_H

#include <QTextEdit>
#include <QMenu>
#include "FontStyle.h"
#include "TableManager.h"
#include "WrongWordHighlighter.h"

class TextEditManager : public QTextEdit
{
    Q_OBJECT

    static TextEditManager* instance;
    WrongWordHighlighter* highlighter;
    Dictionary* dictionary = new Dictionary;
    TableManager* tableManager = new TableManager;
    QMenu* textEditContextMenu = new QMenu(this);
    QMenu* addTableCellsMenu = new QMenu("Вставить...", this);
    QMenu* deleteTableCellsMenu = new QMenu("Удалить...", this);
    bool isTableMenusAdded = false;

    TextEditManager();

    void showTextEditContextMenu(const QPoint &pos);
    void mousePressEvent(QMouseEvent *event) override;

    void insertTable(const int& rows, const int& columns, const QTextTableFormat& format) const;

    void insertRowAbove();
    void insertRowBelow();
    void insertColumnLeft();
    void insertColumnRight();

    void deleteRow();
    void deleteColumn();

signals:
    void rightButtonClicked(const QPoint &pos);
    void styleChanged(const FontStyle& style);

public:
    ~TextEditManager();

    TextEditManager* getInstance();

    void deleteWord();
    void addMissingWord();

    void setTextEditContent(QString text);
    void setTextEditFont(const QFont& font);
    void setTextEditFontStyle(const FontStyle& style);

    void mergeCells();
    void splitCells();
};

#endif // TEXTEDITMANAGER_H
