#include "WrongWordHighlighter.h"

WrongWordHighlighter::WrongWordHighlighter(Dictionary* dictionary, QTextDocument* parent) : QSyntaxHighlighter(parent), dictionary(dictionary)
{
    QTextCharFormat format;

    format.setFontUnderline(true);
    format.setUnderlineColor(QColor("red"));
    format.setUnderlineStyle(QTextCharFormat::WaveUnderline);

    rule.wrongWordFormat = format;
    rule.pattern = QRegularExpression("[A-Za-z]+", QRegularExpression::UseUnicodePropertiesOption);
}

void WrongWordHighlighter::highlightBlock(const QString& text)
{
    QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
    while (matchIterator.hasNext())
    {
        QRegularExpressionMatch match = matchIterator.next();
        QString word = match.captured(0);
        if(!dictionary->searchNode(word.toLower()))
        {
            setFormat(match.capturedStart(), match.capturedLength(), rule.wrongWordFormat);
        }
    }
}
