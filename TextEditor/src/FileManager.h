#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>
#include <QObject>
#include "Dictionary.h"
#include "FontStyle.h"
#include "List.h"


class FileManager : public QObject
{
    Q_OBJECT

    static FileManager* instance;
    int fileCount = 0;

    FileManager();

public:
    ~FileManager();

    FileManager* getInstance();

    QString openFile();
    QString saveFile(const QString& text, const QString& filePath);
    QString saveAsFile(const QString& text);
    bool closeFile(const QString& text, QString& filePath, const QString& fileName, const int& timerId);

    void saveToTemp(QString& text, QString& fileName);
    QString loadFromTemp(QString& fileName);

    static void loadDictionary(Dictionary* dictionary);
    static void saveDictionary(Dictionary* dictionary);

    static void loadStyles(List<FontStyle>& styles);
    static void saveStyles(const List<FontStyle>& styles);

signals:
    void textRead(const QString&);
    void fileOpened(const QString&);
};

#endif // FILEMANAGER_H
