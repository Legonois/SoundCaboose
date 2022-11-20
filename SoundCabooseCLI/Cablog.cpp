#include "pch.h"
#include "Cablog.h"

HANDLE Cablog::_hConsole;

Cablog::Cablog()
{
	_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Cablog::info(std::string input)
{
    //Sets to Info Color
    int k = 240;
    SetConsoleTextAttribute(_hConsole, k);

    std::cout << "Info:";

    //Sets back to original color
    SetConsoleTextAttribute(_hConsole, 15);

    std::cout << " " << input << "\n";
}
void Cablog::warn(std::string input)
{
    int k = 224;

    SetConsoleTextAttribute(_hConsole, k);
    std::cout << "Warn:";

    SetConsoleTextAttribute(_hConsole, 15);

    std::cout << " " << input << "\n";
}
void Cablog::error(std::string input)
{
    int k = 79;
    SetConsoleTextAttribute(_hConsole, k);

    std::cout << "Error:";

    SetConsoleTextAttribute(_hConsole, 15);

    std::cout << " " << input << "\n";
}
void Cablog::empt()
{
    std::cout << "\n";
}