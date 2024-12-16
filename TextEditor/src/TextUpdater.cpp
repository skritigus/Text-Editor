#include "TextUpdater.h"

void TextUpdater::selectForReplacing(const int& textIndex, const int& patternLength)
{
    QTextCursor cursor = textEdit->textCursor();

    if(!isTextEmphasized)
    {
        QList<QTextEdit::ExtraSelection> selections;

        isTextEmphasized = true;
        textEdit->setExtraSelections(selections);
    }

    cursor.setPosition(textIndex, QTextCursor::MoveAnchor);
    cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, patternLength);
    isTextChangedByUser = false;
    textEdit->setTextCursor(cursor);
    isTextChangedByUser = true;
}

void TextUpdater::emphasizeText(QList<QTextEdit::ExtraSelection>& selections, const int& textIndex, const int& patternLength)
{
    QTextCursor cursor = textEdit->textCursor();
    QTextCharFormat backgroundColor;

    textEdit->setExtraSelections(QList<QTextEdit::ExtraSelection>());

    cursor.setPosition(textIndex);
    cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, patternLength);

    selections.last().cursor = cursor;

    textEdit->setExtraSelections(selections);
}

void TextUpdater::replaceText(List<int>& indexes, int& currentIndex, const int& patternLength, const QString& replacing)
{
    if(!isTextEmphasized)
    {
        selectForReplacing(indexes[currentIndex], patternLength);
        isTextEmphasized = true;
        return;
    }

    isTextChangedByUser = false;
    textEdit->insertHtml(replacing);
    isTextChangedByUser = true;

    indexes.deleteByIndex(currentIndex);
    if(indexes.getCount() != 0)
    {
        if(currentIndex == indexes.getCount())
        {
            --currentIndex;
        }

        selectForReplacing(indexes[currentIndex], patternLength);
    }
}

void TextUpdater::replaceAllText(const QString& text)
{
    textEdit->selectAll();
    textEdit->insertHtml(text);
}

void TextUpdater::resetFlag()
{
    isTextEmphasized = false;
}

bool TextUpdater::getIsTextChangedByUser() const
{
    return isTextChangedByUser;
}
