#include "WrongWordHighlighter.h"

WrongWordHighlighter::WrongWordHighlighter(Dictionary* dictionary, QTextDocument* parent) : QSyntaxHighlighter(parent), dictionary(dictionary)
{
    wrongWordFormat.setFontUnderline(true);
    wrongWordFormat.setUnderlineColor(QColor("red"));
    wrongWordFormat.setUnderlineStyle(QTextCharFormat::WaveUnderline);

    rule.format = wrongWordFormat;
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
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}

QTextCharFormat WrongWordHighlighter::getFormat(const int& pos)
{
    return format(pos);
}
