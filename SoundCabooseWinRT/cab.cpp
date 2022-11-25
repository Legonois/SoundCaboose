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



Cab::Cab()
{
    Cab::intcablog = new cablog();
}

Cab::~Cab()
{
    delete Cab::intcablog;
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

//std::bool IsInvadChar(char c)
//{
    
//}

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

winrt::Windows::Foundation::IAsyncOperation<AudioGraph> Cab::SetupAudioGraph()
{

	//// Creates the audio graph settings
	//AudioGraphSettings settings(AudioRenderCategory::Media);
	//AudioGraphSettings settings = new AudioGraphSettings(winrt::Windows::Media::Render::AudioRenderCategory::Media);
	AudioGraphSettings settings(AudioRenderCategory::Media);
	//settings.QuantumSizeSelectionMode(QuantumSizeSelectionMode::LowestLatency);

	////TODO: Fix 
	//Sets frequency of audio graph
	settings.QuantumSizeSelectionMode(winrt::Windows::Media::Audio::QuantumSizeSelectionMode::LowestLatency);
	settings.EncodingProperties(AudioEncodingProperties::CreatePcm(4100, 1, 16));
	cablog::created("Settings");

	//TODO: Fix Unknown Error
	////Sets the audio graph to use the default audio device
	//winrt::hstring defaultdevice = winrt::Windows::Media::Devices::MediaDevice::GetDefaultAudioCaptureId(winrt::Windows::Media::Devices::AudioDeviceRole::Default);
	//winrt::Windows::Devices::Enumeration::DeviceInformation devinfo = winrt::Windows::Devices::Enumeration::DeviceInformation::CreateFromIdAsync(defaultdevice).get();
	//settings.PrimaryRenderDevice(devinfo);

	//Creates the audio graph
	CreateAudioGraphResult result = co_await AudioGraph::CreateAsync(settings);

	if (result.Status() == AudioGraphCreationStatus::Success) {
		cablog::created("AudioGraphResult 'result'");
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
        cablog::created("AudioGraph 'audiograph'");

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