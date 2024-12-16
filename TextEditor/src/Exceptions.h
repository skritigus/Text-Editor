#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <QString>

class InvalidTypeException : public std::exception
{
    QString message;

public:
    InvalidTypeException(const QString& message): message(message) {};

    QString& getMessage();
};

class DeleteNonExistingException : public std::exception
{
    QString message;

public:
    DeleteNonExistingException(const QString& message): message(message) {};

    QString& getMessage();
};

class AddExistingException : public std::exception
{
    QString message;

public:
    AddExistingException(const QString& message): message(message) {};

    QString& getMessage();
};

#endif // EXCEPTIONS_H
