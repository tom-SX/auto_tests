#include "gtest/gtest.h"
#include "PipelineInterface.h"

#include "merlin_generated_tests.h"
#include "merlin_print_enums.h"
#include "helper.h"
#include "general_tests.h"
#include <thread>
#include <chrono>

using namespace sightx;

namespace general_tests {

// Global variables
std::shared_ptr<sdk::Pipeline> pPipeline;
sdk::StartStreamConfiguration startConfiguration;
std::shared_ptr<sdk::Stream> pStream;
UserData* data;
std::vector<int> vTracks;

/*
Test suits for general tests
*/

// Test suit for TrackerRate
class GeneralGraphStructureTest : public ::testing::Test {
protected:
    void SetUp() override {
        startConfiguration = pPipeline->createStartStreamConfiguration();
        startConfiguration.getRawSource(); // Activate raw source
        pStream = pPipeline->startStream(startConfiguration);
        waitForStreamStarted(pStream, data);
        sendFrames(pStream, 30, data, "",
            [](uint32_t nFrameId) {
                
                if (nFrameId == 10) {
                    std::vector<sdk::EdgeInfo> tmpEdges;
                    std::vector<sdk::EdgeInfo> edges = pStream->getStreamInfo().Edges.toVector();
                    for (auto edge : edges) {
                        auto it = tmpEdges.begin();
                        while (it != tmpEdges.end()) {
                            if (it->In.toString() == edge.In.toString() && it->Out.toString() == edge.Out.toString()) {
                                ADD_FAILURE() << "Duplicated egde: In: " << edge.In.toString() << ", Out: " << edge.Out.toString();
                                break;
                            }
                            it++;
                        }
                        if (it == tmpEdges.end()) {
                            tmpEdges.push_back(edge);
                        }
                        // std::cout << "Edge Active: " << edge.Active << ", In: " << edge.In.toString() << ", Out: " << edge.Out.toString() << std::endl;
                    }
                }

            }
        );
        // pStream.reset();
        // waitForStreamStopped(data);
    }

    void TearDown() override {
        pStream.reset();
        waitForStreamStopped(data);
    }

};
// Test suit for TrackerRate
class GeneralTrackerRateTest : public ::testing::Test {
protected:
    void SetUp() override {
        startConfiguration = pPipeline->createStartStreamConfiguration();
        startConfiguration.getRawSource(); // Activate raw source
        startConfiguration.getTrackerRate().setOutputFramerate(30); // Setting tracker to 30 FPS
        pStream = pPipeline->startStream(startConfiguration);
        waitForStreamStarted(pStream, data);
        sendFrames(pStream, 500, data, "",
            [](uint32_t nFrameId) {
                
                if (nFrameId == 120) {
                    std::vector<sdk::ModuleInfo> modules = pStream->getStreamInfo().Modules.toVector();
                    for (auto module : modules) {
                        if (module.Type == "DeepSortTracker" && module.Name.toString() != "vmd_tracker" && module.Active) {
                            // std::cout << "Module: " << module.Name.toString() << ", FPS: " << module.FPS << ", Settings: 30" << std::endl;
                            EXPECT_LE(std::abs(module.FPS - 30), 2);
                        }
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(200));
                    std::cout << "Setting FPS to 10" << std::endl;
                    pStream->getConfiguration().getTrackerRate().setOutputFramerate(10);
                    pStream->update();
                }

                if (nFrameId == 220) {
                    std::vector<sdk::ModuleInfo> modules = pStream->getStreamInfo().Modules.toVector();
                    for (auto module : modules) {
                        if (module.Type == "DeepSortTracker" && module.Name.toString() != "vmd_tracker" && module.Active) {
                            // std::cout << "Module: " << module.Name.toString() << ", FPS: " << module.FPS << ", Settings: 10" << std::endl;
                            EXPECT_LE(std::abs(module.FPS - 10), 2);
                        }
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(200));
                    std::cout << "Setting FPS to 20" << std::endl;
                    pStream->getConfiguration().getTrackerRate().setOutputFramerate(20);
                    pStream->update();
                }

                if (nFrameId == 400) {
                    std::vector<sdk::ModuleInfo> modules = pStream->getStreamInfo().Modules.toVector();
                    for (auto module : modules) {
                        if (module.Type == "DeepSortTracker" && module.Name.toString() != "vmd_tracker" && module.Active) {
                            // std::cout << "Module: " << module.Name.toString() << ", FPS: " << module.FPS << ", Settings: 20" << std::endl;
                            EXPECT_LE(std::abs(module.FPS - 20), 2);
                        }
                    }
                }

            }
        );
    }

    void TearDown() override {
        pStream.reset();
        waitForStreamStopped(data);
    }

};

// Setters
void setPipeline(std::shared_ptr<sdk::Pipeline> new_pipeline) {
    pPipeline = new_pipeline;
}

void setUserData(UserData* new_data) {
    data = new_data;
}

/**
 * Thresholds range test - called within onFrameResults callback. Testing whether the actual score is greater than or equal to the threshold
 * Params: 
 * score_value (float) - The actual score of the tested track
 * threshold_value (float) - The threshold of the corresponding class within the tested detector
 */
void RunThresholdInRangeTest(float score_value, float threshold_value, const std::string class_name_str, int track_id) {
    class ThresholdInRangeTest : public ::testing::Test {
    public:
        float score;
        float threshold;
        float trackerThreshold = 0;
        int track_id;

        ThresholdInRangeTest(float score, float threshold, std::string className, int track_id)
            : score(score), threshold(threshold), track_id(track_id) {
                auto it = trackerThresholdMap.find(className + "Tracker");
                if (it != trackerThresholdMap.end()) {
                    trackerThreshold = trackerThresholdMap[className + "Tracker"];
                    // std::cout << "Added tracker threshold --> " << className + "Tracker: " << trackerThreshold << std::endl;
                }
            }

        void TestBody() override {
            EXPECT_GE(score, threshold);
            if (std::find(vTracks.begin(), vTracks.end(), track_id) == vTracks.end()) {
                // std::cout << "Track not checked: " << track_id << std::endl;
                EXPECT_GE(score, trackerThreshold);
                vTracks.push_back(track_id);
            }
            // else {
            //     std::cout << "Track already tested: " << track_id << std::endl;
            // }
            
        }
    };
    ThresholdInRangeTest test(score_value, threshold_value, class_name_str, track_id);
    test.TestBody();
}

// Testing full video files stream run
TEST_P(VideoStreams, FlowTest) {
    sdk::FlowSwitcherFlowId flowId = GetParam();
    startConfiguration = pPipeline->createStartStreamConfiguration();
    startConfiguration.getRawSource();
    startConfiguration.getFlowSwitcher().setFlowId(flowId);
    startConfiguration.getGstSink().setUrl("rtsp://172.12.10.51:8554/auto_tests");
    pStream = pPipeline->startStream(startConfiguration);
    waitForStreamStarted(pStream, data);
    sendFrames(pStream, -1, data);
    pStream.reset();
    waitForStreamStopped(data);
}

TEST(ContinuousTest, Run5MinTest) {
    startConfiguration = pPipeline->createStartStreamConfiguration();
    startConfiguration.getRawSource();
    startConfiguration.getGstSink().setUrl("rtsp://172.12.10.51:8554/auto_tests");
    pStream = pPipeline->startStream(startConfiguration);
    waitForStreamStarted(pStream, data);
    sendFramesBySeconds(pStream, 5 * 60, data, "", 
    [](double sec) {
        if ((int) sec == 30) {
            pStream->getConfiguration().getFlowSwitcher().setFlowId(availableFlows[1 % availableFlows.size()]);
            pStream->update();
        }
        else if ((int) sec == 45) {
            pStream->getConfiguration().getVmd().setEnable(true);
            pStream->update();
        }
        else if ((int) sec == 120) {
            pStream->getConfiguration().getVmd().setEnable(false);
            pStream->getConfiguration().getFlowSwitcher().setFlowId(availableFlows[2 % availableFlows.size()]);
            pStream->update();
        }
        else if ((int) sec == 130) {
            pStream->getConfiguration().getCvRenderer().setDrawDetections(true);
            pStream->getConfiguration().getCvRenderer().setDrawTracks(false);
            pStream->update();
        }
        else if ((int) sec == 140) {
            pStream->getConfiguration().getCvRenderer().setSkipAllRendering(true);
            pStream->update();
        }
        else if ((int) sec == 145) {
            pStream->getConfiguration().getCvRenderer().setSkipAllRendering(false);
            pStream->getConfiguration().getCvRenderer().setDrawDetections(false);
            pStream->getConfiguration().getCvRenderer().setDrawTracks(true);
            pStream->update();
        }
    });
    pStream.reset();
    waitForStreamStopped(data);
}

TEST(ContinuousTest, Run10MinTest) {
    startConfiguration = pPipeline->createStartStreamConfiguration();
    startConfiguration.getRawSource();
    startConfiguration.getGstSink().setUrl("rtsp://172.12.10.51:8554/auto_tests");
    pStream = pPipeline->startStream(startConfiguration);
    waitForStreamStarted(pStream, data);
    sendFramesBySeconds(pStream, 10 * 60, data, "", 
    [](double sec) {
        if ((int) sec == 30) {
            pStream->getConfiguration().getFlowSwitcher().setFlowId(availableFlows[1 % availableFlows.size()]);
            pStream->update();
        }
        else if ((int) sec == 45) {
            pStream->getConfiguration().getVmd().setEnable(true);
            pStream->update();
        }
        else if ((int) sec == 120) {
            pStream->getConfiguration().getVmd().setEnable(false);
            pStream->getConfiguration().getFlowSwitcher().setFlowId(availableFlows[2 % availableFlows.size()]);
            pStream->update();
        }
        else if ((int) sec == 130) {
            pStream->getConfiguration().getCvRenderer().setDrawDetections(true);
            pStream->getConfiguration().getCvRenderer().setDrawTracks(false);
            pStream->update();
        }
        else if ((int) sec == 140) {
            pStream->getConfiguration().getCvRenderer().setSkipAllRendering(true);
            pStream->update();
        }
        else if ((int) sec == 145) {
            pStream->getConfiguration().getCvRenderer().setSkipAllRendering(false);
            pStream->getConfiguration().getCvRenderer().setDrawDetections(false);
            pStream->getConfiguration().getCvRenderer().setDrawTracks(true);
            pStream->update();
        }
        else if ((int) sec == 322) {
            pStream->getConfiguration().getTrackerRate().setOutputFramerate(12);
            pStream->update();
        }
        else if ((int) sec == 360) {
            pStream->getConfiguration().getTrackerRate().setOutputFramerate(25);
            pStream->update();
        }
        else if ((int) sec == 450) {
            pStream->getConfiguration().getTracksPublisher().setSourceData(sdk::PublisherDataType::Detections);
            pStream->update();
        }
        else if ((int) sec == 480) {
            pStream->getConfiguration().getTracksPublisher().setSourceData(sdk::PublisherDataType::Tracks);
            pStream->update();
        }
        else if ((int) sec == 524) {
            pStream->getConfiguration().getFlowSwitcher().setFlowId(sdk::FlowSwitcherFlowId::Sot);
            pStream->update();
        }
        else if ((int) sec == 530) {
            pStream->getSingleObjectTracker().TrackBoundingBox(200, 200, 220, 230);
            // pStream->update();
        }
    });
    pStream.reset();
    waitForStreamStopped(data);
}

TEST(ContinuousTest, Run4HoursTest) {
    startConfiguration = pPipeline->createStartStreamConfiguration();
    startConfiguration.getRawSource();
    startConfiguration.getGstSink().setUrl("rtsp://172.12.10.51:8554/auto_tests");
    startConfiguration.getFlowSwitcher().setFlowId(sdk::FlowSwitcherFlowId::Mwir);
    pStream = pPipeline->startStream(startConfiguration);
    waitForStreamStarted(pStream, data);
    sendFramesBySeconds(pStream, 4 * 60 * 60, data, "", 
    [](double sec) {
        if (((int) sec % 30) == 0) {
            pStream->getConfiguration().getFlowSwitcher().setFlowId(availableFlows[1 % availableFlows.size()]);
            pStream->update();
            EXPECT_EQ(pStream->getConfiguration().getFlowSwitcher().getFlowId(), availableFlows[1 % availableFlows.size()]);
        }
        else if (((int) sec % 45) == 0) {
            pStream->getConfiguration().getVmd().setEnable(true);
            pStream->update();
            EXPECT_EQ(pStream->getConfiguration().getVmd().getEnable(), true);
        }
        else if (((int) sec % 120) == 0) {
            pStream->getConfiguration().getVmd().setEnable(false);
            pStream->getConfiguration().getFlowSwitcher().setFlowId(availableFlows[2 % availableFlows.size()]);
            pStream->update();
            EXPECT_EQ(pStream->getConfiguration().getVmd().getEnable(), false);
            EXPECT_EQ(pStream->getConfiguration().getFlowSwitcher().getFlowId(), availableFlows[2 % availableFlows.size()]);
        }
        else if (((int) sec % 130) == 0) {
            pStream->getConfiguration().getCvRenderer().setDrawDetections(true);
            pStream->getConfiguration().getCvRenderer().setDrawTracks(false);
            pStream->update();
            EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getDrawDetections(), true);
            EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getDrawTracks(), false);
        }
        else if (((int) sec % 140) == 0) {
            pStream->getConfiguration().getCvRenderer().setSkipAllRendering(true);
            pStream->update();
            EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getSkipAllRendering(), true);
        }
        else if (((int) sec % 145) == 0) {
            pStream->getConfiguration().getCvRenderer().setSkipAllRendering(false);
            pStream->getConfiguration().getCvRenderer().setDrawDetections(false);
            pStream->getConfiguration().getCvRenderer().setDrawTracks(true);
            pStream->update();
            EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getSkipAllRendering(), false);
            EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getDrawDetections(), false);
            EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getDrawTracks(), true);
        }
        else if (((int) sec % 322) == 0) {
            pStream->getConfiguration().getTrackerRate().setOutputFramerate(12);
            pStream->update();
            EXPECT_EQ(pStream->getConfiguration().getTrackerRate().getOutputFramerate(), 12);
        }
        else if (((int) sec % 360) == 0) {
            pStream->getConfiguration().getTrackerRate().setOutputFramerate(25);
            pStream->update();
            EXPECT_EQ(pStream->getConfiguration().getTrackerRate().getOutputFramerate(), 25);
        }
        else if (((int) sec % 450) == 0) {
            pStream->getConfiguration().getTracksPublisher().setSourceData(sdk::PublisherDataType::Detections);
            pStream->update();
            EXPECT_EQ(pStream->getConfiguration().getTracksPublisher().getSourceData(), sdk::PublisherDataType::Detections);
        }
        else if (((int) sec % 480) == 0) {
            pStream->getConfiguration().getTracksPublisher().setSourceData(sdk::PublisherDataType::Tracks);
            pStream->update();
            EXPECT_EQ(pStream->getConfiguration().getTracksPublisher().getSourceData(), sdk::PublisherDataType::Tracks);
        }
        else if (((int) sec % 524) == 0) {
            pStream->getConfiguration().getFlowSwitcher().setFlowId(sdk::FlowSwitcherFlowId::Sot);
            pStream->update();
            EXPECT_EQ(pStream->getConfiguration().getFlowSwitcher().getFlowId(), sdk::FlowSwitcherFlowId::Sot);
        }
        else if (((int) sec % 530) == 0) {
            pStream->getSingleObjectTracker().TrackBoundingBox(200, 200, 220, 230);
            // pStream->update();
        }
    });
    pStream.reset();
    waitForStreamStopped(data);
}

TEST_F(GeneralTrackerRateTest, TrackerRateOutput) {}
TEST_F(GeneralGraphStructureTest, GraphEdgeDuplications) {}

}