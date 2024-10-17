#pragma once

#include <string>
#include <fstream>

enum class Align { NotSettled, Left, Center, Right, Justify };

class FontStyle
{
	std::string name = "";
	std::string fontFamily = "";
	int fontSize = 0;
	Align align = Align::NotSettled;
	
public:
	FontStyle() = default;
	FontStyle(std::string_view name, std::string_view fontFamily, const int& fontSize, const Align& align) :
		name{name}, fontFamily{fontFamily}, fontSize{fontSize}, align{align} {}

	std::string getName() const;
	std::string getFontFamily() const;
	int getFontSize() const;
	Align getAlign() const;

	void setName(std::string_view name);
	void setFontFamily(std::string_view fontFamily);
	void setFontSize(const int& size);
	void setAlign(const Align& align);

	friend std::ofstream& operator<<(std::ofstream& file, const FontStyle& style)
	{
		size_t nameLength = style.getName().size();
		size_t familyLength = style.getName().size();
		int size = style.getFontSize();
		Align alignToWrite = style.getAlign();

		file.write(reinterpret_cast<const char*>(&nameLength), sizeof(size_t));
		file.write(style.getName().c_str(), nameLength);
		file.write(reinterpret_cast<const char*>(&familyLength), sizeof(size_t));
		file.write(style.getFontFamily().c_str(), familyLength);
		file.write(reinterpret_cast<const char*>(&size), sizeof(int));
		file.write(reinterpret_cast<const char*>(&alignToWrite), sizeof(Align));

		return file;
	}

	friend std::ifstream& operator>>(std::ifstream& file, FontStyle& style)
	{
		size_t nameLength;
		size_t familyLength;
		int readSize;
		Align readAlign;

		file.read(reinterpret_cast<char*>(&nameLength), sizeof(size_t));
		std::string readName(nameLength, '\0');
		file.read(&readName[0], nameLength);
		file.read(reinterpret_cast<char*>(&familyLength), sizeof(size_t));
		std::string readFontFamily(familyLength, '\0');
		file.read(&readFontFamily[0], familyLength);
		file.read(reinterpret_cast<char*>(&readSize), sizeof(int));
		file.read(reinterpret_cast<char*>(&readAlign), sizeof(Align));

		style = FontStyle(readName, readFontFamily, readSize, readAlign);

		return file;
	}
};