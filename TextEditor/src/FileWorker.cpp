#include "FileWorker.h"
#include <QStringBuilder>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

FileWorker::FileWorker()
{

}

/*void FileWorker::CreateFile()
{
    if(fileName)
    fileName = QFileDialog::getOpenFileName(nullptr, "test");
    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(nullptr, "Error", "Failed to open file");
        return;
    }
    emit OnTextOpen(fileName);

    QTextStream inputStream(&file);
    QString line;

    while (!inputStream.atEnd())
    {
        line = line % inputStream.readLine() % "\n";
    }
    emit OnTextRead(line);

    file.close();
}*/

void FileWorker::OpenFile()
{
    fileName = QFileDialog::getOpenFileName(nullptr, "test");
    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(nullptr, "Error", "Failed to open file");
        return;
    }
    emit OnTextOpen(fileName);

    QTextStream inputStream(&file);
    QString line;

    while (!inputStream.atEnd())
    {
        line = line % inputStream.readLine() % "\n";
    }
    emit OnTextRead(line);

    file.close();
}

void FileWorker::SaveFile(QString text)
{
    fileName = QFileDialog::getSaveFileName(nullptr, "test", "", "Documents (*.html)");
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(nullptr, "Error", "Failed to save file");
        return;
    }

    QTextStream outputStream(&file);
    outputStream << text;

    file.close();
}
