#pragma once
#include <iostream>
#include <limits>

class InputCheck
{
public:
	static int InputInt(std::string_view info);
    static int InputIntWithLimits(std::string_view info, int min = std::numeric_limits<int>::min(), int max = std::numeric_limits<int>::max());

	static char InputChar(std::string_view info);
};