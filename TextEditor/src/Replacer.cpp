#include "Replacer.h"

Replacer::~Replacer()
{
    indexes.clear();
}

void Replacer::shiftIndexes(const int& replacedIndex, const int& wordsDifference)
{
    int countIndexes = indexes.getCount();

    for(int i = replacedIndex + 1; i < countIndexes; ++i)
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

    ListIterator<int> left = indexes.begin(&indexes[currentIndex - 1]);
    ListIterator<int> right = indexes.begin(&indexes[currentIndex + 1]);
    int leftEnd = indexes[currentIndex].getData() - patternLength + 1;
    int rightEnd = indexes[currentIndex].getData() + patternLength - 1;

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
        if(right->getNext() != nullptr)
        {
            ++right;
            indexes.deleteByNode(right->getPrev());
        }
        else
        {
            indexes.deleteByNode(right.getPtr());
        }
    }
    while(left->getData() >= leftEnd && currentIndex > 0)
    {
        if(left->getPrev() != nullptr)
        {
            --left;
            indexes.deleteByNode(left->getNext());
        }
        else
        {
            indexes.deleteByNode(left.getPtr());
        }
        --currentIndex;
    }
    textLength += wordsDifference;
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
        int wordsDifference = replacing.length() - patternLength;

        removeNonExistIndex(wordsDifference);
        shiftIndexes(currentIndex, wordsDifference);
    }
}

void Replacer::performAll(QString& text, const QString& pattern, const QString& replacing)
{
    indexes = KMP(text, pattern);
    int wordsDifference = replacing.length() - patternLength;
    textLength = text.length();
    currentIndex = 0;

    while(indexes.getCount() > 0)
    {
        removeNonExistIndex(wordsDifference);
        shiftIndexes(currentIndex, wordsDifference);
        text.replace(indexes[currentIndex].getData(), patternLength, replacing);
        indexes.deleteByIndex(currentIndex);
    }
}

List<int>& Replacer::getIndexes()
{
    return indexes;
}

int& Replacer::getTextIndex()
{
    return indexes[currentIndex].getData();
}

int& Replacer::getCurrentIndex()
{
    return currentIndex;
}

void Replacer::next()
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

void Replacer::prev()
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

void Replacer::setCurrentIndex(const int& index)
{
    currentIndex = index;
}
