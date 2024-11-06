#ifndef REPLACER_H
#define REPLACER_H

#include "KnuthMorrisPratt.h"
#include "IFindDependent.h"

class Replacer : public IFindDependent, public KnuthMorrisPratt
{
    int textLength;

    void removeNonExistIndex(int& textLength, const int& wordsDifference);
    void shiftIndexes(const int& replacedIndex, const int& wordsDifference);

public:
    ~Replacer() {};

    void performSingle(const QString& text, const QString& pattern, const QString& replacing) override;
    void performAll(QString& text, const QString& pattern, const QString& replacing) override;

    List<int>& getIndexes() override;
    int& getTextIndex() override;

    void next() override;
    void prev() override;
};

#endif // REPLACER_H
