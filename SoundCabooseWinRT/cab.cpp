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

IAsyncOperation<int> Cab::PlayFileOut(std::string input)
{
    input = ToBackSlash(input);

    cablog::job("Started 'PlayFileOut'", input);
    try
    {
        //Setting up Audio Graph
        //Might want to condense into it's own function
        AudioGraphSettings settings = AudioGraphSettings(winrt::Windows::Media::Render::AudioRenderCategory::Media);
        cablog::created("Settings");
        CreateAudioGraphResult final2 = co_await AudioGraph::CreateAsync(settings); //.get;     //.wait_for(30);
        cablog::created("AudioGraphResult 'final2'");
        AudioGraph audiograph = final2.Graph();
        cablog::created("AudioGraph 'audiograph'");

        //Importing Folder
        hstring folderPath = to_hstring(Cab::PathParse(input));
        cablog::job("Importing Folder", to_string(folderPath));


        winrt::Windows::Storage::StorageFolder storageFolder{ co_await winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(folderPath) };

        //auto storageFolder{ co_await StorageFolder::GetFolderFromPathAsync(folderPath) };
        cablog::job("Imported Folder", to_string(folderPath));

        //Importing File
        hstring relFilePath = to_hstring(FileParse(input));
        cablog::job("Importing File", to_string(relFilePath));

		

        auto audioFile{ co_await storageFolder.GetFileAsync(relFilePath)};
        cablog::job("Imported File", to_string(relFilePath));

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

        //Starting all nodes

        fileNode.Start();
        audioOutputNode.Start();
        audiograph.Start();
        cablog::info("Started all nodes");

        system("pause");

        //stop
        audiograph.Stop();
        audioOutputNode.Stop();
        fileNode.Stop();
        cablog::info("Stopped all nodes");

        system("pause");

        //Close All Nodes
        audiograph.Close();
        cablog::info("Closed AudioGraph");
        audioOutputNode.Close();
        cablog::info("Closed audioOutputNode");
        fileNode.Close();
        cablog::info("Closed fileNode");    



    }
    catch (winrt::hresult_error const& ex)
    {
        hstring message = ex.message();
        cablog::error("WinRT/C++: " + to_string(message));
    }

    cablog::job("Ended 'PlayFileOut'", input);

    co_return 1;
}