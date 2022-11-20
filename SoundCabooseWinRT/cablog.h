#pragma once
class cablog
{
public:
	static HANDLE _hConsole;
	cablog();
	static void info(std::string input);
	void static warn(std::string input);
	void static error(std::string input);
	void static empt();
	void static wait();

};

