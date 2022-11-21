#pragma once
#include "winrt/Windows.Foundation.h"
#include "cablog.h"

class Cab 
{
private:
	cablog* intcablog;

public:
	Cab();
	static std::string RemoveInvalidChars(std::string input);
	static std::string FileParse(std::string input);
	static std::string PathParse(std::string input);
	static std::string ToBackSlash(std::string input);
	static winrt::Windows::Foundation::IAsyncOperation<int> PlayFileOut(std::string input);
	~Cab();


};