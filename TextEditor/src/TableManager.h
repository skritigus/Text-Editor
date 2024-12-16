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

    void insertRowAbove(const QTextCursor& cursor);
    void insertRowBelow(const QTextCursor& cursor);
    void insertColumnLeft(const QTextCursor& cursor);
    void insertColumnRight(const QTextCursor& cursor);

    void deleteRow(const QTextCursor& cursor);
    void deleteColumn(const QTextCursor& cursor);

    void mergeCells(const QTextCursor& cursor);
    void splitCells(const QTextCursor& cursor);

signals:
    void tableCreated(const int& rows, const int& columns, const QTextTableFormat& format);

};

#endif // TABLEMANAGER_H
