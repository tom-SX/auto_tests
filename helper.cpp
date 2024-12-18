#include "PipelineInterface.h"
#include "gtest/gtest.h"
#include "CustomTestListener.h"
// #include "merlin_generated_tests.h" 
#include "merlin_print_enums.h" 

#include <ctime>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <map>

#include <opencv2/opencv.hpp>
#include "helper.h"


using namespace sightx;

std::map<std::string, std::map<std::string, float>> thresholdMap;
std::map<std::string, float> trackerThresholdMap;
std::map<sdk::FlowSwitcherFlowId, std::string> videoPathsMap;
std::map<sdk::FlowSwitcherFlowId, sdk::PixelFormat> pixelFormatMap;
std::vector<std::string> trackerNameVector;
std::vector<sdk::FlowSwitcherFlowId> availableFlows;

void setThresholdMap(std::map<std::string, std::map<std::string, float>> tMap) {
    thresholdMap = tMap;
}

void setTrackerThresholdMap(std::map<std::string, float> tMap) {
    trackerThresholdMap = tMap;
}

void setVideoPaths(std::map<sdk::FlowSwitcherFlowId, std::string> newMap) {
    videoPathsMap = newMap;
}

void setPixelFormats(std::map<sdk::FlowSwitcherFlowId, sdk::PixelFormat> newMap) {
    pixelFormatMap = newMap;
    for (auto item : newMap) {
        availableFlows.push_back(item.first);
    }
}

void setTrackerNames(std::vector<std::string> newVector) {
    trackerNameVector = newVector;
}

void waitForStreamStarted(const std::shared_ptr<sdk::Stream> &stream, UserData* data) {
    // std::cout << "\nWaiting for stream: " << stream->getId().toString() << std::endl;
    // std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::unique_lock<std::mutex> lock(data->Mutex);
    data->Condition.wait_for(lock, std::chrono::seconds(10), [&data]() { return data->StreamState; });
    if (!data->StreamState) {
        std::cerr << "Couldn't start stream for 10 seconds, exiting" << std::endl;
        throw std::exception();
    }
}

void waitForStreamStopped(UserData* data) {
    // std::cout << "\nWaiting for stream to stop" << std::endl;
    std::unique_lock<std::mutex> lock(data->Mutex);
    data->Condition.wait_for(lock, std::chrono::seconds(10), [&data]() { return !data->StreamState; });
    if (data->StreamState) {
        std::cerr << "Couldn't stop stream for 10 seconds, exiting" << std::endl;
        throw std::exception();
    }
}

std::string snakeToCamel(const std::string &snake_case) {
    std::string camel_case;
    bool to_upper = true;

    for (char ch : snake_case) {
        if (ch == '_') {
            to_upper = true;
        } else {
            camel_case += to_upper ? std::toupper(ch) : ch;
            to_upper = false;
        }
    }

    return camel_case;
}

std::string getActiveDetector(std::vector<sdk::ModuleInfo> modules) {
    for (auto module : modules) {
        // std::cout << "Module: " << module.Name.toString() << ", Type: " << module.Type.toString() << ", Active: " << module.Active << std::endl;
        if (module.Type == "Detector" && module.Active) {
            // std::cout << "Active detector is: " << module.Name.toString() << std::endl;
            return snakeToCamel(module.Name.toString());
        }
    }
    return "";
}

void sendFrames(const std::shared_ptr<sdk::Stream> &stream, size_t numOfFramesToSend, UserData* data, std::string videoPath, const std::function<void(uint32_t)> &func) {

    sdk::FlowSwitcherFlowId flowID = stream->getConfiguration().getFlowSwitcher().getFlowId();
    if (videoPath.empty()) {
        videoPath = videoPathsMap[flowID];
    }
    
    // sdk::PixelFormat pixelFormat = pixelFormatMap[flowID];
    sdk::PixelFormat pixelFormat = sdk::PixelFormat::BGR8;

    // push raw video frames
    cv::VideoCapture capture(videoPath);

    uint32_t nFrameId = 0;
    cv::Mat  matFrame;
    while (capture.read(matFrame))
    {
        if (nFrameId == 10) {
            data->currentDetector = getActiveDetector(stream->getStreamInfo().Modules.toVector());
            // std::cout << "Current Detector: " << data->currentDetector << std::endl;
        }
        // Break if reached numOfFramesToSend
        if (nFrameId >= numOfFramesToSend && numOfFramesToSend != -1)
            break;

        // push frame
        stream->pushRawFrame(
            sdk::RawSourceId::RawSource, // ids are defined in Configuration.h
            matFrame.data,
            matFrame.cols,
            matFrame.rows,
            pixelFormat, // supported pixel formats are defined in Types.h
            matFrame.step[0],
            nFrameId++, // can be default (-1) to use frame ids automatically generated by the engine
                        // this frame id is used in track callback
            -1);        // timestamp in ms, if -1 current time is used


        if (func != nullptr) {
            func(nFrameId);
        }

        std::this_thread::sleep_for(
            std::chrono::milliseconds(50));
    }
}

void sendFramesBySeconds(const std::shared_ptr<sdk::Stream> &stream, double seconds, UserData* data, std::string videoPath, const std::function<void(double)> &func) {
    
    sdk::FlowSwitcherFlowId flowID = stream->getConfiguration().getFlowSwitcher().getFlowId();
    if (videoPath.empty()) {
        videoPath = videoPathsMap[flowID];
    }

    auto start = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(start);
    std::cout << "Started test at ^*^ " << std::ctime(&start_time) << " ^*^" << std::endl;

    // sdk::PixelFormat pixelFormat = pixelFormatMap[flowID];
    sdk::PixelFormat pixelFormat = sdk::PixelFormat::BGR8;

    // push raw video frames
    cv::VideoCapture capture(videoPath);

    uint32_t nFrameId = 0;
    cv::Mat  matFrame;
    auto isFrame = capture.read(matFrame);

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    while (seconds >= elapsed_seconds.count())
    {
        if (nFrameId == 10) {
            data->currentDetector = getActiveDetector(stream->getStreamInfo().Modules.toVector());
            // std::cout << "Current Detector: " << data->currentDetector << std::endl;
        }
        

        // push frame
        stream->pushRawFrame(
            sdk::RawSourceId::RawSource, // ids are defined in Configuration.h
            matFrame.data,
            matFrame.cols,
            matFrame.rows,
            pixelFormat, // supported pixel formats are defined in Types.h
            matFrame.step[0],
            nFrameId++, // can be default (-1) to use frame ids automatically generated by the engine
                        // this frame id is used in track callback
            -1);        // timestamp in ms, if -1 current time is used


        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;

        if (func != nullptr) {
            double sec = elapsed_seconds.count();
            func(sec);
        }
        
        isFrame = capture.read(matFrame);
        if (!isFrame) {
            std::cout << "Reached end of file, restarting..." << std::endl;
            capture.set(cv::CAP_PROP_POS_FRAMES, 0); // Reset to first frame
            isFrame = capture.read(matFrame);
        }

        std::this_thread::sleep_for(
            std::chrono::milliseconds(50));
    }
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::cout << "Ended test at ^*^ " << std::ctime(&end_time) << " ^*^" << std::endl;
}