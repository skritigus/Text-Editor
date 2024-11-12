#ifndef REPLACER_H
#define REPLACER_H

#include "KnuthMorrisPratt.h"
#include "IFindDependent.h"

class Replacer : public KnuthMorrisPratt, public IFindDependent
{
    List<int> indexes;
    int& patternLength = getPatternLength();
    int& currentIndex = getCurrentIndex();
    int textLength;

    void removeNonExistIndex(const int& wordsDifference);
    void shiftIndexes(const int& replacedIndex, const int& wordsDifference);

public:
    Replacer() = default;
    Replacer(const Replacer& other) : indexes(other.indexes), patternLength(other.patternLength),
        currentIndex(other.currentIndex), textLength(other.textLength) {}
    ~Replacer();

    void performSingle(const QString& text, const QString& pattern, const QString& replacing) override;
    void performAll(QString& text, const QString& pattern, const QString& replacing) override;

    List<int>& getIndexes() override;
    int& getTextIndex() override;

    void next() override;
    void prev() override;
};

#endif // REPLACER_H
