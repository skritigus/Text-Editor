#ifndef FINDREPLACEMANAGER_H
#define FINDREPLACEMANAGER_H

#include <QTextEdit>
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
    FindReplaceManager(QTextEdit* textEdit);
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
    void disableConnections();
};

#endif // FINDREPLACEMANAGER_H
