#ifndef FINDER_H
#define FINDER_H

#include "KnuthMorrisPratt.h"
#include "IFindDependent.h"

class Finder : public IFindDependent, public KnuthMorrisPratt
{
public:
    ~Finder() {};

    void performSingle(const QString& text, const QString& pattern, const QString&) override;
    void performAll(QString& text, const QString& pattern, const QString&) override;

    List<int>& getIndexes() override;
    int& getTextIndex() override;

    void next() override;
    void prev() override;
};

#endif // FINDER_H
