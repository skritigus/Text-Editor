#ifndef TEXTUPDATER_H
#define TEXTUPDATER_H

#include <QTextEdit>
#include "List.h"

class TextUpdater
{
    QTextEdit* textEdit;
    bool isTextEmphasized = false;
    bool isTextChangedByUser = true;

public:
    explicit TextUpdater(QTextEdit* textEdit) : textEdit(textEdit) {}

    void selectForReplacing(const int& textIndex, const int& patternLength);
    void emphasizeText(QList<QTextEdit::ExtraSelection>& selections, const int& textIndex, const int& patternLength);
    void replaceText(List<int>& indexes, int& currentIndex, const int& patternLength, const QString& replacing);
    void replaceAllText(const QString& text);

    void resetFlag();

    bool getIsTextChangedByUser() const;
};

#endif // TEXTUPDATER_H
