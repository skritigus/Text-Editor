#pragma once

#include "FontStyle.h"
#include <vector>

class Menu
{
public:
	void PrintMenu();

	void CreateFontStyle();
	void PrintFontStyle();
	void EditFontStyle();
	void SwapFontStyles();
	void DeleteFontStyle();
};