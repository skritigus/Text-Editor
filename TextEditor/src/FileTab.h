#ifndef FILETAB_H
#define FILETAB_H

#include "List.h"
#include "FileTabItem.h"
#include "FileManager.h"
#include "TextEditManager.h"
#include <QListWidget>
#include <QFontComboBox>
#include <QMenu>

class FileTab : public QListWidget
{
    Q_OBJECT

    FileManager* fileManager;
    TextEditManager* textEdit;
    List<FileTabItem> files;
    QMenu* contextMenu = new QMenu(this);
    QAction* closeFileAction = new QAction("Закрыть файл");
    bool isTextEditConnected = false;
    bool isTextChangedByUser = true;

    void changeFiles(const QListWidgetItem* current, const QListWidgetItem* previous);

    void savePrevFileInfo(FileTabItem& prevItem);
    void setCurrentFileInfo(FileTabItem& curItem);

signals:
    void fileChanged(const QString& filePath);

public:
    FileTab();
    ~FileTab();

    FileTabItem& getCurrentFile();
    List<FileTabItem>& getFiles();

    void setFileUnsaved();
    void setFileSaved(const QString& filePath);

    void addFile(const QString& filePath);
    void removeFile();

    void mousePressEvent(QMouseEvent* event) override;
};

#endif // FILETAB_H
