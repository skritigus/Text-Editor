#ifndef FileTabItem_H
#define FileTabItem_H

#include "FontStyle.h"
#include "FileManager.h"
#include <QListWidget>
#include <QObject>

class  FileTabItem : public QObject
{
    Q_OBJECT

    QString fileName;
    QString filePath;
    QString text = nullptr;
    FileManager* fileManager;
    int timerId = -1;
    int cursorPosition = 0;
    int anchorPosition = 0;
    bool isSaved = true;

public:
    FileTabItem(const QString& filePath, const QString& text);
    FileTabItem(const FileTabItem& other);
    ~FileTabItem();

    QString& getFileName();
    QString& getFilePath();
    QString& getText();
    int& getTimerId();
    int& getCursorPosition();
    int& getAnchorPosition();
    bool& getIsSaved();

    void setText(const QString& text);
    void setFilePath(const QString& filePath);
    void setFontStyle(const FontStyle& fontStyle);
    void setCursorPosition(const int& pos);
    void setAnchorPosition(const int& pos);
    void setIsSaved(const bool& isSaved);

    void stopTimer();
    void beginTimer();

    void timerEvent(QTimerEvent* event) override;

    FileTabItem& operator=(const FileTabItem& other)
    {
        fileName = other.fileName;
        fileManager->getInstance();
        filePath = other.filePath;
        cursorPosition = other.cursorPosition;
        anchorPosition = other.anchorPosition;
        timerId = other.timerId;
        text = other.text;
        isSaved = other.isSaved;

        return *this;
    }
};

#endif // FileTabItem_H
