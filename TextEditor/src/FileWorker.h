#ifndef FILEWORKER_H
#define FILEWORKER_H

#include <QString>
#include <QStringBuilder>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QObject>
#include "FontStyle.h"
#include "List.h"


class FileWorker : public QObject
{
    Q_OBJECT

    QString fileName;

public:
    FileWorker();

    void CreateFile();
    void OpenFile();
    void SaveFile(QString text);

    void OpenFontStyles(List<FontStyle>& styles);
    void SaveFontStyles(List<FontStyle>& styles);

signals:
    void OnTextRead(QString);
    void OnTextOpen(QString);
};

#endif // FILEWORKER_H
