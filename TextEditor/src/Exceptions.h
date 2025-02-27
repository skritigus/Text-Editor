#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <QString>

class InvalidTypeException : public std::exception
{
    QString message;

public:
    explicit InvalidTypeException(const QString& message): message(message) {};

    QString& getMessage();
};

class DeleteNonExistingException : public std::exception
{
    QString message;

public:
    explicit DeleteNonExistingException(const QString& message): message(message) {};

    QString& getMessage();
};

class AddExistingException : public std::exception
{
    QString message;

public:
    explicit AddExistingException(const QString& message): message(message) {};

    QString& getMessage();
};

#endif // EXCEPTIONS_H
