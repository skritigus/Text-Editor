#pragma once

#include "FontStyle.h"
#include "List.h"

class FileManager
{
public:
	static void writeToFile(const std::string& fileName, const List<FontStyle>& styles);
	static void readFromFile(const std::string& fileName, List<FontStyle>& styles);
};