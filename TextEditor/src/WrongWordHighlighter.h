#ifndef WRONGWORDHIGHLIGHTER_H
#define WRONGWORDHIGHLIGHTER_H

#include <QRegularExpression>
#include <QSyntaxHighlighter>
#include <QObject>
#include "Dictionary.h"

struct HighlightingRule
{
    QRegularExpression pattern;
    QTextCharFormat format;
};

class WrongWordHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

    Dictionary* dictionary;
    QTextCharFormat wrongWordFormat;
    HighlightingRule rule;

public:
    WrongWordHighlighter(Dictionary* dictionary, QTextDocument* parent = nullptr);

    QTextCharFormat getFormat(const int& pos);

protected:
    void highlightBlock(const QString& text) override;
};

#endif // WRONGWORDHIGHLIGHTER_H
