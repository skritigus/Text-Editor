#include "Finder.h"

void Finder::performAll(QString& text, const QString& pattern, const QString&)
{
    KMP(text, pattern);

    if(indexes.getCount() != 0)
    {
        currentIndex = 0;
    }
}

void Finder::performSingle(const QString& text, const QString& pattern, const QString&)
{
    KMP(text, pattern);

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
