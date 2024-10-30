#ifndef ALIGNMANAGER_H
#define ALIGNMANAGER_H

#include <qnamespace.h>

class AlignManager
{   
public:
    static int alignToInt(const Qt::Alignment& align);
    static Qt::Alignment intToAlign(int value);
};

#endif // ALIGNMANAGER_H
