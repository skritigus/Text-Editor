#pragma once

#include "FontStyle.h"
#include "List.h"
#include <string>

class StyleManager
{
public:
	static void EnterParameters(List<int>& parameters);
	static void PrintParameters();

	static std::string PrintAlign(const Align& align);
	static void PrintAllAlign();
	static void PrintData(const FontStyle& style);

	static void CreateFontStyle(List<FontStyle>& styles);
	static void PrintFontStyle(const List<FontStyle>& styles);
	static void EditFontStyle(List<FontStyle>& styles);
	static void EditingByParameters(int parameter, FontStyle& editedStyle);
	static void SwapFontStyles(List<FontStyle>& styles);
	static void DeleteFontStyle(List<FontStyle>& styles);
	static void FilterFontStyle(const List<FontStyle>& styles, List<FontStyle>& filteredStyles);
};