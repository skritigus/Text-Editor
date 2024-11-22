#ifndef FINDREPLACEMANAGER_H
#define FINDREPLACEMANAGER_H

#include <QObject>
#include "TextUpdater.h"
#include "IFindDependent.h"

class FindReplaceManager : public QObject
{
    Q_OBJECT

    QTextEdit* textEdit;
    TextUpdater* textUpdater;
    IFindDependent* finder = nullptr;
    bool isReplacerCalled = false;

public:
    explicit FindReplaceManager(QTextEdit* textEdit): textEdit(textEdit), textUpdater(new TextUpdater(textEdit)) {};
    ~FindReplaceManager();

    void setForFind();
    void setForReplace();

    void findPattern(const QString& pattern);
    void findAllPatterns(const QString& pattern);

    void nextPattern(const QString& pattern);
    void prevPattern(const QString& pattern);

    void replacePattern(const QString& pattern, const QString& replacing);
    void replaceAllPatterns(const QString& pattern, const QString& replacing);

    void resetResults();
    void disableConnections() const;
};

#endif // FINDREPLACEMANAGER_H
