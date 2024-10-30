#ifndef FINDER_H
#define FINDER_H

#include "Find.h"
#include "IHasMemory.h"
#include <QObject>
#include <QVector>

class Finder : public QObject, public Find, public virtual IHasMemory
{
    Q_OBJECT

    static inline List<int> indexes;
    static inline int currentIndex = -1;
    int patternLength;

signals:
    void patternFound(const int& textIndex, const int& patternLength);

public:
    Finder();

    int& getCurrentIndex();
    List<int>& getIndexes();
    int& getPatternLength();

    void setCurrentIndex(const int& newCurrentIndex);

    void find(const QString& text, const QString& pattern);
    void next();
    void prev();

    void addPattern(QString& pattern);
};

#endif // FINDER_H
