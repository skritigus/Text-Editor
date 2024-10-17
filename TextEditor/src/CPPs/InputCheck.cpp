#include "InputCheck.h"
#include <iostream>
#include <limits>
#include <set>

int InputCheck::inputInt(std::string_view info)
{
    int num;

    std::cout << info << std::endl;
    while (!(std::cin >> num))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Wrong input. Try again" << std::endl;
    }

    return num;
}

int InputCheck::inputIntWithLimits(std::string_view info, int min, int max)
{
    int num;

    while (true)
    {
        num = inputInt(info);
        if (num < min || num > max)
        {
            std::cout << "Wrong input. Enter number from " << min << " to " << max << std::endl << std::flush;
            continue;
        }
        break;
    }

    return num;
}