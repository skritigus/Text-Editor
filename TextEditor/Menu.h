#pragma once

#include "FontStyle.h"
#include "List.h"

class Menu
{
public:
	void PrintMenu() const;
	void PrintAlign() const;

	void CreateFontStyle(List<FontStyle>& styles) const;
	void PrintFontStyle(const List<FontStyle>& styles) const;
	void EditFontStyle(List<FontStyle>& styles) const;
	void SwapFontStyles(List<FontStyle>& styles) const;
	void DeleteFontStyle(List<FontStyle>& styles) const;
};