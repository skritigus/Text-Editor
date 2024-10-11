#pragma once

#include "FontStyle.h"
#include "List.h"
#include <iostream>
#include <fstream>
#include <string>

class FileManager
{
public:
	static void WriteToFile(const std::string& fileName, const List<FontStyle>& styles);
	static void ReadFromFile(const std::string& fileName, List<FontStyle>& styles);
};