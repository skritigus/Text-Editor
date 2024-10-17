#include "StyleManager.h"
#include "FileManager.h"
#include "InputCheck.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <format>

void StyleManager::printParameters()
{
	std::cout << "Choose filtering parameters from below or 0 to stop:" << std::endl;
	std::cout << "1. Font style's name" << std::endl;
	std::cout << "2. Font family" << std::endl;
	std::cout << "3. Font size" << std::endl;
	std::cout << "4. Align" << std::endl;
}

void StyleManager::createFontStyle(List<FontStyle>& styles)
{
	int amount;
	int size;
	std::string name;
	std::string fontFamily;
	int align;

	amount = InputCheck::inputIntWithLimits("Enter the font style's amount to add:", 1);

	for (int i = 0; i < amount; ++i)
	{
		system("cls");
		std::cout << "Enter the font style's name or 0 to stop:" << std::endl;
		std::cin.ignore();
		std::getline(std::cin, name);
		if (name == "0")
		{
			break;
		}

		std::cout << "Enter the font family's name:" << std::endl;
		std::getline(std::cin, fontFamily);

		size = InputCheck::inputIntWithLimits("Enter the font size", 1);

		printAllAlign();
		align = InputCheck::inputIntWithLimits("", 1, 4);

		FontStyle style(name, fontFamily, size, (Align)align);

		styles.pushBack(style);
	}

	std::cout << "The result:" << std::endl;
	printFontStyle(styles);
}


void StyleManager::printFontStyle(const List<FontStyle>& styles)
{
	int count = 0;

	if(styles.getCount())
	{
		std::cout << "   Name              Font family       Size   Align" << std::endl;

		auto print = [&count](Node<FontStyle>& node)
		{
			++count;
			std::cout << count << ". ";
			printData(node.getData());
		};

		std::for_each(styles.cbegin(), styles.cend(), print);
	}
	else
	{
		std::cout << "There is no font styles" << std::endl;
	}
}

void StyleManager::editingByParameters(int parameter, FontStyle& editedStyle)
{
	int size;
	std::string name;
	std::string fontFamily;
	int align;

	switch (parameter)
	{
	case 1:
		std::cout << "Enter the new font style's name:" << std::endl;
		std::cin.ignore();
		std::getline(std::cin, name);
		editedStyle.setName(name);
		break;
	case 2:
		std::cout << "Enter the new font family's name:" << std::endl;
		std::cin.ignore();
		std::getline(std::cin, fontFamily);
		editedStyle.setFontFamily(fontFamily);
		break;
	case 3:
		size = InputCheck::inputIntWithLimits("Enter the new font size:", 1);
		editedStyle.setFontSize(size);
		break;
	case 4:
		printAllAlign();
		align = InputCheck::inputIntWithLimits("", 1, 4);
		editedStyle.setAlign((Align)align);
		break;
	default:
		break;
	}
}

void StyleManager::editFontStyle(List<FontStyle>& styles)
{
	List<int> parameters;
	int select;
	
	std::cout << "Choose style to edit:" << std::endl;
	printFontStyle(styles);
	select = InputCheck::inputIntWithLimits("", 1, styles.getCount());
	--select;

	FontStyle& editedFontStyle = styles[select].getData();

	enterParameters(parameters);

	auto edit = [&editedFontStyle](Node<int>& node)
	{
		editingByParameters(node.getData(), editedFontStyle);
	};

	std::for_each(parameters.cbegin(), parameters.cend(), edit);

	std::cout << "The result:" << std::endl;
	printFontStyle(styles);
}

void StyleManager::swapFontStyles(List<FontStyle>& styles)
{
	int select1;
	int select2;

	printFontStyle(styles);
	std::cout << "Choose the font styles to swap:" << std::endl;
	select1 = InputCheck::inputIntWithLimits("", 1, styles.getCount());
	--select1;
	select2 = InputCheck::inputIntWithLimits("", 1, styles.getCount());
	--select2;

	styles.swapNodes(styles[select1], styles[select2]);

	std::cout << "The result:" << std::endl;
	printFontStyle(styles);
}

void StyleManager::deleteFontStyle(List<FontStyle>& styles)
{
	int select;
	List<int> indexes;

	printFontStyle(styles);
	std::cout << "Choose the font styles to delete or 0 to stop:" << std::endl;
	do
	{
		std::cin >> select;
		--select;
		if (select > -1)
		{
			indexes.pushBack(select);
		}
	} while (select != -1);

	indexes.sort();

	for (ListIterator<int> it = indexes.begin(nullptr), end = indexes.end(indexes.getLast()); it != end;)
	{
		styles.deleteByIndex(end->getData());
		--end;
		indexes.popBack();
	}

	std::cout << "The result:" << std::endl;
	printFontStyle(styles);
}

void StyleManager::filterFontStyle(const List<FontStyle>& styles, List<FontStyle>& oldFilteredStyles)
{
	List<int> parameters;
	List<FontStyle> newFilteredStyles;
	FontStyle filteredStyle;

	enterParameters(parameters);

	auto edit = [&filteredStyle](Node<int>& node)
	{
		editingByParameters(node.getData(), filteredStyle);
	};

	std::for_each(parameters.cbegin(), parameters.cend(), edit);

	auto filter = [&filteredStyle](Node<FontStyle>& node)
	{
		if (FontStyle styleFromList = node.getData(); 
			filteredStyle.getName() != "" && filteredStyle.getName() != styleFromList.getName() ||
			filteredStyle.getFontFamily() != "" && filteredStyle.getFontFamily() != styleFromList.getFontFamily() ||
			filteredStyle.getFontSize() != 0 && filteredStyle.getFontSize() != styleFromList.getFontSize() ||
			filteredStyle.getAlign() != Align::NotSettled && filteredStyle.getAlign() != styleFromList.getAlign())
		{
			return false;
		}

		return true;
	};

	auto create = [&newFilteredStyles, &filter](Node<FontStyle>& node)
	{
		if (filter(node))
		{
			newFilteredStyles.pushBack(node.getData());
		}
	};

	std::for_each(styles.cbegin(), styles.cend(), create);

	if (newFilteredStyles.getCount() != 0)
	{
		std::cout << "The filtered list:" << std::endl;
		printFontStyle(newFilteredStyles);
	}
	else
	{
		std::cout << "Nothing matches the parameters" << std::endl;
	}

	oldFilteredStyles = std::move(newFilteredStyles);
}

void StyleManager::printAllAlign()
{
	std::cout << "Choose the align:" << std::endl;
	std::cout << "1. Left" << std::endl;
	std::cout << "2. Center" << std::endl;
	std::cout << "3. Right" << std::endl;
	std::cout << "4. Justify" << std::endl;
}

void StyleManager::printAlign(const Align& align)
{
	switch (align)
	{
		using enum Align;
	case Left:
		std::cout << "Left";
		break;
	case Center:
		std::cout << "Center";
		break;
	case Right:
		std::cout << "Right";
		break;
	case Justify:
		std::cout << "Justify";
		break;
	case NotSettled:
		std::cout << "Not Settled";
		break;
	}
}

void StyleManager::printData(const FontStyle& style)
{
	std::cout << std::format("{:<15}   ", style.getName());
	std::cout << std::format("{:<15}   ", style.getFontFamily());
	std::cout << std::format("{:<4}   ", style.getFontSize());
	printAlign(style.getAlign());
	std::cout << std::endl;
}

void StyleManager::enterParameters(List<int>& parameters)
{
	int select;

	printParameters();
	do
	{
		select = InputCheck::inputIntWithLimits("", 0, 4);
		if (select > 0)
		{
			parameters.pushBack(select);
		}
	} while (select != 0);
}