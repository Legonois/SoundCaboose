#pragma once
#include "winrt/Windows.Foundation.h"
#include "cablog.h"
#include "winrt/Windows.Media.Audio.h"
#include "winrt/Windows.Storage.h"

class Cab 
{
private:
	cablog* intcablog;

public:
	Cab();
	static std::string RemoveInvalidChars(std::string input);
	static std::string FileParse(std::string input);
	static std::string PathParse(std::string input);
	static std::string ToBackSlash(std::string input);
	static std::string ToLower(std::string input);
	static bool isAudioFile(std::string input);
	winrt::Windows::Foundation::IAsyncOperation<int> PlayFileOut(std::string input);
	winrt::Windows::Foundation::IAsyncOperation<int> play2AudioFiles(std::string input, std::string input2);
	winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Media::Audio::AudioGraph> SetupAudioGraph();
	static winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFile> getAudioFile(std::string input);
	
	
	~Cab();

	//Test Functions
	static std::string* stringy();
};