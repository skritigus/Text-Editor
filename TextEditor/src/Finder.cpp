#include "Finder.h"

Finder::Finder()
{

}

void Finder::find(const QString& text, const QString& pattern)
{
    patternLength = pattern.length();
    indexes.clear();
    KMP(text, pattern, indexes);

    if(indexes.getCount() != 0)
    {
        currentIndex = 0;
        emit patternFound(indexes[currentIndex].getData(), patternLength);
    }
}

void Finder::next()
{
    ++currentIndex;
    if(currentIndex < indexes.getCount())
    {
        emit patternFound(indexes[currentIndex].getData(), patternLength);
    }
    else
    {
        --currentIndex;
    }
}

void Finder::prev()
{
    --currentIndex;
    if(currentIndex >= 0)
    {
        emit patternFound(indexes[currentIndex].getData(), patternLength);
    }
    else
    {
        ++currentIndex;
    }
}

int& Finder::getCurrentIndex()
{
    return currentIndex;
}

List<int>& Finder::getIndexes()
{
    return indexes;
}

int& Finder::getPatternLength()
{
    return patternLength;
}

void Finder::setCurrentIndex(const int& newCurrentIndex)
{
    currentIndex = newCurrentIndex;
}

void Finder::addPattern(QString& pattern)
{

}
