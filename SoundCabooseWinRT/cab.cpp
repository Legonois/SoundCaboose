#include "pch.h"
#include "cab.h"

//#include <winrt/Windows.Foundation.h>
//using namespace winrt;
//using namespace Windows::Foundation;

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


//cab class constructor
Cab::Cab()
{
    Cab::intcablog = new cablog();
}

//cab class destructor
Cab::~Cab()
{
    delete Cab::intcablog;
}

//Test Function
std::string* Cab::stringy()
{
    std::string* color = new std::string[4];
    color[0] = "Simon";
    color[1] = "Peter";
    color[2] = "Dave";
	color[3] = "John";
	
	//std::string color[4] = { "red", "green", "blue", "yellow" };

	return color;
}

std::string Cab::PathParse(std::string input)
{
    size_t pos = 0;
    std::string token;
    std::string delimiter = "\\";
    std::string tempInput = input;

    while ((pos = tempInput.find(delimiter)) != std::string::npos)
    {
        token = tempInput.substr(0, pos);
        tempInput.erase(0, pos + delimiter.length());
    }

    std::string output = input.substr(0, input.find(tempInput));

    return output;
}

std::string Cab::FileParse(std::string input)
{
	
    input = ToBackSlash(input);

    size_t pos = 0;
    std::string token;
    std::string delimiter = "\\";

    while ((pos = input.find(delimiter)) != std::string::npos)
    {
        token = input.substr(0, pos);
        input.erase(0, pos + delimiter.length());
    }

    //if (input.length() == 0)
    //{
    //    throw 3;
    //}

    return input;
	
}

std::string Cab::ToBackSlash(std::string input)
{
    std::string manip = input;

    // for (int i = input.length(); i >= 0; i--)
    // {
    //     std::string fs = "/";
    //     std::string bs = "\\";

    //     if (manip[i] == fs[1])
    //     {
    //         std::cout << "I hope this runs" << std::endl;

    //         manip[i] = bs[1];
    //     }
    // }

    std::replace(manip.begin(), manip.end(), '/', '\\');
    //std::replace( manip.begin(), manip.end(), '"');
    // manip.erase(std::remove(manip.begin(), manip.end(), '\''), manip.end());
    // manip.erase(std::remove(manip.begin(), manip.end(), '\"'), manip.end());
    manip = RemoveInvalidChars(manip);

    return manip;
}

std::string Cab::RemoveInvalidChars(std::string input)
{
    // std::string::iterator it;
    // std::string invalidChars = "<>:\"\\|?*";
    // for (it = input.begin() ; it < input->end() ; ++it)
    // {
    //     bool found = invalidChars.find(it) != std::string::npos;
    // }

    //TODO: Make a more efficcent process
    input.erase(std::remove(input.begin(), input.end(), '<'), input.end());
    input.erase(std::remove(input.begin(), input.end(), '>'), input.end());
    //input.erase(std::remove(input.begin(), input.end(), ':'), input.end());
    //input.erase(std::remove(input.begin(), input.end(), '/'), input.end());
    //input.erase(std::remove(input.begin(), input.end(), '\\'), input.end());
    input.erase(std::remove(input.begin(), input.end(), '|'), input.end());
    input.erase(std::remove(input.begin(), input.end(), '?'), input.end());
    input.erase(std::remove(input.begin(), input.end(), '*'), input.end());
    input.erase(std::remove(input.begin(), input.end(), '\''), input.end());
    input.erase(std::remove(input.begin(), input.end(), '\"'), input.end());

    return input;
}

//function that converts the input string to lowercase string
std::string Cab::ToLower(std::string input)
{
	std::string output = input;

	for (int i = 0; i < input.length(); i++)
	{
		output[i] = tolower(input[i]);
	}

	return output;
}
 
//A function that converts the input string to lowercase string
//std::string Cab::ToLower(std::string input)
//{
//	std::string output = input;
//
//	std::transform(output.begin(), output.end(), output.begin(), ::tolower);
//
//	return output;
//}


winrt::Windows::Foundation::IAsyncOperation<AudioGraph> Cab::SetupAudioGraph()
{
	try {
		AudioGraphSettings settings(AudioRenderCategory::Media);

		//Sets frequency of audio graph
		settings.QuantumSizeSelectionMode(winrt::Windows::Media::Audio::QuantumSizeSelectionMode::LowestLatency);
		settings.EncodingProperties(AudioEncodingProperties::CreatePcm(44100, 1, 16));
		cablog::created("Settings");

		//TODO: Fix Unknown Error
		////Sets the audio graph to use the default audio device

		AudioDeviceRole defaultAudioDeviceRole = winrt::Windows::Media::Devices::AudioDeviceRole::Default;

		Windows::Devices::Enumeration::DeviceClass defaultAudioDeviceClass = winrt::Windows::Devices::Enumeration::DeviceClass::AudioRender;
		Windows::Devices::Enumeration::DeviceInformationCollection audioRenderers = Windows::Devices::Enumeration::DeviceInformation::FindAllAsync(defaultAudioDeviceClass).get();
		winrt::Windows::Devices::Enumeration::DeviceInformation firstAudioRender = audioRenderers.GetAt(0);
		

		//winrt::hstring defaultdevice 
		//	= winrt::Windows::Media::Devices::MediaDevice::GetDefaultAudioCaptureId(defaultAudioDeviceRole);

		//
		//winrt::Windows::Devices::Enumeration::DeviceInformation devinfo 
		//	= winrt::Windows::Devices::Enumeration::DeviceInformation::CreateFromIdAsync(defaultdevice).get();

		settings.PrimaryRenderDevice(firstAudioRender);

		//Creates the audio graph
		cablog::error("Creating Audio Graph");
		CreateAudioGraphResult result = co_await AudioGraph::CreateAsync(settings);

		if (result.Status() == AudioGraphCreationStatus::Success) {
			cablog::created("AudioGraph 'audiograph'");
		}
		else if (result.Status() == AudioGraphCreationStatus::FormatNotSupported) {
			cablog::error("Format Not Supported");
		}
		else if (result.Status() == AudioGraphCreationStatus::DeviceNotAvailable) {
			cablog::error("Device Not Available");
		}
		else if (result.Status() == AudioGraphCreationStatus::UnknownFailure) {
			cablog::error("Unknown Failure");
		}

		AudioGraph agfinal = result.Graph();

		//if (agfinal == std::null) {
		//    throw "AHHHH";
		//}

		co_return agfinal;
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
	//// Create the audio graph
	//AudioGraphSettings settings(nullptr);
	//settings.EncodingProperties(AudioEncodingProperties::CreatePcm(44100, 2, 16));
	//settings.QuantumSizeSelectionMode(AudioQuantumSizeSelectionMode::LowestLatency);
	//settings.PrimaryRenderDevice(AudioDeviceRole::Default);
	//settings.DesiredRenderDeviceAudioProcessing(AudioProcessing::Raw);

	//co_await winrt::resume_background();

	//AudioGraph result = co_await AudioGraph::CreateAsync(settings);

	//if (result.Status() != AudioGraphCreationStatus::Success)
	//{
	//	// Display an error message
	//	//rootPage.NotifyUser(L"AudioGraph Creation Error: " + result.Status().ToString(), NotifyType::ErrorMessage);
	//	//return;
	//}

	//// Create a device output node
	//CreateAudioDeviceOutputNodeResult deviceOutputNodeResult = co_await result.CreateDeviceOutputNodeAsync();

	//if (deviceOutputNodeResult.Status() != AudioDeviceNodeCreationStatus::Success)
	//{
	//	// Display an error message
	//	//rootPage.NotifyUser(L"Audio Device Output unavailable: " + deviceOutputNodeResult.Status().ToString(), NotifyType::ErrorMessage);
	//	//return;
	//}

	//// Create a frame input node
	//CreateAudioFrameInputNodeResult frameInputNodeResult = co_await result.CreateFrameInputNodeAsync(MediaEncodingProfile::CreateWav(AudioEncodingQuality::High));

	//if (frameInputNodeResult.Status() != AudioFrameInputNodeCreationStatus::Success)
	//{
	//	// Display an error message
	//	//rootPage.NotifyUser(L"Audio Frame Input Node unavailable: " + frameInputNodeResult.Status().ToString(), NotifyType::ErrorMessage);
	//	//return;
	//}

	//// Create a frame output node
	//CreateAudioFrameOutputNodeResult frameOutputNodeResult = co_await result.CreateFrameOutputNodeAsync(MediaEncodingProfile::CreateWav(AudioEncodingQuality::High));

	//if (frameOutputNodeResult.Status() != AudioFrameOutputNodeCreationStatus::Success)
	//{
	//	// Display an error message
	//	//rootPage.NotifyUser(L"Audio Frame Output Node unavailable: " + frameOutputNodeResult.Status().ToString(), NotifyType::ErrorMessage);
	//	//return;
	//}

	// Create a file output node
	//CreateAudioFileOutputNodeResult fileOutputNodeResult = co_await result.CreateFileOutputNodeAsync(StorageFile::GetFileFromPathAsync("C:\\
    
	//// Creates the audio graph settings
	
	
}

IAsyncOperation<winrt::Windows::Storage::StorageFile> Cab::getAudioFile(std::string input) {
    hstring folderPath = to_hstring(Cab::PathParse(input));
    cablog::job("Importing Folder", to_string(folderPath));


    winrt::Windows::Storage::StorageFolder storageFolder{ co_await winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(folderPath) };

    //auto storageFolder{ co_await StorageFolder::GetFolderFromPathAsync(folderPath) };
    cablog::job("Imported Folder", to_string(folderPath));

    //Importing File
    hstring relFilePath = to_hstring(FileParse(input));
    cablog::job("Importing File", to_string(relFilePath));

    auto audioFile{ co_await storageFolder.GetFileAsync(relFilePath) };
    cablog::job("Imported File", to_string(relFilePath));


    co_return audioFile;
}

//check if input is a valid audio file
bool Cab::isAudioFile(std::string input) {
	std::string ext = FileParse(input);
	if (ext == ".wav" || ext == ".mp3" || ext == ".wma" || ext == ".aac" || ext == ".flac" || ext == ".ogg" || ext == ".m4a") {
		return true;
	}
	else {
		return false;
	}
}


IAsyncOperation<int> Cab::PlayFileOut(std::string input)
{
    input = ToBackSlash(input);

    cablog::job("Started 'PlayFileOut'", input);
    try
    {
        ////Setting up Audio Graph
        ////Might want to condense into it's own function
        //AudioGraphSettings settings = AudioGraphSettings(winrt::Windows::Media::Render::AudioRenderCategory::Media);
        //
        //CreateAudioGraphResult final2 = co_await AudioGraph::CreateAsync(settings); //.get;     //.wait_for(30);
        
        AudioGraph audiograph = co_await SetupAudioGraph();
        

        //Importing File

        auto audioFile = co_await getAudioFile(input);

        //FileNode
        CreateAudioFileInputNodeResult fileNodeResult{ co_await audiograph.CreateFileInputNodeAsync(audioFile) };
        cablog::created("CreateAudioFileInputNodeResult 'fileNodeResult'");
        AudioFileInputNode fileNode = fileNodeResult.FileInputNode();
        cablog::created("AudioFileInputNode 'fileNode'");

        //OutputNode
        CreateAudioDeviceOutputNodeResult outputNodeResult{ co_await audiograph.CreateDeviceOutputNodeAsync() };
        cablog::created("CreateAudioDeviceOutputNodeResult 'outputNodeResult'");
        AudioDeviceOutputNode audioOutputNode{ outputNodeResult.DeviceOutputNode() };
        cablog::created("AudioDeviceOutputNode 'audioOutputNode'");;

        //Creating connections
        fileNode.AddOutgoingConnection(audioOutputNode);

        //Starting all nodes
        fileNode.Start();
        audioOutputNode.Start();
        audiograph.Start();
        cablog::info("Started all nodes");

        system("pause");

        //Stops all nodes
        audiograph.Stop();
        audioOutputNode.Stop();
        fileNode.Stop();
        cablog::info("Stopped all nodes");

        system("pause");

        //Close All Nodes
        //audioOutputNode.Close();
        //cablog::info("Closed audioOutputNode");
        //fileNode.Close();
        //cablog::info("Closed fileNode");
        audiograph.Close();
        cablog::info("Closed AudioGraph");



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
	

    cablog::job("Ended 'PlayFileOut'", input);

    co_return 1;
}

//Verify that file exists
bool Cab::FileExists(std::string input) 
{
	input = ToBackSlash(input);
	
	std::ifstream file (input);
	if (file.good()) {
		return true;
	}
	else {
		return false;
	}
}

IAsyncOperation<int> Cab::play2AudioFiles(std::string input, std::string input2)
{
	input = ToBackSlash(input);
    input2 = ToBackSlash(input2);
	cablog::job("Started 'play2AudioFiles'", input);
	
    try {
        AudioGraph audiograph = co_await SetupAudioGraph();
		
		auto audioFile = co_await getAudioFile(input);
		auto audioFile2 = co_await getAudioFile(input2);
		
		//FileNode
		CreateAudioFileInputNodeResult fileNodeResult{ co_await audiograph.CreateFileInputNodeAsync(audioFile) };
		cablog::created("CreateAudioFileInputNodeResult 'fileNodeResult'");
		AudioFileInputNode fileNode = fileNodeResult.FileInputNode();
		
		//FileNode2
		CreateAudioFileInputNodeResult fileNodeResult2{ co_await audiograph.CreateFileInputNodeAsync(audioFile2) };
		cablog::created("CreateAudioFileInputNodeResult 'fileNodeResult2'");
		AudioFileInputNode fileNode2 = fileNodeResult2.FileInputNode();
		
		//OutputNode
		CreateAudioDeviceOutputNodeResult outputNodeResult{ co_await audiograph.CreateDeviceOutputNodeAsync() };
		cablog::created("CreateAudioDeviceOutputNodeResult 'outputNodeResult'");
		AudioDeviceOutputNode audioOutputNode{ outputNodeResult.DeviceOutputNode() };
		cablog::created("AudioDeviceOutputNode 'audioOutputNode'");
		
		//Creating connections
		fileNode.AddOutgoingConnection(audioOutputNode);
		fileNode2.AddOutgoingConnection(audioOutputNode);
		
		//Starting all nodes
		fileNode.Start();
		fileNode2.Start();
		audioOutputNode.Start();
		audiograph.Start();
		cablog::info("Started all nodes");
		
		system("pause");
		
		//Stops all nodes
		audiograph.Stop();
		audioOutputNode.Stop();
		fileNode.Stop();
		fileNode2.Stop();
		
		cablog::info("Stopped all nodes");
		
		system("pause");
		
		//Close All Nodes
        audiograph.Close();
		
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
	
	co_return 1;
}

//parse json file using winrt
