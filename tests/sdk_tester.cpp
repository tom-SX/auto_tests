#include "PipelineInterface.h"
#include "SdkHelper.h"
#include "/usr/local/Merlin/include/Configuration.h"

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <thread>
#include <cassert>
#include <map>
#include <typeindex>

#include </usr/include/opencv4/opencv2/videoio.hpp>

#define BOOST_TEST_MODULE SDK testcases

#include <boost/core/ignore_unused.hpp>
#include <boost/test/included/unit_test.hpp>

#include <nlohmann/json.hpp>

#define DEFAULTS
#define PREPROCESSOR
#define ROTATE_ANGLE
#define PREPROCESSOR_ROI
#define FLOW_SWITCHER
#define DETECTOR
#define DETECTOR_ROI
#define DETECTOR_GROUPS
#define DETECTOR_GROUND_MWIR
#define DETECTOR_GROUND_RGB
//#define DETECTOR_GROUND_MWIRH
//#define DETECTOR_GROUND_RGBH
//#define TRACKER
//#define TRACKER_RATE
//#define TRACKER_CONFIGURATION
#define RENDERER
#define OUTPUT
//#define OUTPUT_DDS_PUBLISHER
#define OUTPUT_FULL_VIDEO
#define OUTPUT_PREVIEW
#define DEBUG
#define DISCOVERY


using namespace sightx;
using json = nlohmann::json; 

enum streamError {
    NONE,
    RotateAngleUnsupported,
    RoiIncorrectSize,
    PreviewError
};

enum rangeError {
    RotateAngle,
    ROI,
    Threshold,
    None
};

enum ddsPublisher {
    Null,
    Tracks,
    Detections,
    Disabled
};

struct UserData {
    bool ServerState = false;
    bool StreamState = false;

    std::mutex Mutex;
    std::condition_variable Condition;
};

struct FrameDimensions {
    float Height;
    float Width;
};

struct Roi {
    float X;
    float Y;
    float Width;
    float Height;
};
struct Object {
    float minWidth;
    float minHeight;
    float maxWidth;
    float maxHeight;
    float threshold;

    Object(float minWidth = 1, float minHeight = 1, float maxWidth = 1000, float maxHeight = 1000, float threshold = 0.1){
        this->minWidth = minWidth;
        this->maxWidth = maxWidth;
        this->minHeight = minHeight;
        this->maxHeight = maxHeight;
        this->threshold = threshold;
    }
};
struct StreamSettings {
    /// Each detector min-max width-height values
//        float minWidth = 0;
//        float minHeight = 0;
//        float maxWidth = 0;
//        float maxHeight = 0;

        std::map<std::string, struct Object> Classes = {
                {"Person", Object()},
                {"Vehicle", Object()},
                {"two-wheeled", Object()},
                {"ship", Object()},
                {"motorboat", Object()},
                {"jetski", Object()},
                {"sailboat", Object()},
        };
};

std::map <sdk::FlowSwitcherFlowId, std::string> printDetectorFlow = {
        {sdk::FlowSwitcherFlowId::Rgb, "\n*-*-*-*-*-*-*-* Ground RgbSwir Detector *-*-*-*-*-*-*-*"},
        {sdk::FlowSwitcherFlowId::Mwir, "\n*-*-*-*-*-*-*-* Ground Mwir Detector *-*-*-*-*-*-*-*"},
        {sdk::FlowSwitcherFlowId::Unspecified, "\n*-*-*-*-*-*-*-* Preprocessor *-*-*-*-*-*-*-*"}
};

std::map <sdk::FlowSwitcherFlowId, std::string> printTrackerFlow = {
        {sdk::FlowSwitcherFlowId::Rgb, "\n*-*-*-*-*-*-*-* Ground RgbSwir Tracker *-*-*-*-*-*-*-*"},
        {sdk::FlowSwitcherFlowId::Mwir, "\n*-*-*-*-*-*-*-* Ground Mwir Tracker *-*-*-*-*-*-*-*"},
};

UserData data;
sdk::FlowSwitcherFlowId currentFlowId = sdk::FlowSwitcherFlowId::Unspecified;
streamError currentStreamError = streamError::NONE;
StreamSettings currentStreamSettings;
rangeError currentRangeError = rangeError::None; // TODO - check if needed
std::string currentErrorStr;
FrameDimensions currentFrameDimensions;
Roi currentRoi;
bool isRoiTest = false;
bool isSizeTest = false;
bool testThreshold = false;
bool isArmTest = false;
bool isRangeTest = false;
bool isDebugTest = false;
ddsPublisher ddsPublisherEnum;
size_t rangeInMeters = 0;
std::shared_ptr <sdk::Pipeline> mainPipeline;
std::shared_ptr <sdk::Stream> currentStream;
std::map<std::string, bool> runningStreams;
cv::VideoCapture videoCapture;

std::string a_strVideoPath;
std::string a_strServerIP;
std::string sinkStr;
cv::Mat matFrame;
uint32_t numOfFrames = 500;
int errorCounter = 0;

std::string groundMwirVideo;
std::string groundRgbVideo;

std::string rotateAngleNotInRange;
std::string rotateAngleUnsupported;
std::string ROINotInRange;
std::string ROIUnsupported;
std::string previewError;

json jsonData;

void evalBooleans() {
    for (auto& [key, val] : jsonData.items()) {
//        std::cout << key << std::endl;
        for (auto& [sub_key, sub_val] : jsonData[key].items()) {
//            std::cout << '\t' << sub_key << std::endl;
            if (jsonData[key][sub_key]["Default value"] == "true") {
                jsonData[key][sub_key]["Default value"] = true;
            }
            else if (jsonData[key][sub_key]["Default value"] == "false") {
                jsonData[key][sub_key]["Default value"] = false;
            }
        }
    }
}

void getParamsFromJson() {
    // read file
    std::ifstream file("/home/tom/Desktop/merlin_runner/module_parameters.json");
    jsonData = json::parse(file);
    evalBooleans();
    // complete JSON data
//    std::cout << "Complete JSON data: " << std::endl << jsonData["Stream FlowSwitcher configuration"] << std::endl;
}

/// \i
/// Checking if detected object is in defined ROI
/// \param objLocation detected object location
/// \return is object inside ROI
bool isInRoi(sdk::BoundingBox objLocation) {

    if (objLocation.X1 >= currentRoi.X && objLocation.Y1 >= currentRoi.Y &&
        objLocation.X2 <= (currentRoi.X + currentRoi.Width) && objLocation.Y2 <= (currentRoi.Y + currentRoi.Height))
        return true;


    std::cout << "Object: [" << objLocation.X1 << "," << objLocation.Y1 << "," << objLocation.X2 << ","
              << objLocation.Y2 << "]" << std::endl;
    std::cout << "ROI: [" << currentRoi.X << "," << currentRoi.Y << "," << currentRoi.X + currentRoi.Width
              << "," << currentRoi.Y + currentRoi.Height << "]" << std::endl;
    return false;


}

bool isArmed(const sdk::Attribute& attribute){
    return (attribute.Value == "yes");
}
void onMessage(const sdk::MessageLog& a_Log) {
//    std::cout << static_cast<uint32_t>(a_Log.Level) << ": " << a_Log.Text.toString() << std::endl;
}

/// \onFrameResults
/// Function for checking the engine's tracks results.
/// For each frame of the current stream, we are checking the followings: 1. Class threshold result 2. Detected object location compare to defined ROI
/// \param a_FrameResults Struct containing the track results

void onFrameResults(const sdk::FrameResults &a_FrameResults) {
    /**
* Getting once the threshold and min-max width-height defined for each class depends on what flow we working with right now
* */
    try {
        /// Counting the frames which processed
        std::cout << "\rFrame " << a_FrameResults.FrameId << " out of: " << numOfFrames <<
                  " [" << a_FrameResults.StreamId.toString() << "]" << std::flush;
        if (ddsPublisherEnum != ddsPublisher::Null) {
            if (ddsPublisherEnum == ddsPublisher::Disabled) {
                BOOST_TEST(a_FrameResults.Tracks.toVector().size() == 0, "Tracks publisher not disabled");
            }
            else {
                for (const sdk::Track &track: a_FrameResults.Tracks.toVector()) {
                    if (ddsPublisherEnum == ddsPublisher::Tracks) {
                        BOOST_TEST(track.TrackId != -1, "Track with ID=-1 found");
                    } else if (ddsPublisherEnum == ddsPublisher::Detections) {
                        BOOST_TEST(track.TrackId == -1, "Track with ID different than -1 found");
                    }
                }
            }
            return;
        }
        float threshold = 0;
        float trackWidth = 0, trackHeight = 0;

        /// Verify that the frame results we checking is for the current stream running
        if (a_FrameResults.StreamId == currentStream->getId().toString()) {
            /// Checking for each track at the frame the followings: threshold, location compare to defined ROI, object width and height, armed and range (if relevant)
            for (const sdk::Track &track: a_FrameResults.Tracks.toVector()) {
                std::string trackClass = track.DetectionData.Class.toString();
//                if (trackClass == "Unknown") {
//                    continue;
//                }
                /// Extracting the tracked object's width and height
                trackWidth = track.DetectionData.Location.X2 - track.DetectionData.Location.X1;
                trackHeight = track.DetectionData.Location.Y2 - track.DetectionData.Location.Y1;
                threshold = currentStreamSettings.Classes[trackClass].threshold;
                /// Checking detection threshold score validation
                if (testThreshold && trackClass != "Vmd") {
                    BOOST_TEST((track.DetectionData.Score >= threshold || track.DetectionData.Score == 0),
                               "Threshold for class " << trackClass << " [" << threshold << "] > Score ["
                                                      << track.DetectionData.Score <<
                                                      "] --> [" << a_FrameResults.StreamId << ", "
                                                      << currentStream->getId().toString() << "]");
                }

                /// Checking detection location is inside defined ROI
                if (isRoiTest && track.DetectionData.Score != 0)
                    BOOST_TEST(isInRoi(track.DetectionData.Location));

                if (isSizeTest) {
                    /// Checking detected object Width&Height values is withing min-max Width-Height defined
                    BOOST_TEST(((currentStreamSettings.Classes[trackClass].minHeight <= trackHeight &&
                                 trackHeight <= currentStreamSettings.Classes[trackClass].maxHeight) || trackHeight == 0),
                               "Track class: " << trackClass << " with Height of: " << trackHeight << "\nIs not in range of min-max: " <<
                                               currentStreamSettings.Classes[trackClass].minHeight << ", " << currentStreamSettings.Classes[trackClass].maxHeight << "\n");
                    BOOST_TEST(((currentStreamSettings.Classes[trackClass].minWidth <= trackWidth &&
                                 trackWidth <= currentStreamSettings.Classes[trackClass].maxWidth) || trackWidth == 0),
                               "Track class: " << trackClass << " with Width of: " << trackWidth << "\nIs not in range of min-max: " <<
                                               currentStreamSettings.Classes[trackClass].minWidth << ", " << currentStreamSettings.Classes[trackClass].maxWidth << "\n");
                }

                /// Checking detection class is Person for armed test
                if(isArmTest && trackClass == "Person"){
                    //BOOST_TEST(isArmed(track.Attributes.data()), "Armed Person not detected");
                    for(const auto& attribute : track.Attributes.toVector()){
                        BOOST_TEST(isArmed(attribute), "Armed Person not detected in frame: " + std::to_string(a_FrameResults.FrameId) << "\n");
                    }
                }
                /// Checking the detection range estimation is within offset of 5 meters at most
                if(isRangeTest && trackClass == "Person"){
                    switch(rangeInMeters){
                        case 10:
                            BOOST_TEST((track.DistanceInMeters >= 5 && track.DistanceInMeters <= 15),
                                       "Track estimated range --> " << track.DistanceInMeters << "\nActual range --> " << rangeInMeters);
                            break;
                        case 50:
                            BOOST_TEST((track.DistanceInMeters >= 45 && track.DistanceInMeters <= 55),
                                       "Track estimated range --> " << track.DistanceInMeters << "\nActual range --> " << rangeInMeters);
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
    catch (std::exception &e) {
        BOOST_TEST((((std::string) e.what()).find("Deadline Exceeded") != std::string::npos ||
                ((std::string) e.what()).find("not registered")),
                   "Caught unexpected error: " + (std::string) e.what());
    }

}

/// \outOfRangeErrorTest
/// Function verify each call that we get the relevant out-of-range error string.
/// We decreasing the error counter every call
/// \param errorMsg The error message caught

void outOfRangeErrorTest(const std::string &errorMsg) {
    std::string rangeStr = "is not in range of";
    BOOST_TEST(errorMsg.find(rangeStr) != std::string::npos);
//    std::cout << "errMsg = " + errorMsg << std::endl;
//    std::cout << "rangeStr = " + rangeStr << std::endl;
    errorCounter = errorCounter > 0 ? errorCounter - 1 : 0;
}

/// \streamErrorTest
/// Checking what stream error we get. The options are invalid rotate angle, unsupported ROI or Preview error.
/// For each streamError we caught, we checking the error string we get and decreasing the error counter
/// \param errorCaught The error message caught
/// \param streamId The stream Id

void streamErrorTest(const std::string& errorCaught, const std::string &streamId) {
    // If this is not "not registered" and "no data for..."
    if (errorCaught.find("not registered") == std::string::npos
        && errorCaught.find("No data read for 20 seconds, closing stream") == std::string::npos) {
        switch (currentStreamError) {
            case streamError::RotateAngleUnsupported:
                BOOST_TEST_MESSAGE("\nRotate angle unsupported test --> " + streamId);
                BOOST_TEST(errorCaught.find(currentErrorStr) != std::string::npos);
                errorCounter = errorCounter > 0 ? errorCounter - 1 : 0;
                break;
            case streamError::RoiIncorrectSize:
                BOOST_TEST_MESSAGE("\nROI incorrect size test --> " + streamId);
                BOOST_TEST(errorCaught.find(currentErrorStr) != std::string::npos); //TODO
//                std::cout << "errorCaught: " + errorCaught << std::endl;
//                std::cout << "errorStr: " + currentErrorStr << std::endl;
                errorCounter = errorCounter > 0 ? errorCounter - 1 : 0;
                break;
//            case streamError::ThresholdIncorrectSize:
//                BOOST_TEST_MESSAGE("Threshold incorrect size test --> ")

            case streamError::PreviewError:
                BOOST_TEST_MESSAGE("\nPreview error test --> " + streamId);
                BOOST_TEST(errorCaught.find(currentErrorStr) != std::string::npos);
                errorCounter = errorCounter > 0 ? errorCounter - 1 : 0;
                break;
            default:
		        if(errorCaught.find("not registered") == std::string::npos)
                	BOOST_TEST_ERROR("\nUnrecognized error for stream id--> " + streamId << "Error caught: " + errorCaught);
                break;
        }
    }
    currentStreamError = streamError::NONE;
}


void onStreamEvent(const sdk::StreamLog &a_StreamLog, void *a_pUserData) {
    auto pUserData = static_cast<UserData *>(
            a_pUserData);

    std::lock_guard <std::mutex> lock(pUserData->Mutex);

    switch (a_StreamLog.Event) {
        case sdk::StreamEvent::Started:
            std::cout << "\nStream " << a_StreamLog.StreamId.toString() << " started" << std::endl;
            break;
        case sdk::StreamEvent::Connected:
            std::cout << "\nStream " << a_StreamLog.StreamId.toString() << " connected" << std::endl;
            if (runningStreams.find(a_StreamLog.StreamId.toString()) == runningStreams.end())
                runningStreams.insert({a_StreamLog.StreamId.toString(), true});
            pUserData->StreamState = true;
            break;
        case sdk::StreamEvent::Stopped:
            std::cout << "\nStream " << a_StreamLog.StreamId.toString() << " stopped" << std::endl;
            if (runningStreams.find(a_StreamLog.StreamId.toString()) != runningStreams.end()) {
                runningStreams.erase(a_StreamLog.StreamId.toString());
            }
            pUserData->StreamState = false;
            break;
        case sdk::StreamEvent::Error:
            streamErrorTest(a_StreamLog.Text, a_StreamLog.StreamId.toString());
            if (runningStreams.find(a_StreamLog.StreamId.toString()) != runningStreams.end()) {
                runningStreams.erase(a_StreamLog.StreamId.toString());
            }
            std::cout << "\nStream " << a_StreamLog.StreamId.toString() << " got error at module "
                      << a_StreamLog.ModuleName.toString() << ": " << a_StreamLog.Text.toString() << std::endl;
            break;
        case sdk::StreamEvent::EOS:
            std::cout << "\nStream " << a_StreamLog.StreamId.toString() << " got end-of-stream" << std::endl;
            break;
    }
    pUserData->Condition.notify_one();
}

void onServerStateChange(sdk::ServerState a_eServerState, void *a_pUserData) {
    switch (a_eServerState) {
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

    auto pUserData = static_cast<UserData *>(
            a_pUserData);

    {
        std::lock_guard <std::mutex> lock(pUserData->Mutex);
        pUserData->ServerState = a_eServerState == sdk::ServerState::ServerUp;
    }

    pUserData->Condition.notify_one();
}


/// \run
/// The first function we call in our test cases to configure all necessary settings

void run() {
    boost::unit_test::unit_test_log.set_threshold_level(boost::unit_test::log_messages);

    getParamsFromJson();
    groundMwirVideo = "/home/tom/Desktop/merlin_runner/test_videos/ground_MWIR/Caesarea_1520_0023_T_VOx_FOV40_lwir/%05d.png";
    groundRgbVideo = "/home/tom/Desktop/merlin_runner/test_videos/ground_RGB/Caesarea_1405_0003_W_CMOS_FOV83_rgb/%05d.png";

    rotateAngleNotInRange = "is not in range of 0 and 270";
    rotateAngleUnsupported = "Unsupported rotate angle";
    ROINotInRange = "is not in range of 0 and 8192";
    ROIUnsupported = "Invalid ROI";
    previewError = "Failed to open display; can't use CVPreview";
//    currentRangeError = rangeError::None; // TODO -check if needed
    a_strVideoPath = groundRgbVideo;
//    a_strVideoPath = "rtsp://root:password@172.12.10.199/axis-media/media.amp";
    a_strServerIP = "172.12.10.7";

//    a_strServerIP = "172.12.10.49";
    sinkStr = "rtsp://172.12.10.45:8554/sdk_test";
    videoCapture.open(a_strVideoPath);

    std::cout << "Server IP: " << a_strServerIP << std::endl;
    std::cout << "Video input: " << a_strVideoPath << std::endl;
    std::cout << "Sink URL: " << sinkStr << std::endl;

    matFrame = cv::Mat::zeros(480, 640, CV_8UC3);

    // init logger
    sdk::LoggerCallbacks loggerCallbacks;
    loggerCallbacks.OnMessage = &onMessage;

    sdk::Logger::init(
            loggerCallbacks,
            sdk::LogLevel::Error);

    sdk::GrpcSettings grpcSettings;
    grpcSettings.ServerIP = a_strServerIP;
//    grpcSettings.TimeoutInMsecs = 500;

    sdk::Callbacks callbacks;
    callbacks.OnFrameResults      = &onFrameResults;
    callbacks.OnStreamEvent       = std::bind(&onStreamEvent, std::placeholders::_1, &data);
    callbacks.OnServerStateChange = std::bind(&onServerStateChange, std::placeholders::_1, &data);
//    callbacks.UserData = &data;
//    callbacks.MinLogLevel = sdk::LogLevel::Error;

    mainPipeline = sdk::Pipeline::create(
            grpcSettings,
            {}, // dds settings
            {}, // raw stream settings
            callbacks);

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

namespace std //NOLINT
{
    ostream &operator<<(ostream &os, const sdk::FlowSwitcherFlowId flowId) //NOLINT
    {
        switch (flowId) {
            case sdk::FlowSwitcherFlowId::Mwir:
                return os << "GroundMwir";
            case sdk::FlowSwitcherFlowId::Rgb:
                return os << "GroundRgb";
            default:
                return os << "";
        }
    }

//    ostream &operator<<(ostream &os, const sdk::InitScoreMetric initScoreMetric) //NOLINT
//    {
//        return os << initScoreMetric;
//    }

    ostream &operator<<(ostream &os, const sdk::String &str) //NOLINT
    {
        return os << str.toString();
    }

    ostream &operator<<(ostream &os, const sdk::PublisherDataType publisherDataType) //NOLINT
    {
        switch (publisherDataType) {
            case sdk::PublisherDataType::Tracks:
                return os << "Tracks";
            case sdk::PublisherDataType::Detections:
                return os << "Detections";
            case sdk::PublisherDataType::Disabled:
                return os << "Disabled";
//            case sdk::PublisherDataType::PointTracks:
//                return os << "PointTracks";
            case sdk::PublisherDataType::Unspecified:
                return os << "Unspecified";
            default:
                return os << "";
        }

    }

    ostream &operator<<(ostream &os, const sdk::NormalizationType &normalizationType) //NOLINT
    {
        return os << normalizationType;
    }

    ostream &operator<<(ostream &os, const sdk::Corner corner) //NOLINT
    {
        return os << corner;
    }

    ostream &operator<<(ostream &os, const sdk::OsdValue osdValue) //NOLINT
    {
        return os << osdValue;
    }

    ostream &operator<<(ostream &os, const sdk::RawSourceMode rawSourceMode) //NOLINT
    {
        return os << rawSourceMode;
    }

//    ostream &operator<<(ostream &os, const sdk::DeviceAccess deviceAccess) //NOLINT
//    {
//        return os << deviceAccess;
//    }

}

/// \SendingSingleFrame
/// Function we call to send single frame to Meerkat enginee
/// \param stream The stream we started
void sendSingleFrame(const std::shared_ptr<sdk::Stream> &stream) {

    currentFrameDimensions = {
            (float) matFrame.rows,
            (float) matFrame.cols
    };
    currentRoi = {
            0,
            0,
            (float) matFrame.rows,
            (float) matFrame.cols
    };
    if (data.StreamState) {
        stream->pushRawFrame(
                sdk::RawSourceId::RawSource,
                matFrame.data,
                matFrame.cols,
                matFrame.rows,
                sdk::PixelFormat::BGR8,
                matFrame.step[0],
                0,
                -1
        );
    }
}

/// \sendFrames
/// The function we call in order to send sequence of raw frames to Meerkat enginee
/// \param stream The stream we want send frames to
/// \param numOfFramesToSend The number of frames we send to the stream
/// \param func Reference to the function we want to execute during sending frames
void sendFrames(const std::shared_ptr<sdk::Stream> &stream, size_t numOfFramesToSend,
                const std::function<void(uint32_t)> &func) {
    numOfFrames = numOfFramesToSend;

//    cv::VideoCapture capture(a_strVideoPath);
    videoCapture.open(a_strVideoPath);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    uint32_t nFrameId = 0;
    cv::Mat mat;
    if (currentStream->getId().toString() != stream->getId().toString()) {
        currentStream = stream;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    BOOST_TEST_MESSAGE("Video file: " + a_strVideoPath);
    std::string framesToSend = numOfFramesToSend != -1 ? std::to_string(numOfFramesToSend) : "all video";
    BOOST_TEST_MESSAGE("Sending " + framesToSend + " frames, to stream ID: " + stream->getId().toString());
    while (videoCapture.read(mat)) {
        // Initiate frame size and ROI
        if (nFrameId == 0) {
            currentFrameDimensions = {
                    (float) mat.rows,
                    (float) mat.cols
            };
            currentRoi = {
                    0,
                    0,
                    (float) mat.cols,
                    (float) mat.rows
            };
        }
        // push frame
        if (runningStreams.find(currentStream->getId().toString())->second) {
            try {
                if (nFrameId > numOfFramesToSend && numOfFramesToSend != -1) {
                    break;
                }
                currentStream->pushRawFrame(
                        sdk::RawSourceId::RawSource, // ids are defined in Configuration.h
                        mat.data,
                        mat.cols,
                        mat.rows,
                        sdk::PixelFormat::BGR8, // supported pixel formats are defined in Types.h
                        mat.step[0],
                        nFrameId++, // can be default (-1) to use frame ids automatically generated by the engine
                        -1);        // timestamp in ms, if -1 current time is used

                std::this_thread::sleep_for(
                        std::chrono::milliseconds(50));

                if (func != nullptr) {
                    func(nFrameId);
                }
            }
            catch (std::exception &e) {
                BOOST_TEST(((std::string) e.what()).find("not registered") != std::string::npos,
                           "Caught unexpected error: " + (std::string) e.what());
            }
        } else {
//            BOOST_TEST_MESSAGE("Stream not started!");
            break;
        }
    }
}

/// \waitForStreamStarted
/// Function that stop our program process until stream starting
/// \param stream The stream we waiting to
void waitForStreamStarted(const std::shared_ptr<sdk::Stream> &stream) {
    std::cout << "\nWaiting for stream: " << stream->getId().toString() << std::endl;
    std::unique_lock<std::mutex> lock(data.Mutex);
    data.Condition.wait_for(lock, std::chrono::seconds(10), []() { return data.StreamState; });
    if (!data.StreamState) {
        std::cerr << "Couldn't start stream for 10 seconds, exiting" << std::endl;
        throw std::exception();
    }
    currentStream = stream;
}

/// \waitForStreamStopped
/// Function that stop our program process until stream stops
/// \param stream The stream we waiting to
void waitForStreamStopped(const std::shared_ptr<sdk::Stream> &stream) {
    std::cout << "\nStopping stream: " << stream->getId().toString() << std::endl;
    std::unique_lock<std::mutex> lock(data.Mutex);
    data.Condition.wait_for(lock, std::chrono::seconds(10), []() { return data.StreamState; });
}


//void waitForStreamStopped(std::shared_ptr<sdk::Stream>& stream){ // TODO - try and fix this function
//    std::cout << "\nWaiting for stream: " << stream->getId().toString() << " to stop" << std::endl;
//    std::unique_lock<std::mutex> lock(data.Mutex);
//    stream.reset();
//    data.Condition.wait_until(lock, std::chrono::seconds(10), []() { return ! data.StreamState; });
//}

/// \getStartConfiguration
/// Returns start stream configurations
/// \param customSettings stream configurations, default values assigned if not sent customized settings
/// \return Start stream configurations
sdk::StartStreamConfiguration getStartConfiguration(const std::string &customSettings = "stream_settings.bin") {
    sdk::StartStreamConfiguration startConfiguration = mainPipeline->createStartStreamConfiguration(customSettings);
    startConfiguration.getRawSource();
    // std::cout << "Default Raw Source Mode: " << startConfiguration.getRawSource().getMode() << std::endl;
    std::cout << "Default ReadTimeoutInSec: " << startConfiguration.getRawSource().getReadTimeoutInSec() << std::endl;
    startConfiguration.getRawSource().setReadTimeoutInSec(-1); // Wait forever
    if (!isDebugTest) {
        startConfiguration.getFlowSwitcher().setFlowId(sdk::FlowSwitcherFlowId::Rgb); // Set testing default to RGB
        startConfiguration.getGstSink().setUrl(sinkStr); // Set sink URL
    }
    if (isRoiTest)
        startConfiguration.getTracksPublisher().setSourceData(sdk::PublisherDataType::Detections); // Set output to detections
//    startConfiguration.getVmd().setEnable(false); // Disable VMD by default
    return startConfiguration;
}

/// \rotateAngleTestFunc
/// Test function for rotate angle mechanism
/// \param flowId The flow id we working with
void rotateAngleTestFunc(sdk::FlowSwitcherFlowId flowId){
    std::cout << printDetectorFlow[flowId] << std::endl;
    sdk::StartStreamConfiguration startConfiguration;
    errorCounter = 0;

    BOOST_TEST_MESSAGE("\nRotate angle valid angle test\n");
    try {
        startConfiguration = getStartConfiguration();
//        BOOST_TEST_MESSAGE(startConfiguration.getPreprocessor().minRotateAngle());
        std::shared_ptr<sdk::Stream> stream = mainPipeline->startStream(startConfiguration);
        waitForStreamStarted(stream);
        sendFrames(stream, 15,
                   [&stream](uint32_t nFrameId) {
                       if (nFrameId == 5)
                           BOOST_TEST(stream->getFullConfiguration().getPreprocessor().getRotateAngle() == 0);
                   }
        );

        int angle;
        for (int i = 1; i < 4; i++) {
            try {

                angle = i * 90;
                BOOST_TEST_MESSAGE("\n" << angle);
                startConfiguration = getStartConfiguration();
                startConfiguration.getPreprocessor().setRotateAngle(angle);
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                stream = mainPipeline->startStream(startConfiguration);
                waitForStreamStarted(stream);
                sendFrames(stream, 15, [&stream, angle](uint32_t nFrameId) {
                               if (nFrameId == 5)
                                   BOOST_TEST(stream->getFullConfiguration().getPreprocessor().getRotateAngle() == angle);
                           }
                );
            }
            catch (std::exception &e) {
                BOOST_TEST(((std::string) e.what()).find("not registered") != std::string::npos,
                           "Caught unexpected error: " + (std::string) e.what());
            }
        }
        stream.reset();
    }
    catch (std::exception& e) {
        BOOST_TEST(((std::string) e.what()).find("not registered") != std::string::npos,
                   "Caught unexpected error: " + (std::string) e.what());
    }

    BOOST_TEST_MESSAGE("\nRotate angle out of range test\n");

    try {
        startConfiguration = getStartConfiguration();
//        BOOST_TEST_MESSAGE("\n" << startConfiguration.getPreprocessor().minRotateAngle() - 1);
        errorCounter++;
        startConfiguration.getPreprocessor().setRotateAngle(startConfiguration.getPreprocessor().minRotateAngle() - 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    try {
        startConfiguration = getStartConfiguration();
//        BOOST_TEST_MESSAGE("\n" << startConfiguration.getPreprocessor().maxRotateAngle() + 1);
        errorCounter++;
        startConfiguration.getPreprocessor().setRotateAngle(startConfiguration.getPreprocessor().maxRotateAngle() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    BOOST_TEST(errorCounter == 0, "Not all expected errors returned! Number of missed errors: " + std::to_string(errorCounter));
//    currentRangeError = rangeError::None; // TODO - check if needed

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    BOOST_TEST_MESSAGE("\nRotate angle unsupported test\n");
    int angle;
    for (int i = 0; i < 9; i++) {
        try {
            currentStreamError = streamError::RotateAngleUnsupported;
            currentErrorStr = rotateAngleUnsupported;
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            angle = (int) (random() % 270) + 1;
            BOOST_TEST_MESSAGE(angle);
            startConfiguration = getStartConfiguration();
            startConfiguration.getPreprocessor().setRotateAngle(angle);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            errorCounter++;
            std::shared_ptr<sdk::Stream> stream = mainPipeline->startStream(startConfiguration);
            if (angle % 90 == 0) {
                currentStreamError = streamError::NONE;
                errorCounter = errorCounter > 0 ? errorCounter - 1 : 0;
            } else {
                waitForStreamStarted(stream);
                sendFrames(stream, 10, nullptr);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//                    currentStreamError = streamError::RotateAngleNotInRange;
        }
        catch (std::exception &e) {
            BOOST_TEST(((std::string) e.what()).find("not registered") != std::string::npos,
                       "Caught unexpected error: " + (std::string) e.what());
        }
    }
    BOOST_TEST(errorCounter == 0, "Not all expected errors returned! Number of missed errors: " + std::to_string(errorCounter));
}

/// \roiTestFunc
/// Test function for start stream ROI settings
/// \param flowId The flow id we working with
template<typename CONF, typename T>
void roiTestFunc(sdk::FlowSwitcherFlowId flowId) {

    std::cout << printDetectorFlow[flowId] << std::endl;
    sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
    CONF conf = getDetectorConfiguration(startConfiguration, (T) 1.0);
    currentFlowId = flowId;
    errorCounter = 0;
    isRoiTest = true;
    BOOST_TEST_MESSAGE("\nValid ROI test\n");

    /**
    * Test valid ROI for 100 frames
    */
    try {
        startConfiguration = getStartConfiguration();
        startConfiguration.getFlowSwitcher().setFlowId(flowId);
        conf = getDetectorConfiguration(startConfiguration, (T) 1.0);
        //TODO - implement here random valid roi depends on currentFrameDimension.Width/Height
        conf.getRoi().setX(100);
        conf.getRoi().setY(100);
        conf.getRoi().setHeight(100);
        conf.getRoi().setWidth(100);
        currentRoi = {
                100,
                100,
                100,
                100
        };
        std::shared_ptr<sdk::Stream> stream = mainPipeline->startStream(startConfiguration);
        waitForStreamStarted(stream);
        sendFrames(stream, 100, nullptr);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//        waitForStreamStopped(stream); // TODO - implement stop stream func depends on threading
    }
    catch (std::exception &e) {
        BOOST_TEST(((std::string) e.what()).find("not registered") != std::string::npos, "Caught unexpected error: " + (std::string) e.what());
    }

    /**
    * Test valid ROI for 100 frames with height/width set to default
    */
    try {
        startConfiguration = getStartConfiguration();
        startConfiguration.getFlowSwitcher().setFlowId(flowId);
        CONF conf = getDetectorConfiguration(startConfiguration, (T) 1.0);
        conf.getRoi().setX(100);
        conf.getRoi().setY(100);
        currentRoi = {
                (float) conf.getRoi().getX(),
                (float) conf.getRoi().getY(),
                currentFrameDimensions.Width - (float)(conf.getRoi().getX()),
                currentFrameDimensions.Height - (float)(conf.getRoi().getX())
        };

        std::shared_ptr<sdk::Stream> stream = mainPipeline->startStream(startConfiguration);
        waitForStreamStarted(stream);
        sendFrames(stream, 100, nullptr);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        stream.reset();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    catch (std::exception &e) {
        BOOST_TEST(((std::string) e.what()).find("not registered") != std::string::npos,
                   "Caught unexpected error: " + (std::string) e.what());
    }


    BOOST_TEST_MESSAGE("\nOuf of range ROI test\n");
    errorCounter = 0;
    startConfiguration = getStartConfiguration();
    conf = getDetectorConfiguration(startConfiguration, (T) 1.0);

    int minHeight = conf.getRoi().minHeight();
    size_t maxHeight = conf.getRoi().maxHeight();
    int minWidth = conf.getRoi().minWidth();
    size_t maxWidth = conf.getRoi().maxWidth();
    int minX = conf.getRoi().minX();
    size_t maxX = conf.getRoi().maxX();
    int minY = conf.getRoi().minY();
    size_t maxY = conf.getRoi().maxY();


    try {
        conf = getDetectorConfiguration(startConfiguration, (T) 1.0);
//        BOOST_TEST_MESSAGE("Height=" + std::to_string(maxHeight + 1));
        errorCounter++;
        conf.getRoi().setHeight(maxHeight + 1);
    }
    catch(const std::exception& e){
        outOfRangeErrorTest((std::string) e.what());
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    try{
        startConfiguration = getStartConfiguration();
        conf = getDetectorConfiguration(startConfiguration, (T) 1.0);
//        BOOST_TEST_MESSAGE("Height=" + std::to_string(minHeight - 1));
        errorCounter++;
        conf.getRoi().setHeight(minHeight - 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());

    }
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    try{
        startConfiguration = getStartConfiguration();
        conf = getDetectorConfiguration(startConfiguration, (T) 1.0);
//        BOOST_TEST_MESSAGE("Width=" + std::to_string(maxWidth + 1));
        errorCounter++;
        conf.getRoi().setWidth(maxWidth + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    try{
        startConfiguration = getStartConfiguration();
        conf = getDetectorConfiguration(startConfiguration, (T) 1.0);
//        BOOST_TEST_MESSAGE("Width=" + std::to_string(minWidth - 1));
        errorCounter++;
        conf.getRoi().setWidth(minWidth - 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());

    }
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    try{
        startConfiguration = getStartConfiguration();
        conf = getDetectorConfiguration(startConfiguration, (T) 1.0);
//        BOOST_TEST_MESSAGE("X=" + std::to_string(maxX + 1));
        errorCounter++;
        conf.getRoi().setX(maxX + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());

    }
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    try{
        startConfiguration = getStartConfiguration();
        conf = getDetectorConfiguration(startConfiguration, (T) 1.0);
//        BOOST_TEST_MESSAGE("X=" + std::to_string(minX - 1));
        errorCounter++;
        conf.getRoi().setX(minX - 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());

    }
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    try{
        startConfiguration = getStartConfiguration();
        conf = getDetectorConfiguration(startConfiguration, (T) 1.0);
//        BOOST_TEST_MESSAGE("Y=" + std::to_string(maxY + 1));
        errorCounter++;
        conf.getRoi().setY(maxY + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());

    }
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    try{
        startConfiguration = getStartConfiguration();
        conf = getDetectorConfiguration(startConfiguration, (T) 1.0);
//        BOOST_TEST_MESSAGE("Y=" + std::to_string(minY - 1));
        errorCounter++;
        conf.getRoi().setY(minY - 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    BOOST_TEST(errorCounter == 0, "Not all Out of range ROI expected errors returned! Number of missed errors: " + std::to_string(errorCounter));

    BOOST_TEST_MESSAGE("\nUnsupported ROI test\n");
    errorCounter = 0;
    startConfiguration = getStartConfiguration();
    //currentStreamError = streamError::RoiIncorrectSize;
    currentErrorStr = ROIUnsupported;
    conf = getDetectorConfiguration(startConfiguration, (T) 1.0);

    /**
     * width out of frame
     */
    try {
	    currentStreamError = streamError::RoiIncorrectSize;
        startConfiguration = getStartConfiguration();
        conf = getDetectorConfiguration(startConfiguration, (T) 1.0);
        conf.getRoi().setX(1);
        conf.getRoi().setY(1);
        conf.getRoi().setHeight(1);
        conf.getRoi().setWidth((uint32_t)(100 + currentFrameDimensions.Width));
        errorCounter++;
        std::shared_ptr<sdk::Stream> stream = mainPipeline->startStream(startConfiguration);
        waitForStreamStarted(stream);
        sendFrames(stream, 50, nullptr);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    catch (std::exception &e) {
        BOOST_TEST(((std::string) e.what()).find("not registered") != std::string::npos,
                   "Caught unexpected error: " + (std::string) e.what());
    }

    /**
     * height out of frame
     */
    try {
	    currentStreamError = streamError::RoiIncorrectSize;
        startConfiguration = getStartConfiguration();
        conf = getDetectorConfiguration(startConfiguration, (T) 1.0);
        conf.getRoi().setX(1);
        conf.getRoi().setY(1);
        conf.getRoi().setWidth(1);
        conf.getRoi().setHeight((uint32_t)(100 + currentFrameDimensions.Height));
        errorCounter++;
        std::shared_ptr<sdk::Stream> stream = mainPipeline->startStream(startConfiguration);
        waitForStreamStarted(stream);
        sendFrames(stream, 50, nullptr);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    catch (std::exception &e) {
        BOOST_TEST(((std::string) e.what()).find("not registered") != std::string::npos,
                   "Caught unexpected error: " + (std::string) e.what());
    }

    /**
     * X out of frame
     */

    try {
	    currentStreamError = streamError::RoiIncorrectSize;
        startConfiguration = getStartConfiguration();
        conf = getDetectorConfiguration(startConfiguration, (T) 1.0);
        conf.getRoi().setY(1);
        conf.getRoi().setWidth(1);
        conf.getRoi().setHeight(1);
        conf.getRoi().setX((uint32_t)(100 + currentFrameDimensions.Width));
        errorCounter++;
        std::shared_ptr<sdk::Stream> stream = mainPipeline->startStream(startConfiguration);
        waitForStreamStarted(stream);
        sendFrames(stream, 50, nullptr);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    catch (std::exception &e) {
        BOOST_TEST(((std::string) e.what()).find("not registered") != std::string::npos,
                   "Caught unexpected error: " + (std::string) e.what());
    }

    /**
     * Y out of frame
     */

    try {
	    currentStreamError = streamError::RoiIncorrectSize;
        startConfiguration = getStartConfiguration();
        conf = getDetectorConfiguration(startConfiguration, (T) 1.0);
        conf.getRoi().setHeight(1);
        conf.getRoi().setWidth(1);
        conf.getRoi().setX(1);
        conf.getRoi().setY((uint32_t)(100 + currentFrameDimensions.Height));
        errorCounter++;
        std::shared_ptr<sdk::Stream> stream = mainPipeline->startStream(startConfiguration);
        waitForStreamStarted(stream);
        sendFrames(stream, 50, nullptr);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    catch (std::exception &e) {
        BOOST_TEST(((std::string) e.what()).find("not registered") != std::string::npos,
                   "Caught unexpected error: " + (std::string) e.what());
    }
    BOOST_TEST(errorCounter == 0, "Not all unsupported ROI expected errors returned! Number of missed errors: " + std::to_string(errorCounter));
    isRoiTest = false;
}

/// \updateRoiTestFunc
/// Test function for updating stream ROI settings
/// \param flowId The flow id we working with
template<typename CONF, typename T>
void updateRoiTestFunc(sdk::FlowSwitcherFlowId flowId) {
    std::cout << printDetectorFlow[flowId] << std::endl;
    currentFlowId = flowId;
    errorCounter = 0;
    isRoiTest = true;

    sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
    startConfiguration.getFlowSwitcher().setFlowId(flowId);
    std::shared_ptr<sdk::Stream> stream = mainPipeline->startStream(startConfiguration);
    waitForStreamStarted(stream);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    CONF conf = getDetectorUpdateConfiguration(stream, (T) 1.0);

    //TODO - change all values to more generic method (if preprocessor will "delete")
    int minHeight = conf.getRoi().minHeight();
    size_t maxHeight = conf.getRoi().maxHeight();
    int minWidth = conf.getRoi().minWidth();
    size_t maxWidth = conf.getRoi().maxWidth();
    int minX = conf.getRoi().minX();
    size_t maxX = conf.getRoi().maxX();
    int minY = conf.getRoi().minY();
    size_t maxY = conf.getRoi().maxY();

    BOOST_TEST_MESSAGE("\nValid Roi update test\n");
    try{
//        BOOST_TEST_MESSAGE("(X:100, Y:100, W:100, H:100)");
        conf.getRoi().setX(100);
        conf.getRoi().setY(100);
        conf.getRoi().setWidth(100);
        conf.getRoi().setHeight(100);

        currentRoi = {
            (float) conf.getRoi().getX(),
            (float) conf.getRoi().getY(),
            (float) conf.getRoi().getWidth(),
            (float) conf.getRoi().getHeight()
        };

        stream->update();

        sendFrames(stream, 100, [&conf](uint32_t nFrameId){
           if (nFrameId == 10) {
               BOOST_TEST(conf.getRoi().getX() == 100);
               BOOST_TEST(conf.getRoi().getY() == 100);
               BOOST_TEST(conf.getRoi().getWidth() == 100);
               BOOST_TEST(conf.getRoi().getHeight() == 100);
           }
        });
    }
    catch (const std::exception& e) {
        errorCounter++;
        std::cerr << "Caught unexpected error: " + (std::string) e.what() << std::endl;
    }
    try{
        BOOST_TEST_MESSAGE("(X:100, Y:100, W:100, H:100)");
        conf.getRoi().setX(100);
        conf.getRoi().setY(100);

        currentRoi = {
                (float) conf.getRoi().getX(),
                (float) conf.getRoi().getY(),
                currentFrameDimensions.Width - (float)(conf.getRoi().getX()),
                currentFrameDimensions.Height - (float)(conf.getRoi().getX())
        };

        stream->update();

        sendFrames(stream, 100, [&conf](uint32_t nFrameId){
            if (nFrameId == 10) {
                BOOST_TEST(conf.getRoi().getX() == 100);
                BOOST_TEST(conf.getRoi().getY() == 100);
            }
        });
    }
    catch (const std::exception& e) {
        errorCounter++;
        std::cerr << "Caught unexpected error: " + (std::string) e.what() << std::endl;
    }
    BOOST_TEST(errorCounter == 0, "Not all valid update ROI expected errors returned! Number of missed errors: " + std::to_string(errorCounter));

    BOOST_TEST_MESSAGE("\nOut of range ROI update test\n");
    errorCounter = 0;
    try{
//        BOOST_TEST_MESSAGE("X=" + std::to_string(minX - 1));
        errorCounter++;
        conf.getRoi().setX(minX - 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }

    try{
//        BOOST_TEST_MESSAGE("X=" + std::to_string(maxX + 1));
        errorCounter++;
        conf.getRoi().setX(maxX + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }

    try{
//        BOOST_TEST_MESSAGE("Y=" + std::to_string(minY -1));
        errorCounter++;
        conf.getRoi().setY(minY - 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }

    try{
//        BOOST_TEST_MESSAGE("Y=" + std::to_string(maxY + 1));
        errorCounter++;
        conf.getRoi().setY(maxY + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }

    try{
//        BOOST_TEST_MESSAGE("Width=" + std::to_string(minWidth - 1));
        errorCounter++;
        conf.getRoi().setWidth(minWidth - 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }

    try{
//        BOOST_TEST_MESSAGE("Width=" + std::to_string(maxWidth + 1));
        errorCounter++;
        conf.getRoi().setWidth(maxWidth + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }

    try{
//        BOOST_TEST_MESSAGE("Height=" + std::to_string(minHeight - 1));
        errorCounter++;
        conf.getRoi().setHeight(minHeight - 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }

    try{
//        BOOST_TEST_MESSAGE("Height=" + std::to_string(maxHeight + 1));
        errorCounter++;
        conf.getRoi().setHeight(maxHeight + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    BOOST_TEST(errorCounter == 0, "Not all update ROI out of range expected errors returned! Number of missed errors: " + std::to_string(errorCounter));


    BOOST_TEST_MESSAGE("\nUnsupported ROI update test\n");
    errorCounter = 0;
    currentErrorStr = ROIUnsupported;
    //currentStreamError = streamError::RoiIncorrectSize;

    /**
     * Width out of frame
     */
    try{
	currentStreamError = streamError::RoiIncorrectSize;
        errorCounter++;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        startConfiguration = getStartConfiguration();
        startConfiguration.getFlowSwitcher().setFlowId(flowId);
        stream = mainPipeline->startStream(startConfiguration);
        waitForStreamStarted(stream);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        conf = getDetectorUpdateConfiguration(stream, (T) 1.0);

        sendFrames(stream, 100, [&stream, &conf](uint32_t nFrameId){
           if(nFrameId == 10){
               conf.getRoi().setX(1);
               conf.getRoi().setY(1);
               conf.getRoi().setHeight(1);
               conf.getRoi().setWidth((uint32_t) (100 + currentFrameDimensions.Width));
               stream->update();
           }
        });
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    catch (const std::exception& e) {
        std::cerr << "Caught unexpected error: " + (std::string) e.what() << std::endl;
    }
    /**
     * Height out of frame
     */
    try{
	currentStreamError = streamError::RoiIncorrectSize;
        errorCounter++;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        startConfiguration = getStartConfiguration();
        startConfiguration.getFlowSwitcher().setFlowId(flowId);
        stream = mainPipeline->startStream(startConfiguration);
        waitForStreamStarted(stream);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        conf = getDetectorUpdateConfiguration(stream, (T) 1.0);

        sendFrames(stream, 100, [&stream, &conf](uint32_t nFrameId){
            if(nFrameId == 10){
                conf.getRoi().setX(1);
                conf.getRoi().setY(1);
                conf.getRoi().setWidth(1);
                conf.getRoi().setHeight((uint32_t) (100 + currentFrameDimensions.Height));
                stream->update();
            }
        });
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    catch (const std::exception& e) {
        std::cerr << "Caught unexpected error: " + (std::string) e.what() << std::endl;
    }
    /**
     * X out of frame
     */
    try{
	currentStreamError = streamError::RoiIncorrectSize;
        errorCounter++;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        startConfiguration = getStartConfiguration();
        startConfiguration.getFlowSwitcher().setFlowId(flowId);
        stream = mainPipeline->startStream(startConfiguration);
        waitForStreamStarted(stream);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        conf = getDetectorUpdateConfiguration(stream, (T) 1.0);

        sendFrames(stream, 100, [&stream, &conf](uint32_t nFrameId){
            if(nFrameId == 10){
		        conf.getRoi().setWidth(1);
                conf.getRoi().setHeight(1);
                conf.getRoi().setY(1);
                conf.getRoi().setX((uint32_t) (100 + currentFrameDimensions.Width));
                stream->update();
            }
        });
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    catch (const std::exception& e) {
        std::cerr << "Caught unexpected error: " + (std::string) e.what() << std::endl;
    }
    /**
     * Y out of frame
     */
    try{
	    currentStreamError = streamError::RoiIncorrectSize;
        errorCounter++;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        startConfiguration = getStartConfiguration();
        startConfiguration.getFlowSwitcher().setFlowId(flowId);
        stream = mainPipeline->startStream(startConfiguration);
        waitForStreamStarted(stream);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        conf = getDetectorUpdateConfiguration(stream, (T) 1.0);

        sendFrames(stream, 100, [&stream, &conf](uint32_t nFrameId){
            if(nFrameId == 10){
                conf.getRoi().setHeight(1);
                conf.getRoi().setWidth(1);
                conf.getRoi().setX(1);
                conf.getRoi().setY((uint32_t) (100 + currentFrameDimensions.Height));
                stream->update();
            }
        });
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    catch (const std::exception& e) {
        std::cerr << "Caught unexpected error: " + (std::string) e.what() << std::endl;
    }

    BOOST_TEST(errorCounter == 0, "Not all update ROI unsupported expected errors returned! Number of missed errors: " + std::to_string(errorCounter));
    isRoiTest = false;
}

/// \thresholdTestFunc
/// Test function for start and update stream threshold settings;
/// \param flowId The flow id we working with
/// \param groups Array of group names according to flow id we working with
// TODO - change the test that all groups get the threshold score, not only one class each time
template<typename CONF, typename T>
void thresholdTestFunc(std::vector<sdk::String> &groups, sdk::FlowSwitcherFlowId flowId) {
    std::cout << printDetectorFlow[flowId] << std::endl;
    currentFlowId = flowId;
    errorCounter = 0;

    /**
     * Threshold
     */
    for (const sdk::String &group: groups){
        BOOST_TEST_MESSAGE("\nTesting group: " + group.toString());
        BOOST_TEST_MESSAGE("\nValid threshold");
        try{
            sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
            CONF conf = getDetectorConfiguration(startConfiguration, (T) 1.0);
            conf.getGroups(group).setScoreThreshold(0.5);
            startConfiguration.getFlowSwitcher().setFlowId(flowId);
            std::shared_ptr<sdk::Stream> stream = mainPipeline->startStream(startConfiguration);
            waitForStreamStarted(stream);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            sendFrames(stream, 20, nullptr);
        }
        catch (const std::exception& e) {
            BOOST_TEST(((std::string) e.what()).find("not registered") != std::string::npos, "Caught unexpected error: " + (std::string) e.what());
        }

        BOOST_TEST_MESSAGE("\nOut of range threshold");
        try {
            BOOST_TEST_MESSAGE("\n1.1");
            errorCounter++;
//            currentRangeError = rangeError::Threshold; // TODO -check if needed
            sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
            CONF conf = getDetectorConfiguration(startConfiguration, (T) 1.0);
            conf.getGroups(group).setScoreThreshold(1.1);
        }
        catch (const std::exception& e) {
            outOfRangeErrorTest((std::string) e.what());
        }

        try{
            BOOST_TEST_MESSAGE("\n0");
            errorCounter++;
            sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
            CONF conf = getDetectorConfiguration(startConfiguration, (T) 1.0);
            conf.getGroups(group).setScoreThreshold(-1);
        }
        catch (const std::exception& e) {
            outOfRangeErrorTest((std::string) e.what());
        }

        BOOST_TEST_MESSAGE("\nUpdating threshold test");
        try{
            sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
            startConfiguration.getFlowSwitcher().setFlowId(flowId);
            std::shared_ptr<sdk::Stream> stream = mainPipeline->startStream(startConfiguration);
            waitForStreamStarted(stream);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            auto conf = getDetectorUpdateConfiguration(stream, (T) 1.0);

            sendFrames(stream, 600,
                       [&stream, &conf, &group](uint32_t nFrameId) {
                           float threshold = (float) ((random() % 91) + 10) / 100;
                           if (nFrameId == 60| nFrameId == 111 || nFrameId == 160 || nFrameId == 210 || nFrameId == 260 || nFrameId == 310 || nFrameId == 410)
                               testThreshold = true;
                           if (nFrameId == 50) {
                               BOOST_TEST_MESSAGE("\n" << threshold);
                               testThreshold = false;
                               conf.getGroups(group).setScoreThreshold(threshold);
                               stream->update();
                               currentStream = stream;
                               BOOST_TEST(conf.getGroups(group).getScoreThreshold() == threshold);
                               std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                           } else if (nFrameId == 100) {
                               threshold = (float) ((random() % 91) + 10) / 100;
                               BOOST_TEST_MESSAGE("\n" << threshold);
                               testThreshold = false;
                               conf.getGroups(group).setScoreThreshold(threshold);
                               stream->update();
                               currentStream = stream;
                               BOOST_TEST(conf.getGroups(group).getScoreThreshold() == threshold);
                               std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                           } else if (nFrameId == 150) {
                               threshold = (float) ((random() % 91) + 10) / 100;
                               BOOST_TEST_MESSAGE("\n" << threshold);
                               testThreshold = false;
                               conf.getGroups(group).setScoreThreshold(threshold);
                               stream->update();
                               currentStream = stream;
                               BOOST_TEST(conf.getGroups(group).getScoreThreshold() == threshold);
                               std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                           } else if (nFrameId == 200) {
                               threshold = (float) ((random() % 91) + 10) / 100;
                               BOOST_TEST_MESSAGE("\n" << threshold);
                               testThreshold = false;
                               conf.getGroups(group).setScoreThreshold(threshold);
                               stream->update();
                               currentStream = stream;
                               BOOST_TEST(conf.getGroups(group).getScoreThreshold() == threshold);
                               std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                           } else if (nFrameId == 250){
                               threshold = (float) ((random() % 91) + 10) / 100;
                               BOOST_TEST_MESSAGE("\n" << threshold);
                               testThreshold = false;
                               conf.getGroups(group).setScoreThreshold(threshold);
                               stream->update();
                               currentStream = stream;
                               BOOST_TEST(conf.getGroups(group).getScoreThreshold() == threshold);
                               std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                           } else if (nFrameId == 300) {
                               threshold = (float) ((random() % 91) + 10) / 100;
                               BOOST_TEST_MESSAGE("\n" << threshold);
                               testThreshold = false;
                               conf.getGroups(group).setScoreThreshold(threshold);
                               stream->update();
                               currentStream = stream;
                               BOOST_TEST(conf.getGroups(group).getScoreThreshold() == threshold);
                               std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                           } else if (nFrameId == 400) {
                               threshold = (float) ((random() % 91) + 10) / 100;
                               BOOST_TEST_MESSAGE("\n" << threshold);
                               testThreshold = false;
                               conf.getGroups(group).setScoreThreshold(threshold);
                               stream->update();
                               currentStream = stream;
                               BOOST_TEST(conf.getGroups(group).getScoreThreshold() == threshold);
                               std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                           } else if (nFrameId == 450) {
                               try{
                                   errorCounter++;
                                   conf.getGroups(group).setScoreThreshold(1.1);
                               }
                               catch (const std::exception& e) {
                                   outOfRangeErrorTest((std::string) e.what());
                               }
                           } else if (nFrameId == 500){
                               try{
                                   errorCounter++;
                                   conf.getGroups(group).setScoreThreshold(0);
                               }
                               catch (const std::exception& e) {
                                   outOfRangeErrorTest((std::string) e.what());
                               }
                           }
                       }
            );
        }
        catch (const std::exception& e) {
            BOOST_TEST(((std::string) e.what()).find("not registered") != std::string::npos, "Caught unexpected error: " + (std::string) e.what());
        }

        BOOST_TEST(errorCounter == 0, "Not all expected errors returned! Number of missed errors: " + std::to_string(errorCounter));
    }
}

/// \minMaxTestFunc
/// Test function for all detector's min-max values
/// \param flowId The flow id we working with
/// \param groups Array of group names according to flow id we working with
template<typename CONF, typename T>
void minMaxTestFunc(const std::vector<sdk::String>& groups, sdk::FlowSwitcherFlowId flowId){
    std::cout << printDetectorFlow[flowId] << std::endl;
    currentFlowId = flowId;
    errorCounter = 0;

    for (sdk::String group: groups){
        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        CONF conf = getDetectorConfiguration(startConfiguration, (T)1.0);

        if(group == "None")
            break;
        BOOST_TEST_MESSAGE("\nTesting group: " + group.toString());
        BOOST_TEST_MESSAGE("\nValid test");
        try{
            auto minVal = (float) (random() % 501);
            auto maxVal = (float) ((random() % 501) + 500);

            BOOST_TEST_MESSAGE("\nmin value = " + std::to_string(minVal));
            BOOST_TEST_MESSAGE("\nmax value = " + std::to_string(maxVal));

            conf.getGroups(group).setMinWidth(minVal);
            conf.getGroups(group).setMaxWidth(maxVal);
            conf.getGroups(group).setMinHeight(minVal);
            conf.getGroups(group).setMaxHeight(maxVal);
            conf.getGroups(group).setMinAspectRatio(minVal);
            conf.getGroups(group).setMaxAspectRatio(maxVal);

            BOOST_TEST(conf.getGroups(group).getMinWidth() == minVal);
            BOOST_TEST(conf.getGroups(group).getMaxWidth() == maxVal);
            BOOST_TEST(conf.getGroups(group).getMinHeight() == minVal);
            BOOST_TEST(conf.getGroups(group).getMaxHeight() == maxVal);
            BOOST_TEST(conf.getGroups(group).getMinAspectRatio() == minVal);
            BOOST_TEST(conf.getGroups(group).getMaxAspectRatio() == maxVal);

            startConfiguration.getFlowSwitcher().setFlowId(flowId);
            std::shared_ptr<sdk::Stream> stream = mainPipeline->startStream(startConfiguration);
            waitForStreamStarted(stream);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            sendFrames(stream, 20, nullptr);
        }
        catch (const std::exception& e) {
            std::cerr << "Caught unexpected error: " + (std::string) e.what() << std::endl;
        }

        BOOST_TEST_MESSAGE("\nOut of range min/max");
        /*
         * group's min/max Width
         * */
        try {
            startConfiguration = getStartConfiguration();
            conf = getDetectorConfiguration(startConfiguration, (T) 1.0);
//            BOOST_TEST_MESSAGE("\nminWidth = " + std::to_string(conf.getGroups(group).minMinWidth() - 1));
            errorCounter++;
//            currentRangeError = rangeError::Threshold; // TODO - check afterwards if need add rangeError::min/max to outOfRangeFunc
            conf.getGroups(group).setMinWidth(conf.getGroups(group).minMinWidth() - 1);
        }
        catch (const std::exception& e) {
            outOfRangeErrorTest((std::string) e.what());
        }

        try {
            startConfiguration = getStartConfiguration();
            conf = getDetectorConfiguration(startConfiguration, (T) 1.0);
//            BOOST_TEST_MESSAGE("\nminWidth = " + std::to_string(conf.getGroups(group).maxMinWidth() + 1));
            errorCounter++;
            conf.getGroups(group).setMinWidth(conf.getGroups(group).maxMinWidth() + 1);
        }
        catch (const std::exception& e) {
            outOfRangeErrorTest((std::string) e.what());
        }

        try {
            startConfiguration = getStartConfiguration();
            conf = getDetectorConfiguration(startConfiguration, (T) 1.0);
//            BOOST_TEST_MESSAGE("\nmaxWidth = " + std::to_string(conf.getGroups(group).minMaxWidth() - 1));
            errorCounter++;
            conf.getGroups(group).setMaxWidth(conf.getGroups(group).minMaxWidth() - 1);
        }
        catch (const std::exception& e) {
            outOfRangeErrorTest((std::string) e.what());
        }

        try {
            startConfiguration = getStartConfiguration();
            conf = getDetectorConfiguration(startConfiguration, (T) 1.0);
//            BOOST_TEST_MESSAGE("\nmaxWidth = " + std::to_string(conf.getGroups(group).maxMaxWidth() + 1));
            errorCounter++;
            conf.getGroups(group).setMaxWidth(conf.getGroups(group).maxMaxWidth() + 1);
        }
        catch (const std::exception& e) {
            outOfRangeErrorTest((std::string) e.what());
        }
        /*
         * group's min/max Height
         * */
        try {
            startConfiguration = getStartConfiguration();
            conf = getDetectorConfiguration(startConfiguration, (T) 1.0);
//            BOOST_TEST_MESSAGE("\nminHeight = " + std::to_string(conf.getGroups(group).minMinHeight() - 1));
            errorCounter++;
            conf.getGroups(group).setMinHeight(conf.getGroups(group).minMinHeight() - 1);
        }
        catch (const std::exception& e) {
            outOfRangeErrorTest((std::string) e.what());
        }

        try {
            startConfiguration = getStartConfiguration();
            conf = getDetectorConfiguration(startConfiguration, (T) 1.0);
//            BOOST_TEST_MESSAGE("\nminHeight = " + std::to_string(conf.getGroups(group).maxMinHeight() + 1));
            errorCounter++;
            conf.getGroups(group).setMinHeight(conf.getGroups(group).maxMinHeight() + 1);
        }
        catch (const std::exception& e) {
            outOfRangeErrorTest((std::string) e.what());
        }

        try {
            startConfiguration = getStartConfiguration();
            conf = getDetectorConfiguration(startConfiguration, (T) 1.0);
//            BOOST_TEST_MESSAGE("\nmaxHeight = " + std::to_string(conf.getGroups(group).minMaxHeight() - 1));
            errorCounter++;
            conf.getGroups(group).setMaxHeight(conf.getGroups(group).minMaxHeight() - 1);
        }
        catch (const std::exception& e) {
            outOfRangeErrorTest((std::string) e.what());
        }

        try {
            startConfiguration = getStartConfiguration();
            conf = getDetectorConfiguration(startConfiguration, (T) 1.0);
//            BOOST_TEST_MESSAGE("\nmaxHeight = " + std::to_string(conf.getGroups(group).maxMaxHeight() + 1));
            errorCounter++;
            conf.getGroups(group).setMaxHeight(conf.getGroups(group).maxMaxHeight() + 1);
        }
        catch (const std::exception& e) {
            outOfRangeErrorTest((std::string) e.what());
        }
        /*
         * group's min/max AspectRatio
         * */
        try {
            startConfiguration = getStartConfiguration();
            conf = getDetectorConfiguration(startConfiguration, (T) 1.0);
//            BOOST_TEST_MESSAGE("\nminAspectRatio = " + std::to_string(conf.getGroups(group).minMinAspectRatio() - 1));
            errorCounter++;
            conf.getGroups(group).setMinAspectRatio(conf.getGroups(group).minMaxAspectRatio() - 1);
        }
        catch (const std::exception& e) {
            outOfRangeErrorTest((std::string) e.what());
        }

        try {
            startConfiguration = getStartConfiguration();
            conf = getDetectorConfiguration(startConfiguration, (T) 1.0);
//            BOOST_TEST_MESSAGE("\nminAspectRatio = " + std::to_string(conf.getGroups(group).maxMinAspectRatio() + 1));
            errorCounter++;
            conf.getGroups(group).setMinAspectRatio(conf.getGroups(group).maxMaxAspectRatio() + 1);
        }
        catch (const std::exception& e) {
            outOfRangeErrorTest((std::string) e.what());
        }

        try {
            startConfiguration = getStartConfiguration();
            conf = getDetectorConfiguration(startConfiguration, (T) 1.0);
//            BOOST_TEST_MESSAGE("\nmaxAspectRatio = " + std::to_string(conf.getGroups(group).minMaxAspectRatio() - 1));
            errorCounter++;
            conf.getGroups(group).setMaxAspectRatio(conf.getGroups(group).minMinAspectRatio() - 1);
        }
        catch (const std::exception& e) {
            outOfRangeErrorTest((std::string) e.what());
        }

        try {
            startConfiguration = getStartConfiguration();
            conf = getDetectorConfiguration(startConfiguration, (T) 1.0);
//            BOOST_TEST_MESSAGE("\nmaxAspectRatio = " + std::to_string(conf.getGroups(group).maxMaxAspectRatio() + 1));
            errorCounter++;
            conf.getGroups(group).setMaxAspectRatio(conf.getGroups(group).maxMinAspectRatio() + 1);
        }
        catch (const std::exception& e) {
            outOfRangeErrorTest((std::string) e.what());
        }
        // TODO - finish from here - updating to oor test cases *** most important
        BOOST_TEST_MESSAGE("\nUpdate min/max test...");
        try{
            errorCounter++;
            startConfiguration = getStartConfiguration();
            std::shared_ptr<sdk::Stream> stream = mainPipeline->startStream(startConfiguration);
            waitForStreamStarted(stream);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            sendFrames(stream, 50, nullptr);
            auto conf = getDetectorUpdateConfiguration(stream, (T) 1.0);
            conf.getGroups(group).setMaxAspectRatio(conf.getGroups(group).maxMaxAspectRatio() + 1);
        }
        catch (const std::exception& e) {
            outOfRangeErrorTest((std::string) e.what());
        }

        BOOST_TEST(errorCounter == 0, "Not all expected errors returned! Number of missed errors: " + std::to_string(errorCounter));
    }
}

/// \trackerRateTestFunc
/// Test function for tracker's output frame rate
/// \param flowId The flow id we working with
template<typename T>
void trackerRateTestFunc(sdk::FlowSwitcherFlowId flowId){
    std::cout << printTrackerFlow[flowId] << std::endl;
    currentFlowId = flowId;
    errorCounter = 0;

    sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
    startConfiguration.getFlowSwitcher().setFlowId(flowId);
    sdk::FramerateControllerStartStreamConfiguration conf = getTrackerRateStartConfiguration(startConfiguration, (T) 1.0);

    BOOST_TEST_MESSAGE("\nValid test");
    try {
        auto rate = (uint32_t) ((random() % 101) + 1);
        BOOST_TEST_MESSAGE(rate);
        conf.setOutputFramerate(rate);
        std::shared_ptr<sdk::Stream> stream = mainPipeline->startStream(startConfiguration);
        waitForStreamStarted(stream);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        sendFrames(stream, 20, [&conf, &rate](uint32_t nFrameId){
            if(nFrameId == 5)
                BOOST_TEST(conf.getOutputFramerate() == rate);
        });
        stream.reset();
        std::cout << "Sleeping 6 seconds..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(6000));
    }
    catch (const std::exception &e) {
        std::cerr << "Caught unexpected error: " + (std::string) e.what() << std::endl;
    }

    BOOST_TEST_MESSAGE("\nOut of range test");
    try{
        errorCounter++;
        BOOST_TEST_MESSAGE("\nTracker rate = " + std::to_string((int)conf.minOutputFramerate() -1));
        startConfiguration = getStartConfiguration();
        conf = getTrackerRateStartConfiguration(startConfiguration, (T) 1.0);
        conf.setOutputFramerate(conf.minOutputFramerate() -1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }

    try{
        errorCounter++;
        BOOST_TEST_MESSAGE("\nTracker rate = " + std::to_string(conf.maxOutputFramerate() + 1));
        startConfiguration = getStartConfiguration();
        conf = getTrackerRateStartConfiguration(startConfiguration, (T) 1.0);
        conf.setOutputFramerate(conf.maxOutputFramerate() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }


    BOOST_TEST_MESSAGE("\nUpdate test");
    try{
        errorCounter = 0;
        startConfiguration = getStartConfiguration();
        startConfiguration.getFlowSwitcher().setFlowId(flowId);
        std::shared_ptr<sdk::Stream> stream = mainPipeline->startStream(startConfiguration);
        waitForStreamStarted(stream);
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        auto conf = getTrackerRateUpdateConfiguration(stream, (T) 1.0);
        uint32_t rate;

        sendFrames(stream, 300, [&stream, &conf, &rate](uint32_t nFrameId){
            switch(nFrameId){
                case 50:
                    rate = (uint32_t) (random() % 101);
                    BOOST_TEST_MESSAGE(rate);
                    conf.setOutputFramerate(rate);
                    stream->update();
                    BOOST_TEST(conf.getOutputFramerate() == rate);
                    break;
                case 100:
                    rate = (uint32_t) (random() % 101);
                    BOOST_TEST_MESSAGE(rate);
                    conf.setOutputFramerate(rate);
                    stream->update();
                    BOOST_TEST(conf.getOutputFramerate() == rate);
                    break;
                case 150:
                    rate = (uint32_t) (random() % 101);
                    BOOST_TEST_MESSAGE(rate);
                    conf.setOutputFramerate(rate);
                    stream->update();
                    BOOST_TEST(conf.getOutputFramerate() == rate);
                    break;
                case 200:
                    try{
                        errorCounter++;
                        conf.setOutputFramerate(conf.maxOutputFramerate() + 1);
//                        stream->update();
                    }
                    catch (const std::exception& e) {
                        outOfRangeErrorTest((std::string) e.what());
                    }
                case 225:
                    try{
                        errorCounter++;
                        conf.setOutputFramerate(conf.minOutputFramerate() - 1);
                    }
                    catch (const std::exception& e) {
                        outOfRangeErrorTest((std::string) e.what());
                    }
                    break;
            }
        });
        stream.reset();
        std::cout << "Sleeping 6 seconds..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(6000));
    }
    catch (const std::exception& e) {
        std::cerr << "Caught unexpected error: " + (std::string) e.what() << std::endl;
    }

    BOOST_TEST(errorCounter == 0, "Not all expected errors returned! Number of missed errors: " + std::to_string(errorCounter));
}

/// \trackerTestFunc
/// Test function for general tracker's settings
/// \param flowId The flow id we working with
template<typename T>
//void trackerTestFunc(sdk::FlowSwitcherFlowId flowId){
//    std::cout << printTrackerFlow[flowId] << std::endl;
//    currentFlowId = flowId;
//    errorCounter = 0;
//    sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
//    sdk::DeepSortTrackerStartStreamConfiguration conf = getTrackerStartConfiguration(startConfiguration, (T) 1.0);
//
////    float maxFeatureWeight = conf.maxFeatureWeight();
////    float maxInitThreshold = conf.maxInitThreshold();
////    uint32_t maxInitTrackSize = conf.maxInitTrackSize();
////    float maxMaxCosineDistance = conf.maxMaxCosineDistance();
////    float maxMaxMahalanbisDistance = conf.maxMaxMahalanobisDistance();
////    uint32_t maxMaxPredictedFrames = conf.maxMaxPredictedFrames();
////    uint32_t maxTrackFeaturesHistorySize = conf.maxTrackFeaturesHistorySize();
////    float maxMinIouThreshold = conf.maxMinIouThreshold();
////    uint32_t maxMaxTimeSinceUpdateToReport = conf.maxMaxTimeSinceUpdateToReport();
////
////    float minFeatureWeight = conf.minFeatureWeight();
////    float minInitThreshold = conf.minInitThreshold();
////    uint32_t minInitTrackSize = conf.minInitTrackSize();
////    float minMaxCosineDistance = conf.minMaxCosineDistance();
////    float minMaxMahalanbisDistance = conf.minMaxMahalanobisDistance();
////    uint32_t minMaxPredictedFrames = conf.minMaxPredictedFrames();
////    uint32_t minTrackFeaturesHistorySize = conf.minTrackFeaturesHistorySize();
////    float minMinIouThreshold = conf.minMinIouThreshold();
////    uint32_t minMaxTimeSinceUpdateToReport = conf.minMaxTimeSinceUpdateToReport();
//
//
//    BOOST_TEST_MESSAGE("\nValid test");
//    try{
////        conf.setFeatureWeight((float)((random() % 101) / 100));
////        conf.setInitThreshold((float)((random() % 101) / 100));
////        conf.setInitTrackSize((uint32_t)(random() % (maxInitTrackSize + 1)));
////        conf.setMaxCosineDistance(((random() % (uint32_t) (maxMaxCosineDistance + 1)) / 100));
////        conf.setMaxMahalanobisDistance((random() % (uint32_t)(maxMaxMahalanbisDistance + 1)));
////        conf.setMaxPredictedFrames((uint32_t)(random() % 1001));
////        conf.setMinIouThreshold((float)((random() % 101) / 100));
////        conf.setTrackFeaturesHistorySize((random() % (maxTrackFeaturesHistorySize)) + 1);
//
//        std::shared_ptr<sdk::Stream> stream = mainPipeline->startStream(startConfiguration);
//        waitForStreamStarted(stream);
//        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//        sendFrames(stream, 30, nullptr);
//        stream.reset();
//    }
//    catch (const std::exception& e) {
//        std::cerr << (std::string) e.what() << std::endl;
//    }
//
//    BOOST_TEST_MESSAGE("\nOut of range test");
//    /*
//     * feature weight
//     * */
//    try{
////        BOOST_TEST_MESSAGE("Feature weight = " + std::to_string(minFeatureWeight - 1));
//        errorCounter++;
//        conf.setFeatureWeight(minFeatureWeight - 1);
//    }
//    catch (const std::exception& e) {
//        outOfRangeErrorTest((std::string) e.what());
//    }
//
//    try{
////        BOOST_TEST_MESSAGE("Feature weight = " + std::to_string(maxFeatureWeight + 1));
//        errorCounter++;
//        conf.setFeatureWeight(maxFeatureWeight + 1);
//    }
//    catch (const std::exception& e) {
//        outOfRangeErrorTest((std::string) e.what());
//    }
//    /*
//     * Init threshold
//     * */
//    try{
////        BOOST_TEST_MESSAGE("Init threshold = " + std::to_string(minInitThreshold - 1));
//        errorCounter++;
//        conf.setInitThreshold(minInitThreshold - 1);
//    }
//    catch (const std::exception& e) {
//        outOfRangeErrorTest((std::string) e.what());
//    }
//
//    try{
////        BOOST_TEST_MESSAGE("Init threshold = " + std::to_string(maxInitThreshold + 1));
//        errorCounter++;
//        conf.setInitThreshold(maxInitThreshold + 1);
//    }
//    catch (const std::exception& e) {
//        outOfRangeErrorTest((std::string) e.what());
//    }
//    /*
//     * Init track size
//     * */
//    try{
////        BOOST_TEST_MESSAGE("Init track size = " + std::to_string(minInitTrackSize - 1));
//        errorCounter++;
//        conf.setInitTrackSize(minInitTrackSize - 1);
//    }
//    catch (const std::exception& e) {
//        outOfRangeErrorTest((std::string) e.what());
//    }
//
//    try{
////        BOOST_TEST_MESSAGE("Init track size = " + std::to_string(maxInitTrackSize + 1));
//        errorCounter++;
//        conf.setInitThreshold(maxInitTrackSize + 1);
//    }
//    catch (const std::exception& e) {
//        outOfRangeErrorTest((std::string) e.what());
//    }
//    /*
//     * MaxCosineDistance
//     * */
//    try{
////        BOOST_TEST_MESSAGE("MaxCosineDistance = " + std::to_string(minMaxCosineDistance - 1));
//        errorCounter++;
//        conf.setMaxCosineDistance(minMaxCosineDistance - 1);
//    }
//    catch (const std::exception& e) {
//        outOfRangeErrorTest((std::string) e.what());
//    }
//
//    try{
////        BOOST_TEST_MESSAGE("MaxCosineDistance = " + std::to_string(maxInitTrackSize + 1));
//        errorCounter++;
//        conf.setMaxCosineDistance(maxMaxCosineDistance + 1);
//    }
//    catch (const std::exception& e) {
//        outOfRangeErrorTest((std::string) e.what());
//    }
//    /*
//     * MaxMahalanobisDistance
//     * */
//    try{
////        BOOST_TEST_MESSAGE("MaxMahalanobisDistance = " + std::to_string(minMaxMahalanbisDistance - 1));
//        errorCounter++;
//        conf.setMaxMahalanobisDistance(minMaxCosineDistance - 1);
//    }
//    catch (const std::exception& e) {
//        outOfRangeErrorTest((std::string) e.what());
//    }
//
//    try{
////        BOOST_TEST_MESSAGE("MaxMahalanobisDistance = " + std::to_string(maxMaxMahalanbisDistance + 1));
//        errorCounter++;
//        conf.setMaxMahalanobisDistance(maxMaxMahalanbisDistance + 1);
//    }
//    catch (const std::exception& e) {
//        outOfRangeErrorTest((std::string) e.what());
//    }
//    /*
//     *  MaxPredictedFrames
//     * */
//    try{
////        BOOST_TEST_MESSAGE("MaxPredictedFrames = " + std::to_string(minMaxPredictedFrames - 1));
//        errorCounter++;
//        conf.setMaxPredictedFrames(minMaxPredictedFrames - 1);
//    }
//    catch (const std::exception& e) {
//        outOfRangeErrorTest((std::string) e.what());
//    }
//
//    try{
////        BOOST_TEST_MESSAGE("MaxPredictedFrames = " + std::to_string(maxMaxPredictedFrames + 1));
//        errorCounter++;
//        conf.setMaxPredictedFrames(maxMaxPredictedFrames + 1);
//    }
//    catch (const std::exception& e) {
//        outOfRangeErrorTest((std::string) e.what());
//    }
//    /*
//     * TrackFeaturesHistorySize
//     * */
//    try{
////        BOOST_TEST_MESSAGE("TrackFeaturesHistorySize = " + std::to_string(minTrackFeaturesHistorySize - 1));
//        errorCounter++;
//        conf.setTrackFeaturesHistorySize(minTrackFeaturesHistorySize - 1);
//    }
//    catch (const std::exception& e) {
//        outOfRangeErrorTest((std::string) e.what());
//    }
//
//    try{
////        BOOST_TEST_MESSAGE("TrackFeaturesHistorySize = " + std::to_string(maxTrackFeaturesHistorySize + 1));
//        errorCounter++;
//        conf.setMaxPredictedFrames(maxTrackFeaturesHistorySize + 1);
//    }
//    catch (const std::exception& e) {
//        outOfRangeErrorTest((std::string) e.what());
//    }
//    /*
//     * MinIouThreshold
//     * */
//    try{
////        BOOST_TEST_MESSAGE("MinIouThreshold = " + std::to_string(minMinIouThreshold - 1));
//        errorCounter++;
//        conf.setMinIouThreshold(minMinIouThreshold - 1);
//    }
//    catch (const std::exception& e) {
//        outOfRangeErrorTest((std::string) e.what());
//    }
//
//    try{
////        BOOST_TEST_MESSAGE("MinIouThreshold = " + std::to_string(maxMinIouThreshold + 1));
//        errorCounter++;
//        conf.setMinIouThreshold(maxMinIouThreshold + 1);
//    }
//    catch (const std::exception& e) {
//        outOfRangeErrorTest((std::string) e.what());
//    }
//    /*
//     * MaxTimeSinceUpdateToReport
//     * */
//    try{
////        BOOST_TEST_MESSAGE("MaxTimeSinceUpdateToReport = " + std::to_string(minMaxTimeSinceUpdateToReport - 1));
//        errorCounter++;
//        conf.setMaxTimeSinceUpdateToReport(minMaxTimeSinceUpdateToReport - 1);
//    }
//    catch (const std::exception& e) {
//        outOfRangeErrorTest((std::string) e.what());
//    }
//
//    try{
////        BOOST_TEST_MESSAGE("MaxTimeSinceUpdateToReport = " + std::to_string(maxMaxTimeSinceUpdateToReport + 1));
//        errorCounter++;
//        conf.setMaxTimeSinceUpdateToReport(maxMaxTimeSinceUpdateToReport + 1);
//    }
//    catch (const std::exception& e) {
//        outOfRangeErrorTest((std::string) e.what());
//    }
//
//    BOOST_TEST_MESSAGE("\nUpdate test");
//    /*
//     * Valid update
//     * */
//    try{
//        startConfiguration = getStartConfiguration();
//        startConfiguration.getFlowSwitcher().setFlowId(flowId);
//        std::shared_ptr<sdk::Stream> stream = mainPipeline->startStream(startConfiguration);
//        waitForStreamStarted(stream);
//        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//        auto conf = getTrackerUpdateConfiguration(stream, (T) 1.0);
//        conf.setEnable(false);
//        uint32_t updateVal = (uint32_t) random() % 1001;
//        conf.setMaxTimeSinceUpdateToReport(updateVal);
//        stream->update();
//        BOOST_TEST(conf.getMaxTimeSinceUpdateToReport() == updateVal);
//        sendFrames(stream, 50, nullptr);
//    }
//    catch (const std::exception& e) {
//        std::cerr << (std::string) e.what() << std::endl;
//    }
//    /*
//     * Updating to o.o.r value
//     * */
//    try{
//        errorCounter++;
//        startConfiguration = getStartConfiguration();
//        startConfiguration.getFlowSwitcher().setFlowId(flowId);
//        std::shared_ptr<sdk::Stream> stream = mainPipeline->startStream(startConfiguration);
//        waitForStreamStarted(stream);
//        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//        auto conf = getTrackerUpdateConfiguration(stream, (T) 1.0);
//        sendFrames(stream, 10, [&conf, &maxMaxTimeSinceUpdateToReport](uint32_t nFrameId){
//            if (nFrameId == 3) {
//                try {
//                    conf.setMaxTimeSinceUpdateToReport(maxMaxTimeSinceUpdateToReport + 1);
//                }
//                catch (const std::exception& e) {
//                    outOfRangeErrorTest((std::string) e.what());
//                }
//            }
//        });
//    }
//    catch (const std::exception& e) {
//        outOfRangeErrorTest((std::string) e.what());
//    }
//
//    BOOST_TEST(errorCounter == 0, "Not all expected errors returned! Number of missed errors: " + std::to_string(errorCounter));
//}

/// \rendererTestFunc
/// Test function for renderer settings
void rendererTestFunc(){
    sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
    errorCounter = 0;
    BOOST_TEST_MESSAGE("\nStarting Out of range tests...");
    try {
//        BOOST_TEST_MESSAGE("Target Width = " + std::to_string(startConfiguration.getCvRenderer().maxTargetWidth()+ 1));
        errorCounter++;
//        startConfiguration = getStartConfiguration();
        startConfiguration.getCvRenderer().setTargetWidth(startConfiguration.getCvRenderer().maxTargetWidth() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    try {
//        BOOST_TEST_MESSAGE("Target Height = " + std::to_string(startConfiguration.getCvRenderer().maxTargetHeight() + 1));
        errorCounter++;
//        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        startConfiguration.getCvRenderer().setTargetHeight(startConfiguration.getCvRenderer().maxTargetHeight() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    try {
//        BOOST_TEST_MESSAGE("Normalization.Alpha = " + std::to_string(startConfiguration.getCvRenderer().getNormalization().maxAlpha() + 1));
        errorCounter++;
//        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        startConfiguration.getCvRenderer().getNormalization().setAlpha(startConfiguration.getCvRenderer().getNormalization().maxAlpha() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    try {
//        BOOST_TEST_MESSAGE("Normalization.Beta = " + std::to_string(startConfiguration.getCvRenderer().getNormalization().maxBeta() + 1));
        errorCounter++;
//        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        startConfiguration.getCvRenderer().getNormalization().setBeta(startConfiguration.getCvRenderer().getNormalization().maxBeta() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    try {
//        BOOST_TEST_MESSAGE("Normalization.StdCropSize = " + std::to_string(startConfiguration.getCvRenderer().getNormalization().maxStdCropSize() + 1));
        errorCounter++;
//        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        startConfiguration.getCvRenderer().getNormalization().setStdCropSize(startConfiguration.getCvRenderer().getNormalization().maxStdCropSize() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    try {
//        BOOST_TEST_MESSAGE("TrackVelocityFactor = " + std::to_string(startConfiguration.getCvRenderer().maxTrackVelocityFactor() + 1));
        errorCounter++;
        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        startConfiguration.getCvRenderer().setTrackVelocityFactor(startConfiguration.getCvRenderer().maxTrackVelocityFactor() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
//    try {
////        BOOST_TEST_MESSAGE("PointTrackRadius = " + std::to_string(startConfiguration.getCvRenderer().maxPointTrackRadius() + 1));
//        errorCounter++;
//        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
//        startConfiguration.getCvRenderer().setPointTrackRadius(startConfiguration.getCvRenderer().maxPointTrackRadius() + 1);
//    }
//    catch (const std::exception& e) {
//        outOfRangeErrorTest((std::string) e.what());
//    }
    try {
//        BOOST_TEST_MESSAGE("CenterOfMassRadius = " + std::to_string(startConfiguration.getCvRenderer().maxCenterOfMassRadius() + 1));
        errorCounter++;
        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        startConfiguration.getCvRenderer().setCenterOfMassRadius(startConfiguration.getCvRenderer().maxCenterOfMassRadius() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    try {
//        BOOST_TEST_MESSAGE("DetectorRoi.Color = " + std::to_string(startConfiguration.getCvRenderer().getDetectorRoi().maxColor() + 1));
        errorCounter++;
        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        startConfiguration.getCvRenderer().getDetectorRoi().setColor(startConfiguration.getCvRenderer().getDetectorRoi().maxColor() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    try {
//        BOOST_TEST_MESSAGE("DetectorRoi.LineThickness = " + std::to_string(startConfiguration.getCvRenderer().getDetectorRoi().maxLineThickness() + 1));
        errorCounter++;
        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        startConfiguration.getCvRenderer().getDetectorRoi().setLineThickness(startConfiguration.getCvRenderer().getDetectorRoi().maxLineThickness() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    try {
//        BOOST_TEST_MESSAGE("DetectorRoi.LineThickness = " + std::to_string(startConfiguration.getCvRenderer().getDetectorRoi().maxLineThickness() + 1));
        errorCounter++;
        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        startConfiguration.getCvRenderer().getDetectorRoi().setLineThickness(startConfiguration.getCvRenderer().getDetectorRoi().maxLineThickness() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    try {
//        BOOST_TEST_MESSAGE("BoundingBoxes[].BoxColor = " + std::to_string(startConfiguration.getCvRenderer().getBoundingBoxes("").maxBoxColor() + 1));
        errorCounter++;
        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        startConfiguration.getCvRenderer().getBoundingBoxes("").setBoxColor(startConfiguration.getCvRenderer().getBoundingBoxes("").maxBoxColor() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    try {
//        BOOST_TEST_MESSAGE("BoundingBoxes[].LineThickness = " + std::to_string(startConfiguration.getCvRenderer().getBoundingBoxes("").maxLineThickness() + 1));
        errorCounter++;
        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        startConfiguration.getCvRenderer().getBoundingBoxes("").setLineThickness(startConfiguration.getCvRenderer().getBoundingBoxes("").maxLineThickness() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    try {
//        BOOST_TEST_MESSAGE("BoundingBoxes[].TextOffsetX = " + std::to_string(startConfiguration.getCvRenderer().getBoundingBoxes("").maxTextOffsetX() + 1));
        errorCounter++;
        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        startConfiguration.getCvRenderer().getBoundingBoxes("").setTextOffsetX(startConfiguration.getCvRenderer().getBoundingBoxes("").maxTextOffsetX() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    try {
//        BOOST_TEST_MESSAGE("BoundingBoxes[].TextOffsetY = " + std::to_string(startConfiguration.getCvRenderer().getBoundingBoxes("").maxTextOffsetY() + 1));
        errorCounter++;
        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        startConfiguration.getCvRenderer().getBoundingBoxes("").setTextOffsetY(startConfiguration.getCvRenderer().getBoundingBoxes("").maxTextOffsetY() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    try {
//        BOOST_TEST_MESSAGE("BoundingBoxes[].FontColor = " + std::to_string(startConfiguration.getCvRenderer().getBoundingBoxes("").maxFontColor() + 1));
        errorCounter++;
        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        startConfiguration.getCvRenderer().getBoundingBoxes("").setFontColor(startConfiguration.getCvRenderer().getBoundingBoxes("").maxFontColor() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    try {
//        BOOST_TEST_MESSAGE("BoundingBoxes[].FontScale = " + std::to_string(startConfiguration.getCvRenderer().getBoundingBoxes("").maxFontScale() + 1));
        errorCounter++;
        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        startConfiguration.getCvRenderer().getBoundingBoxes("").setFontScale(startConfiguration.getCvRenderer().getBoundingBoxes("").maxFontScale() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    try {
//        BOOST_TEST_MESSAGE("BoundingBoxes[].FontThickness = " + std::to_string(startConfiguration.getCvRenderer().getBoundingBoxes("").maxFontThickness() + 1));
        errorCounter++;
        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        startConfiguration.getCvRenderer().getBoundingBoxes("").setFontScale(startConfiguration.getCvRenderer().getBoundingBoxes("").maxFontThickness() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    try {
//        BOOST_TEST_MESSAGE("Osd.MarginX = " + std::to_string(startConfiguration.getCvRenderer().getOsd().maxMarginX() + 1));
        errorCounter++;
        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        startConfiguration.getCvRenderer().getOsd().setMarginX(startConfiguration.getCvRenderer().getOsd().maxMarginX() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    try {
//        BOOST_TEST_MESSAGE("Osd.MarginY = " + std::to_string(startConfiguration.getCvRenderer().getOsd().maxMarginY() + 1));
        errorCounter++;
        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        startConfiguration.getCvRenderer().getOsd().setMarginY(startConfiguration.getCvRenderer().getOsd().maxMarginY() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    try {
//        BOOST_TEST_MESSAGE("Osd.LineDistance = " + std::to_string(startConfiguration.getCvRenderer().getOsd().maxLineDistance() + 1));
        errorCounter++;
        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        startConfiguration.getCvRenderer().getOsd().setMarginY(startConfiguration.getCvRenderer().getOsd().maxLineDistance() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    try {
//        BOOST_TEST_MESSAGE("Osd.BackColor = " + std::to_string(startConfiguration.getCvRenderer().getOsd().maxBackColor() + 1));
        errorCounter++;
        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        startConfiguration.getCvRenderer().getOsd().setBackColor(startConfiguration.getCvRenderer().getOsd().maxBackColor() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    try {
//        BOOST_TEST_MESSAGE("Osd.BackTransparency = " + std::to_string(startConfiguration.getCvRenderer().getOsd().maxBackTransparency() + 1));
        errorCounter++;
        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        startConfiguration.getCvRenderer().getOsd().setBackColor(startConfiguration.getCvRenderer().getOsd().maxBackTransparency() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    try {
//        BOOST_TEST_MESSAGE("Osd.FontColor = " + std::to_string(startConfiguration.getCvRenderer().getOsd().maxFontColor() + 1));
        errorCounter++;
        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        startConfiguration.getCvRenderer().getOsd().setFontColor(startConfiguration.getCvRenderer().getOsd().maxFontColor() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    try {
//        BOOST_TEST_MESSAGE("Osd.FontScale = " + std::to_string(startConfiguration.getCvRenderer().getOsd().maxFontScale() + 1));
        errorCounter++;
        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        startConfiguration.getCvRenderer().getOsd().setFontScale(startConfiguration.getCvRenderer().getOsd().maxFontScale() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    try {
//        BOOST_TEST_MESSAGE("Osd.FontThickness = " + std::to_string(startConfiguration.getCvRenderer().getOsd().maxFontThickness() + 1));
        errorCounter++;
        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        startConfiguration.getCvRenderer().getOsd().setFontScale(startConfiguration.getCvRenderer().getOsd().maxFontThickness() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    try {
//        BOOST_TEST_MESSAGE("Histogram.MarginX = " + std::to_string(startConfiguration.getCvRenderer().getHistogram().maxMarginX() + 1));
        errorCounter++;
        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        startConfiguration.getCvRenderer().getHistogram().setMarginX(startConfiguration.getCvRenderer().getHistogram().maxMarginX() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    try {
//        BOOST_TEST_MESSAGE("Histogram.MarginY = " + std::to_string(startConfiguration.getCvRenderer().getHistogram().maxMarginY() + 1));
        errorCounter++;
        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        startConfiguration.getCvRenderer().getHistogram().setMarginY(startConfiguration.getCvRenderer().getHistogram().maxMarginY() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    try {
//        BOOST_TEST_MESSAGE("Histogram.Bins = " + std::to_string(startConfiguration.getCvRenderer().getHistogram().maxBins() + 1));
        errorCounter++;
        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        startConfiguration.getCvRenderer().getHistogram().setMarginY(startConfiguration.getCvRenderer().getHistogram().maxBins() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    try {
//        BOOST_TEST_MESSAGE("Histogram.Width = " + std::to_string(startConfiguration.getCvRenderer().getHistogram().maxWidth() + 1));
        errorCounter++;
        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        startConfiguration.getCvRenderer().getHistogram().setWidth(startConfiguration.getCvRenderer().getHistogram().maxWidth() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    try {
//        BOOST_TEST_MESSAGE("Histogram.Height = " + std::to_string(startConfiguration.getCvRenderer().getHistogram().maxHeight() + 1));
        errorCounter++;
        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        startConfiguration.getCvRenderer().getHistogram().setHeight(startConfiguration.getCvRenderer().getHistogram().maxHeight() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    try {
//        BOOST_TEST_MESSAGE("Histogram.BackColor = " + std::to_string(startConfiguration.getCvRenderer().getHistogram().maxBackColor() + 1));
        errorCounter++;
        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        startConfiguration.getCvRenderer().getHistogram().setBackColor(startConfiguration.getCvRenderer().getHistogram().maxBackColor() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    try {
//        BOOST_TEST_MESSAGE("Histogram.BackTransparency = " + std::to_string(startConfiguration.getCvRenderer().getHistogram().maxBackTransparency() + 1));
        errorCounter++;
        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        startConfiguration.getCvRenderer().getHistogram().setBackTransparency(startConfiguration.getCvRenderer().getHistogram().maxBackTransparency() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    try {
//        BOOST_TEST_MESSAGE("Histogram.ColorBefore = " + std::to_string(startConfiguration.getCvRenderer().getHistogram().maxColorBefore() + 1));
        errorCounter++;
        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        startConfiguration.getCvRenderer().getHistogram().setColorBefore(startConfiguration.getCvRenderer().getHistogram().maxColorBefore() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    try {
//        BOOST_TEST_MESSAGE("Histogram.ColorAfter = " + std::to_string(startConfiguration.getCvRenderer().getHistogram().maxColorAfter() + 1));
        errorCounter++;
        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        startConfiguration.getCvRenderer().getHistogram().setColorAfter(startConfiguration.getCvRenderer().getHistogram().maxColorAfter() + 1);
    }
    catch (const std::exception& e) {
        outOfRangeErrorTest((std::string) e.what());
    }
    BOOST_TEST(errorCounter == 0, "Not all expected errors returned! Number of missed errors: " + std::to_string(errorCounter));
}

//BOOST_AUTO_TEST_CASE(get_params) { // NOLINT
//    getParamsFromJson();
//}

BOOST_AUTO_TEST_CASE(run_tests) { // NOLINT
        run();
}

//const bool is_merlin = project == "Merlin" ? true : false;

const bool flag_bool = true;

#ifdef DEFAULTS
BOOST_AUTO_TEST_SUITE(icd_tests) // NOLINT
BOOST_AUTO_TEST_CASE(start_defaults, *boost::unit_test::enable_if<flag_bool>()) { // NOLINT
        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();

        /*
         * Preprocessor
         */
        BOOST_TEST_MESSAGE("Starting test - Preprocessor");
        BOOST_TEST(startConfiguration.getPreprocessor().getRoi().getWidth() == jsonData["Preprocessor"]["Roi.Width"]["Default value"]);
        BOOST_TEST(startConfiguration.getPreprocessor().getRoi().getHeight() == jsonData["Preprocessor"]["Roi.Height"]["Default value"]);
        BOOST_TEST(startConfiguration.getPreprocessor().getRoi().getX() == jsonData["Preprocessor"]["Roi.X"]["Default value"]);
        BOOST_TEST(startConfiguration.getPreprocessor().getRoi().getY() == jsonData["Preprocessor"]["Roi.Y"]["Default value"]);
        BOOST_TEST(startConfiguration.getPreprocessor().getRotateAngle() == jsonData["Preprocessor"]["RotateAngle"]["Default value"]);


        /*
         * Default Flow ID (Rgb)
         */
//        BOOST_TEST_MESSAGE("Starting test - Default Flow ID (Rgb)");
//
//        std::cout << "Current Flow: " << startConfiguration.getFlowSwitcher().getFlowId() << std::endl;
//        std::cout << sdk::FlowSwitcherFlowId::Rgb << std::endl;
//        BOOST_TEST(startConfiguration.getFlowSwitcher().getFlowId() == sdk::FlowSwitcherFlowId::Rgb);

        /*
         * Ground Rgb Detector
         */
        BOOST_TEST_MESSAGE("Starting test - Ground Rgb Detector");
        BOOST_TEST(startConfiguration.getGroundRgbDetector().getRoi().getWidth() == jsonData["GroundRgbDetector"]["Roi.Width"]["Default value"]);
        BOOST_TEST(startConfiguration.getGroundRgbDetector().getRoi().getHeight() == jsonData["GroundRgbDetector"]["Roi.Height"]["Default value"]);
        BOOST_TEST(startConfiguration.getGroundRgbDetector().getRoi().getX() == jsonData["GroundRgbDetector"]["Roi.X"]["Default value"]);
        BOOST_TEST(startConfiguration.getGroundRgbDetector().getRoi().getY() == jsonData["GroundRgbDetector"]["Roi.Y"]["Default value"]);
        // Vehicle
        BOOST_TEST_MESSAGE("Vehicle");
        std::cout << "Vehicle: " << startConfiguration.getGroundRgbDetector().getGroups("Vehicle").getScoreThreshold() << std::endl;
        BOOST_TEST(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").getScoreThreshold() == (float) jsonData["GroundRgbDetector"]["Groups[\"Vehicle\"].ScoreThreshold"]["Default value"]);
        BOOST_TEST(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").getMinWidth() == (float) jsonData["GroundRgbDetector"]["Groups[\"Vehicle\"].MinWidth"]["Default value"]);
        BOOST_TEST(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").getMaxWidth() == (float) jsonData["GroundRgbDetector"]["Groups[\"Vehicle\"].MaxWidth"]["Default value"]);
        BOOST_TEST(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").getMinHeight() == (float) jsonData["GroundRgbDetector"]["Groups[\"Vehicle\"].MinHeight"]["Default value"]);
        BOOST_TEST(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").getMaxHeight() == (float) jsonData["GroundRgbDetector"]["Groups[\"Vehicle\"].MaxHeight"]["Default value"]);
        BOOST_TEST(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").getMinAspectRatio() == (float) jsonData["GroundRgbDetector"]["Groups[\"Vehicle\"].MinAspectRatio"]["Default value"]);
        BOOST_TEST(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").getMaxAspectRatio() == (float) jsonData["GroundRgbDetector"]["Groups[\"Vehicle\"].MaxAspectRatio"]["Default value"]);
        // HeavyVehicle
//        BOOST_TEST_MESSAGE("HeavyVehicle");
//        BOOST_TEST(startConfiguration.getGroundRgbDetector().getGroups("HeavyVehicle").getScoreThreshold() == (float) jsonData["GroundRgbDetector"]["Groups[\"HeavyVehicle\"].ScoreThreshold"]["Default value"]);
//        BOOST_TEST(startConfiguration.getGroundRgbDetector().getGroups("HeavyVehicle").getMinWidth() == (float) jsonData["GroundRgbDetector"]["Groups[\"HeavyVehicle\"].MinWidth"]["Default value"]);
//        BOOST_TEST(startConfiguration.getGroundRgbDetector().getGroups("HeavyVehicle").getMaxWidth() == (float) jsonData["GroundRgbDetector"]["Groups[\"HeavyVehicle\"].MaxWidth"]["Default value"]);
//        BOOST_TEST(startConfiguration.getGroundRgbDetector().getGroups("HeavyVehicle").getMinHeight() == (float) jsonData["GroundRgbDetector"]["Groups[\"HeavyVehicle\"].MinHeight"]["Default value"]);
//        BOOST_TEST(startConfiguration.getGroundRgbDetector().getGroups("HeavyVehicle").getMaxHeight() == (float) jsonData["GroundRgbDetector"]["Groups[\"HeavyVehicle\"].MaxHeight"]["Default value"]);
//        BOOST_TEST(startConfiguration.getGroundRgbDetector().getGroups("HeavyVehicle").getMinAspectRatio() == (float) jsonData["GroundRgbDetector"]["Groups[\"HeavyVehicle\"].MinAspectRatio"]["Default value"]);
//        BOOST_TEST(startConfiguration.getGroundRgbDetector().getGroups("HeavyVehicle").getMaxAspectRatio() == (float) jsonData["GroundRgbDetector"]["Groups[\"HeavyVehicle\"].MaxAspectRatio"]["Default value"]);
        // Person
        BOOST_TEST_MESSAGE("Person");
        BOOST_TEST(startConfiguration.getGroundRgbDetector().getGroups("Person").getScoreThreshold() == (float) jsonData["GroundRgbDetector"]["Groups[\"Person\"].ScoreThreshold"]["Default value"]);
        BOOST_TEST(startConfiguration.getGroundRgbDetector().getGroups("Person").getMinWidth() == (float) jsonData["GroundRgbDetector"]["Groups[\"Person\"].MinWidth"]["Default value"]);
        BOOST_TEST(startConfiguration.getGroundRgbDetector().getGroups("Person").getMaxWidth() == (float) jsonData["GroundRgbDetector"]["Groups[\"Person\"].MaxWidth"]["Default value"]);
        BOOST_TEST(startConfiguration.getGroundRgbDetector().getGroups("Person").getMinHeight() == (float) jsonData["GroundRgbDetector"]["Groups[\"Person\"].MinHeight"]["Default value"]);
        BOOST_TEST(startConfiguration.getGroundRgbDetector().getGroups("Person").getMaxHeight() == (float) jsonData["GroundRgbDetector"]["Groups[\"Person\"].MaxHeight"]["Default value"]);
        BOOST_TEST(startConfiguration.getGroundRgbDetector().getGroups("Person").getMinAspectRatio() == (float) jsonData["GroundRgbDetector"]["Groups[\"Person\"].MinAspectRatio"]["Default value"]);
        BOOST_TEST(startConfiguration.getGroundRgbDetector().getGroups("Person").getMaxAspectRatio() == (float) jsonData["GroundRgbDetector"]["Groups[\"Person\"].MaxAspectRatio"]["Default value"]);
        // TwoWheeled
//        BOOST_TEST_MESSAGE("TwoWheeled");
//        BOOST_TEST(startConfiguration.getGroundRgbDetector().getGroups("TwoWheeled").getScoreThreshold() == (float) jsonData["GroundRgbDetector"]["Groups[\"TwoWheeled\"].ScoreThreshold"]["Default value"]);
//        BOOST_TEST(startConfiguration.getGroundRgbDetector().getGroups("TwoWheeled").getMinWidth() == (float) jsonData["GroundRgbDetector"]["Groups[\"TwoWheeled\"].MinWidth"]["Default value"]);
//        BOOST_TEST(startConfiguration.getGroundRgbDetector().getGroups("TwoWheeled").getMaxWidth() == (float) jsonData["GroundRgbDetector"]["Groups[\"TwoWheeled\"].MaxWidth"]["Default value"]);
//        BOOST_TEST(startConfiguration.getGroundRgbDetector().getGroups("TwoWheeled").getMinHeight() == (float) jsonData["GroundRgbDetector"]["Groups[\"TwoWheeled\"].MinHeight"]["Default value"]);
//        BOOST_TEST(startConfiguration.getGroundRgbDetector().getGroups("TwoWheeled").getMaxHeight() == (float) jsonData["GroundRgbDetector"]["Groups[\"TwoWheeled\"].MaxHeight"]["Default value"]);
//        BOOST_TEST(startConfiguration.getGroundRgbDetector().getGroups("TwoWheeled").getMinAspectRatio() == (float) jsonData["GroundRgbDetector"]["Groups[\"TwoWheeled\"].MinAspectRatio"]["Default value"]);
//        BOOST_TEST(startConfiguration.getGroundRgbDetector().getGroups("TwoWheeled").getMaxAspectRatio() == (float) jsonData["GroundRgbDetector"]["Groups[\"TwoWheeled\"].MaxAspectRatio"]["Default value"]);

        BOOST_TEST(startConfiguration.getGroundRgbDetector().getMaxDetections() == jsonData["GroundRgbDetector"]["MaxDetections"]["Default value"]);
//        BOOST_TEST(startConfiguration.getGroundRgbDetector().getOutputClasses(0) == (std::string)jsonData["GroundRgbDetector"]["OutputClasses[0]"]["Default value"]);

        /*
         * Ground Rgb Tracker
         */
        BOOST_TEST_MESSAGE("Starting test - Ground Rgb Tracker");
        BOOST_TEST(startConfiguration.getPersonTracker().getEnable() == jsonData["PersonTracker"]["Enable"]["Default value"]);
//        BOOST_TEST(startConfiguration.getPersonTracker().getMaxTimeSinceUpdateToReport() == jsonData["PersonTracker"]["MaxTimeSinceUpdateToReport"]["Default value"]);
//        BOOST_TEST(startConfiguration.getPersonTracker().getInitTrackSize() == jsonData["PersonTracker"]["Parameters.InitTrackSize"]["Default value"]);
//        BOOST_TEST(startConfiguration.getPersonTracker().getInitThreshold() == (float) jsonData["PersonTracker"]["Parameters.InitThreshold"]["Default value"]);
//        BOOST_TEST(startConfiguration.getPersonTracker().getInitMetric() == sdk::InitScoreMetric::Median);
//        BOOST_TEST(startConfiguration.getPersonTracker().getMaxPredictedFrames() == jsonData["PersonTracker"]["Parameters.MaxPredictedFrames"]["Default value"]);
//        BOOST_TEST(startConfiguration.getPersonTracker().getTrackFeaturesHistorySize() == jsonData["PersonTracker"]["Parameters.TrackFeaturesHistorySize"]["Default value"]);
//        BOOST_TEST(startConfiguration.getPersonTracker().getFeatureWeight() == jsonData["PersonTracker"]["Parameters.FeatureWeight"]["Default value"]);
//        BOOST_TEST(startConfiguration.getPersonTracker().getMaxCosineDistance() == (float) jsonData["PersonTracker"]["Parameters.MaxCosineDistance"]["Default value"]);
//        BOOST_TEST(startConfiguration.getPersonTracker().getMaxMahalanobisDistance() == jsonData["PersonTracker"]["Parameters.MaxMahalanobisDistance"]["Default value"]);
//        BOOST_TEST(startConfiguration.getPersonTracker().getMinIouThreshold() == (float) jsonData["PersonTracker"]["Parameters.MinIouThreshold"]["Default value"]);


        /*
         * Ground Mwir Flow ID
         */
        startConfiguration.getFlowSwitcher().setFlowId(sdk::FlowSwitcherFlowId::Mwir);
        BOOST_TEST_MESSAGE("Starting test - Ground Mwir Flow ID");
        BOOST_TEST(startConfiguration.getFlowSwitcher().getFlowId() == sdk::FlowSwitcherFlowId::Mwir);

        /*
         * Ground Mwir Detector
         */
        BOOST_TEST_MESSAGE("Starting test - Ground Mwir Detector");
        BOOST_TEST(startConfiguration.getGroundMwirDetector().getRoi().getWidth() == jsonData["GroundMwirDetector"]["Roi.Width"]["Default value"]);
        BOOST_TEST(startConfiguration.getGroundMwirDetector().getRoi().getHeight() == jsonData["GroundMwirDetector"]["Roi.Height"]["Default value"]);
        BOOST_TEST(startConfiguration.getGroundMwirDetector().getRoi().getX() == jsonData["GroundMwirDetector"]["Roi.X"]["Default value"]);
        BOOST_TEST(startConfiguration.getGroundMwirDetector().getRoi().getY() == jsonData["GroundMwirDetector"]["Roi.Y"]["Default value"]);
        // Vehicle
        BOOST_TEST(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").getScoreThreshold() == (float) jsonData["GroundMwirDetector"]["Groups[\"Vehicle\"].ScoreThreshold"]["Default value"]);
        BOOST_TEST(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").getMinWidth() == (float) jsonData["GroundMwirDetector"]["Groups[\"Vehicle\"].MinWidth"]["Default value"]);
        BOOST_TEST(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").getMaxWidth() == (float) jsonData["GroundMwirDetector"]["Groups[\"Vehicle\"].MaxWidth"]["Default value"]);
        BOOST_TEST(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").getMinHeight() == (float) jsonData["GroundMwirDetector"]["Groups[\"Vehicle\"].MinHeight"]["Default value"]);
        BOOST_TEST(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").getMaxHeight() == (float) jsonData["GroundMwirDetector"]["Groups[\"Vehicle\"].MaxHeight"]["Default value"]);
        BOOST_TEST(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").getMinAspectRatio() == (float) jsonData["GroundMwirDetector"]["Groups[\"Vehicle\"].MinAspectRatio"]["Default value"]);
        BOOST_TEST(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").getMaxAspectRatio() == (float) jsonData["GroundMwirDetector"]["Groups[\"Vehicle\"].MaxAspectRatio"]["Default value"]);
        // Person
        BOOST_TEST(startConfiguration.getGroundMwirDetector().getGroups("Person").getScoreThreshold() == (float) jsonData["GroundMwirDetector"]["Groups[\"Person\"].ScoreThreshold"]["Default value"]);
        BOOST_TEST(startConfiguration.getGroundMwirDetector().getGroups("Person").getMinWidth() == (float) jsonData["GroundMwirDetector"]["Groups[\"Person\"].MinWidth"]["Default value"]);
        BOOST_TEST(startConfiguration.getGroundMwirDetector().getGroups("Person").getMaxWidth() == (float) jsonData["GroundMwirDetector"]["Groups[\"Person\"].MaxWidth"]["Default value"]);
        BOOST_TEST(startConfiguration.getGroundMwirDetector().getGroups("Person").getMinHeight() == (float) jsonData["GroundMwirDetector"]["Groups[\"Person\"].MinHeight"]["Default value"]);
        BOOST_TEST(startConfiguration.getGroundMwirDetector().getGroups("Person").getMaxHeight() == (float) jsonData["GroundMwirDetector"]["Groups[\"Person\"].MaxHeight"]["Default value"]);
        BOOST_TEST(startConfiguration.getGroundMwirDetector().getGroups("Person").getMinAspectRatio() == (float) jsonData["GroundMwirDetector"]["Groups[\"Person\"].MinAspectRatio"]["Default value"]);
        BOOST_TEST(startConfiguration.getGroundMwirDetector().getGroups("Person").getMaxAspectRatio() == (float) jsonData["GroundMwirDetector"]["Groups[\"Person\"].MaxAspectRatio"]["Default value"]);

        BOOST_TEST(startConfiguration.getGroundMwirDetector().getMaxDetections() == jsonData["GroundMwirDetector"]["MaxDetections"]["Default value"]);
//        BOOST_TEST(startConfiguration.getGroundMwirDetector().getOutputClasses(0) == (std::string)jsonData["GroundMwirDetector"]["OutputClasses[0]"]["Default value"]);

        /*
         * Ground Mwir Tracker
         */
        BOOST_TEST_MESSAGE("Starting test - Ground Mwir Tracker");
        BOOST_TEST(startConfiguration.getVehicleTracker().getEnable() == jsonData["VehicleTracker"]["Enable"]["Default value"]);
//        BOOST_TEST(startConfiguration.getVehicleTracker().getMaxTimeSinceUpdateToReport() == jsonData["VehicleTracker"]["MaxTimeSinceUpdateToReport"]["Default value"]);
//        BOOST_TEST(startConfiguration.getVehicleTracker().getInitTrackSize() == jsonData["VehicleTracker"]["Parameters.InitTrackSize"]["Default value"]);
//        BOOST_TEST(startConfiguration.getVehicleTracker().getInitThreshold() == (float) jsonData["VehicleTracker"]["Parameters.InitThreshold"]["Default value"]);
//        BOOST_TEST(startConfiguration.getVehicleTracker().getInitMetric() == sdk::InitScoreMetric::Median);
//        BOOST_TEST(startConfiguration.getVehicleTracker().getMaxPredictedFrames() == jsonData["VehicleTracker"]["Parameters.MaxPredictedFrames"]["Default value"]);
//        BOOST_TEST(startConfiguration.getVehicleTracker().getTrackFeaturesHistorySize() == jsonData["VehicleTracker"]["Parameters.TrackFeaturesHistorySize"]["Default value"]);
//        BOOST_TEST(startConfiguration.getVehicleTracker().getFeatureWeight() == jsonData["VehicleTracker"]["Parameters.FeatureWeight"]["Default value"]);
//        BOOST_TEST(startConfiguration.getVehicleTracker().getMaxCosineDistance() == (float) jsonData["VehicleTracker"]["Parameters.MaxCosineDistance"]["Default value"]);
//        BOOST_TEST(startConfiguration.getVehicleTracker().getMaxMahalanobisDistance() == jsonData["VehicleTracker"]["Parameters.MaxMahalanobisDistance"]["Default value"]);
//        BOOST_TEST(startConfiguration.getVehicleTracker().getMinIouThreshold() == (float) jsonData["VehicleTracker"]["Parameters.MinIouThreshold"]["Default value"]);


        /*
         * Tracks Publisher
         */
        BOOST_TEST_MESSAGE("Starting test - Tracks Publisher");
        BOOST_TEST(startConfiguration.getTracksPublisher().getSourceData() == sdk::PublisherDataType::Tracks);

        /*
         * CvRenderer
         */
        BOOST_TEST_MESSAGE("Starting test - CvRenderer");
        BOOST_TEST(startConfiguration.getCvRenderer().getTargetWidth() == jsonData["CvRenderer"]["TargetWidth"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getTargetHeight() == jsonData["CvRenderer"]["TargetHeight"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getSkipAllRendering() == jsonData["CvRenderer"]["SkipAllRendering"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getNormalization().getType() == sdk::NormalizationType::MeanStdCrop);
        BOOST_TEST(startConfiguration.getCvRenderer().getNormalization().getAlpha() == jsonData["CvRenderer"]["Normalization.Alpha"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getNormalization().getBeta() == jsonData["CvRenderer"]["Normalization.Beta"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getNormalization().getStdCropSize() == jsonData["CvRenderer"]["Normalization.StdCropSize"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getDrawDetections() == jsonData["CvRenderer"]["DrawDetections"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getDrawTracks() == jsonData["CvRenderer"]["DrawTracks"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getPrintClass() == jsonData["CvRenderer"]["PrintClass"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getPrintScore() == jsonData["CvRenderer"]["PrintScore"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getPrintTrackId() == jsonData["CvRenderer"]["PrintTrackId"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getColorTrack() == jsonData["CvRenderer"]["ColorTrack"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getDrawTrackVelocity() == jsonData["CvRenderer"]["DrawTrackVelocity"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getTrackVelocityFactor() == jsonData["CvRenderer"]["TrackVelocityFactor"]["Default value"]);
//        BOOST_TEST(startConfiguration.getCvRenderer().getPointTrackRadius() == jsonData["CvRenderer"]["PointTrackRadius"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getPrintDistance() == jsonData["CvRenderer"]["PrintDistance"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getDrawCenterOfMass() == jsonData["CvRenderer"]["DrawCenterOfMass"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getCenterOfMassRadius() == jsonData["CvRenderer"]["CenterOfMassRadius"]["Default value"]);

        // Detector ROI
        BOOST_TEST(startConfiguration.getCvRenderer().getDetectorRoi().getSkipRendering() == jsonData["CvRenderer"]["DetectorRoi.SkipRendering"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getDetectorRoi().getColor() == jsonData["CvRenderer"]["DetectorRoi.Color"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getDetectorRoi().getLineThickness() == jsonData["CvRenderer"]["DetectorRoi.LineThickness"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getDetectorRoi().getHideOutside() == jsonData["CvRenderer"]["DetectorRoi.HideOutside"]["Default value"]);
//        BOOST_TEST(startConfiguration.getCvRenderer().getDetectorRoi().getOutsideColor() == 0);
        BOOST_TEST_MESSAGE("Testing BB");
        // Bounding Boxes
        BOOST_TEST(startConfiguration.getCvRenderer().getBoundingBoxes("").getSkipRendering() == jsonData["CvRenderer"]["BoundingBoxes[\"\"].SkipRendering"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getBoundingBoxes("").getBoxColor() == jsonData["CvRenderer"]["BoundingBoxes[\"\"].BoxColor"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getBoundingBoxes("").getLineThickness() == jsonData["CvRenderer"]["BoundingBoxes[\"\"].LineThickness"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getBoundingBoxes("").getTextOffsetX() == jsonData["CvRenderer"]["BoundingBoxes[\"\"].TextOffsetX"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getBoundingBoxes("").getTextOffsetY() == jsonData["CvRenderer"]["BoundingBoxes[\"\"].TextOffsetY"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getBoundingBoxes("").getBottomTextOffsetY() == jsonData["CvRenderer"]["BoundingBoxes[\"\"].BottomTextOffsetY"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getBoundingBoxes("").getFontColor() == jsonData["CvRenderer"]["BoundingBoxes[\"\"].FontColor"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getBoundingBoxes("").getFontScale() == (float) jsonData["CvRenderer"]["BoundingBoxes[\"\"].FontScale"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getBoundingBoxes("").getFontThickness() == jsonData["CvRenderer"]["BoundingBoxes[\"\"].FontThickness"]["Default value"]);
        // OSD
        BOOST_TEST(startConfiguration.getCvRenderer().getOsd().getSkipRendering() == jsonData["CvRenderer"]["Osd.SkipRendering"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getOsd().getCorner() == sdk::Corner::TopLeft);
        BOOST_TEST(startConfiguration.getCvRenderer().getOsd().getValues(0) == sdk::OsdValue::Version);
        BOOST_TEST(startConfiguration.getCvRenderer().getOsd().getValues(1) == sdk::OsdValue::StreamId);
        BOOST_TEST(startConfiguration.getCvRenderer().getOsd().getValues(2) == sdk::OsdValue::InputDescription);
        BOOST_TEST(startConfiguration.getCvRenderer().getOsd().getValues(3) == sdk::OsdValue::FrameId);
        BOOST_TEST(startConfiguration.getCvRenderer().getOsd().getValues(4) == sdk::OsdValue::Pts);
        BOOST_TEST(startConfiguration.getCvRenderer().getOsd().getValues(5) == sdk::OsdValue::Fps);
        BOOST_TEST(startConfiguration.getCvRenderer().getOsd().getValues(6) == sdk::OsdValue::Latency);
        BOOST_TEST(startConfiguration.getCvRenderer().getOsd().getValues(7) == sdk::OsdValue::TelemetryPlatform);
        BOOST_TEST(startConfiguration.getCvRenderer().getOsd().getValues(8) == sdk::OsdValue::TelemetryPayload);
        BOOST_TEST(startConfiguration.getCvRenderer().getOsd().getValues(9) == sdk::OsdValue::FrameRegistration);
        BOOST_TEST(startConfiguration.getCvRenderer().getOsd().getMarginX() == jsonData["CvRenderer"]["Osd.MarginX"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getOsd().getMarginY() == jsonData["CvRenderer"]["Osd.MarginY"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getOsd().getLineDistance() == jsonData["CvRenderer"]["Osd.LineDistance"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getOsd().getBackColor() == jsonData["CvRenderer"]["Osd.BackColor"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getOsd().getBackTransparency() == (float) jsonData["CvRenderer"]["Osd.BackTransparency"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getOsd().getFontColor() == jsonData["CvRenderer"]["Osd.FontColor"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getOsd().getFontScale() == (float) jsonData["CvRenderer"]["Osd.FontScale"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getOsd().getFontThickness() == jsonData["CvRenderer"]["Osd.FontThickness"]["Default value"]);
        // Histogram
        BOOST_TEST(startConfiguration.getCvRenderer().getHistogram().getSkipRendering() == jsonData["CvRenderer"]["Histogram.SkipRendering"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getHistogram().getCorner() == sdk::Corner::BottomLeft);
        BOOST_TEST(startConfiguration.getCvRenderer().getHistogram().getMarginX() == jsonData["CvRenderer"]["Histogram.MarginX"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getHistogram().getMarginY() == jsonData["CvRenderer"]["Histogram.MarginY"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getHistogram().getBins() == jsonData["CvRenderer"]["Histogram.Bins"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getHistogram().getWidth() == jsonData["CvRenderer"]["Histogram.Width"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getHistogram().getHeight() == jsonData["CvRenderer"]["Histogram.Height"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getHistogram().getBackColor() == jsonData["CvRenderer"]["Histogram.BackColor"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getHistogram().getBackTransparency() == (float) jsonData["CvRenderer"]["Histogram.BackTransparency"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getHistogram().getColorBefore() == jsonData["CvRenderer"]["Histogram.ColorBefore"]["Default value"]);
        BOOST_TEST(startConfiguration.getCvRenderer().getHistogram().getColorAfter() == jsonData["CvRenderer"]["Histogram.ColorAfter"]["Default value"]);

        /*
         * Preview Module
         */
        BOOST_TEST_MESSAGE("Starting test - Preview Module");
        BOOST_TEST(startConfiguration.getPreviewModule().getEnable() == jsonData["PreviewModule"]["Enable"]["Default value"]);

        /*
         * GstSink
         */
        BOOST_TEST_MESSAGE("Starting test - GstSink");
        BOOST_TEST(startConfiguration.getGstSink().getSink().toString() == jsonData["GstSink"]["Sink"]["Default value"]);
        BOOST_TEST(startConfiguration.getGstSink().getUrl().toString() == sinkStr);
        BOOST_TEST(startConfiguration.getGstSink().getFrameRate() == jsonData["GstSink"]["FrameRate"]["Default value"]);

        // V1.2 NEW TESTS FOR ICD (default values)
        /*
         * DebugModule
         */
//        BOOST_TEST_MESSAGE("Starting test - DebugModule");
//        BOOST_TEST(startConfiguration.getDebugModule().getEnable() == false);

        BOOST_TEST_MESSAGE("Starting test - FramerateController configuration");
        BOOST_TEST(startConfiguration.getFramerateController().getOutputFramerate() == jsonData["FramerateController"]["OutputFramerate"]["Default value"]);

        BOOST_TEST_MESSAGE("Starting test - GroundMwirTrackerRate configuration");
        BOOST_TEST(startConfiguration.getTrackerRate().getOutputFramerate() == jsonData["TrackerRate"]["OutputFramerate"]["Default value"]);

        BOOST_TEST_MESSAGE("Starting test - GroundRgbTrackerRate configuration");
        BOOST_TEST(startConfiguration.getTrackerRate().getOutputFramerate() == jsonData["TrackerRate"]["OutputFramerate"]["Default value"]);
        
}
BOOST_AUTO_TEST_SUITE_END() // NOLINT icd_tests
#endif // DEFAULTS

BOOST_AUTO_TEST_SUITE(icd_tests1) // NOLINT

#ifdef PREPROCESSOR
BOOST_AUTO_TEST_SUITE(preprocessor)
#ifdef ROTATE_ANGLE
BOOST_AUTO_TEST_CASE(rotate_angle){
    BOOST_TEST_MESSAGE("\nStarting preprocessor rotate angle test...");
    rotateAngleTestFunc(sdk::FlowSwitcherFlowId::Unspecified);
}
#endif // ROTATE_ANGLE
#ifdef PREPROCESSOR_ROI
BOOST_AUTO_TEST_CASE(roi){
    BOOST_TEST_MESSAGE("\nStarting preprocessor ROI test...");
    roiTestFunc<typeof(sdk::CvPreprocessorStartStreamConfiguration), size_t>(sdk::FlowSwitcherFlowId::Unspecified);
}
#endif // PREPROCESSOR_ROI
BOOST_AUTO_TEST_SUITE_END() // NOLINT preprocessor
#endif // PREPROCESSOR

#ifdef FLOW_SWITCHER
BOOST_AUTO_TEST_CASE(flow_switcher) { // NOLINT
        //TODO - decide if create also flow_switcher_test_func
        try {

            BOOST_TEST_MESSAGE("\nStarting flow switcher test...");
            /**
             * Update test
             */
            sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
            std::shared_ptr<sdk::Stream> stream = mainPipeline->startStream(startConfiguration);
            waitForStreamStarted(stream);
            sendFrames(stream, 100, nullptr);
            sendFrames(stream, 50,
                       [&stream](uint32_t nFrameId) {
                           if (nFrameId == 10) {
                               BOOST_TEST_MESSAGE("\n" << stream->getConfiguration().getFlowSwitcher().getFlowId());
                               stream->getConfiguration().getFlowSwitcher().setFlowId(sdk::FlowSwitcherFlowId::Mwir);
                               stream->update();
                               BOOST_TEST(stream->getConfiguration().getFlowSwitcher().getFlowId() == sdk::FlowSwitcherFlowId::Mwir);
                           } else if (nFrameId == 20) {
                               BOOST_TEST_MESSAGE("\n" << stream->getConfiguration().getFlowSwitcher().getFlowId());
                               stream->getConfiguration().getFlowSwitcher().setFlowId(sdk::FlowSwitcherFlowId::Rgb);
                               stream->update();
                               BOOST_TEST(stream->getConfiguration().getFlowSwitcher().getFlowId() == sdk::FlowSwitcherFlowId::Rgb);
                           }
                       }
            );
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
            stream.reset();
        }
        catch (std::exception& e) {
            BOOST_TEST((((std::string) e.what()).find("not registered") != std::string::npos || ((std::string) e.what()).find("Deadline Exceeded") != std::string::npos),
                       "Caught unexpected error: " + (std::string) e.what());
            BOOST_TEST_MESSAGE((std::string) e.what());
        }
}
#endif // FLOW_SWITCHER

#ifdef DETECTOR
BOOST_AUTO_TEST_SUITE(detector) // NOLINT
#ifdef DETECTOR_ROI
BOOST_AUTO_TEST_SUITE(detector_roi_start)   // NOLINT
BOOST_AUTO_TEST_CASE(ground_mwir){
    a_strVideoPath = groundMwirVideo;
    roiTestFunc<typeof(sdk::DetectorStartStreamConfiguration), float>(sdk::FlowSwitcherFlowId::Mwir);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}
BOOST_AUTO_TEST_CASE(ground_rgb){
    a_strVideoPath = groundRgbVideo;
    roiTestFunc<typeof(sdk::DetectorStartStreamConfiguration), double>(sdk::FlowSwitcherFlowId::Rgb);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}
BOOST_AUTO_TEST_SUITE_END() // NOLINT detector_roi_start


BOOST_AUTO_TEST_SUITE(detector_roi_update) // NOLINT
BOOST_AUTO_TEST_CASE(ground_mwir){
    a_strVideoPath = groundMwirVideo;
    updateRoiTestFunc<typeof(sdk::DetectorUpdateStreamConfiguration), float>(sdk::FlowSwitcherFlowId::Mwir);
}
BOOST_AUTO_TEST_CASE(ground_rgb) {
    a_strVideoPath = groundRgbVideo;
    updateRoiTestFunc<typeof(sdk::DetectorUpdateStreamConfiguration), double>(sdk::FlowSwitcherFlowId::Rgb);
}
BOOST_AUTO_TEST_SUITE_END() // NOLINT detector_roi_update
#endif // DETECTOR_ROI

#ifdef DETECTOR_GROUPS
BOOST_AUTO_TEST_SUITE(detector_groups) // NOLINT
#ifdef DETECTOR_GROUND_MWIR
    BOOST_AUTO_TEST_SUITE(ground_mwir)
        BOOST_AUTO_TEST_CASE(ground_mwir_threshold){
            a_strVideoPath = groundMwirVideo;
            sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
            std::vector<sdk::String> groups = startConfiguration.getGroundMwirDetector().keysGroups().toVector();
            std::cout << "Thresholds - Ground MWIR - Groups:" << std::endl;
            for (std::string group : groups) {
                std::cout << group << std::endl;
            }
            thresholdTestFunc<typeof(startConfiguration.getGroundMwirDetector()), float>(groups, sdk::FlowSwitcherFlowId::Mwir);
        }
        BOOST_AUTO_TEST_CASE(ground_mwir_min_max){
            a_strVideoPath = groundMwirVideo;
            sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
            std::vector<sdk::String> groups = startConfiguration.getGroundMwirDetector().keysGroups().toVector();
            minMaxTestFunc<typeof(startConfiguration.getGroundMwirDetector()), float>(groups, sdk::FlowSwitcherFlowId::Mwir);
        }
    BOOST_AUTO_TEST_SUITE_END() // NOLINT ground_mwir
#endif // DETECTOR_GROUND_MWIR
#ifdef DETECTOR_GROUND_RGB
    BOOST_AUTO_TEST_SUITE(ground_rgb)
        BOOST_AUTO_TEST_CASE(ground_rgb_threshold){
            a_strVideoPath = groundRgbVideo;
            sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
            std::vector<sdk::String> groups = startConfiguration.getGroundRgbDetector().keysGroups().toVector();
            thresholdTestFunc<typeof(startConfiguration.getGroundRgbDetector()), double>(groups, sdk::FlowSwitcherFlowId::Rgb);
        }
        BOOST_AUTO_TEST_CASE(ground_rgb_min_max){
            a_strVideoPath = groundRgbVideo;
            sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
            std::vector<sdk::String> groups = startConfiguration.getGroundRgbDetector().keysGroups().toVector();
            minMaxTestFunc<typeof(startConfiguration.getGroundRgbDetector()), double>(groups, sdk::FlowSwitcherFlowId::Rgb);
        }
        BOOST_AUTO_TEST_SUITE_END() // NOLINT ground_rgb
#endif // DETECTOR_GROUND_RGB
#ifdef DETECTOR_GROUND_MWIRH
            BOOST_AUTO_TEST_SUITE(ground_mwirh)
                BOOST_AUTO_TEST_CASE(ground_mwirh_threshold){
                    a_strVideoPath = groundMwirVideo;
                    sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
                    std::vector<sdk::String> groups = startConfiguration.getGroundMwirhDetector().keysGroups().toVector();
                    thresholdTestFunc<typeof(startConfiguration.getGroundMwirDetector()), int>(groups, sdk::FlowSwitcherFlowId::MwirH);
                }
                BOOST_AUTO_TEST_CASE(ground_mwirh_min_max){
                    a_strVideoPath = groundMwirVideo;
                    sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
                    std::vector<sdk::String> groups = startConfiguration.getGroundMwirhDetector().keysGroups().toVector();
                    minMaxTestFunc<typeof(startConfiguration.getGroundMwirDetector()), int>(groups, sdk::FlowSwitcherFlowId::MwirH);
                }
            BOOST_AUTO_TEST_SUITE_END() // NOLINT ground_mwirh
#endif // DETECTOR_GROUND_MWIRH
#ifdef DETECTOR_GROUND_RGBH
            BOOST_AUTO_TEST_SUITE(ground_rgbh)
                BOOST_AUTO_TEST_CASE(ground_rgbh_threshold){
                    a_strVideoPath = groundRgbVideo;
                    sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
                    std::vector<sdk::String> groups = startConfiguration.getGroundRgbhDetector().keysGroups().toVector();
                    thresholdTestFunc<typeof(startConfiguration.getGroundRgbDetector()), short>(groups, sdk::FlowSwitcherFlowId::RgbH);
                }
                BOOST_AUTO_TEST_CASE(ground_rgbh_min_max){
                    a_strVideoPath = groundRgbVideo;
                    sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
                    std::vector<sdk::String> groups = startConfiguration.getGroundRgbhDetector().keysGroups().toVector();
                    minMaxTestFunc<typeof(startConfiguration.getGroundRgbDetector()), short>(groups, sdk::FlowSwitcherFlowId::RgbH);
                }
            BOOST_AUTO_TEST_SUITE_END() // NOLINT ground_rgbh
#endif // DETECTOR_GROUND_RGBH
    BOOST_AUTO_TEST_SUITE_END() // NOLINT detector_groups
#endif // DETECTOR_GROUPS
BOOST_AUTO_TEST_SUITE_END() // NOLINT detector
#endif // DETECTOR

#ifdef TRACKER
BOOST_AUTO_TEST_SUITE(tracker)
#ifdef TRACKER_RATE
BOOST_AUTO_TEST_SUITE(tracker_rate)
BOOST_AUTO_TEST_CASE(ground_mwir){
    a_strVideoPath = groundMwirVideo;
    trackerRateTestFunc<float>(sdk::FlowSwitcherFlowId::Mwir);
}
BOOST_AUTO_TEST_CASE(ground_rgb){
    a_strVideoPath = groundRgbVideo;
    trackerRateTestFunc<double>(sdk::FlowSwitcherFlowId::Rgb);
}
BOOST_AUTO_TEST_SUITE_END() // NOLINT tracker_rate
#endif // TRACKER_RATE

#ifdef TRACKER_CONFIGURATION
BOOST_AUTO_TEST_SUITE(tracker_configuration)
BOOST_AUTO_TEST_CASE(ground_mwir_person){
    a_strVideoPath = groundMwirVideo;
    std::cout << "Testing Person tracker" << std::endl;
    trackerTestFunc<double>(sdk::FlowSwitcherFlowId::Mwir);
}
BOOST_AUTO_TEST_CASE(ground_mwir_vehicle){
    a_strVideoPath = groundMwirVideo;
        std::cout << "Testing Vehicle tracker" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    trackerTestFunc<float>(sdk::FlowSwitcherFlowId::Mwir);
}

BOOST_AUTO_TEST_CASE(ground_rgb_person){
    a_strVideoPath = groundRgbVideo;
        std::cout << "Testing Person tracker" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    trackerTestFunc<double>(sdk::FlowSwitcherFlowId::Rgb);
}
BOOST_AUTO_TEST_CASE(ground_rgb_vehicle){
    a_strVideoPath = groundRgbVideo;
        std::cout << "Testing Vehicle tracker" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    trackerTestFunc<float>(sdk::FlowSwitcherFlowId::Rgb);
}

//    BOOST_AUTO_TEST_CASE(ground_mwirh){
//        a_strVideoPath = groundMwirVideo;
//        trackerTestFunc<int>(sdk::FlowSwitcherFlowId::MwirH);
//    }
//    BOOST_AUTO_TEST_CASE(ground_rgbh){
//        a_strVideoPath = groundRgbVideo;
//        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//        trackerTestFunc<short>(sdk::FlowSwitcherFlowId::RgbH);
//    }
BOOST_AUTO_TEST_SUITE_END() // NOLINT tracker_configuration
#endif // TRACKER_CONFIGURATION
BOOST_AUTO_TEST_SUITE_END() // NOLINT tracker
#endif // TRACKER

#ifdef RENDERER
BOOST_AUTO_TEST_SUITE(renderer) // NOLINT
BOOST_AUTO_TEST_CASE(renderer_general) { // NOLINT
        try {
            a_strVideoPath = groundMwirVideo;
            sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
            startConfiguration.getFlowSwitcher().setFlowId(sdk::FlowSwitcherFlowId::Mwir);
            BOOST_TEST_MESSAGE("\nStarting test - CvRenderer General");
            startConfiguration.getCvRenderer().setSkipAllRendering(true);
            startConfiguration.getCvRenderer().setDrawDetections(true);
            startConfiguration.getCvRenderer().setDrawTracks(false);
            startConfiguration.getCvRenderer().setPrintClass(false);
            startConfiguration.getCvRenderer().setPrintScore(true);
            startConfiguration.getCvRenderer().setPrintTrackId(false);
            startConfiguration.getCvRenderer().setColorTrack(false);
            startConfiguration.getCvRenderer().setDrawTrackVelocity(false);
            startConfiguration.getCvRenderer().setTrackVelocityFactor(100);

            BOOST_TEST(startConfiguration.getCvRenderer().getSkipAllRendering() == true);
            BOOST_TEST(startConfiguration.getCvRenderer().getDrawDetections() == true);
            BOOST_TEST(startConfiguration.getCvRenderer().getDrawTracks() == false);
            BOOST_TEST(startConfiguration.getCvRenderer().getPrintClass() == false);
            BOOST_TEST(startConfiguration.getCvRenderer().getPrintScore() == true);
            BOOST_TEST(startConfiguration.getCvRenderer().getPrintTrackId() == false);
            BOOST_TEST(startConfiguration.getCvRenderer().getColorTrack() == false);
            BOOST_TEST(startConfiguration.getCvRenderer().getDrawTrackVelocity() == false);
            BOOST_TEST(startConfiguration.getCvRenderer().getTrackVelocityFactor() == 100);

            std::shared_ptr<sdk::Stream> stream = mainPipeline->startStream(startConfiguration);

            waitForStreamStarted(stream);
//            rendererTestFunc();
            sendFrames(stream, 500, nullptr);
            sendFrames(stream, 200,
                       [&stream](uint32_t nFrameId) {
                           if (nFrameId == 10) {
                               //                   BOOST_TEST_MESSAGE("Frame ID: " + std::to_string(nFrameId));
                               stream->getConfiguration().getCvRenderer().setSkipAllRendering(false);
                               stream->update();
                               BOOST_TEST(stream->getConfiguration().getCvRenderer().getSkipAllRendering() == false);
                           } else if (nFrameId == 20) {
                               //                   BOOST_TEST_MESSAGE("Frame ID: " + std::to_string(nFrameId));
                               stream->getConfiguration().getCvRenderer().setDrawDetections(false);
                               stream->update();
                               BOOST_TEST(stream->getConfiguration().getCvRenderer().getDrawDetections() == false);
                           } else if (nFrameId == 30) {
                               //                   BOOST_TEST_MESSAGE("Frame ID: " + std::to_string(nFrameId));
                               stream->getConfiguration().getCvRenderer().setDrawTracks(true);
                               stream->update();
                               BOOST_TEST(stream->getConfiguration().getCvRenderer().getDrawTracks() == true);
                           } else if (nFrameId == 40) {
                               //                   BOOST_TEST_MESSAGE("Frame ID: " + std::to_string(nFrameId));
                               stream->getConfiguration().getCvRenderer().setPrintClass(true);
                               stream->update();
                               BOOST_TEST(stream->getConfiguration().getCvRenderer().getPrintClass() == true);
                           } else if (nFrameId == 50) {
                               //                   BOOST_TEST_MESSAGE("Frame ID: " + std::to_string(nFrameId));
                               stream->getConfiguration().getCvRenderer().setPrintScore(false);
                               stream->update();
                               BOOST_TEST(stream->getConfiguration().getCvRenderer().getPrintScore() == false);
                           } else if (nFrameId == 60) {
                               //                   BOOST_TEST_MESSAGE("Frame ID: " + std::to_string(nFrameId));
                               stream->getConfiguration().getCvRenderer().setPrintTrackId(true);
                               stream->update();
                               BOOST_TEST(stream->getConfiguration().getCvRenderer().getPrintTrackId() == true);
                           } else if (nFrameId == 70) {
                               //                   BOOST_TEST_MESSAGE("Frame ID: " + std::to_string(nFrameId));
                               stream->getConfiguration().getCvRenderer().setColorTrack(true);
                               stream->update();
                               BOOST_TEST(stream->getConfiguration().getCvRenderer().getColorTrack() == true);
                           } else if (nFrameId == 80) {
                               //                   BOOST_TEST_MESSAGE("Frame ID: " + std::to_string(nFrameId));
                               stream->getConfiguration().getCvRenderer().setDrawTrackVelocity(true);
                               stream->update();
                               BOOST_TEST(stream->getConfiguration().getCvRenderer().getDrawTrackVelocity() == true);
                           } else if (nFrameId == 90) {
                               //                   BOOST_TEST_MESSAGE("Frame ID: " + std::to_string(nFrameId));
                               stream->getConfiguration().getCvRenderer().setTrackVelocityFactor(35.5f);
                               stream->update();
                               BOOST_TEST(stream->getConfiguration().getCvRenderer().getTrackVelocityFactor() == 35.5);
                           }
                       }
            );

            BOOST_TEST_MESSAGE("\nTest finished");
            stream.reset();
        }
        catch (std::exception& e) {
            BOOST_TEST(((std::string) e.what()).find("not registered") != std::string::npos, "Caught unexpected error: " + (std::string) e.what());
        }
}
BOOST_AUTO_TEST_SUITE_END() // NOLINT renderer
#endif // RENDERER
BOOST_AUTO_TEST_SUITE_END() // NOLINT icd_tests1

#ifdef OUTPUT
BOOST_AUTO_TEST_SUITE(output) //NOLINT

    #ifdef OUTPUT_DDS_PUBLISHER
    BOOST_AUTO_TEST_CASE(dds_publisher) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        ddsPublisherEnum = ddsPublisher::Tracks;
        a_strVideoPath = groundRgbVideo;
        BOOST_TEST_MESSAGE("\nDDS Publisher test");
        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        std::shared_ptr<sdk::Stream> stream = mainPipeline->startStream(startConfiguration);
        waitForStreamStarted(stream);
        sendFrames(stream, 50, nullptr);

//        stream.reset();
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
//        waitForStreamStopped(stream);

        ddsPublisherEnum = ddsPublisher::Detections;
        startConfiguration = getStartConfiguration();
        startConfiguration.getTracksPublisher().setSourceData(sdk::PublisherDataType::Detections);
        stream = mainPipeline->startStream(startConfiguration);
        waitForStreamStarted(stream);
        sendFrames(stream, 50, nullptr);

//        stream.reset();
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
//        waitForStreamStopped(stream);

        ddsPublisherEnum = ddsPublisher::Disabled;
        startConfiguration = getStartConfiguration();
        startConfiguration.getTracksPublisher().setSourceData(sdk::PublisherDataType::Disabled);
        stream = mainPipeline->startStream(startConfiguration);
        waitForStreamStarted(stream);
        sendFrames(stream, 50, nullptr);
    }
    #endif // OUTPUT_DDS_PUBLISHER
    #ifdef OUTPUT_FULL_VIDEO
    BOOST_AUTO_TEST_SUITE(full_video) //NOLINT
        BOOST_AUTO_TEST_CASE(ground_mwir){
            testThreshold = true;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            BOOST_TEST_MESSAGE("\nGround MWIR");
            sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
            startConfiguration.getFlowSwitcher().setFlowId(sdk::FlowSwitcherFlowId::Mwir);
            a_strVideoPath = groundMwirVideo;
            std::shared_ptr<sdk::Stream> stream = mainPipeline->startStream(startConfiguration);
            waitForStreamStarted(stream);
            sendFrames(stream, -1, nullptr);
            testThreshold = false;
        }
        BOOST_AUTO_TEST_CASE(ground_rgb){
            testThreshold = true;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            BOOST_TEST_MESSAGE("\nGround RGB");
            sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
            startConfiguration.getFlowSwitcher().setFlowId(sdk::FlowSwitcherFlowId::Rgb);
            a_strVideoPath = groundRgbVideo;
            std::shared_ptr<sdk::Stream> stream = mainPipeline->startStream(startConfiguration);
            waitForStreamStarted(stream);
            sendFrames(stream, -1, nullptr);
            testThreshold = false;
        }
//        BOOST_AUTO_TEST_CASE(ground_mwirh){
//            testThreshold = true;
//            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//            BOOST_TEST_MESSAGE("\nGround MWIR_H");
//            sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
//            startConfiguration.getFlowSwitcher().setFlowId(sdk::FlowSwitcherFlowId::MwirH);
//            a_strVideoPath = groundMwirVideo;
//            std::shared_ptr<sdk::Stream> stream = mainPipeline->startStream(startConfiguration);
//            waitForStreamStarted(stream);
//            sendFrames(stream, -1, nullptr);
//            testThreshold = false;
//        }
//        BOOST_AUTO_TEST_CASE(ground_rgbh){
//            testThreshold = true;
//            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//            BOOST_TEST_MESSAGE("\nGround RGB_H");
//            sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
//            startConfiguration.getFlowSwitcher().setFlowId(sdk::FlowSwitcherFlowId::RgbH);
//            a_strVideoPath = groundRgbVideo;
//            std::shared_ptr<sdk::Stream> stream = mainPipeline->startStream(startConfiguration);
//            waitForStreamStarted(stream);
//            sendFrames(stream, -1, nullptr);
//            testThreshold = false;
//        }

    BOOST_AUTO_TEST_SUITE_END() // NOLINT full_video
    #endif // OUTPUT_FULL_VIDEO

#ifdef OUTPUT_PREVIEW
BOOST_AUTO_TEST_CASE(output_preview) { //NOLINT
    try {

        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration();
        startConfiguration.getPreviewModule().setEnable(true);
        currentStreamError = streamError::PreviewError;
        errorCounter++;
        std::shared_ptr<sdk::Stream> stream = mainPipeline->startStream(startConfiguration);
        waitForStreamStarted(stream);
    }
    catch (const std::exception &e) {
        std::cerr << "Error is: " + (std::string) e.what() << std::endl;
    }
    BOOST_TEST(errorCounter == 0, "Not all expected errors returned! Number of missed errors: " + std::to_string(errorCounter));
}
#endif // OUTPUT_PREVIEW

BOOST_AUTO_TEST_SUITE_END() // NOLINT output
#endif // OUTPUT

#ifdef DEBUG
BOOST_AUTO_TEST_SUITE(debug) // NOLINT
BOOST_AUTO_TEST_CASE(debug_environment) { // NOLINT
        isDebugTest = true;
        std::string settingsFile = "/home/tom/Desktop/merlin_runner/stream_settings.bin";
        sdk::StartStreamConfiguration startConfiguration = getStartConfiguration(settingsFile);
        startConfiguration.getGcSource().getGcParameters(0).getName();
        a_strVideoPath = groundMwirVideo;
        BOOST_TEST(startConfiguration.getFlowSwitcher().getFlowId() == sdk::FlowSwitcherFlowId::Mwir);
        BOOST_TEST(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").getScoreThreshold() == 0.9f);
        BOOST_TEST(startConfiguration.getGroundMwirDetector().getAveragePixelValue(0) == 0.2);
        BOOST_TEST(startConfiguration.getGroundMwirDetector().getPixelValueStandardDeviation(0) == 0.3);
        BOOST_TEST(startConfiguration.getCvRenderer().getOsd().getSkipRendering() == false);
        isDebugTest = false;
    }
BOOST_AUTO_TEST_SUITE_END() // NOLINT debug
#endif // DEBUG

//BOOST_AUTO_TEST_CASE(test_arm){
//    try {
//        sdk::StartStreamConfiguration startConf = getStartConfiguration();
//        startConf.getFlowSwitcher().setFlowId(sdk::FlowSwitcherFlowId::Rgb);
//        groundRgbVideo = "/home/tom/Desktop/sdk_runner/test_videos/Armed/DJI_20221026160239_0001_W.mp4";
//        isArmTest = true;
//        a_strVideoPath = groundRgbVideo;
//        std::shared_ptr<sdk::Stream> stream = mainPipeline->startStream(startConf);
//        waitForStreamStarted(stream);
//        sendFrames(stream, -1, nullptr);
//    }
//    catch(std::exception& e){
//        std::cerr << "Exception= " + (std::string)e.what() << std::endl;
//    }
//}

#ifdef DISCOVERY
BOOST_AUTO_TEST_CASE(discovery){
    int counter = 3;
    // discover running servers
    sdk::Vector<sdk::ServerInfo> vServers = sdk::Pipeline::discover(1000, false);
    std::cout << "Discovered servers:" << std::endl;
    std::cout << "HostName | IP | PORT | Project | Version" << std::endl;
    for (const sdk::ServerInfo& info : vServers.toVector())
    {
        std::cout << info.HostName.toString() << " | " << info.IP.toString() << " | " << info.Port << " | " << info.Project.toString() << " | " << info.Version.toString() << std::endl;
        if (info.IP.toString() == "172.12.10.28" && info.Project.toString() == "Merlin") {
            counter--;
        }
        else if (info.IP.toString() == "172.12.10.153" && info.Project.toString() == "Merlin") {
            counter--;
        }
        else if (info.IP.toString() == "172.12.10.24" && info.Project.toString() == "Meerkat") {
            counter--;
        }
        else {
            continue;
        }
    }

    BOOST_TEST(counter == 0, "Not all QA ip's found!");
}
#endif // DISCOVERY
BOOST_AUTO_TEST_CASE(destroy) { // NOLINT
        mainPipeline.reset();
}


