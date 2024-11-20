#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <vector>
#include "PipelineInterface.h"

using namespace sightx;

struct UserData
{
    bool ServerState = false;
    bool StreamState = false;
    std::string currentDetector = "";

    std::mutex              Mutex;
    std::condition_variable Condition;
};

extern std::map<std::string, std::map<std::string, float>> thresholdMap;
extern std::map<std::string, float> trackerThresholdMap;
extern std::map<sdk::FlowSwitcherFlowId, std::string> videoPathsMap;
extern std::map<sdk::FlowSwitcherFlowId, sdk::PixelFormat> pixelFormatMap;
extern std::vector<std::string> trackerNameVector;
extern std::vector<sdk::FlowSwitcherFlowId> availableFlows;

void setThresholdMap(std::map<std::string, std::map<std::string, float>> tMap);
void setTrackerThresholdMap(std::map<std::string, float> tMap);
void setVideoPaths(std::map<sdk::FlowSwitcherFlowId, std::string> newMap);
void setPixelFormats(std::map<sdk::FlowSwitcherFlowId, sdk::PixelFormat> newMap);
void setTrackerNames(std::vector<std::string> newVector);
void waitForStreamStarted(const std::shared_ptr<sdk::Stream> &stream, UserData* data);
void waitForStreamStopped(UserData* data);
void sendFrames(const std::shared_ptr<sdk::Stream> &stream, size_t numOfFramesToSend, UserData* data, std::string videoPath = "", const std::function<void(uint32_t)> &func = nullptr);
void sendFramesBySeconds(const std::shared_ptr<sdk::Stream> &stream, double seconds, UserData* data, std::string videoPath = "", const std::function<void(double)> &func = nullptr);

#endif // HELPER_H