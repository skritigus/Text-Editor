#include "FileManager.h"
#include "StyleManager.h"
#include "InputCheck.h"
#include <iostream>

int main()
{
	List<FontStyle> styles;
	List<FontStyle> filteredStyles;

	int select;

	std::cout << "Hello, user!" << std::endl;

	FileManager::ReadFromFile("FontStyles.bin", styles);
	FileManager::ReadFromFile("FilteredFontStyles.bin", filteredStyles);

	do
	{
		std::cout << "Choose one option from below:" << std::endl;
		std::cout << "1. Create font styles" << std::endl;
		std::cout << "2. Print font styles" << std::endl;
		std::cout << "3. Edit font style" << std::endl;
		std::cout << "4. Swap font styles" << std::endl;
		std::cout << "5. Delete font styles" << std::endl;
		std::cout << "6. Filter font styles" << std::endl;
		std::cout << "7. Quit" << std::endl;
		
		select = InputCheck::InputIntWithLimits("", 1, 7);
		system("cls");

		switch (select)
		{
		case 1:
			StyleManager::CreateFontStyle(styles);
			FileManager::WriteToFile("FontStyles.bin", styles);
			break;
		case 2:
			StyleManager::PrintFontStyle(styles);
			break;
		case 3:
			StyleManager::EditFontStyle(styles);
			FileManager::WriteToFile("FontStyles.bin", styles);
			break;
		case 4:
			StyleManager::SwapFontStyles(styles);
			FileManager::WriteToFile("FontStyles.bin", styles);
			break;
		case 5:
			StyleManager::DeleteFontStyle(styles);
			FileManager::WriteToFile("FontStyles.bin", styles);
			break;
		case 6:
			StyleManager::FilterFontStyle(styles, filteredStyles);
			break;
		default:
			break;
		}
	} while (select != 7);
}