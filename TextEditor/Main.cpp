#include "Menu.h"
#include <iostream>

int main()
{
	Menu menu;
	
	List<FontStyle> styles;

	unsigned short select;
	FontStyle style1("asd", "asd", 1, Align::Center);
	FontStyle style2("asd", "asd", 100, Align::Center);
	FontStyle style3("asd", "asd", 3, Align::Center);
	FontStyle style4("asd", "asd", 7, Align::Center);
	styles.PushBack(style1);
	styles.PushBack(style2);
	styles.PushBack(style3);
	styles.PushBack(style4);

	std::cout << "Hello, user!" << std::endl;
	do
	{
		menu.PrintMenu();
		
		std::cin >> select;
		system("cls");

		switch (select)
		{
		case 1:
			menu.CreateFontStyle(styles);
			std::cout << "The result:" << std::endl;
			menu.PrintFontStyle(styles);
			break;
		case 2:
			menu.PrintFontStyle(styles);
			break;
		case 3:
			menu.PrintFontStyle(styles);
			menu.EditFontStyle(styles);
			std::cout << "The result:" << std::endl;
			menu.PrintFontStyle(styles);
			break;
		case 4:
			menu.PrintFontStyle(styles);
			menu.SwapFontStyles(styles);
			std::cout << "The result:" << std::endl;
			menu.PrintFontStyle(styles);
			break;
		case 5:
			menu.PrintFontStyle(styles);
			menu.DeleteFontStyle(styles);
			std::cout << "The result:" << std::endl;
			menu.PrintFontStyle(styles);
			break;
		default:
			break;
		}
	} while (select != 6);
}