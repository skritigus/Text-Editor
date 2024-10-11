#include "FileManager.h"
#include "FontStyle.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

void FileManager::WriteToFile(const std::string& fileName, const List<FontStyle>& styles)
{
    std::ofstream file(fileName, std::ios::out | std::ios::binary);

    if (!file) 
    {
        std::cerr << "Error: File was not opened" << std::endl;
        return;
    }

    auto write = [&file](Node<FontStyle>& node)
    {
        file << node.GetData().GetName() << std::endl;
        file << node.GetData().GetFontFamily() << std::endl;
        file << node.GetData().GetFontSize() << std::endl;
        file << (int)node.GetData().GetAlign() << std::endl;
    };

    file << styles.GetCount() << std::endl;
    std::for_each(styles.cbegin(), styles.cend(), write);

    file.close();
}

void FileManager::ReadFromFile(const std::string& fileName, List<FontStyle>& styles)
{
    std::ifstream file(fileName, std::ios::binary | std::ios::in);

    if (!file) 
    {
        std::cerr << "Error: File was not opened" << std::endl;
        return;
    }

    int count;
    int size;
    std::string name;
    std::string fontFamily;
    int align;

    file >> count;
    for (int i = 0; i < count; ++i)
    {
        file >> name >> fontFamily >> size >> align;

        FontStyle style(name, fontFamily, size, (Align)align);
        styles.PushBack(style);
    }

    file.close();
}

