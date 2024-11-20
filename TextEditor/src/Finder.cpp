#include "Finder.h"

Finder::Finder(const QTextCursor& cursor) : textCursor(cursor)
{
    QTextCharFormat backgroundColor;

    backgroundColor.setBackground(QColor("orange"));
    selections.push_back(QTextEdit::ExtraSelection{textCursor, backgroundColor});
}

Finder::~Finder()
{
    indexes.clear();
    selections.clear();
}

void Finder::performSingle(const QString& text, const QString& pattern, const QString&)
{
    if(selections.size() > 1)
    {
        selections.erase(selections.cbegin(), selections.cend() - 1);
    }

    indexes = KMP(text, pattern);

    if(indexes.getCount() != 0)
    {
        currentIndex = 0;
    }
}

void Finder::performAll(QString& text, const QString& pattern, const QString&)
{
    indexes = KMP(text, pattern);
    int countIndexes = indexes.getCount();

    if(countIndexes != 0)
    {
        QTextCharFormat backgroundColor;

        backgroundColor.setBackground(QColor(Qt::yellow).darker());
        currentIndex = 0;

        for(int i = 0; i < countIndexes; ++i)
        {
            textCursor.setPosition(indexes[i].getData());
            textCursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, patternLength);

            selections.push_front(QTextEdit::ExtraSelection{textCursor, backgroundColor});
        }
    }
}

QList<QTextEdit::ExtraSelection>& Finder::getSelections()
{
    return selections;
}

List<int>& Finder::getIndexes()
{
    return indexes;
}

int& Finder::getTextIndex()
{
    return indexes[currentIndex].getData();
}

int& Finder::getCurrentIndex()
{
    return currentIndex;
}

void Finder::next()
{
    if(currentIndex + 1 < indexes.getCount())
    {
        ++currentIndex;
    }
    else
    {
        currentIndex = 0;
    }
}

void Finder::prev()
{
    if(currentIndex - 1 >= 0)
    {
        --currentIndex;
    }
    else
    {
        currentIndex = indexes.getCount() - 1;
    }
}

void Finder::setCurrentIndex(const int& index)
{
    currentIndex = index;
}
