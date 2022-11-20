#pragma once
class Cablog
{
	private:
	static HANDLE _hconsole;
	public:
	Cablog();
	void static info(std::string input);
	void static warn(std::string input);
	void static error(std::string input);
	void static empt();
};

