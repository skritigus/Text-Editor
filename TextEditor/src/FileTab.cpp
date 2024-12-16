#include "FileTab.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QMouseEvent>

FileTab::FileTab(QFontComboBox* fontFamily, TextEditManager* textEdit):
    fontFamily(fontFamily), textEdit(textEdit)
{
    fileManager->getInstance();
    styleManager = styleManager->getInstance();

    contextMenu->addAction(closeFileAction);

    connect(closeFileAction, &QAction::triggered, this, &FileTab::removeFile);
    connect(this, &QListWidget::currentItemChanged, this, &FileTab::changeFiles);
}

FileTab::~FileTab()
{
    disconnect(this, &QListWidget::currentItemChanged, this, &FileTab::changeFiles);
    takeItem(0);
    files.clear();
}

void FileTab::changeFiles(QListWidgetItem* current, QListWidgetItem* previous)
{
    if(previous == nullptr || current == nullptr)
    {
        return;
    }

    FileTabItem& prevItem = files[row(previous)];
    FileTabItem& curItem = files[row(current)];

    if(curItem.getTimerId() != -1)
    {
        if(curItem.getTimerId() == 0)
        {
            curItem.setText(fileManager->loadFromTemp(curItem.getFileName()));
        }
        else
        {
            curItem.stopTimer();
        }
    }

    savePrevFileInfo(prevItem);
    setCurrentFileInfo(curItem);

    isTextChangedByUser = false;
    textEdit->setText(curItem.getText());
    isTextChangedByUser = true;

    if(!isTextEditConnected && curItem.getIsSaved())
    {
        isTextEditConnected = connect(textEdit, &QTextEdit::textChanged, this, &FileTab::setFileUnsaved);
    }
    else
    {
        if(isTextEditConnected && !curItem.getIsSaved())
        {
            isTextEditConnected = !disconnect(textEdit, &QTextEdit::textChanged, this, &FileTab::setFileUnsaved);
        }
    }

    if(curItem.getFilePath() == nullptr)
    {
        emit fileChanged("Без имени");
    }
    else
    {
        emit fileChanged(curItem.getFilePath());
    }

    prevItem.beginTimer();
}

void FileTab::addFile(const QString& filePath)
{
    files.pushFront(FileTabItem(filePath, textEdit->toHtml()));
    insertItem(0, QFileInfo(filePath).fileName());
    setCurrentRow(0);

    if(!isTextEditConnected)
    {
        isTextEditConnected = connect(textEdit, &QTextEdit::textChanged, this, &FileTab::setFileUnsaved);
    }
}

void FileTab::setFileUnsaved()
{
    FileTabItem& file = getCurrentFile();
    if(!isTextChangedByUser || !file.getIsSaved())
    {
        return;
    }

    QListWidgetItem* fileItem = currentItem();
    fileItem->setText(fileItem->text().append('*'));

    file.setIsSaved(false);
    isTextEditConnected = !disconnect(textEdit, &QTextEdit::textChanged, this, &FileTab::setFileUnsaved);
}

void FileTab::setFileSaved(const QString& filePath)
{
    QListWidgetItem* fileItem = currentItem();
    FileTabItem& file = getCurrentFile();

    if(filePath != file.getFilePath())
    {
        file.setFilePath(filePath);
        fileItem->setText(file.getFileName());
    }
    else
    {
        fileItem->setText(fileItem->text().removeLast());
    }
    file.setIsSaved(true);

    if(!isTextEditConnected)
    {
        isTextEditConnected = connect(textEdit, &QTextEdit::textChanged, this, &FileTab::setFileUnsaved);
    }
}

FileTabItem& FileTab::getCurrentFile()
{
    return files[currentRow()];
}

void FileTab::savePrevFileInfo(FileTabItem& prevItem)
{
    prevItem.setAnchorPosition(textEdit->textCursor().anchor());
    prevItem.setAnchorPosition(textEdit->textCursor().position());
    prevItem.setText(textEdit->toHtml());
}

void FileTab::setCurrentFileInfo(FileTabItem& curItem)
{
    QTextCursor cursor = textEdit->textCursor();
    int cursorPos = curItem.getCursorPosition();
    int anchorPos = curItem.getAnchorPosition();

    if(cursorPos == anchorPos)
    {
        cursor.setPosition(cursorPos);
    }
    else
    {
        cursor.setPosition(anchorPos);
        cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, cursorPos - anchorPos);
    }
    textEdit->setTextCursor(cursor);

    isTextChangedByUser = false;
    textEdit->setText(curItem.getText());
    isTextChangedByUser = true;
}

void FileTab::removeFile()
{
    QPoint position = closeFileAction->data().toPoint();
    QListWidgetItem* fileItem = itemAt(position);
    FileTabItem& file = files[row(fileItem)];
    bool isClosed = true;

    if(fileItem == currentItem())
    {
        if(row(fileItem) + 1 == files.getCount())
        {
            setCurrentRow(0);
        }
        else
        {
            setCurrentRow(row(fileItem) + 1);
        }
    }
    if(!file.getIsSaved())
    {
        isClosed = fileManager->closeFile(file.getText(), file.getFilePath(), file.getText(), file.getTimerId());
    }
    if(!isClosed)
    {
        return;
    }

    file.setIsSaved(true);
    files.deleteByIndex(row(fileItem));
    takeItem(row(fileItem));

    if(files.getCount() == 0)
    {
        isTextEditConnected = !disconnect(textEdit, &QTextEdit::textChanged, this, &FileTab::setFileUnsaved);
        textEdit->setText("Откройте или создайте новый файл");
        textEdit->setReadOnly(true);
    }
}

void FileTab::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::RightButton && itemAt(event->pos()) != nullptr)
    {
        contextMenu->popup(mapToGlobal(event->pos()));
        closeFileAction->setData(QVariant(event->pos()));
        return;
    }
    QListWidget::mousePressEvent(event);
}

List<FileTabItem>& FileTab::getFiles()
{
    return files;
}
