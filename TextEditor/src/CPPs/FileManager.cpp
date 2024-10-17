#include "FileManager.h"
#include "FontStyle.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

void FileManager::writeToFile(const std::string& fileName, const List<FontStyle>& styles)
{
    std::ofstream file(fileName, std::ios::out | std::ios::binary);

    if (!file) 
    {
        std::cerr << "Error: File was not opened" << std::endl;
        return;
    }

    int count = styles.getCount();
    file.write(reinterpret_cast<const char*>(&count), sizeof(int));

    auto write = [&file](Node<FontStyle>& node)
    {
        file << node.getData();
    };

    std::for_each(styles.cbegin(), styles.cend(), write);

    file.close();
}

void FileManager::readFromFile(const std::string& fileName, List<FontStyle>& styles)
{
    std::ifstream file(fileName, std::ios::binary | std::ios::in);

    if (!file) 
    {
        std::cerr << "Error: File was not opened" << std::endl;
        return;
    }

    int count;
    FontStyle style;

    file.read(reinterpret_cast<char*>(&count), sizeof(int));
    for (int i = 0; i < count; ++i)
    {
        file >> style;
        styles.pushBack(style);
    }

    file.close();
}

