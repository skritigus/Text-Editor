#include "Replacer.h"

Replacer::Replacer() {}

void Replacer::replace(const QString& text, const QString& pattern, const int& replaceLength)
{
    int currentIndex = getCurrentIndex();
    int patternLength = pattern.size();

    if(currentIndex == -1)
    {
        find(text, pattern);
        currentIndex = getCurrentIndex();
    }

    if(getIndexes().getCount() > 0)
    {
        removeNonExistIndex(text.length(), patternLength, currentIndex, getIndexes());
        shiftIndexes(currentIndex, replaceLength - patternLength);
        emit replacePattern(getIndexes(), currentIndex, patternLength);

        getIndexes().deleteByIndex(currentIndex);
    }
}

void Replacer::replaceAll(const QString& text, const QString& pattern)
{
    int patternLength = pattern.size();

    find(text, pattern);

    emit replaceAllPatterns(getIndexes(), patternLength);

    getIndexes().clear();
    setCurrentIndex(-1);
}

void Replacer::shiftIndexes(const int& replacedIndex, const int& wordsDifference)
{
    for(int i = replacedIndex + 1; i < getIndexes().getCount(); ++i)
    {
        getIndexes()[i].getData() += wordsDifference;
    }
}

void Replacer::removeNonExistIndex(const int& textLength, const int& patternLength, const int& currentIndex, List<int>& indexes)
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

    while(left->getData() >= leftEnd && currentIndex > 0)
    {
        if(left.getPtr()->getPrev() != nullptr)
        {
            --left;
            indexes.deleteByIndex(left.getPtr()->getNext());
        }
        else
        {
            indexes.deleteByIndex(left.getPtr());
        }
    }
    while(right->getData() <= rightEnd && currentIndex < indexes.getCount() - 1)
    {
        if(right.getPtr()->getNext() != nullptr)
        {
            ++right;
            indexes.deleteByIndex(right.getPtr()->getPrev());
        }
        else
        {
            indexes.deleteByIndex(right.getPtr());
        }
    }
}

