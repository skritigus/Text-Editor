#include "FontStyle.h"
#include <iostream>

FontStyle::FontStyle()
{
	name = "";
	fontFamily = "";
	fontSize = 0;
	align = Align::Left;
}

FontStyle::FontStyle(const std::string& name, const std::string& fontFamily, const unsigned short& fontSize, const Align& align)
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

unsigned short FontStyle::GetFontSize() const
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

void FontStyle::SetName(std::string& newName)
{
	name = newName;
}

void FontStyle::SetFontFamily(std::string& newFontFamily)
{
	fontFamily = newFontFamily;
}

void FontStyle::SetFontSize(const unsigned short& newFontSize)
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
	case Align::Left:
		std::cout << "Left";
		break;
	case  Align::Center:
		std::cout << "Center";
		break;
	case  Align::Right:
		std::cout << "Right";
		break;
	case  Align::Justify:
		std::cout << "Justify";
		break;
	}
}

void FontStyle::ChooseAlign()
{
	unsigned short newAlign;
	
	std::cin >> newAlign;

	switch (newAlign)
	{
	case 1:
		align = Align::Left;
		break;
	case 2:
		align = Align::Center;
		break;
	case 3:
		align = Align::Right;
		break;
	case 4:
		align = Align::Justify;
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