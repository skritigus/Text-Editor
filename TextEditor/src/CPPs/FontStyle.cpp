#include "FontStyle.h"
#include <iostream>

std::string FontStyle::getName() const
{
	return name;
}

int FontStyle::getFontSize() const
{
	return fontSize;
}

std::string FontStyle::getFontFamily() const
{
	return fontFamily;
}

Align FontStyle::getAlign() const
{
	return align;
}

void FontStyle::setName(std::string_view newName)
{
	name = newName;
}

void FontStyle::setFontFamily(std::string_view newFontFamily)
{
	fontFamily = newFontFamily;
}

void FontStyle::setFontSize(const int& newFontSize)
{
	fontSize = newFontSize;
}

void FontStyle::setAlign(const Align& newAlign)
{
	align = newAlign;
}