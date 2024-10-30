#ifndef REPLACER_H
#define REPLACER_H

#include "Finder.h"
#include "IHasMemory.h"

class Replacer : public Finder, public virtual IHasMemory
{
    Q_OBJECT

    int replaceLength;

    void removeNonExistIndex(const int& textLength, const int& patternLength, const int& currentIndex, List<int>& indexes);
    void shiftIndexes(const int& replacedIndex, const int& wordsDifference);

signals:
    void replacePattern(const List<int>& indexes, int& currentIndex, const int& patternLength);
    void replaceAllPatterns(const List<int>& indexes, const int& patternLength);

public:
    Replacer();

    void replace(const QString& text, const QString& pattern, const int& replaceLength);
    void replaceAll(const QString& text, const QString& pattern);
};

#endif // REPLACER_H
