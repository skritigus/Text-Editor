#include "Menu.h"
#include <algorithm>
#include <iostream>


void Menu::PrintMenu() const
{
	std::cout << "Choose one option from below:" << std::endl;
	std::cout << "1. Create font styles" << std::endl;
	std::cout << "2. Print font styles" << std::endl;
	std::cout << "3. Edit font style" << std::endl;
	std::cout << "4. Swap font styles" << std::endl;
	std::cout << "5. Delete font styles" << std::endl;
	std::cout << "6. Quit" << std::endl;
}

void Menu::PrintAlign() const
{
	std::cout << "Choose align:" << std::endl;
	std::cout << "1. Left" << std::endl;
	std::cout << "2. Center" << std::endl;
	std::cout << "3. Right" << std::endl;
	std::cout << "4. Justify" << std::endl;
}

void Menu::CreateFontStyle(List<FontStyle>& styles) const
{
	int amount;
	int size;
	std::string name;
	std::string fontFamily;

	std::cout << "Enter the font style's amount to add:" << std::endl;
	std::cin >> amount;

	for (int i = 0; i < amount; ++i)
	{
		system("cls");
		std::cout << "Enter the font style's name:" << std::endl;
		std::cin >> name;

		std::cout << "Enter the font family's name:" << std::endl;
		std::cin >> fontFamily;

		std::cout << "Enter the font size:" << std::endl;
		std::cin >> size;

		std::cout << "Choose the align:" << std::endl;
		PrintAlign();
		
		FontStyle style(name, fontFamily, size, Align::Left);

		style.ChooseAlign();
		styles.PushBack(style);
	}
}


void Menu::PrintFontStyle(const List<FontStyle>& styles) const
{
	int count = 0;

	std::cout << "   Name\t\tFont family\tSize\tAlign" << std::endl;

	auto print = [&count](Node<FontStyle>& node)
	{
		++count;
		std::cout << count << ". ";
		node.GetData().PrintData();
	};

	std::for_each(styles.cbegin(), styles.cend(), print);
}

void Menu::EditFontStyle(List<FontStyle>& styles) const
{
	int select;
	int size;
	std::string name;
	std::string fontFamily;
	Align align;

	std::cout << "Choose the font style to edit:" << std::endl;
	std::cin >> select;
	--select;
	FontStyle& editedFontStyle = styles[select].GetData();

	std::cout << "Enter the font style's name:" << std::endl;
	std::cin >> name;
	editedFontStyle.SetName(name);

	std::cout << "Enter the font family's name:" << std::endl;
	std::cin >> fontFamily;
	editedFontStyle.SetFontFamily(fontFamily);

	std::cout << "Enter the font size:" << std::endl;
	std::cin >> size;
	editedFontStyle.SetFontSize(size);

	std::cout << "Choose the align:" << std::endl;
	editedFontStyle.PrintAlign();
	editedFontStyle.ChooseAlign();
	editedFontStyle.SetAlign(align);
}

void Menu::SwapFontStyles(List<FontStyle>& styles) const
{
	int select1;
	int select2;

	std::cout << "Choose the font styles to swap:" << std::endl;
	std::cin >> select1;
	--select1;
	std::cin >> select2;
	--select2;
	
	styles.SwapNodes(styles[select1], styles[select2]);
}

void Menu::DeleteFontStyle(List<FontStyle>& styles) const
{
	int num;
	List<int> indexes;

	std::cout << "Choose the font styles to delete or 0 to stop:" << std::endl;
	do
	{
		std::cin >> num;
		--num;
		indexes.PushBack(num);
	} while (++num != 0);
	indexes.PopBack();

	indexes.QuickSort();

	for (ListIterator<int> it = indexes.begin(nullptr), end = indexes.end(indexes.GetLast()); it != end;)
	{
		try
		{
			styles.DeleteByIndex(end->GetData());
		}
		catch (std::exception& ex)
		{
			std::cout << ex.what() << "\n";
		}
		--end;
		indexes.PopBack();
	}
}