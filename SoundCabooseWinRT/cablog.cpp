#include "pch.h"
#include "cablog.h"

HANDLE cablog::_hConsole;

cablog::cablog()
{
	_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}
void cablog::info(std::string input)
{
    int k = 240;
    SetConsoleTextAttribute(_hConsole, k);

    std::cout << "Info:";

    SetConsoleTextAttribute(_hConsole, 15);

    std::cout << " " << input << "\n";

}
void cablog::warn(std::string input)
{
    int k = 224;

    SetConsoleTextAttribute(_hConsole, k);
    std::cout << "Warn:";

    SetConsoleTextAttribute(_hConsole, 15);

    std::cout << " " << input << "\n";
}
void cablog::error(std::string input)
{
    int k = 79;
    SetConsoleTextAttribute(_hConsole, k);

    std::cout << "Error:";

    SetConsoleTextAttribute(_hConsole, 15);

    std::cout << " " << input << "\n";
}
void cablog::empt()
{
    std::cout << "\n";
}
void cablog::wait()
{
    empt();
    warn("Debug has paused the App. Press 'Enter' to continue");
    std::cin.ignore();
    info("... Resuming");
    empt();
}