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

//IAsyncAction for void
//IAsyncOperation< "type" > for type

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

    std::string inputcommand = cablog::input("Command");

    while (inputcommand != "exit" && inputcommand != "quit" && inputcommand != "q" && inputcommand != "^C")
    {
        std::string* commandArray = cablog::stringSplitter(inputcommand);
		std::string command = commandArray[0];
		cablog::info("Command: " + command);

		//if command is playfile
		if (command == "playfile")
		{
			//playfile
			co_await intcab->PlayFileOut(commandArray[1]);
		}
		//if command is play2files
		else if (command == "play2files")
		{
			//play2files
			co_await intcab->play2AudioFiles(commandArray[1], commandArray[2]);
		}

		
        delete[] commandArray;
			
        inputcommand = cablog::input("Command");
    }
    
    delete intcab;

	co_return;
}


int main()
{
    //Initalize Windows Apartment
    init_apartment();

    //Initalize "Caboose Audio Backend"
    
 //   try {
 //       std::string* namess = Cab::stringy();
	//	
 //       cablog::info(namess[1]);
	//	
 //       delete[] namess;
 //   }
	//catch (const hresult_error& e) {
	//	cablog::error(to_string(e.message()));
	//}
	//catch (const std::exception& e) {
	//	cablog::error(e.what());
	//}
	//catch (...) {
	//	cablog::error("Unknown error");
	//}
	
    TestMain();

    //cablog::info("");
    

    /*Uri uri(L"http://aka.ms/cppwinrt");
    printf("Hello, %ls!\n", uri.AbsoluteUri().c_str());*/

    //MainAsync().get();

    


    //cablog::cablog();

    //cablog::wait();
    //cablog::empt();
    //cablog::error("Test Error");
    //cablog::info("Test Info");
    //cablog::warn("Test Warn");
    
    return 0;
}
