#ifndef KNUTHMORRISPRATT_H
#define KNUTHMORRISPRATT_H

#include "List.h"
#include <QString>
#include <QVector>

class KnuthMorrisPratt
{
protected:
    List<int> indexes;
    int patternLength;

public:
    ~KnuthMorrisPratt();

    void computeLPS(const QString& pattern, QVector<int>& lps);
    void KMP(const QString& text, const QString& pattern);

    List<int>& getIndexes();
    int& getPatternLength();
};

#endif // KNUTHMORRISPRATT_H
