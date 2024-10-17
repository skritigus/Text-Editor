#pragma once

#include "FontStyle.h"
#include "List.h"
#include <string>

class StyleManager
{
public:
	static void enterParameters(List<int>& parameters);
	static void printParameters();

	static void printAlign(const Align& align);
	static void printAllAlign();
	static void printData(const FontStyle& style);
	static void printFontStyle(const List<FontStyle>& styles);

	static void createFontStyle(List<FontStyle>& styles);

	static void editFontStyle(List<FontStyle>& styles);
	static void editingByParameters(int parameter, FontStyle& editedStyle);

	static void swapFontStyles(List<FontStyle>& styles);

	static void deleteFontStyle(List<FontStyle>& styles);

	static void filterFontStyle(const List<FontStyle>& styles, List<FontStyle>& filteredStyles);
};