#pragma once
#include <string>

enum class Align { Left, Center, Right, Justify };

class FontStyle
{
	std::string name = "";
	std::string fontFamily = "";
	int fontSize = 0;
	Align align = Align::Left;
	
public:
	FontStyle() = default;
	FontStyle(std::string_view name, std::string_view fontFamily, const int& fontSize, const Align& align);
	
	std::string GetName() const;
	std::string GetFontFamily() const;
	int GetFontSize() const;
	Align GetAlign() const;

	void SetName(std::string_view name);
	void SetFontFamily(std::string_view fontFamily);
	void SetFontSize(const int& color);
	void SetAlign(const Align& align);

	void PrintAlign() const;
	void ChooseAlign();

	void PrintData() const;
};