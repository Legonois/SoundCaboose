#include "pch.h"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Web::Syndication;

using namespace winrt::Windows::Foundation::Collections;

using namespace winrt::Windows::Media;
using namespace winrt::Windows::Media::Devices;
using namespace winrt::Windows::Media::Capture;
using namespace winrt::Windows::Media::Audio;
using namespace winrt::Windows::Media::Render;
using namespace winrt::Windows::Media::MediaProperties;

IAsyncOperation<int> MainAsync()
{
    Cab* intcab = new Cab();
	
    co_await intcab->play2AudioFiles(cablog::input("filepath for an audiofile"), cablog::input("filepath for a second audiofile"));
    
    delete intcab;
	
    co_return 1;
}

IAsyncAction TestMain()
{
    Cab* intcab = new Cab();
	cabcui* intcabcui = new cabcui();

    std::string inputcommand = cablog::input("Command");

    while (inputcommand != "I")
    {
        std::string* commandArray = cablog::stringSplitter(inputcommand);
		std::string command = intcab->ToLower(commandArray[0]);
		cablog::info("Command: " + command);

		//if command is playfile
		if (command == "playfile")
		{
			bool fileTest = Cab::FileExists(commandArray[1]);
			if (fileTest == true)
			{
				//PlayFile
				co_await intcab->PlayFileOut(commandArray[1]);
			}
			else
			{
				//Dislpays command error
				cablog::error("File does not exist!");
			}
		}
		//if command is play2files
		else if (command == "play2files")
		{
			//play2files

			//check if commandarray[1] and commandarray[2] are valid files
			co_await intcab->play2AudioFiles(commandArray[1], commandArray[2]);
		}
		else if (command == "json")
		{
			auto jsonOBJ = co_await intcabcui->getjson(commandArray[1]);
			
			hstring printout = jsonOBJ.GetNamedString(to_hstring(commandArray[2]));
			
			cablog::info("Name: " + winrt::to_string(printout));
		}
		else if (command == "jsoncommand")
		{
			auto jsonOBJ = co_await intcabcui->getjson(commandArray[1]);
			
			std::string args = to_string(jsonOBJ.GetNamedString(to_hstring("arguments")));
			
			co_await intcab->PlayFileOut(args);
		}
		else if (command == "file?")
		{
			bool hi = Cab::FileExists(commandArray[1]);
			if (hi) {
				cablog::info("File exists!");
			}
			else {
				cablog::error("File does not exist!");
			}
		}
        else if (command == "exit")
        {
			break;
		}
		else if (command == "quit")
		{
			break;
		}
		else if (command == "q")
		{
			break;
		}
		else if (command == "^C")
		{
			break;
		}
		else if (command == "i")
		{
			
			//print valid commands
			cablog::empt();
			cablog::info("Valid Commands:");
			cablog::info("playfile          | Plays Audio file with an <filepath>");
			cablog::info("play2files        | Plays 2 Audio files  <filepath> <filepath>");
			cablog::info("                  |");
			cablog::info("exit              | Exits the program");
			cablog::info("quit              |");
			cablog::info("q                 |");
			cablog::info("^C                |");
			cablog::empt();
			cablog::info("i                 | Prints this help message");
			
		}
		else
		{
			cablog::error("Command '" + command + "' not found");
			cablog::error("Type 'I' for help");
        }

		
        delete[] commandArray;
			
        inputcommand = cablog::input("Command");
    }
	
	intcabcui->~cabcui();
	delete intcabcui;
    
    delete intcab;

	co_return;
}


int main()
{
    init_apartment();
	
    TestMain().get();
    
    return 0;
}
