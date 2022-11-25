#pragma once
class cablog
{
private:
	static HANDLE hConsole;

public:
	cablog();
	static void info(std::string input);
	void static warn(std::string input);
	void static error(std::string input);
	void static job(std::string job, std::string input);
	void static created(std::string input);
	void static empt();
	void static wait();
	std::string static input();
	std::string static input(std::string toinput);

	static std::string* stringSplitter(std::string input);
};

