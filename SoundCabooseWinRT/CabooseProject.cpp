#include "pch.h"
#include "CabooseProject.h"

//Creates project with default configuation
CabooseProject::CabooseProject()
{
	
}
//Creates project with custom JSON configuation
CabooseProject::CabooseProject(std::string JSONfilepath)
{

}
//Creates project with custom JSON configuation using JSON object
CabooseProject::CabooseProject(winrt::Windows::Data::Json::JsonObject JSONobject)
{
	
}
//Deconstructs project (eventually close and serialize project)
CabooseProject::~CabooseProject()
{
	
}