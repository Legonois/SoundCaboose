#pragma once
class Cablog
{
	private:

	public:
	static HANDLE _hConsole;
	Cablog();
	void static info(std::string input);
	void static warn(std::string input);
	void static error(std::string input);
	void static empt();
};

