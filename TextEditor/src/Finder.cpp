#include "Finder.h"

Finder::~Finder()
{
    indexes.clear();
    selections.clear();
}

void Finder::performAll(QString& text, const QString& pattern, const QString&)
{
    indexes = KMP(text, pattern);

    if(indexes.getCount() != 0)
    {
        QTextCursor cursor = textCursor;
        QTextCharFormat backgroundColor;

        backgroundColor.setBackground(QColor(Qt::yellow).darker());

        currentIndex = 0;

        for(int i = 0; i < indexes.getCount(); ++i)
        {
            cursor.setPosition(indexes[i].getData());
            cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, patternLength);

            selections.push_back(QTextEdit::ExtraSelection{cursor, backgroundColor});
        }

        backgroundColor.setBackground(QColor("orange"));
        selections.push_back(QTextEdit::ExtraSelection{cursor, backgroundColor});
    }
}

void Finder::performSingle(const QString& text, const QString& pattern, const QString&)
{
    indexes = KMP(text, pattern);

    if(indexes.getCount() != 0)
    {
        currentIndex = 0;
    }
}

int& Finder::getTextIndex()
{
    return indexes[currentIndex].getData();
}

List<int>& Finder::getIndexes()
{
    return indexes;
}

void Finder::next()
{
    if(currentIndex + 1 < indexes.getCount())
    {
        ++currentIndex;
    }
}

void Finder::prev()
{
    if(currentIndex - 1 >= 0)
    {
        --currentIndex;
    }
}

QList<QTextEdit::ExtraSelection>& Finder::getSelections()
{
    return selections;
}

void Finder::setCursor(const QTextCursor& newCursor)
{
    textCursor = newCursor;
}
