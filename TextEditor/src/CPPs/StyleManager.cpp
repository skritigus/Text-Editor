#include "StyleManager.h"
#include "FileManager.h"
#include "InputCheck.h"
#include <iostream>
#include <algorithm>

void StyleManager::PrintParameters()
{
	std::cout << "Choose filtering parameters from below or 0 to stop:" << std::endl;
	std::cout << "1. Font style's name" << std::endl;
	std::cout << "2. Font family" << std::endl;
	std::cout << "3. Font size" << std::endl;
	std::cout << "4. Align" << std::endl;
}

void StyleManager::CreateFontStyle(List<FontStyle>& styles)
{
	int amount;
	int size;
	std::string name;
	std::string fontFamily;
	int align;

	amount = InputCheck::InputIntWithLimits("Enter the font style's amount to add:", 1);

	for (int i = 0; i < amount; ++i)
	{
		system("cls");
		std::cout << "Enter the font style's name or 0 to stop:" << std::endl;
		std::cin >> name;
		if (name == "0")
		{
			break;
		}

		std::cout << "Enter the font family's name:" << std::endl;
		std::cin >> fontFamily;

		size = InputCheck::InputIntWithLimits("Enter the font size", 1);

		PrintAllAlign();
		align = InputCheck::InputIntWithLimits("", 1, 4);

		FontStyle style(name, fontFamily, size, (Align)align);

		styles.PushBack(style);
	}

	std::cout << "The result:" << std::endl;
	PrintFontStyle(styles);
}


void StyleManager::PrintFontStyle(const List<FontStyle>& styles)
{
	int count = 0;

	if(styles.GetCount())
	{
		std::cout << "   Name\t\tFont family\tSize\tAlign" << std::endl;

		auto print = [&count](Node<FontStyle>& node)
		{
			++count;
			std::cout << count << ". ";
			PrintData(node.GetData());
		};

		std::for_each(styles.cbegin(), styles.cend(), print);
	}
	else
	{
		std::cout << "There is no font styles" << std::endl;
	}
}

void StyleManager::EditingByParameters(int parameter, FontStyle& editedStyle)
{
	int size;
	std::string name;
	std::string fontFamily;
	int align;

	switch (parameter)
	{
	case 1:
		std::cout << "Enter the new font style's name:" << std::endl;
		std::cin >> name;
		editedStyle.SetName(name);
		break;
	case 2:
		std::cout << "Enter the new font family's name:" << std::endl;
		std::cin >> fontFamily;
		editedStyle.SetFontFamily(fontFamily);
		break;
	case 3:
		size = InputCheck::InputIntWithLimits("Enter the new font size:", 1);
		editedStyle.SetFontSize(size);
		break;
	case 4:
		PrintAllAlign();
		align = InputCheck::InputIntWithLimits("", 1, 4);
		editedStyle.SetAlign((Align)align);
		break;
	default:
		break;
	}
}

void StyleManager::EditFontStyle(List<FontStyle>& styles)
{
	List<int> parameters;
	int select;
	
	std::cout << "Choose style to edit:" << std::endl;
	PrintFontStyle(styles);
	select = InputCheck::InputIntWithLimits("", 1, styles.GetCount());
	--select;

	FontStyle& editedFontStyle = styles[select].GetData();

	EnterParameters(parameters);

	auto edit = [&editedFontStyle](Node<int>& node)
	{
		EditingByParameters(node.GetData(), editedFontStyle);
	};

	std::for_each(parameters.cbegin(), parameters.cend(), edit);

	std::cout << "The result:" << std::endl;
	PrintFontStyle(styles);
}

void StyleManager::SwapFontStyles(List<FontStyle>& styles)
{
	int select1;
	int select2;

	PrintFontStyle(styles);
	std::cout << "Choose the font styles to swap:" << std::endl;
	std::cin >> select1;
	--select1;
	std::cin >> select2;
	--select2;

	styles.SwapNodes(styles[select1], styles[select2]);

	std::cout << "The result:" << std::endl;
	PrintFontStyle(styles);
}

void StyleManager::DeleteFontStyle(List<FontStyle>& styles)
{
	int select;
	List<int> indexes;

	PrintFontStyle(styles);
	std::cout << "Choose the font styles to delete or 0 to stop:" << std::endl;
	do
	{
		std::cin >> select;
		--select;
		if (select > -1)
		{
			indexes.PushBack(select);
		}
	} while (select != -1);

	indexes.Sort();

	for (ListIterator<int> it = indexes.begin(nullptr), end = indexes.end(indexes.GetLast()); it != end;)
	{
		styles.DeleteByIndex(end->GetData());
		--end;
		indexes.PopBack();
	}

	std::cout << "The result:" << std::endl;
	PrintFontStyle(styles);
}

void StyleManager::FilterFontStyle(const List<FontStyle>& styles, List<FontStyle>& filteredStyles)
{
	List<int> parameters;
	FontStyle filteredStyle;

	EnterParameters(parameters);

	auto edit = [&filteredStyle](Node<int>& node)
	{
		EditingByParameters(node.GetData(), filteredStyle);
	};

	std::for_each(parameters.cbegin(), parameters.cend(), edit);

	auto filter = [&filteredStyle](Node<FontStyle>& node)
	{

		if (FontStyle styleFromList = node.GetData(); 
			filteredStyle.GetName() != "" && filteredStyle.GetName() != styleFromList.GetName() ||
			filteredStyle.GetFontFamily() != "" && filteredStyle.GetFontFamily() != styleFromList.GetFontFamily() ||
			filteredStyle.GetFontSize() != 0 && filteredStyle.GetFontSize() != styleFromList.GetFontSize() ||
			filteredStyle.GetAlign() != Align::NotSettled && filteredStyle.GetAlign() != styleFromList.GetAlign())
		{
			return false;
		}

		return true;
	};

	auto create = [&filteredStyles, &filter](Node<FontStyle>& node)
	{
		if (filter(node))
		{
			filteredStyles.PushBack(node.GetData());
		}
	};

	std::for_each(styles.cbegin(), styles.cend(), create);

	if (filteredStyles.GetCount() != 0)
	{
		std::cout << "The filtered list:" << std::endl;
		PrintFontStyle(filteredStyles);
	}
	else
	{
		std::cout << "Nothing matches the parameters" << std::endl;
	}
}

void StyleManager::PrintAllAlign()
{
	std::cout << "Choose the align:" << std::endl;
	std::cout << "1. Left" << std::endl;
	std::cout << "2. Center" << std::endl;
	std::cout << "3. Right" << std::endl;
	std::cout << "4. Justify" << std::endl;
}

std::string StyleManager::PrintAlign(const Align& align)
{
	switch (align)
	{
		using enum Align;
	case Left:
		return "Left";
	case Center:
		return "Center";
	case Right:
		return "Right";
	case Justify:
		return "Justify";
	case NotSettled:
		return "Not Settled";
	}
}

void StyleManager::PrintData(const FontStyle& style)
{
	std::cout << style.GetName() << "\t\t";
	std::cout << style.GetFontFamily() << "\t\t";
	std::cout << style.GetFontSize() << "\t";
	std::cout << PrintAlign(style.GetAlign());
	std::cout << "\t" << std::endl;
}

void StyleManager::EnterParameters(List<int>& parameters)
{
	int select;

	PrintParameters();
	do
	{
		select = InputCheck::InputIntWithLimits("", 0, 4);
		if (select > 0)
		{
			parameters.PushBack(select);
		}
	} while (select != 0);
}