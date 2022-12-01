#include "pch.h"
#include "cablog.h"

HANDLE cablog::hConsole;

cablog::cablog()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}
void cablog::info(std::string input)
{
    WORD k = 240;
    SetConsoleTextAttribute(hConsole, k);

    std::cout << "Info:";

    SetConsoleTextAttribute(hConsole, 15);

    std::cout << " " << input << "\n";

}
void cablog::warn(std::string input)
{
    WORD k = 224;

    SetConsoleTextAttribute(hConsole, k);
    std::cout << "Warn:";

    SetConsoleTextAttribute(hConsole, 15);

    std::cout << " " << input << "\n";
}
void cablog::error(std::string input)
{
    WORD k = 79;
    SetConsoleTextAttribute(hConsole, k);

    std::cout << "Error:";

    SetConsoleTextAttribute(hConsole, 15);

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

void cablog::job(std::string job, std::string input)
{
    info(job + " with input: " + "'" + input + "'");
    //started audiograph with input: 'C:/your mother'
}

void cablog::created(std::string input)
{
    info("... Created " + input);
    //Created AudioGraph
}

std::string cablog::input()
{
    std::string input;
    std::getline(std::cin >> std::ws, input);

    return input;
}
std::string cablog::input(std::string toinput)
{
    
    WORD k = 240;
    SetConsoleTextAttribute(hConsole, k);

    std::cout << "Input";

    SetConsoleTextAttribute(hConsole, 15);

    std::cout << " " << toinput << ": ";

    std::string input;
    std::getline(std::cin >> std::ws, input);

    return input;

}

std::string* cablog::stringSplitter(std::string input)
{
	//Parce strings to array of strings
	std::string* output = new std::string[100];
	int i = 0;
	std::string temp = "";
	for (int j = 0; j < input.length(); j++)
	{
        if (i >= 100)
        {
			error("Input has too many commands!");
			break;
        }

		if (input[j] == ' ')
		{
			output[i] = temp;
			temp = "";
			i++;
		}
		else
		{
			temp += input[j];
		}
	}
	
	output[i] = temp;
	return output;
}