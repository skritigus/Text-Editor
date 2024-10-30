#ifndef FIND_H
#define FIND_H

#include "List.h"
#include <QString>
#include <QVector>

class Find
{
public:
    void computeLPS(const QString& pattern, int& sizePattern, QVector<int>& lps);
    void KMP(const QString& text, const QString& pattern, List<int>& indexes);
};

#endif // FIND_H
