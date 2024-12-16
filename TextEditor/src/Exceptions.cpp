#include "Exceptions.h"

QString& InvalidTypeException::getMessage()
{
    return message;
}

QString& DeleteNonExistingException::getMessage()
{
    return message;
}

QString& AddExistingException::getMessage()
{
    return message;
}
