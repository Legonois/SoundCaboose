#pragma once
#include "winrt/Windows.Data.Json.h"

class CabooseProject
{
public:
	//Creates project with default configuation
	CabooseProject();
	//Creates project with custom JSON configuation
	CabooseProject(std::string JSONfilepath);
	//Creates project with custom JSON configuation using JSON object
	CabooseProject(winrt::Windows::Data::Json::JsonObject JSONobject);
	//Deconstructs project
	~CabooseProject();
};


