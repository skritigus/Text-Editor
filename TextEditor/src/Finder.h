#ifndef FINDER_H
#define FINDER_H

#include "KnuthMorrisPratt.h"
#include "IFindDependent.h"
#include <QTextEdit>

class Finder final : public KnuthMorrisPratt, public IFindDependent
{
    QList<QTextEdit::ExtraSelection> selections;
    QTextCursor textCursor;
    List<int> indexes;
    int& patternLength = getPatternLength();
    int currentIndex = -1;

public:
    Finder(const QTextCursor& cursor);
    Finder(const Finder& finder) : selections(finder.selections), textCursor(finder.textCursor), indexes(finder.indexes) {}
    ~Finder() final;

    void performSingle(const QString& text, const QString& pattern, const QString&) override;
    void performAll(QString& text, const QString& pattern, const QString&) override;

    QList<QTextEdit::ExtraSelection>& getSelections();
    List<int>& getIndexes() override;
    int& getTextIndex() override;
    int& getCurrentIndex() override;

    void setCurrentIndex(const int& index) override;

    void next() override;
    void prev() override;
};

#endif // FINDER_H
