#ifndef REPLACER_H
#define REPLACER_H

#include "KnuthMorrisPratt.h"
#include "IFindDependent.h"

class Replacer final: public KnuthMorrisPratt, public IFindDependent
{
    List<int> indexes;
    int& patternLength = getPatternLength();
    int currentIndex = -1;
    int textLength;

    void removeNonExistIndex(const int& wordsDifference);
    void shiftIndexes(const int& replacedIndex, const int& wordsDifference);

public:
    Replacer() = default;
    ~Replacer() override;

    void performSingle(const QString& text, const QString& pattern, const QString& replacing) override;
    void performAll(QString& text, const QString& pattern, const QString& replacing) override;

    List<int>& getIndexes() override;
    int& getTextIndex() override;
    int& getCurrentIndex() override;

    void setCurrentIndex(const int& index) override;

    void next() override;
    void prev() override;
};

#endif // REPLACER_H
