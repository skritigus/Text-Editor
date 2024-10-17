#pragma once

#include <iostream>
#include <limits>

class InputCheck
{
public:
	static int inputInt(std::string_view info);
    static int inputIntWithLimits(std::string_view info, int min = std::numeric_limits<int>::min(), int max = std::numeric_limits<int>::max());
};