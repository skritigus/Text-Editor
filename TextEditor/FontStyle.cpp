#include "FontStyle.h"
#include <iostream>

FontStyle::FontStyle(std::string_view name, std::string_view fontFamily, const int& fontSize, const Align& align)
{
	this->name = name;
	this->fontFamily = fontFamily;
	this->fontSize = fontSize;
	this->align = align;
}

std::string FontStyle::GetName() const
{
	return name;
}

int FontStyle::GetFontSize() const
{
	return fontSize;
}

std::string FontStyle::GetFontFamily() const
{
	return fontFamily;
}

Align FontStyle::GetAlign() const
{
	return align;
}

void FontStyle::SetName(std::string_view newName)
{
	name = newName;
}

void FontStyle::SetFontFamily(std::string_view newFontFamily)
{
	fontFamily = newFontFamily;
}

void FontStyle::SetFontSize(const int& newFontSize)
{
	fontSize = newFontSize;
}

void FontStyle::SetAlign(const Align& newAlign)
{
	align = newAlign;
}

void FontStyle::PrintAlign() const
{
	switch (align)
	{
		using enum Align;
	case Left:
		std::cout << "Left";
		break;
	case Center:
		std::cout << "Center";
		break;
	case Right:
		std::cout << "Right";
		break;
	case Justify:
		std::cout << "Justify";
		break;
	}
}

void FontStyle::ChooseAlign()
{
	int newAlign;
	
	std::cin >> newAlign;

	switch (newAlign)
	{
		using enum Align;
	case 1:
		align = Left;
		break;
	case 2:
		align = Center;
		break;
	case 3:
		align = Right;
		break;
	case 4:
		align = Justify;
		break;
	default:
		break;
	}
}

void FontStyle::PrintData() const
{
	std::cout << name << "\t\t";
	std::cout << fontFamily << "\t\t";
	std::cout << fontSize << "\t";
	PrintAlign();
	std::cout << "\t" << std::endl;
}