#ifndef KNUTHMORRISPRATT_H
#define KNUTHMORRISPRATT_H

#include "List.h"
#include <QString>
#include <QVector>

class KnuthMorrisPratt
{
    int patternLength;

    void computeLPS(const QString& pattern, QVector<int>& lps) const;

public:
    List<int> KMP(const QString& text, const QString& pattern);

    int& getPatternLength();
};

#endif // KNUTHMORRISPRATT_H
