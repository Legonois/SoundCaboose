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
    

    co_await Cab::PlayFileOut(cablog::input("filepath for an audiofile"));
    
    
    co_return 1;
}

int main()
{
    //Initalize Windows Apartment
    init_apartment();

    //Initalize "Caboose Audio Backend"
    Cab* intcab = new Cab();

    /*Uri uri(L"http://aka.ms/cppwinrt");
    printf("Hello, %ls!\n", uri.AbsoluteUri().c_str());*/

    MainAsync().get();

    delete intcab;


    //cablog::cablog();

    //cablog::wait();
    //cablog::empt();
    //cablog::error("Test Error");
    //cablog::info("Test Info");
    //cablog::warn("Test Warn");
    
    return 0;
}
