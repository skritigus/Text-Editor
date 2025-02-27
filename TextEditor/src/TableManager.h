#ifndef TABLEMANAGER_H
#define TABLEMANAGER_H

#include "CreateTableDialog.h"
#include <QTextCursor>
#include <QObject>

class TableManager : public QObject
{
    Q_OBJECT

    CreateTableDialog* createTableDialog = new CreateTableDialog;

public:
    TableManager();

    void showCreateTableDialog();

    void createTable(const int& rows, const int& columns);

    void insertRowAbove(const QTextCursor& cursor) const;
    void insertRowBelow(const QTextCursor& cursor) const;
    void insertColumnLeft(const QTextCursor& cursor) const;
    void insertColumnRight(const QTextCursor& cursor) const;

    void deleteRow(const QTextCursor& cursor) const;
    void deleteColumn(const QTextCursor& cursor) const;

    void mergeCells(const QTextCursor& cursor) const;
    void splitCells(const QTextCursor& cursor) const;

signals:
    void tableCreated(const int& rows, const int& columns, const QTextTableFormat& format);

};

#endif // TABLEMANAGER_H
