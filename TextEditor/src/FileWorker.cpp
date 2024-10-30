#include "FileWorker.h"

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

void FileWorker::OpenFontStyles(List<FontStyle>& styles)
{
    QFile file("FontStyles.bin");

    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(nullptr, "Error", "Failed to open file");
        return;
    }

    QDataStream inputStream(&file);

    FontStyle style;
    while (inputStream.readRawData(reinterpret_cast<char*>(&style), sizeof(FontStyle)))
    {
        styles.pushBack(style);
    }

    file.close();
}

void FileWorker::SaveFontStyles(List<FontStyle>& styles)
{
    QFile file("FontStyles.bin");

    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(nullptr, "Error", "Failed to save file");
        return;
    }

    QDataStream outputStream(&file);

    for(ListIterator<FontStyle> it = styles.cbegin(), end = styles.cend(); it != end; ++it)
    {
        outputStream.writeRawData(reinterpret_cast<char*>(&it->getData()), sizeof(FontStyle));
    }

    file.close();
}
