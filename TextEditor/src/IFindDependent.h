#ifndef IFINDDEPENDENT_H
#define IFINDDEPENDENT_H

#include <QString>
#include "List.h"

class IFindDependent
{
protected:
    int currentIndex = -1;

public:
    virtual ~IFindDependent() {};

    virtual void performSingle(const QString& text, const QString& pattern, const QString& replacing) = 0;
    virtual void performAll(QString& text, const QString& pattern, const QString& replacing) = 0;

    virtual List<int>& getIndexes() = 0;
    virtual int& getTextIndex() = 0;

    virtual void next() = 0;
    virtual void prev() = 0;

    int& getCurrentIndex()
    {
        return currentIndex;
    }
};

#endif // IFINDDEPENDENT_H
