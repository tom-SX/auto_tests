#include "PipelineInterface.h"
#include "gtest/gtest.h"
#include "CustomTestListener.h"
#include "StatusBarListener.h"
#include "merlin_generated_tests.h" 
#include "merlin_print_enums.h" 
#include "general_tests.h"

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <thread>
#include "helper.h"
#include "update_tests_flag.h"
#include <opencv2/opencv.hpp>

using namespace sightx;

// Custom environment class to handle the custom flag
class CustomEnvironment : public ::testing::Environment {
public:
    virtual void SetUp() {
        // Parse the custom flag here
        bool update_tests_value = ::testing::GTEST_FLAG(update_tests);
        std::cout << "Update tests flag value: " << std::boolalpha << update_tests_value << std::endl;

        // Add your custom setup logic here if needed
        // ...
    }

    virtual void TearDown() {
        // Add your custom teardown logic here if needed
        // ...
    }
};

void onMessage(const sdk::MessageLog& a_Log)
{
    // std::cout << static_cast<uint32_t>(a_Log.Level) << ": " << a_Log.Text.toString() << std::endl;
}

void onFrameResults(const sdk::FrameResults& a_FrameResults, UserData* a_pUserData)
{
    std::cout << "\rFrame " << a_FrameResults.FrameId << " [" << a_FrameResults.StreamId.toString() << "]" << std::flush;
    // if (a_pUserData->currentDetector != "") {
    //     for (const sdk::Track& track : a_FrameResults.Tracks.toVector())
    //     {
    //         // std::cout << "Current detector: " << a_pUserData->currentDetector << ", Class: " << track.DetectionData.Class.toString() << std::endl;
    //         if (track.DetectionData.Score > 0) {
    //             auto track_class = track.DetectionData.Class.toString();
    //             // std::cout << "Current detector: " << a_pUserData->currentDetector << ", Class: " << track.DetectionData.Class.toString() << std::endl;
    //             if (track_class != "Vmd") {
    //                 try {
    //                     general_tests::RunThresholdInRangeTest(track.DetectionData.Score, trackerThresholdMap[track_class + "Tracker"], track_class, track.TrackId);
    //                 }
    //                 catch (...) {
    //                     continue;
    //                 }
    //             }
                
    //         }
                
    //     }
    // }
    
}

void onStreamEvent(const sdk::StreamLog& a_StreamLog, UserData* a_pUserData)
{
    std::lock_guard<std::mutex> lock(a_pUserData->Mutex);

    switch (a_StreamLog.Event)
    {
    case sdk::StreamEvent::Created:
        // std::cout << "Stream " << a_StreamLog.StreamId.toString() << " created" << std::endl;
        break;
    case sdk::StreamEvent::Started:
        // std::cout << "Stream " << a_StreamLog.StreamId.toString() << " started" << std::endl;
        break;
    case sdk::StreamEvent::Connected:
        // std::cout << "Stream " << a_StreamLog.StreamId.toString() << " connected" << std::endl;
        a_pUserData->StreamState = true;
        break;
    case sdk::StreamEvent::Stopped:
        // std::cout << "Stream " << a_StreamLog.StreamId.toString() << " stopped" << std::endl;
        a_pUserData->StreamState = false;
        break;
    case sdk::StreamEvent::Error:
        // std::cout << "Stream " << a_StreamLog.StreamId.toString() << " got error at module " << a_StreamLog.ModuleName.toString() << ": " << a_StreamLog.Text.toString() << std::endl;
        break;
    case sdk::StreamEvent::EOS:
        // std::cout << "Stream " << a_StreamLog.StreamId.toString() << " got end-of-stream" << std::endl;
        break;
    case sdk::StreamEvent::Terminated:
        // std::cout << "Stream " << a_StreamLog.StreamId.toString() << " terminated" << std::endl;
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

// Custom flag parsing function
void ParseCustomFlags(int* argc, char** argv) {
    for (int i = 1; i < *argc; ++i) {
        if (strncmp(argv[i], "--update_tests=", 15) == 0) {
            std::string flag_value = argv[i] + 15;
            if (flag_value == "0") {
                ::testing::GTEST_FLAG(update_tests) = false;
            } else {
                ::testing::GTEST_FLAG(update_tests) = true;
            }
            // Remove the custom flag from argv
            for (int j = i; j < *argc - 1; ++j) {
                argv[j] = argv[j + 1];
            }
            --(*argc);
            --i;
        }
    }
}

int run(
    const char* a_strServerIP, int argc, char** argv)
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
    callbacks.OnFrameResults      = std::bind(&onFrameResults, std::placeholders::_1, &data);
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

    generated_tests::setPipeline(pPipeline);
    generated_tests::setUserData(&data);
    general_tests::setPipeline(pPipeline);
    general_tests::setUserData(&data);
    // Parse custom flags before initializing Google Test
    ParseCustomFlags(&argc, argv);
    
    // start new stream
    // sdk::StartStreamConfiguration startConfiguration = pPipeline->createStartStreamConfiguration();
    // Pass the startConfiguration instance to the generated tests
    // generated_tests::setStartConfiguration(startConfiguration);

    ::testing::InitGoogleTest(&argc, argv);

    // Register the custom environment
    ::testing::AddGlobalTestEnvironment(new CustomEnvironment);

    // Create the custom listener
    CustomTestListener* custom_listener = new CustomTestListener("failed_tests.json");

    // Get the event listeners and add the custom listener
    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();
    listeners.Append(custom_listener);
    // Remove the default result printer
    delete listeners.Release(listeners.default_result_printer());
    // Add the custom status bar listener
    listeners.Append(new StatusBarListener());
    // std::cout << "CustomTestListener added." << std::endl;
    int result = RUN_ALL_TESTS();
    generated_tests::pPipeline.reset();
    std::cout << "Test run ended!!!" << std::endl;
    return result;

    // std::shared_ptr<sdk::Stream> pStream = pPipeline->startStream(
    //     startConfiguration);

    // // wait for stream connected event
    // {
    //     std::unique_lock<std::mutex> lock(data.Mutex);
    //     data.Condition.wait(
    //         lock,
    //         [&data]()
    //         { return data.StreamState; });
    // }

    // // push raw video frames
    // cv::VideoCapture capture(
    //     a_strVideoPath);

    // uint32_t nFrameId = 0;
    // cv::Mat  matFrame;
    // while (capture.read(matFrame))
    // {
    //     // push frame
    //     pStream->pushRawFrame(
    //         sdk::RawSourceId::RawSource, // ids are defined in Configuration.h
    //         matFrame.data,
    //         matFrame.cols,
    //         matFrame.rows,
    //         sdk::PixelFormat::BGR8, // supported pixel formats are defined in Types.h
    //         matFrame.step[0],
    //         nFrameId++, // can be default (-1) to use frame ids automatically generated by the engine
    //                     // this frame id is used in track callback
    //         -1);        // timestamp in ms, if -1 current time is used

    //     // update telemetry; to use this - startConfiguration.getTelemetry() line above should be uncommented
    //     /*sdk::TelemetryInfo telemetry;
    //     telemetry.HorizontalFOVMrads = 10;
    //     telemetry.VerticalFOVMrads   = 10;

    //     pStream->updateTelemetry(
    //         telemetry,
    //         -1); // timestamp in ms, if -1 current time is used; should match frame timestamps*/

    //     std::this_thread::sleep_for(
    //         std::chrono::milliseconds(30));
    // }

    // // stop stream (optional, will be destroyed on scope exit)
    // pStream.reset();

    // // destroy pipeline interface (optional, will be destroyed on scope exit)
    // pPipeline.reset();
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

    if (argc < 2)
    {
        std::cerr << "Syntax: " << argv[0] << " server_ip" << std::endl;
        exit(-1);
    }

    try
    {
        return run(argv[1], argc, argv);
        // std::cout << "Finished testing!! Result is: " << res << std::endl;
        // return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }
}
