#pragma once

#include "FontStyle.h"
#include "List.h"
#include <string>

class StyleManager
{
	List<FontStyle> styles;
	List<FontStyle> filteredStyles;

public:
	StyleManager();

	List<FontStyle>& getStyles();
	List<FontStyle>& getFilteredStyles();

	static void printParameters();
	static void printAlign(const Align& align);
	static void printAllAlign();
	static void printData(const FontStyle& style);
	static void printFontStyles(const List<FontStyle>& styles);

	static void enterParameters(List<int>& parameters);

	void createFontStyles();

	void editFontStyle();
	static void editingByParameters(int parameter, FontStyle& editedStyle);

	void swapFontStyles();

	void deleteFontStyles();

	void filterFontStyles();
};