#pragma once
#include <string>

enum class Align { NotSettled, Left, Center, Right, Justify };

class FontStyle
{
	std::string name = "";
	std::string fontFamily = "";
	int fontSize = 0;
	Align align = Align::NotSettled;
	
public:
	FontStyle() = default;
	FontStyle(std::string_view name, std::string_view fontFamily, const int& fontSize, const Align& align) :
		name{name}, fontFamily{fontFamily}, fontSize{fontSize}, align{align} {}

	std::string GetName() const;
	std::string GetFontFamily() const;
	int GetFontSize() const;
	Align GetAlign() const;

	void SetName(std::string_view name);
	void SetFontFamily(std::string_view fontFamily);
	void SetFontSize(const int& color);
	void SetAlign(const Align& align);

	bool operator==(const FontStyle& style) const
	{
		return name == style.GetName();
	}

	auto operator<=>(const FontStyle& style) const
	{
		return name <=> style.GetName();
	}
};