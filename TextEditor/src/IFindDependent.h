#ifndef IFINDDEPENDENT_H
#define IFINDDEPENDENT_H

#include <QString>
#include "List.h"

class IFindDependent
{
public:
    virtual ~IFindDependent() = default;

    virtual void performSingle(const QString& text, const QString& pattern, const QString& replacing) = 0;
    virtual void performAll(QString& text, const QString& pattern, const QString& replacing) = 0;

    virtual List<int>& getIndexes() = 0;
    virtual int& getTextIndex() = 0;
    virtual int& getCurrentIndex() = 0;

    virtual void setCurrentIndex(const int& index) = 0;

    virtual void next() = 0;
    virtual void prev() = 0;
};

#endif // IFINDDEPENDENT_H
