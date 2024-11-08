#ifndef KNUTHMORRISPRATT_H
#define KNUTHMORRISPRATT_H

#include "List.h"
#include <QString>
#include <QVector>

class KnuthMorrisPratt
{
    int patternLength;

public:
    KnuthMorrisPratt() = default;
    KnuthMorrisPratt(const KnuthMorrisPratt&);

    void computeLPS(const QString& pattern, QVector<int>& lps) const;
    List<int> KMP(const QString& text, const QString& pattern);

    int& getPatternLength();
};

#endif // KNUTHMORRISPRATT_H
