#ifndef FINDER_H
#define FINDER_H

#include "KnuthMorrisPratt.h"
#include "IFindDependent.h"
#include <QTextEdit>

class Finder : public KnuthMorrisPratt, public IFindDependent
{
    QList<QTextEdit::ExtraSelection> selections;
    QTextCursor textCursor;
    List<int> indexes;
    int& patternLength = getPatternLength();
    int& currentIndex = getCurrentIndex();

public:
    Finder() = default;
    Finder(const Finder& finder) = default;
    ~Finder();

    void performSingle(const QString& text, const QString& pattern, const QString&) override;
    void performAll(QString& text, const QString& pattern, const QString&) override;

    QList<QTextEdit::ExtraSelection>& getSelections();
    List<int>& getIndexes() override;
    int& getTextIndex() override;

    void setCursor(const QTextCursor& newCursor);

    void next() override;
    void prev() override;
};

#endif // FINDER_H
