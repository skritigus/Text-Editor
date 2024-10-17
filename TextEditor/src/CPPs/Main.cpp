#include "FileManager.h"
#include "StyleManager.h"
#include "InputCheck.h"
#include <iostream>

int main()
{
	int select;
	List<FontStyle> styles;
	List<FontStyle> filteredStyles;

	std::cout << "Hello, user!" << std::endl;

	FileManager::readFromFile("FontStyles.bin", styles);
	FileManager::readFromFile("FilteredFontStyles.bin", filteredStyles);

	do
	{
		std::cout << "Choose one option from below:" << std::endl;
		std::cout << "1. Create font styles" << std::endl;
		std::cout << "2. Print font styles" << std::endl;
		std::cout << "3. Edit font style" << std::endl;
		std::cout << "4. Swap font styles" << std::endl;
		std::cout << "5. Delete font styles" << std::endl;
		std::cout << "6. Filter font styles" << std::endl;
		std::cout << "7. Print filtered font styles" << std::endl;
		std::cout << "8. Quit" << std::endl;
		
		select = InputCheck::inputIntWithLimits("", 1, 8);
		system("cls");

		switch (select)
		{
		case 1:
			StyleManager::createFontStyle(styles);
			FileManager::writeToFile("FontStyles.bin", styles);
			break;
		case 2:
			StyleManager::printFontStyle(styles);
			break;
		case 3:
			StyleManager::editFontStyle(styles);
			FileManager::writeToFile("FontStyles.bin", styles);
			break;
		case 4:
			StyleManager::swapFontStyles(styles);
			FileManager::writeToFile("FontStyles.bin", styles);
			break;
		case 5:
			StyleManager::deleteFontStyle(styles);
			FileManager::writeToFile("FontStyles.bin", styles);
			break;
		case 6:
			StyleManager::filterFontStyle(styles, filteredStyles);
			FileManager::writeToFile("FilteredFontStyles.bin", filteredStyles);
			break;
		case 7:
			StyleManager::printFontStyle(filteredStyles);
			break;
		default:
			break;
		}
	} while (select != 8);
}