#pragma once
#include "cablog.h"
#include "winrt/Windows.Data.Json.h"
#include "winrt/Windows.Foundation.h"

class cabcui {
private:
	cablog* intcablog;
public:
	//constructor
	cabcui();
	//destructor
	~cabcui();

	static winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Data::Json::JsonObject> getjson(std::string input);

	
};