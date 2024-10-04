#include "Menu.h"
#include "Iterator.h"

int main()
{
	Menu menu;
	FontStyle* styles = new FontStyle[10];
	unsigned short select;

	std::cout << "Hello, user!" << std::endl;
	do
	{
		menu.PrintMenu();
		
		std::cin >> select;

		/*switch (select)
		{
		case 1:
			menu.CreateFontStyle();
			break;
		case 2:
			menu.PrintFontStyle();
			break;
		case 3:
			menu.EditFontStyle();
			break;
		case 4:
			menu.SwapFontStyles();
			break;
		case 5:
			menu.DeleteFontStyle();
			break;
		}*/
	} while (select != 8);
}