#include "FontStyle.h"

std::string FontStyle::GetName()
{
	return name;
}

FontFamily FontStyle::GetFontFamily()
{
	return fontFamily;
}

Color FontStyle::GetColor()
{
	return color;
}

Align FontStyle::GetAlign()
{
	return align;
}

void FontStyle::SetName(std::string name)
{
	this->name = name;
}

void FontStyle::SetFontFamily(FontFamily fontFamily)
{
	this->fontFamily = fontFamily;
}

void FontStyle::SetColor(Color color)
{
	this->color = color;
}

void FontStyle::SetAlign(Align align)
{
	this->align = align;
}