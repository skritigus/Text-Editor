#include "FileManager.h"
#include "StyleSerializer.h"
#include <QXmlStreamWriter>
#include <QJsonObject>
#include <QStringBuilder>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonDocument>

FileManager* FileManager::instance = nullptr;

FileManager::FileManager()
{
    QDir temp;
    temp.mkdir("temp");
}

FileManager::~FileManager()
{
    QDir temp("temp");
    temp.removeRecursively();
}

FileManager* FileManager::getInstance()
{
    if(!instance)
    {
        instance = new FileManager;
    }
    return instance;
}

QString FileManager::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Открыть...", "C:\\", "Documents (*.html *.txt);;XML files (*.xml);;JSON files(*.json)");

    if(filePath == nullptr)
    {
        return nullptr;
    }

    QFile file(filePath);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось открыть файл");
        return nullptr;
    }
    emit fileOpened(filePath);

    QTextStream inputStream(&file);
    QString line;

    while (!inputStream.atEnd())
    {
        line = line % inputStream.readLine() % "\n";
    }
    emit textRead(line);

    file.close();
    return filePath;
}

QString FileManager::saveAsFile(const QString& text)
{
    QString filePath = QFileDialog::getSaveFileName(nullptr, "Сохранить", "C:\\", "Documents (*.html)");

    if(filePath == nullptr)
    {
        return nullptr;
    }
    return saveFile(text, filePath);
}

QString FileManager::saveFile(const QString& text, const QString& filePath)
{
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось сохранить файл");
        return nullptr;
    }

    QTextStream outputStream(&file);
    outputStream << text;

    file.close();
    return filePath;
}

void FileManager::loadDictionary(Dictionary* dictionary)
{
    QFile file("rus.xml");

    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось открыть файл");
        return;
    }

    QXmlStreamReader xmlReader(&file);

    while (!xmlReader.atEnd())
    {
        xmlReader.readNextStartElement();
        if(xmlReader.name().toString() == "word")
        {
            dictionary->addNode(xmlReader.readElementText());
            continue;
        }
    }

    file.close();
}

void FileManager::saveDictionary(Dictionary* dictionary)
{
    QFile file("rus.xml");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось открыть файл");
        return;
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);

    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("dictionary");

    dictionary->deleteTree(xmlWriter);

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();

    file.close();
}

bool FileManager::closeFile(const QString& text, QString& filePath, const QString& fileName, const int& timerId)
{
    QMessageBox messageDialog;
    QString shownName;

    if(filePath == nullptr)
    {
        shownName = "Без имени";
    }
    else
    {
        shownName = QFileInfo(filePath).fileName();
    }

    messageDialog.setText("Сохранить изменения файлa\"" % shownName % "\"?");
    messageDialog.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    int result = messageDialog.exec();

    if(result == QMessageBox::Cancel)
    {
        messageDialog.close();
        return false;
    }

    if(result == QMessageBox::Save)
    {
        if(timerId != 0)
        {
            if(filePath == nullptr)
            {
                saveAsFile(text);
            }
            else
            {
                saveFile(text, filePath);
            }
        }
        else
        {
            QFile tempFile("temp\\" % fileName);
            if(filePath == nullptr)
            {
                QString newFilePath = QFileDialog::getSaveFileName(nullptr, "Сохранить", "C:\\", "Documents (*.html)");
                filePath = newFilePath;
            }
            else
            {
                tempFile.copy(filePath);
            }
        }
    }

    messageDialog.close();
    return true;
}

void FileManager::saveToTemp(QString& text, QString& fileName)
{
    if(fileName == "Без имени")
    {
        fileName = fileName.setNum(fileCount) % ".tmp";
    }
    else
    {
        QString num;
        fileName = fileName.prepend(num.setNum(fileCount));
    }
    ++fileCount;

    QFile file("temp\\" % fileName);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось сохранить файл");
        return;
    }

    QTextStream outputStream(&file);
    outputStream << text;

    text.clear();

    file.close();
}

QString FileManager::loadFromTemp(QString& fileName)
{
    QFile file("temp\\" % fileName);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось открыть файл");
        return nullptr;
    }

    QTextStream inputStream(&file);
    QString text;

    while (!inputStream.atEnd())
    {
        text = text % inputStream.readLine() % "\n";
    }

    file.close();
    return text;
}

void FileManager::loadStyles(List<FontStyle>& styles)
{
    QFile file("FontStyles.json");

    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось открыть файл");
        return;
    }

    QByteArray stylesObject;

    while (!file.atEnd())
    {
        stylesObject = stylesObject % file.readLine();
    }

    QJsonDocument jsonDoc = QJsonDocument::fromJson(stylesObject);

    styles = StyleSerializer::stylesArrayFromJson(jsonDoc.object());

    file.close();
}

void FileManager::saveStyles(const List<FontStyle>& styles)
{
    QFile file("FontStyles.json");

    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось сохранить файл");
        return;
    }

    QJsonObject stylesObject = StyleSerializer::stylesArrayToJson(styles);
    file.write(QJsonDocument(stylesObject).toJson());

    file.close();
}
