#include "FileTabItem.h"
#include "FileManager.h"
#include <QMessageBox>
#include <QStringBuilder>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>

FileTabItem::FileTabItem(const QString& filePath, const QString& text)
{
    fileManager = fileManager->getInstance();

    if(filePath == "Без имени")
    {
        fileName = filePath;
        this->filePath = nullptr;
        this->text = "";
        return;
    }

    fileName = QFileInfo(filePath).fileName();
    this->text = text;
    this->filePath = filePath;
}

FileTabItem::FileTabItem(const FileTabItem& other): fileName(other.fileName), filePath(other.filePath), text(other.text),
    timerId(other.timerId), cursorPosition(other.cursorPosition), anchorPosition(other.anchorPosition), isSaved(other.isSaved)
{
    fileManager->getInstance();
}

FileTabItem::~FileTabItem()
{
    if(!isSaved)
    {
        fileManager->closeFile(text, filePath, fileName, timerId);
    }
    filePath = nullptr;
    fileName = nullptr;
    text = nullptr;
}

QString& FileTabItem::getFileName()
{
    return fileName;
}

QString& FileTabItem::getFilePath()
{
    return filePath;
}

QString& FileTabItem::getText()
{
    return text;
}

int& FileTabItem::getTimerId()
{
    return timerId;
}

int& FileTabItem::getCursorPosition()
{
    return cursorPosition;
}

int& FileTabItem::getAnchorPosition()
{
    return anchorPosition;
}

bool FileTabItem::getIsSaved()
{
    return isSaved;
}

void FileTabItem::setText(const QString& newText)
{
    text = newText;
}

void FileTabItem::setFilePath(const QString& newFilePath)
{
    filePath = newFilePath;
    fileName = QFileInfo(filePath).fileName();
}

void FileTabItem::setCursorPosition(const int& pos)
{
    cursorPosition = pos;
}

void FileTabItem::setAnchorPosition(const int& pos)
{
    anchorPosition = pos;
}

void FileTabItem::setIsSaved(const bool& newIsSaved)
{
    isSaved = newIsSaved;
}

void FileTabItem::stopTimer()
{
    killTimer(timerId);
    timerId = 0;
}

void FileTabItem::beginTimer()
{
    timerId = startTimer(120000);
}

void FileTabItem::timerEvent(QTimerEvent*)
{
    fileManager = fileManager->getInstance();
    stopTimer();
    fileManager->saveToTemp(text, fileName);
}
