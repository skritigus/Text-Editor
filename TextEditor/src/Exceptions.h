#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
#include <QString>

class InvalidTypeException : public std::exception
{
    QString message;

public:
    InvalidTypeException(const QString& message): message(message) {};

    QString& getMessage();
};

#endif // EXCEPTIONS_H
