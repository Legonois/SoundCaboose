#include "cabcui.h"
#include "pch.h"

using namespace winrt;
//using namespace winrt::Windows;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Foundation::Collections;

using namespace winrt::Windows::Media;
using namespace winrt::Windows::Media::Devices;
using namespace winrt::Windows::Media::Capture;
using namespace winrt::Windows::Media::Audio;
using namespace winrt::Windows::Media::Render;
using namespace winrt::Windows::Media::MediaProperties;

//cabio class constructor
cabcui::cabcui() {
	intcablog = new cablog();
}
//cabio class destructor
cabcui::~cabcui() {
	delete intcablog;
}

//cabio class program loop
IAsyncAction IOCommandLoop() {


	cablog::info("Testing info guys!");

	co_return;
}

