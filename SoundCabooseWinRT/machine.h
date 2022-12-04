//Standard way to unserialize bytes
//https://isocpp.org/wiki/faq/serialization#serialize-binary-format

#ifdef _WIN32
#include "pch.h"

using namespace winrt;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Streams;
using namespace winrt::Windows::Foundation::Collections;

using namespace winrt::Windows::Media;
using namespace winrt::Windows::Media::Devices;
using namespace winrt::Windows::Media::Capture;
using namespace winrt::Windows::Media::Audio;
using namespace winrt::Windows::Media::Render;
using namespace winrt::Windows::Media::MediaProperties;


namespace Serialization
{
	inline IAsyncOperation<winrt::Windows::Data::Json::JsonObject> getJSONobjfromfilepath(std::string input)
	{
		try {
			//converts to valid filepath
			input = Cab::ToBackSlash(input);
			//returns file object
			Windows::Storage::StorageFile file = co_await Cab::getAudioFile(input);
			//returns file into buffer
			Windows::Storage::Streams::IBuffer buffer{ co_await Windows::Storage::FileIO::ReadBufferAsync(file) };
			//reads buffer into string
			Windows::Storage::Streams::DataReader jsonReader{ Windows::Storage::Streams::DataReader::FromBuffer(buffer) };
			//reads string into JSON Object
			winrt::hstring jsonFileText{ jsonReader.ReadString(buffer.Length()) };
			cablog::info("String Read!");

			//testing the input
			cablog::info("\n" + to_string(jsonFileText));

			//Checking if JSON file is valid
			winrt::Windows::Data::Json::JsonObject json;
			bool validJSON = winrt::Windows::Data::Json::JsonObject::TryParse(jsonFileText, json);
			if (validJSON == false)
			{
				cablog::error("Json file is not valid!");
			}
			//returns JSON object
			co_return json;
		}
		catch (winrt::hresult_error const& ex)
		{
			cablog::error("Error: " + to_string(ex.message()));
		}
	}
	inline IAsyncOperation<int> writeJSONobjtofilepath(winrt::Windows::Data::Json::JsonObject input, std::string filepath)
	{
		
	}
}


#endif // _WIN32

#ifdef __linux__
namespace Serialization
{

}
#endif // __linux__

#ifdef DEBUG


#endif // DEBUG

#ifdef TARGET_OS_MAC

#endif // TARGET_OS_MAC