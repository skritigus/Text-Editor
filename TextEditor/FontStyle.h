#pragma once
#include <string>

enum class Align { Left, Center, Right, Justify };

class FontStyle
{
	std::string name;
	std::string fontFamily;
	unsigned short fontSize;
	Align align;
	
public:
	FontStyle();
	FontStyle(const std::string& name, const std::string& fontFamily, const unsigned short& fontSize, const Align& align);
	
	std::string GetName() const;
	std::string GetFontFamily() const;
	unsigned short GetFontSize() const;
	Align GetAlign() const;

	void SetName(std::string& name);
	void SetFontFamily(std::string& fontFamily);
	void SetFontSize(const unsigned short& color);
	void SetAlign(const Align& align);

	void PrintAlign() const;
	void ChooseAlign();

	void PrintData() const;
};