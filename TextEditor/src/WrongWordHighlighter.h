#ifndef WRONGWORDHIGHLIGHTER_H
#define WRONGWORDHIGHLIGHTER_H

#include <QRegularExpression>
#include <QSyntaxHighlighter>
#include "Dictionary.h"

struct HighlightingRule
{
    QRegularExpression pattern;
    QTextCharFormat wrongWordFormat;
};

class WrongWordHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

    Dictionary* dictionary;
    HighlightingRule rule;

public:
    WrongWordHighlighter(Dictionary* dictionary, QTextDocument* parent = nullptr);

protected:
    void highlightBlock(const QString& text) override;
};

#endif // WRONGWORDHIGHLIGHTER_H
