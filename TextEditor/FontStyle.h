#pragma once

#include <string>
#include <iostream>

enum class Align { Left, Center, Right, Justify };

class FontStyle
{
	std::string name;
	std::string fontFamily;
	unsigned short fontSize;
	Align align;
	
public:
	FontStyle();
	FontStyle(std::string_view name, std::string_view fontFamily, const unsigned short& fontSize, const Align& align);
	
	std::string GetName() const;
	std::string GetFontFamily() const;
	unsigned short GetFontSize() const;
	Align GetAlign() const;

	void SetName(std::string_view name);
	void SetFontFamily(std::string_view fontFamily);
	void SetFontSize(const unsigned short& color);
	void SetAlign(const Align& align);

	void PrintAlign() const;
	void ChooseAlign();

	void PrintData() const;
};