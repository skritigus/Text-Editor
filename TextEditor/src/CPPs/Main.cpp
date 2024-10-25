#include "FileManager.h"
#include "StyleManager.h"
#include "InputCheck.h"

int main()
{
	int select;
	StyleManager manager;

	std::cout << "Hello, user!" << std::endl;

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
			manager.createFontStyles();
			FileManager::writeToFile("FontStyles.bin", manager.getStyles());
			break;
		case 2:
			StyleManager::printFontStyles(manager.getStyles());
			break;
		case 3:
			manager.editFontStyle();
			FileManager::writeToFile("FontStyles.bin", manager.getStyles());
			break;
		case 4:
			manager.swapFontStyles();
			FileManager::writeToFile("FontStyles.bin", manager.getStyles());
			break;
		case 5:
			manager.deleteFontStyles();
			FileManager::writeToFile("FontStyles.bin", manager.getStyles());
			break;
		case 6:
			manager.filterFontStyles();
			FileManager::writeToFile("FilteredFontStyles.bin", manager.getFilteredStyles());
			break;
		case 7:
			StyleManager::printFontStyles(manager.getFilteredStyles());
			break;
		default:
			break;
		}
	} while (select != 8);
}