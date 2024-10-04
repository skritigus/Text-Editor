#pragma once

#include <string>
#include <iostream>

enum FontFamily { TimesNewRoman, Calibri, ComicSans };
enum Color { Black, Yellow, Red, Green, Blue, White };
enum Align { Left, Center, Right, Justify };

class FontStyle
{
	std::string name;
	FontFamily fontFamily;
	Color color;
	Align align;

public:
	std::string GetName();
	FontFamily GetFontFamily();
	Color GetColor();
	Align GetAlign();

	void SetName(std::string name);
	void SetFontFamily(FontFamily fontFamily);
	void SetColor(Color color);
	void SetAlign(Align align);
};