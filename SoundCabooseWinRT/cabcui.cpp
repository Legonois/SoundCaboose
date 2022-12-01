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

IAsyncOperation<winrt::Windows::Data::Json::JsonObject> cabcui::getjson(std::string input)
{	
	try {
	input = Cab::ToBackSlash(input);
	Windows::Storage::StorageFile file = co_await Cab::getAudioFile(input);
	Windows::Storage::Streams::IBuffer buffer{ co_await Windows::Storage::FileIO::ReadBufferAsync(file) };
	
	Windows::Storage::Streams::DataReader jsonReader{ Windows::Storage::Streams::DataReader::FromBuffer(buffer) };
	winrt::hstring jsonFileText{ jsonReader.ReadString(buffer.Length()) };
	cablog::info("String Read!");

	cablog::info("\n" + to_string(jsonFileText));

	winrt::Windows::Data::Json::JsonObject json;
	bool validJSON = winrt::Windows::Data::Json::JsonObject::TryParse(jsonFileText, json);
	if (validJSON == false)
	{
		cablog::error("Json file is not valid!");
	}

	co_return json;
	}
	catch (winrt::hresult_error const& ex)
	{
		hstring message = ex.message();
		cablog::error("WinRT/C++: " + to_string(message));
	}
	catch (std::exception const& ex)
	{
		cablog::error("C++: " + std::string(ex.what()));
	}
	catch (...)
	{
		cablog::error("Unknown Error");
	}


}