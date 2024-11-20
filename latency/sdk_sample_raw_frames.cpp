#include "PipelineInterface.h"

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <thread>
#include <map>
#include <fstream>

#include <opencv2/opencv.hpp>

using namespace sightx;

struct UserData
{
    bool ServerState = false;
    bool StreamState = false;

    std::mutex              Mutex;
    std::condition_variable Condition;
};

std::map<uint32_t, long long> durations;

void onMessage(const sdk::MessageLog& a_Log)
{
    // std::cout << static_cast<uint32_t>(a_Log.Level) << ": " << a_Log.Text.toString() << std::endl;
}

void onFrameResults(const sdk::FrameResults& a_FrameResults)
{
    std::cout << "\rFrame " << a_FrameResults.FrameId << " [" << a_FrameResults.StreamId.toString() << "]" << std::flush;
    auto now = std::chrono::system_clock::now();

    auto duration = now.time_since_epoch();

    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

    auto start = durations[a_FrameResults.FrameId];

    durations[a_FrameResults.FrameId] = milliseconds - start;

    // if (durations[a_FrameResults.FrameId] > 200)
    //     std::cout << "Long latency: " << durations[a_FrameResults.FrameId] << std::endl;

    // for (const sdk::Track& track : a_FrameResults.Tracks.toVector())
    // {
    //     std::cout << "   Track id: " << track.TrackId << std::endl;
    //     std::cout << "   Class id: " << track.DetectionData.Class.toString() << std::endl;
    //     std::cout << "   Score: " << track.DetectionData.Score << std::endl;
    //     std::cout << "   Location: " << (int32_t)track.DetectionData.Location.X1 << "x" << (int32_t)track.DetectionData.Location.Y1 << "-"
    //               << (int32_t)track.DetectionData.Location.X2 << "x" << (int32_t)track.DetectionData.Location.Y2 << std::endl;
    //     std::cout << "   Velocity: " << track.Velocity.X << "x" << track.Velocity.Y << std::endl;
    //     std::cout << std::endl;
    // }
}

void onStreamEvent(const sdk::StreamLog& a_StreamLog, UserData* a_pUserData)
{
    std::lock_guard<std::mutex> lock(a_pUserData->Mutex);

    switch (a_StreamLog.Event)
    {
    case sdk::StreamEvent::Created:
        std::cout << "Stream " << a_StreamLog.StreamId.toString() << " created" << std::endl;
        break;
    case sdk::StreamEvent::Started:
        std::cout << "Stream " << a_StreamLog.StreamId.toString() << " started" << std::endl;
        break;
    case sdk::StreamEvent::Connected:
        std::cout << "Stream " << a_StreamLog.StreamId.toString() << " connected" << std::endl;
        a_pUserData->StreamState = true;
        break;
    case sdk::StreamEvent::Stopped:
        std::cout << "Stream " << a_StreamLog.StreamId.toString() << " stopped" << std::endl;
        a_pUserData->StreamState = false;
        break;
    case sdk::StreamEvent::Error:
        std::cout << "Stream " << a_StreamLog.StreamId.toString() << " got error at module " << a_StreamLog.ModuleName.toString() << ": " << a_StreamLog.Text.toString() << std::endl;
        break;
    case sdk::StreamEvent::EOS:
        std::cout << "Stream " << a_StreamLog.StreamId.toString() << " got end-of-stream" << std::endl;
        break;
    case sdk::StreamEvent::Terminated:
        std::cout << "Stream " << a_StreamLog.StreamId.toString() << " terminated" << std::endl;
        break;
    }

    a_pUserData->Condition.notify_one();
}

void onServerStateChange(sdk::ServerState a_eServerState, UserData* a_pUserData)
{
    switch (a_eServerState)
    {
    case sdk::ServerState::ServerUp:
        std::cout << "Server is up" << std::endl;
        break;
    case sdk::ServerState::ServerDown:
        std::cout << "Server is down" << std::endl;
        break;
    case sdk::ServerState::InvalidVersion:
        std::cout << "Invalid server version" << std::endl;
        break;
    }

    // notify server state
    {
        std::lock_guard<std::mutex> lock(a_pUserData->Mutex);
        a_pUserData->ServerState = a_eServerState == sdk::ServerState::ServerUp;
    }

    a_pUserData->Condition.notify_one();
}

void run(
    const char* a_strServerIP,
    const char* a_strVideoPath)
{
    UserData data;

    // init logger
    sdk::LoggerCallbacks loggerCallbacks;
    loggerCallbacks.OnMessage = &onMessage;

    sdk::Logger::init(
        loggerCallbacks,
        sdk::LogLevel::Error);

    // init pipeline
    sdk::GrpcSettings grpcSettings;
    grpcSettings.ServerIP = a_strServerIP;

    sdk::Callbacks callbacks;
    callbacks.OnFrameResults      = &onFrameResults;
    callbacks.OnStreamEvent       = std::bind(&onStreamEvent, std::placeholders::_1, &data);
    callbacks.OnServerStateChange = std::bind(&onServerStateChange, std::placeholders::_1, &data);

    std::shared_ptr<sdk::Pipeline> pPipeline = sdk::Pipeline::create(
        grpcSettings,
        {}, // dds settings
        {}, // raw stream settings
        callbacks);

    // wait for server up event
    {
        std::unique_lock<std::mutex> lock(data.Mutex);
        data.Condition.wait_for(
            lock,
            std::chrono::seconds(10),
            [&data]()
            { return data.ServerState; });

        if (!data.ServerState)
        {
            throw std::runtime_error(
                "Couldn't connect to the server for 10 seconds, exiting");
        }
    }

    // start new stream
    sdk::StartStreamConfiguration startConfiguration = pPipeline->createStartStreamConfiguration();
    startConfiguration.getRawSource(); // raw source needs to be 'touched' to enable it, if no internal settings need to be changed
    startConfiguration.getFlowSwitcher().setFlowId(sdk::FlowSwitcherFlowId::Mwir);
    // startConfiguration.getTelemetry(); // telemetry needs to be 'touched' to enable it if it is going to be used
    // startConfiguration.getRecorder().setEnable(true); // uncomment to enable recorder; recorder data is stored under ~/sightx_recorder
    // startConfiguration.getPreviewModule().setEnable(true); // uncomment to enable local preview; docker should be able to access X for this to work
    // startConfiguration.getRenderer().setDrawDetections(true); // uncomment to draw detections in the debug/preview/gstsink
    // sdk::Vector<sdk::String> vGroups = startConfiguration.getDetector().keysGroups(); // uncomment to receive the list of supported classes for this detector
    // startConfiguration.getDetector().getGroups("people").setScoreThreshold(0.15f); // uncomment to change detector threshold (don't set less than 0.1)
    // startConfiguration.getDetector().appendAveragePixelValue(0.420f); // uncomment to change detector average pixel value
    // startConfiguration.getDetector().appendPixelValueStandardDeviation(0.030f); // uncomment to change detector pixel value standard deviation
    // startConfiguration.getRangeEstimator().getWorldObjectSize(0).setHeightInMeters(1.75f); // uncomment to change the height of person
    // startConfiguration.getTrackerRate().setOutputFramerate(30); // uncomment to change the output framerate

    std::shared_ptr<sdk::Stream> pStream = pPipeline->startStream(
        startConfiguration);

    // update stream
    // pStream->getConfiguration().getRenderer().setDrawDetections(true); // uncomment to toggle draw detections while stream is running
    // pStream->update();

    // wait for stream connected event
    {
        std::unique_lock<std::mutex> lock(data.Mutex);
        data.Condition.wait(
            lock,
            [&data]()
            { return data.StreamState; });
    }

    // push raw video frames
    cv::VideoCapture capture(
        a_strVideoPath);

    uint32_t nFrameId = 0;
    cv::Mat  matFrame;
    while (capture.read(matFrame))
    {

        // push frame
        pStream->pushRawFrame(
            sdk::RawSourceId::RawSource, // ids are defined in Configuration.h
            matFrame.data,
            matFrame.cols,
            matFrame.rows,
            sdk::PixelFormat::BGR8, // supported pixel formats are defined in Types.h
            matFrame.step[0],
            nFrameId++, // can be default (-1) to use frame ids automatically generated by the engine
                        // this frame id is used in track callback
            -1);        // timestamp in ms, if -1 current time is used

        // update telemetry; to use this - startConfiguration.getTelemetry() line above should be uncommented
        /*sdk::TelemetryInfo telemetry;
        telemetry.HorizontalFOVMrads = 10;
        telemetry.VerticalFOVMrads   = 10;
        
        pStream->updateTelemetry(
            telemetry,
            -1); // timestamp in ms, if -1 current time is used; should match frame timestamps*/

        auto now = std::chrono::system_clock::now();

        auto duration = now.time_since_epoch();

        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

        durations[nFrameId - 1] = milliseconds;

        std::this_thread::sleep_for(
            std::chrono::milliseconds(100));
    }

    std::ofstream outFile("durations.txt");

    auto it = durations.begin();

    while (it != durations.end()) {
        outFile << "Frame: " << it->first << ", Duration: " << it->second << std::endl;
        it++;
    }

    outFile.close();

    // stop stream (optional, will be destroyed on scope exit)
    pStream.reset();

    // destroy pipeline interface (optional, will be destroyed on scope exit)
    pPipeline.reset();
}

int main(int argc, char** argv)
{
    // discover running servers
    sdk::Vector<sdk::ServerInfo> vServers = sdk::Pipeline::discover();
    std::cout << "Discovered servers:" << std::endl;
    for (const sdk::ServerInfo& info : vServers.toVector())
    {
        std::cout << info.HostName.toString() << " " << info.IP.toString() << ":" << info.Port << std::endl;
    }

    if (argc != 3)
    {
        std::cerr << "Syntax: " << argv[0] << " server_ip video_to_play" << std::endl;
        exit(-1);
    }

    try
    {
        run(
            argv[1],
            argv[2]);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}
