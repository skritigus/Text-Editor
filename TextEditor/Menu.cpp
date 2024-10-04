#include "Menu.h"

void Menu::PrintMenu()
{
	std::cout << "Choose one option from below:" << std::endl;
	std::cout << "1. Create font styles" << std::endl;
	std::cout << "2. Print font styles" << std::endl;
	std::cout << "3. Edit font style" << std::endl;
	std::cout << "4. Swap font styles" << std::endl;
	std::cout << "5. Delete font styles" << std::endl;
	std::cout << "6. Quit" << std::endl;
}

void Menu::CreateFontStyle()
{

}

//void Menu::PrintFontStyle()
//{
//	unsigned short itemNum;
//	Item* item;
//
//	std::cin >> itemNum;
//	item = world.TakeItem(itemNum);
//	if (!hotbar.AddItem(item))
//	{
//		world.AddItem(item);
//	}
//}
//
//void Menu::EditFontStyle()
//{
//
//}
//
//void Menu::SwapFontStyles()
//{
//	unsigned short slotNum1, slotNum2;
//
//	std::cin >> slotNum1 >> slotNum2;
//	hotbar.SwapItems(slotNum1, slotNum2);
//}
//
//void Menu::DeleteFontStyle()
//{
//	unsigned short itemNum;
//
//	std::cin >> itemNum;
//	world.TakeItem(itemNum);
//}