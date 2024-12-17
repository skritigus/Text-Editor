#include "TableManager.h"
#include <QTextTable>

TableManager::TableManager()
{
    connect(createTableDialog, &CreateTableDialog::tableSizeChosen, this, &TableManager::createTable);
}

void TableManager::showCreateTableDialog()
{
    createTableDialog->exec();
}

void TableManager::createTable(const int& rows, const int& columns)
{
    QTextTableFormat tableFormat;
    tableFormat.setCellPadding(3);
    tableFormat.setCellSpacing(0);
    emit tableCreated(rows, columns, tableFormat);
}

void TableManager::insertRowAbove(const QTextCursor& cursor) const
{
    QTextTable* table = cursor.currentTable();
    table->insertRows(table->cellAt(cursor).row(), 1);
}

void TableManager::insertRowBelow(const QTextCursor& cursor) const
{
    QTextTable* table = cursor.currentTable();
    table->insertRows(table->cellAt(cursor).row() + 1, 1);
}

void TableManager::insertColumnLeft(const QTextCursor& cursor) const
{
    QTextTable* table = cursor.currentTable();
    table->insertColumns(table->cellAt(cursor).column(), 1);
}

void TableManager::insertColumnRight(const QTextCursor& cursor) const
{
    QTextTable* table = cursor.currentTable();
    table->insertColumns(table->cellAt(cursor).column() + 1, 1);
}

void TableManager::deleteRow(const QTextCursor& cursor) const
{
    QTextTable* table = cursor.currentTable();
    table->removeRows(table->cellAt(cursor).row(), 1);
}

void TableManager::deleteColumn(const QTextCursor& cursor) const
{
    QTextTable* table = cursor.currentTable();
    table->removeColumns(table->cellAt(cursor).column(), 1);
}

void TableManager::mergeCells(const QTextCursor& cursor) const
{
    QTextTable* table = cursor.currentTable();
    table->mergeCells(cursor);
}

void TableManager::splitCells(const QTextCursor& cursor) const
{
    QTextTable* table = cursor.currentTable();
    QTextTableCell cell = table->cellAt(cursor);

    table->splitCell(cell.row(), cell.column(), 1, 1);
}
