#ifndef FILEWORKER_H
#define FILEWORKER_H

#include <QString>
#include <QObject>


class FileWorker : public QObject
{
    Q_OBJECT

    QString fileName;

public:
    void createFile();
    void openFile();
    void saveFile(QString text);

signals:
    void onTextRead(QString);
    void onTextOpen(QString);
};

#endif // FILEWORKER_H
