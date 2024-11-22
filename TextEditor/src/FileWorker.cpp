#include "FileWorker.h"
#include <QStringBuilder>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

void FileWorker::openFile()
{
    fileName = QFileDialog::getOpenFileName(nullptr, "Открыть...");
    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось открыть файл");
        return;
    }
    emit onTextOpen(fileName);

    QTextStream inputStream(&file);
    QString line;

    while (!inputStream.atEnd())
    {
        line = line % inputStream.readLine() % "\n";
    }
    emit onTextRead(line);

    file.close();
}

void FileWorker::saveFile(QString text)
{
    fileName = QFileDialog::getSaveFileName(nullptr, "Сохранить", "", "Documents (*.html)");
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось сохранить файл");
        return;
    }

    QTextStream outputStream(&file);
    outputStream << text;

    file.close();
}
