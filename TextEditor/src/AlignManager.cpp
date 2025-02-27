#include "AlignManager.h"

int AlignManager::alignToInt(const Qt::Alignment& align)
{
    switch (align)
    {
    case Qt::AlignLeft:
        return 0;
    case Qt::AlignRight:
        return 1;
    case Qt::AlignHCenter:
        return 2;
    case Qt::AlignJustify:
        return 3;
    default:
        return 0;
    }
}

Qt::Alignment AlignManager::intToAlign(int value)
{
    switch (value)
    {
    case 0:
        return Qt::AlignLeft;
    case 1:
        return Qt::AlignRight;
    case 2:
        return Qt::AlignHCenter;
    case 3:
        return Qt::AlignJustify;
    default:
        return Qt::AlignLeft;
    }
}
