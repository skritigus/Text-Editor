#include "FontStyle.h"
#include <iostream>

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