
//Inport Windows Runtime API settings
#include "pch.h"



//#include <Windows.h>

//Test inclusion of a Header File
//#include "testheader.h"

//Added Namespaces so code is easier to find
//using namespace winrt;
//using namespace winrt::Windows::Foundation;

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


IAsyncAction MainAsync()
{
	Uri uri(L"https://kennykerr.ca/feed");
	SyndicationClient client;
	SyndicationFeed feed = co_await client.RetrieveFeedAsync(uri);
	for (auto&& item : feed.Items())
	{
		hstring title = item.Title().Text();
		printf("%ls\n", title.c_str());
	}
}
int main()
{
	init_apartment();
	MainAsync().get();

	Cablog* Log = new Cablog();

	delete Log;
	
	Cablog::error("I hope it realy works guys!");
}
