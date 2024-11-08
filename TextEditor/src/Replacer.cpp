#include "Replacer.h"

Replacer::~Replacer()
{
    indexes.clear();
}

void Replacer::shiftIndexes(const int& replacedIndex, const int& wordsDifference)
{
    for(int i = replacedIndex + 1; i < indexes.getCount(); ++i)
    {
        indexes[i].getData() += wordsDifference;
    }
}

void Replacer::removeNonExistIndex(const int& wordsDifference)
{
    if(patternLength < 2)
    {
        return;
    }

    ListIterator<int> center = indexes.begin(&indexes[currentIndex]);
    ListIterator<int> left = indexes.begin(&indexes[currentIndex - 1]);
    ListIterator<int> right = indexes.begin(&indexes[currentIndex + 1]);
    int leftEnd = center->getData() - patternLength + 1;
    int rightEnd = center->getData() + patternLength - 1;

    if(leftEnd < 0)
    {
        leftEnd = 0;
    }
    if(rightEnd >= textLength)
    {
        rightEnd = textLength - 1;
    }

    while(right->getData() <= rightEnd && currentIndex < indexes.getCount() - 1)
    {
        if(right.getPtr()->getNext() != nullptr)
        {
            ++right;
            indexes.deleteByNode(right.getPtr()->getPrev());
        }
        else
        {
            indexes.deleteByNode(right.getPtr());
        }
    }
    while(left->getData() >= leftEnd && currentIndex > 0)
    {
        if(left.getPtr()->getPrev() != nullptr)
        {
            --left;
            indexes.deleteByNode(left.getPtr()->getNext());
        }
        else
        {
            indexes.deleteByNode(left.getPtr());
        }
        --currentIndex;
    }
    textLength += wordsDifference;
}

void Replacer::performAll(QString& text, const QString& pattern, const QString& replacing)
{
    indexes = KMP(text, pattern);
    textLength = text.length();
    currentIndex = 0;

    while(indexes.getCount() > 0)
    {
        removeNonExistIndex(replacing.length() - patternLength);
        shiftIndexes(currentIndex, replacing.length() - patternLength);
        text.replace(indexes[currentIndex].getData(), patternLength, replacing);
        indexes.deleteByIndex(currentIndex);
    }
}

void Replacer::performSingle(const QString& text, const QString& pattern, const QString& replacing)
{
    if(currentIndex == -1)
    {
        indexes = KMP(text, pattern);
        textLength = text.length();
        currentIndex = 0;
        return;
    }
    if(indexes.getCount() > 0)
    {
        removeNonExistIndex(replacing.length() - patternLength);
        shiftIndexes(currentIndex, replacing.length() - patternLength);
    }
}

void Replacer::next()
{
    if(currentIndex + 1 < indexes.getCount())
    {
        ++currentIndex;
    }
}

void Replacer::prev()
{
    if(currentIndex - 1 >= 0)
    {
        --currentIndex;
    }
}

int& Replacer::getTextIndex()
{
    return indexes[currentIndex].getData();
}

List<int>& Replacer::getIndexes()
{
    return indexes;
}
