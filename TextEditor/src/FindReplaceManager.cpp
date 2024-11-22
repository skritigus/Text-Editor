#include "FindReplaceManager.h"
#include "Finder.h"
#include "Replacer.h"
#include <QMessageBox>
#include <QStringBuilder>

FindReplaceManager::~FindReplaceManager()
{
    isReplacerCalled = false;

    delete finder;
}

void FindReplaceManager::setForFind()
{
    finder = new Finder(textEdit->textCursor());
}

void FindReplaceManager::setForReplace()
{
    finder = new Replacer;
    isReplacerCalled = true;
}

void FindReplaceManager::findPattern(const QString& pattern)
{
    finder->performSingle(textEdit->toPlainText(), pattern, "");

    if(finder->getCurrentIndex() == -1)
    {
        return;
    }
    if(isReplacerCalled)
    {
        textUpdater->selectForReplacing(finder->getTextIndex(), pattern.length());
    }
    else
    {
        textUpdater->emphasizeText(dynamic_cast<Finder*>(finder)->getSelections(), finder->getTextIndex(), pattern.length());
    }
}

void FindReplaceManager::findAllPatterns(const QString& pattern)
{
    QString text = textEdit->toPlainText();

    finder->performAll(text, pattern, "");

    if(finder->getCurrentIndex() == -1)
    {
        return;
    }

    textUpdater->emphasizeText(dynamic_cast<Finder*>(finder)->getSelections(), finder->getTextIndex(), pattern.length());
}

void FindReplaceManager::nextPattern(const QString& pattern)
{
    if(finder->getCurrentIndex() == -1)
    {
        findPattern(pattern);
        return;
    }

    if(finder->getIndexes().getCount() != 0)
    {
        finder->next();

        if(isReplacerCalled)
        {
            textUpdater->selectForReplacing(finder->getTextIndex(), pattern.length());
        }
        else
        {
            textUpdater->emphasizeText(dynamic_cast<Finder*>(finder)->getSelections(), finder->getTextIndex(), pattern.length());
        }
    }
}

void FindReplaceManager::prevPattern(const QString& pattern)
{
    if(finder->getCurrentIndex() == -1)
    {
        findPattern(pattern);
        return;
    }

    if(finder->getIndexes().getCount() != 0)
    {
        finder->prev();

        if(isReplacerCalled)
        {
            textUpdater->selectForReplacing(finder->getTextIndex(), pattern.length());
        }
        else
        {
            textUpdater->emphasizeText(dynamic_cast<Finder*>(finder)->getSelections(), finder->getTextIndex(), pattern.length());
        }
    }
}

void FindReplaceManager::replacePattern(const QString& pattern, const QString& replacing)
{
    finder->performSingle(textEdit->toPlainText(), pattern, replacing);

    if(finder->getCurrentIndex() == -1 || finder->getIndexes().getCount() == 0)
    {
        return;
    }
    textUpdater->replaceText(finder->getIndexes(), finder->getCurrentIndex(), pattern.length(), replacing);
}

void FindReplaceManager::replaceAllPatterns(const QString& pattern, const QString& replacing)
{
    QString text = textEdit->toPlainText();
    QString replaceCount;

    finder->performAll(text, pattern, replacing);
    textUpdater->replaceAllText(text);

    replaceCount = replaceCount.fromStdString(std::to_string(dynamic_cast<Replacer*>(finder)->getReplaceCount()));
    QMessageBox::information(nullptr, "Заменить все", "Готово. Количество замен:" % replaceCount);
}

void FindReplaceManager::resetResults()
{
    if(!textUpdater->getIsTextChangedByUser())
    {
        return;
    }

    if(!isReplacerCalled)
    {
        QList<QTextEdit::ExtraSelection> empty;
        textEdit->setExtraSelections(empty);
    }
    else
    {
        dynamic_cast<Replacer*>(finder)->setReplaceCount(0);
    }

    finder->getIndexes().clear();
    finder->setCurrentIndex(-1);
    textUpdater->resetFlag();
}

void FindReplaceManager::disableConnections() const
{
    if(isReplacerCalled)
    {
        disconnect(textEdit, &QTextEdit::selectionChanged, this, &FindReplaceManager::resetResults);
    }
    else
    {
        disconnect(textEdit, &QTextEdit::textChanged, this, &FindReplaceManager::resetResults);
    }
}
