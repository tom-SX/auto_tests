#include "gtest/gtest.h"
#include "PipelineInterface.h"
#include <map>
#include <string>

#include "merlin_generated_tests.h"
#include "merlin_print_enums.h"
#include "helper.h"
#include "update_tests_flag.h"
#include "general_tests.h"

using namespace sightx;

namespace generated_tests {

std::shared_ptr<sdk::Pipeline> pPipeline;

sdk::StartStreamConfiguration startConfiguration;
sdk::StartStreamConfiguration tmpStartConfiguration;
std::shared_ptr<sdk::Stream> pStream;
UserData* data;

std::map<sdk::FlowSwitcherFlowId, std::string> videos = {
   {sdk::FlowSwitcherFlowId::Rgb, "/home/tom/Desktop/merlin_runner/test_videos/ground_RGB/Caesarea_1405_0003_W_CMOS_FOV83_rgb/%05d.png"},
   {sdk::FlowSwitcherFlowId::Mwir, "/home/tom/Desktop/merlin_runner/test_videos/ground_MWIR/Caesarea_1500_0007_T_VOx_FOV40_lwir/%05d.png"},
};

std::map<sdk::FlowSwitcherFlowId, sdk::PixelFormat> pixels = {
    {sdk::FlowSwitcherFlowId::Rgb, sdk::PixelFormat::BGR8},
    {sdk::FlowSwitcherFlowId::Mwir, sdk::PixelFormat::GRAY8}
};

std::map<std::string, std::map<std::string, float>> tMap {
    {"GroundRgbDetector", {{"Person", 0.1f}, {"Vehicle", 0.1f}}},
    {"GroundMwirDetector", {{"Person", 0.1f}, {"Vehicle", 0.1f}}},
};
std::map<std::string, float> trackerMap {
    {"PersonTracker", 0.5},
    {"VehicleTracker", 0.2},
    {"VmdTracker", 0.2},
};
void setPipeline(std::shared_ptr<sdk::Pipeline> new_pipeline) {
    pPipeline = new_pipeline;
    setVideoPaths(videos);
    setPixelFormats(pixels);
    setThresholdMap(tMap);
    setTrackerThresholdMap(trackerMap);
}

void setUserData(UserData* new_data) {
    data = new_data;
}

// Test suit for FramerateController
class FramerateControllerTest : public ::testing::Test {
protected:
    void SetUp() override {
        startConfiguration = pPipeline->createStartStreamConfiguration();
        if (::testing::GTEST_FLAG(update_tests)) {
            tmpStartConfiguration = startConfiguration;
            tmpStartConfiguration.getRawSource(); // Touch Raw Source
            tmpStartConfiguration.getRawSource().setReadTimeoutInSec(0); // Wait forever
            pStream = pPipeline->startStream(tmpStartConfiguration);
            waitForStreamStarted(pStream, data);
        }

    }

    void TearDown() override {
        if (::testing::GTEST_FLAG(update_tests)) {
            pStream.reset();
            waitForStreamStopped(data);
        }

    }

};

    // Test for OutputFramerate in FramerateController
    TEST_F(FramerateControllerTest, FramerateController_OutputFramerateDefault) {
        EXPECT_EQ(startConfiguration.getFramerateController().getOutputFramerate(), 0);
    }

    TEST_F(FramerateControllerTest, Update_FramerateController_OutputFramerateDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getFramerateController().getOutputFramerate(), 0);
    }

    TEST_F(FramerateControllerTest, FramerateController_OutputFramerateRandom) {
        startConfiguration.getFramerateController().setOutputFramerate(87);
        EXPECT_EQ(startConfiguration.getFramerateController().getOutputFramerate(), 87);
    }

    TEST_F(FramerateControllerTest, Update_FramerateController_OutputFramerateRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getFramerateController().setOutputFramerate(87);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getFramerateController().getOutputFramerate(), 87);
    }

// Test suit for Preprocessor
class PreprocessorTest : public ::testing::Test {
protected:
    void SetUp() override {
        startConfiguration = pPipeline->createStartStreamConfiguration();
    }

};

    // Test for Width in Preprocessor
    TEST_F(PreprocessorTest, Preprocessor_WidthDefault) {
        EXPECT_EQ(startConfiguration.getPreprocessor().getWidth(), 0);
    }

    TEST_F(PreprocessorTest, Preprocessor_WidthRandom) {
        startConfiguration.getPreprocessor().setWidth(571);
        EXPECT_EQ(startConfiguration.getPreprocessor().getWidth(), 571);
    }

    // Test for Height in Preprocessor
    TEST_F(PreprocessorTest, Preprocessor_HeightDefault) {
        EXPECT_EQ(startConfiguration.getPreprocessor().getHeight(), 0);
    }

    TEST_F(PreprocessorTest, Preprocessor_HeightRandom) {
        startConfiguration.getPreprocessor().setHeight(351);
        EXPECT_EQ(startConfiguration.getPreprocessor().getHeight(), 351);
    }

    // Test for KeepAspectRatio in Preprocessor
    TEST_F(PreprocessorTest, Preprocessor_KeepAspectRatioDefault) {
        EXPECT_EQ(startConfiguration.getPreprocessor().getKeepAspectRatio(), true);
    }

    TEST_F(PreprocessorTest, Preprocessor_KeepAspectRatioRandom) {
        startConfiguration.getPreprocessor().setKeepAspectRatio(false);
        EXPECT_EQ(startConfiguration.getPreprocessor().getKeepAspectRatio(), false);
    }

    // Test for RotateAngle in Preprocessor
    TEST_F(PreprocessorTest, Preprocessor_RotateAngleDefault) {
        EXPECT_EQ(startConfiguration.getPreprocessor().getRotateAngle(), 0);
    }

    TEST_F(PreprocessorTest, Preprocessor_RotateAngleRandom) {
        startConfiguration.getPreprocessor().setRotateAngle(166);
        EXPECT_EQ(startConfiguration.getPreprocessor().getRotateAngle(), 166);
    }

    // Test for X in Preprocessor
    TEST_F(PreprocessorTest, Preprocessor_Roi_XDefault) {
        EXPECT_EQ(startConfiguration.getPreprocessor().getRoi().getX(), 0);
    }

    TEST_F(PreprocessorTest, Preprocessor_Roi_XRandom) {
        startConfiguration.getPreprocessor().getRoi().setX(4400);
        EXPECT_EQ(startConfiguration.getPreprocessor().getRoi().getX(), 4400);
    }

    // Test for Y in Preprocessor
    TEST_F(PreprocessorTest, Preprocessor_Roi_YDefault) {
        EXPECT_EQ(startConfiguration.getPreprocessor().getRoi().getY(), 0);
    }

    TEST_F(PreprocessorTest, Preprocessor_Roi_YRandom) {
        startConfiguration.getPreprocessor().getRoi().setY(7782);
        EXPECT_EQ(startConfiguration.getPreprocessor().getRoi().getY(), 7782);
    }

    // Test for Width in Preprocessor
    TEST_F(PreprocessorTest, Preprocessor_Roi_WidthDefault) {
        EXPECT_EQ(startConfiguration.getPreprocessor().getRoi().getWidth(), 0);
    }

    TEST_F(PreprocessorTest, Preprocessor_Roi_WidthRandom) {
        startConfiguration.getPreprocessor().getRoi().setWidth(474);
        EXPECT_EQ(startConfiguration.getPreprocessor().getRoi().getWidth(), 474);
    }

    // Test for Height in Preprocessor
    TEST_F(PreprocessorTest, Preprocessor_Roi_HeightDefault) {
        EXPECT_EQ(startConfiguration.getPreprocessor().getRoi().getHeight(), 0);
    }

    TEST_F(PreprocessorTest, Preprocessor_Roi_HeightRandom) {
        startConfiguration.getPreprocessor().getRoi().setHeight(744);
        EXPECT_EQ(startConfiguration.getPreprocessor().getRoi().getHeight(), 744);
    }

// Test suit for VideoPassthrough
class VideoPassthroughTest : public ::testing::Test {
protected:
    void SetUp() override {
        startConfiguration = pPipeline->createStartStreamConfiguration();
        if (::testing::GTEST_FLAG(update_tests)) {
            tmpStartConfiguration = startConfiguration;
            tmpStartConfiguration.getRawSource(); // Touch Raw Source
            tmpStartConfiguration.getRawSource().setReadTimeoutInSec(0); // Wait forever
            pStream = pPipeline->startStream(tmpStartConfiguration);
            waitForStreamStarted(pStream, data);
        }

    }

    void TearDown() override {
        if (::testing::GTEST_FLAG(update_tests)) {
            pStream.reset();
            waitForStreamStopped(data);
        }

    }

};

    // Test for FlowId in VideoPassthrough
    TEST_F(VideoPassthroughTest, VideoPassthrough_FlowIdDefault) {
        EXPECT_EQ(startConfiguration.getVideoPassthrough().getFlowId(), sdk::VideoPassthroughFlow::Off);
    }

    TEST_F(VideoPassthroughTest, Update_VideoPassthrough_FlowIdDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getVideoPassthrough().getFlowId(), sdk::VideoPassthroughFlow::Off);
    }

    // Test for FlowId in VideoPassthrough (enum)
    TEST_F(VideoPassthroughTest, VideoPassthrough_FlowIdEnum) {
        startConfiguration.getVideoPassthrough().setFlowId(sdk::VideoPassthroughFlow::On);
        EXPECT_EQ(startConfiguration.getVideoPassthrough().getFlowId(), sdk::VideoPassthroughFlow::On) << testing::PrintToString(sdk::VideoPassthroughFlow::On);
        startConfiguration.getVideoPassthrough().setFlowId(sdk::VideoPassthroughFlow::Off);
        EXPECT_EQ(startConfiguration.getVideoPassthrough().getFlowId(), sdk::VideoPassthroughFlow::Off) << testing::PrintToString(sdk::VideoPassthroughFlow::Off);
    }

    TEST_F(VideoPassthroughTest, Update_VideoPassthrough_FlowIdEnum) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getVideoPassthrough().setFlowId(sdk::VideoPassthroughFlow::On);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVideoPassthrough().getFlowId(), sdk::VideoPassthroughFlow::On) << testing::PrintToString(sdk::VideoPassthroughFlow::On);
        pStream->getConfiguration().getVideoPassthrough().setFlowId(sdk::VideoPassthroughFlow::Off);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVideoPassthrough().getFlowId(), sdk::VideoPassthroughFlow::Off) << testing::PrintToString(sdk::VideoPassthroughFlow::Off);
    }

// Test suit for FrameRegisterImage
class FrameRegisterImageTest : public ::testing::Test {
protected:
    void SetUp() override {
        startConfiguration = pPipeline->createStartStreamConfiguration();
        if (::testing::GTEST_FLAG(update_tests)) {
            tmpStartConfiguration = startConfiguration;
            tmpStartConfiguration.getRawSource(); // Touch Raw Source
            tmpStartConfiguration.getRawSource().setReadTimeoutInSec(0); // Wait forever
            pStream = pPipeline->startStream(tmpStartConfiguration);
            waitForStreamStarted(pStream, data);
        }

    }

    void TearDown() override {
        if (::testing::GTEST_FLAG(update_tests)) {
            pStream.reset();
            waitForStreamStopped(data);
        }

    }

};

    // Test for Enable in FrameRegisterImage
    TEST_F(FrameRegisterImageTest, FrameRegisterImage_EnableDefault) {
        EXPECT_EQ(startConfiguration.getFrameRegisterImage().getEnable(), true);
    }

    TEST_F(FrameRegisterImageTest, Update_FrameRegisterImage_EnableDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getFrameRegisterImage().getEnable(), true);
    }

    TEST_F(FrameRegisterImageTest, FrameRegisterImage_EnableRandom) {
        startConfiguration.getFrameRegisterImage().setEnable(true);
        EXPECT_EQ(startConfiguration.getFrameRegisterImage().getEnable(), true);
    }

    TEST_F(FrameRegisterImageTest, Update_FrameRegisterImage_EnableRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getFrameRegisterImage().setEnable(true);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getFrameRegisterImage().getEnable(), true);
    }

// Test suit for FlowSwitcher
class FlowSwitcherTest : public ::testing::Test {
protected:
    void SetUp() override {
        startConfiguration = pPipeline->createStartStreamConfiguration();
        if (::testing::GTEST_FLAG(update_tests)) {
            tmpStartConfiguration = startConfiguration;
            tmpStartConfiguration.getRawSource(); // Touch Raw Source
            tmpStartConfiguration.getRawSource().setReadTimeoutInSec(0); // Wait forever
            pStream = pPipeline->startStream(tmpStartConfiguration);
            waitForStreamStarted(pStream, data);
        }

    }

    void TearDown() override {
        if (::testing::GTEST_FLAG(update_tests)) {
            pStream.reset();
            waitForStreamStopped(data);
        }

    }

};

    // Test for FlowId in FlowSwitcher
    TEST_F(FlowSwitcherTest, FlowSwitcher_FlowIdDefault) {
        EXPECT_EQ(startConfiguration.getFlowSwitcher().getFlowId(), sdk::FlowSwitcherFlowId::Rgb);
    }

    TEST_F(FlowSwitcherTest, Update_FlowSwitcher_FlowIdDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getFlowSwitcher().getFlowId(), sdk::FlowSwitcherFlowId::Rgb);
    }

    // Test for FlowId in FlowSwitcher (enum)
    TEST_F(FlowSwitcherTest, FlowSwitcher_FlowIdEnum) {
        startConfiguration.getFlowSwitcher().setFlowId(sdk::FlowSwitcherFlowId::Rgb);
        EXPECT_EQ(startConfiguration.getFlowSwitcher().getFlowId(), sdk::FlowSwitcherFlowId::Rgb) << testing::PrintToString(sdk::FlowSwitcherFlowId::Rgb);
        startConfiguration.getFlowSwitcher().setFlowId(sdk::FlowSwitcherFlowId::Mwir);
        EXPECT_EQ(startConfiguration.getFlowSwitcher().getFlowId(), sdk::FlowSwitcherFlowId::Mwir) << testing::PrintToString(sdk::FlowSwitcherFlowId::Mwir);
        startConfiguration.getFlowSwitcher().setFlowId(sdk::FlowSwitcherFlowId::Sot);
        EXPECT_EQ(startConfiguration.getFlowSwitcher().getFlowId(), sdk::FlowSwitcherFlowId::Sot) << testing::PrintToString(sdk::FlowSwitcherFlowId::Sot);
    }

    TEST_F(FlowSwitcherTest, Update_FlowSwitcher_FlowIdEnum) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getFlowSwitcher().setFlowId(sdk::FlowSwitcherFlowId::Rgb);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getFlowSwitcher().getFlowId(), sdk::FlowSwitcherFlowId::Rgb) << testing::PrintToString(sdk::FlowSwitcherFlowId::Rgb);
        pStream->getConfiguration().getFlowSwitcher().setFlowId(sdk::FlowSwitcherFlowId::Mwir);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getFlowSwitcher().getFlowId(), sdk::FlowSwitcherFlowId::Mwir) << testing::PrintToString(sdk::FlowSwitcherFlowId::Mwir);
        pStream->getConfiguration().getFlowSwitcher().setFlowId(sdk::FlowSwitcherFlowId::Sot);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getFlowSwitcher().getFlowId(), sdk::FlowSwitcherFlowId::Sot) << testing::PrintToString(sdk::FlowSwitcherFlowId::Sot);
    }

// Test suit for LockedOnConfiguration
class LockedOnConfigurationTest : public ::testing::Test {
protected:
    void SetUp() override {
        startConfiguration = pPipeline->createStartStreamConfiguration();
        if (::testing::GTEST_FLAG(update_tests)) {
            tmpStartConfiguration = startConfiguration;
            tmpStartConfiguration.getRawSource(); // Touch Raw Source
            tmpStartConfiguration.getRawSource().setReadTimeoutInSec(0); // Wait forever
            pStream = pPipeline->startStream(tmpStartConfiguration);
            waitForStreamStarted(pStream, data);
        }

    }

    void TearDown() override {
        if (::testing::GTEST_FLAG(update_tests)) {
            pStream.reset();
            waitForStreamStopped(data);
        }

    }

};

    // Test for LockOnTrack in LockedOnConfiguration
    TEST_F(LockedOnConfigurationTest, LockedOnConfiguration_LockOnTrackDefault) {
        EXPECT_EQ(startConfiguration.getLockedOnConfiguration().getLockOnTrack(), -1);
    }

    TEST_F(LockedOnConfigurationTest, Update_LockedOnConfiguration_LockOnTrackDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getLockedOnConfiguration().getLockOnTrack(), -1);
    }

    TEST_F(LockedOnConfigurationTest, LockedOnConfiguration_LockOnTrackRandom) {
        startConfiguration.getLockedOnConfiguration().setLockOnTrack(825);
        EXPECT_EQ(startConfiguration.getLockedOnConfiguration().getLockOnTrack(), 825);
    }

    TEST_F(LockedOnConfigurationTest, Update_LockedOnConfiguration_LockOnTrackRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getLockedOnConfiguration().setLockOnTrack(825);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getLockedOnConfiguration().getLockOnTrack(), 825);
    }

// Test suit for GroundRgbDetector
class GroundRgbDetectorTest : public ::testing::Test {
protected:
    void SetUp() override {
        startConfiguration = pPipeline->createStartStreamConfiguration();
        startConfiguration.getGroundRgbDetector().appendAveragePixelValue(0);
        startConfiguration.getGroundRgbDetector().appendPixelValueStandardDeviation(0);

        if (::testing::GTEST_FLAG(update_tests)) {
            tmpStartConfiguration = startConfiguration;
            tmpStartConfiguration.getRawSource(); // Touch Raw Source
            tmpStartConfiguration.getRawSource().setReadTimeoutInSec(0); // Wait forever
            pStream = pPipeline->startStream(tmpStartConfiguration);
            waitForStreamStarted(pStream, data);
        }

    }

    void TearDown() override {
        if (::testing::GTEST_FLAG(update_tests)) {
            pStream.reset();
            waitForStreamStopped(data);
        }

    }

};

    // Test for X in GroundRgbDetector
    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Roi_XDefault) {
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getRoi().getX(), 0);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Roi_XDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getRoi().getX(), 0);
    }

    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Roi_XRandom) {
        startConfiguration.getGroundRgbDetector().getRoi().setX(7298);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getRoi().getX(), 7298);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Roi_XRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbDetector().getRoi().setX(7298);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getRoi().getX(), 7298);
    }

    // Test for Y in GroundRgbDetector
    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Roi_YDefault) {
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getRoi().getY(), 0);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Roi_YDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getRoi().getY(), 0);
    }

    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Roi_YRandom) {
        startConfiguration.getGroundRgbDetector().getRoi().setY(7236);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getRoi().getY(), 7236);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Roi_YRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbDetector().getRoi().setY(7236);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getRoi().getY(), 7236);
    }

    // Test for Width in GroundRgbDetector
    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Roi_WidthDefault) {
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getRoi().getWidth(), 0);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Roi_WidthDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getRoi().getWidth(), 0);
    }

    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Roi_WidthRandom) {
        startConfiguration.getGroundRgbDetector().getRoi().setWidth(4127);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getRoi().getWidth(), 4127);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Roi_WidthRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbDetector().getRoi().setWidth(4127);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getRoi().getWidth(), 4127);
    }

    // Test for Height in GroundRgbDetector
    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Roi_HeightDefault) {
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getRoi().getHeight(), 0);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Roi_HeightDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getRoi().getHeight(), 0);
    }

    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Roi_HeightRandom) {
        startConfiguration.getGroundRgbDetector().getRoi().setHeight(1685);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getRoi().getHeight(), 1685);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Roi_HeightRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbDetector().getRoi().setHeight(1685);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getRoi().getHeight(), 1685);
    }

    // Test for ScoreThreshold_Person_ in GroundRgbDetector
    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Groups__Person___ScoreThreshold_Person_Default) {
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Person").getScoreThreshold(), 0.1f);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Groups__Person___ScoreThreshold_Person_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").getScoreThreshold(), 0.1f);
    }

    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Groups__Person___ScoreThreshold_Person_Range) {
        startConfiguration.getGroundRgbDetector().getGroups("Person").setScoreThreshold(0.1f);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Person").getScoreThreshold(), 0.1f);
        startConfiguration.getGroundRgbDetector().getGroups("Person").setScoreThreshold(1.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Person").getScoreThreshold(), 1.0f);
        EXPECT_THROW(startConfiguration.getGroundRgbDetector().getGroups("Person").setScoreThreshold(0.1f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundRgbDetector().getGroups("Person").setScoreThreshold(1.0f + 1), std::exception);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Groups__Person___ScoreThreshold_Person_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").setScoreThreshold(0.1f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").getScoreThreshold(), 0.1f);
        pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").setScoreThreshold(1.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").getScoreThreshold(), 1.0f);
    }

    // Test for MinWidth_Person_ in GroundRgbDetector
    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Groups__Person___MinWidth_Person_Default) {
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Person").getMinWidth(), 0.0f);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Groups__Person___MinWidth_Person_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").getMinWidth(), 0.0f);
    }

    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Groups__Person___MinWidth_Person_Range) {
        startConfiguration.getGroundRgbDetector().getGroups("Person").setMinWidth(0.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Person").getMinWidth(), 0.0f);
        startConfiguration.getGroundRgbDetector().getGroups("Person").setMinWidth(8192.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Person").getMinWidth(), 8192.0f);
        EXPECT_THROW(startConfiguration.getGroundRgbDetector().getGroups("Person").setMinWidth(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundRgbDetector().getGroups("Person").setMinWidth(8192.0f + 1), std::exception);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Groups__Person___MinWidth_Person_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").setMinWidth(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").getMinWidth(), 0.0f);
        pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").setMinWidth(8192.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").getMinWidth(), 8192.0f);
    }

    // Test for MaxWidth_Person_ in GroundRgbDetector
    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Groups__Person___MaxWidth_Person_Default) {
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Person").getMaxWidth(), 1000.0f);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Groups__Person___MaxWidth_Person_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").getMaxWidth(), 1000.0f);
    }

    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Groups__Person___MaxWidth_Person_Range) {
        startConfiguration.getGroundRgbDetector().getGroups("Person").setMaxWidth(0.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Person").getMaxWidth(), 0.0f);
        startConfiguration.getGroundRgbDetector().getGroups("Person").setMaxWidth(8192.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Person").getMaxWidth(), 8192.0f);
        EXPECT_THROW(startConfiguration.getGroundRgbDetector().getGroups("Person").setMaxWidth(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundRgbDetector().getGroups("Person").setMaxWidth(8192.0f + 1), std::exception);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Groups__Person___MaxWidth_Person_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").setMaxWidth(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").getMaxWidth(), 0.0f);
        pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").setMaxWidth(8192.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").getMaxWidth(), 8192.0f);
    }

    // Test for MinHeight_Person_ in GroundRgbDetector
    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Groups__Person___MinHeight_Person_Default) {
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Person").getMinHeight(), 0.0f);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Groups__Person___MinHeight_Person_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").getMinHeight(), 0.0f);
    }

    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Groups__Person___MinHeight_Person_Range) {
        startConfiguration.getGroundRgbDetector().getGroups("Person").setMinHeight(0.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Person").getMinHeight(), 0.0f);
        startConfiguration.getGroundRgbDetector().getGroups("Person").setMinHeight(8192.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Person").getMinHeight(), 8192.0f);
        EXPECT_THROW(startConfiguration.getGroundRgbDetector().getGroups("Person").setMinHeight(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundRgbDetector().getGroups("Person").setMinHeight(8192.0f + 1), std::exception);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Groups__Person___MinHeight_Person_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").setMinHeight(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").getMinHeight(), 0.0f);
        pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").setMinHeight(8192.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").getMinHeight(), 8192.0f);
    }

    // Test for MaxHeight_Person_ in GroundRgbDetector
    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Groups__Person___MaxHeight_Person_Default) {
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Person").getMaxHeight(), 1000.0f);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Groups__Person___MaxHeight_Person_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").getMaxHeight(), 1000.0f);
    }

    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Groups__Person___MaxHeight_Person_Range) {
        startConfiguration.getGroundRgbDetector().getGroups("Person").setMaxHeight(0.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Person").getMaxHeight(), 0.0f);
        startConfiguration.getGroundRgbDetector().getGroups("Person").setMaxHeight(8192.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Person").getMaxHeight(), 8192.0f);
        EXPECT_THROW(startConfiguration.getGroundRgbDetector().getGroups("Person").setMaxHeight(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundRgbDetector().getGroups("Person").setMaxHeight(8192.0f + 1), std::exception);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Groups__Person___MaxHeight_Person_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").setMaxHeight(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").getMaxHeight(), 0.0f);
        pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").setMaxHeight(8192.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").getMaxHeight(), 8192.0f);
    }

    // Test for MinAspectRatio_Person_ in GroundRgbDetector
    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Groups__Person___MinAspectRatio_Person_Default) {
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Person").getMinAspectRatio(), 0.1f);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Groups__Person___MinAspectRatio_Person_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").getMinAspectRatio(), 0.1f);
    }

    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Groups__Person___MinAspectRatio_Person_Range) {
        startConfiguration.getGroundRgbDetector().getGroups("Person").setMinAspectRatio(0.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Person").getMinAspectRatio(), 0.0f);
        startConfiguration.getGroundRgbDetector().getGroups("Person").setMinAspectRatio(1000.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Person").getMinAspectRatio(), 1000.0f);
        EXPECT_THROW(startConfiguration.getGroundRgbDetector().getGroups("Person").setMinAspectRatio(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundRgbDetector().getGroups("Person").setMinAspectRatio(1000.0f + 1), std::exception);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Groups__Person___MinAspectRatio_Person_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").setMinAspectRatio(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").getMinAspectRatio(), 0.0f);
        pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").setMinAspectRatio(1000.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").getMinAspectRatio(), 1000.0f);
    }

    // Test for MaxAspectRatio_Person_ in GroundRgbDetector
    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Groups__Person___MaxAspectRatio_Person_Default) {
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Person").getMaxAspectRatio(), 10.0f);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Groups__Person___MaxAspectRatio_Person_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").getMaxAspectRatio(), 10.0f);
    }

    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Groups__Person___MaxAspectRatio_Person_Range) {
        startConfiguration.getGroundRgbDetector().getGroups("Person").setMaxAspectRatio(0.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Person").getMaxAspectRatio(), 0.0f);
        startConfiguration.getGroundRgbDetector().getGroups("Person").setMaxAspectRatio(1000.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Person").getMaxAspectRatio(), 1000.0f);
        EXPECT_THROW(startConfiguration.getGroundRgbDetector().getGroups("Person").setMaxAspectRatio(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundRgbDetector().getGroups("Person").setMaxAspectRatio(1000.0f + 1), std::exception);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Groups__Person___MaxAspectRatio_Person_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").setMaxAspectRatio(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").getMaxAspectRatio(), 0.0f);
        pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").setMaxAspectRatio(1000.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Person").getMaxAspectRatio(), 1000.0f);
    }

    // Test for ScoreThreshold_Vehicle_ in GroundRgbDetector
    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Groups__Vehicle___ScoreThreshold_Vehicle_Default) {
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").getScoreThreshold(), 0.1f);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Groups__Vehicle___ScoreThreshold_Vehicle_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").getScoreThreshold(), 0.1f);
    }

    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Groups__Vehicle___ScoreThreshold_Vehicle_Range) {
        startConfiguration.getGroundRgbDetector().getGroups("Vehicle").setScoreThreshold(0.1f);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").getScoreThreshold(), 0.1f);
        startConfiguration.getGroundRgbDetector().getGroups("Vehicle").setScoreThreshold(1.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").getScoreThreshold(), 1.0f);
        EXPECT_THROW(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").setScoreThreshold(0.1f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").setScoreThreshold(1.0f + 1), std::exception);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Groups__Vehicle___ScoreThreshold_Vehicle_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").setScoreThreshold(0.1f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").getScoreThreshold(), 0.1f);
        pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").setScoreThreshold(1.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").getScoreThreshold(), 1.0f);
    }

    // Test for MinWidth_Vehicle_ in GroundRgbDetector
    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Groups__Vehicle___MinWidth_Vehicle_Default) {
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").getMinWidth(), 0.0f);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Groups__Vehicle___MinWidth_Vehicle_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").getMinWidth(), 0.0f);
    }

    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Groups__Vehicle___MinWidth_Vehicle_Range) {
        startConfiguration.getGroundRgbDetector().getGroups("Vehicle").setMinWidth(0.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").getMinWidth(), 0.0f);
        startConfiguration.getGroundRgbDetector().getGroups("Vehicle").setMinWidth(8192.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").getMinWidth(), 8192.0f);
        EXPECT_THROW(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").setMinWidth(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").setMinWidth(8192.0f + 1), std::exception);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Groups__Vehicle___MinWidth_Vehicle_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").setMinWidth(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").getMinWidth(), 0.0f);
        pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").setMinWidth(8192.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").getMinWidth(), 8192.0f);
    }

    // Test for MaxWidth_Vehicle_ in GroundRgbDetector
    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Groups__Vehicle___MaxWidth_Vehicle_Default) {
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").getMaxWidth(), 1000.0f);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Groups__Vehicle___MaxWidth_Vehicle_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").getMaxWidth(), 1000.0f);
    }

    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Groups__Vehicle___MaxWidth_Vehicle_Range) {
        startConfiguration.getGroundRgbDetector().getGroups("Vehicle").setMaxWidth(0.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").getMaxWidth(), 0.0f);
        startConfiguration.getGroundRgbDetector().getGroups("Vehicle").setMaxWidth(8192.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").getMaxWidth(), 8192.0f);
        EXPECT_THROW(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").setMaxWidth(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").setMaxWidth(8192.0f + 1), std::exception);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Groups__Vehicle___MaxWidth_Vehicle_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").setMaxWidth(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").getMaxWidth(), 0.0f);
        pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").setMaxWidth(8192.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").getMaxWidth(), 8192.0f);
    }

    // Test for MinHeight_Vehicle_ in GroundRgbDetector
    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Groups__Vehicle___MinHeight_Vehicle_Default) {
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").getMinHeight(), 0.0f);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Groups__Vehicle___MinHeight_Vehicle_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").getMinHeight(), 0.0f);
    }

    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Groups__Vehicle___MinHeight_Vehicle_Range) {
        startConfiguration.getGroundRgbDetector().getGroups("Vehicle").setMinHeight(0.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").getMinHeight(), 0.0f);
        startConfiguration.getGroundRgbDetector().getGroups("Vehicle").setMinHeight(8192.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").getMinHeight(), 8192.0f);
        EXPECT_THROW(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").setMinHeight(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").setMinHeight(8192.0f + 1), std::exception);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Groups__Vehicle___MinHeight_Vehicle_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").setMinHeight(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").getMinHeight(), 0.0f);
        pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").setMinHeight(8192.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").getMinHeight(), 8192.0f);
    }

    // Test for MaxHeight_Vehicle_ in GroundRgbDetector
    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Groups__Vehicle___MaxHeight_Vehicle_Default) {
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").getMaxHeight(), 1000.0f);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Groups__Vehicle___MaxHeight_Vehicle_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").getMaxHeight(), 1000.0f);
    }

    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Groups__Vehicle___MaxHeight_Vehicle_Range) {
        startConfiguration.getGroundRgbDetector().getGroups("Vehicle").setMaxHeight(0.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").getMaxHeight(), 0.0f);
        startConfiguration.getGroundRgbDetector().getGroups("Vehicle").setMaxHeight(8192.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").getMaxHeight(), 8192.0f);
        EXPECT_THROW(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").setMaxHeight(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").setMaxHeight(8192.0f + 1), std::exception);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Groups__Vehicle___MaxHeight_Vehicle_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").setMaxHeight(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").getMaxHeight(), 0.0f);
        pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").setMaxHeight(8192.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").getMaxHeight(), 8192.0f);
    }

    // Test for MinAspectRatio_Vehicle_ in GroundRgbDetector
    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Groups__Vehicle___MinAspectRatio_Vehicle_Default) {
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").getMinAspectRatio(), 0.1f);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Groups__Vehicle___MinAspectRatio_Vehicle_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").getMinAspectRatio(), 0.1f);
    }

    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Groups__Vehicle___MinAspectRatio_Vehicle_Range) {
        startConfiguration.getGroundRgbDetector().getGroups("Vehicle").setMinAspectRatio(0.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").getMinAspectRatio(), 0.0f);
        startConfiguration.getGroundRgbDetector().getGroups("Vehicle").setMinAspectRatio(1000.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").getMinAspectRatio(), 1000.0f);
        EXPECT_THROW(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").setMinAspectRatio(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").setMinAspectRatio(1000.0f + 1), std::exception);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Groups__Vehicle___MinAspectRatio_Vehicle_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").setMinAspectRatio(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").getMinAspectRatio(), 0.0f);
        pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").setMinAspectRatio(1000.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").getMinAspectRatio(), 1000.0f);
    }

    // Test for MaxAspectRatio_Vehicle_ in GroundRgbDetector
    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Groups__Vehicle___MaxAspectRatio_Vehicle_Default) {
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").getMaxAspectRatio(), 10.0f);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Groups__Vehicle___MaxAspectRatio_Vehicle_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").getMaxAspectRatio(), 10.0f);
    }

    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_Groups__Vehicle___MaxAspectRatio_Vehicle_Range) {
        startConfiguration.getGroundRgbDetector().getGroups("Vehicle").setMaxAspectRatio(0.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").getMaxAspectRatio(), 0.0f);
        startConfiguration.getGroundRgbDetector().getGroups("Vehicle").setMaxAspectRatio(1000.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").getMaxAspectRatio(), 1000.0f);
        EXPECT_THROW(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").setMaxAspectRatio(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundRgbDetector().getGroups("Vehicle").setMaxAspectRatio(1000.0f + 1), std::exception);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_Groups__Vehicle___MaxAspectRatio_Vehicle_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").setMaxAspectRatio(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").getMaxAspectRatio(), 0.0f);
        pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").setMaxAspectRatio(1000.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getGroups("Vehicle").getMaxAspectRatio(), 1000.0f);
    }

    // Test for AveragePixelValue0 in GroundRgbDetector
    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_AveragePixelValue0Default) {
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getAveragePixelValue(0), 0);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_AveragePixelValue0Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getAveragePixelValue(0), 0);
    }

    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_AveragePixelValue0Random) {
        startConfiguration.getGroundRgbDetector().setAveragePixelValue(0, 725.44f);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getAveragePixelValue(0), 725.44f);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_AveragePixelValue0Random) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbDetector().setAveragePixelValue(0, 725.44f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getAveragePixelValue(0), 725.44f);
    }

    // Test for PixelValueStandardDeviation0 in GroundRgbDetector
    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_PixelValueStandardDeviation0Default) {
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getPixelValueStandardDeviation(0), 0);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_PixelValueStandardDeviation0Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getPixelValueStandardDeviation(0), 0);
    }

    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_PixelValueStandardDeviation0Random) {
        startConfiguration.getGroundRgbDetector().setPixelValueStandardDeviation(0, 420.39f);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getPixelValueStandardDeviation(0), 420.39f);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_PixelValueStandardDeviation0Random) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbDetector().setPixelValueStandardDeviation(0, 420.39f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getPixelValueStandardDeviation(0), 420.39f);
    }

    // Test for MaxDetections in GroundRgbDetector
    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_MaxDetectionsDefault) {
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getMaxDetections(), 100);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_MaxDetectionsDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getMaxDetections(), 100);
    }

    TEST_F(GroundRgbDetectorTest, GroundRgbDetector_MaxDetectionsRandom) {
        startConfiguration.getGroundRgbDetector().setMaxDetections(717);
        EXPECT_EQ(startConfiguration.getGroundRgbDetector().getMaxDetections(), 717);
    }

    TEST_F(GroundRgbDetectorTest, Update_GroundRgbDetector_MaxDetectionsRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbDetector().setMaxDetections(717);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbDetector().getMaxDetections(), 717);
    }

// Test suit for GroundMwirDetector
class GroundMwirDetectorTest : public ::testing::Test {
protected:
    void SetUp() override {
        startConfiguration = pPipeline->createStartStreamConfiguration();
        startConfiguration.getGroundMwirDetector().appendAveragePixelValue(0);
        startConfiguration.getGroundMwirDetector().appendPixelValueStandardDeviation(0);

        if (::testing::GTEST_FLAG(update_tests)) {
            tmpStartConfiguration = startConfiguration;
            tmpStartConfiguration.getRawSource(); // Touch Raw Source
            tmpStartConfiguration.getRawSource().setReadTimeoutInSec(0); // Wait forever
            pStream = pPipeline->startStream(tmpStartConfiguration);
            waitForStreamStarted(pStream, data);
        }

    }

    void TearDown() override {
        if (::testing::GTEST_FLAG(update_tests)) {
            pStream.reset();
            waitForStreamStopped(data);
        }

    }

};

    // Test for X in GroundMwirDetector
    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Roi_XDefault) {
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getRoi().getX(), 0);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Roi_XDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getRoi().getX(), 0);
    }

    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Roi_XRandom) {
        startConfiguration.getGroundMwirDetector().getRoi().setX(168);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getRoi().getX(), 168);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Roi_XRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundMwirDetector().getRoi().setX(168);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getRoi().getX(), 168);
    }

    // Test for Y in GroundMwirDetector
    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Roi_YDefault) {
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getRoi().getY(), 0);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Roi_YDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getRoi().getY(), 0);
    }

    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Roi_YRandom) {
        startConfiguration.getGroundMwirDetector().getRoi().setY(2289);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getRoi().getY(), 2289);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Roi_YRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundMwirDetector().getRoi().setY(2289);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getRoi().getY(), 2289);
    }

    // Test for Width in GroundMwirDetector
    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Roi_WidthDefault) {
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getRoi().getWidth(), 0);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Roi_WidthDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getRoi().getWidth(), 0);
    }

    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Roi_WidthRandom) {
        startConfiguration.getGroundMwirDetector().getRoi().setWidth(7490);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getRoi().getWidth(), 7490);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Roi_WidthRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundMwirDetector().getRoi().setWidth(7490);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getRoi().getWidth(), 7490);
    }

    // Test for Height in GroundMwirDetector
    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Roi_HeightDefault) {
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getRoi().getHeight(), 0);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Roi_HeightDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getRoi().getHeight(), 0);
    }

    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Roi_HeightRandom) {
        startConfiguration.getGroundMwirDetector().getRoi().setHeight(6927);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getRoi().getHeight(), 6927);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Roi_HeightRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundMwirDetector().getRoi().setHeight(6927);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getRoi().getHeight(), 6927);
    }

    // Test for ScoreThreshold_Person_ in GroundMwirDetector
    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Groups__Person___ScoreThreshold_Person_Default) {
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Person").getScoreThreshold(), 0.1f);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Groups__Person___ScoreThreshold_Person_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").getScoreThreshold(), 0.1f);
    }

    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Groups__Person___ScoreThreshold_Person_Range) {
        startConfiguration.getGroundMwirDetector().getGroups("Person").setScoreThreshold(0.1f);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Person").getScoreThreshold(), 0.1f);
        startConfiguration.getGroundMwirDetector().getGroups("Person").setScoreThreshold(1.0f);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Person").getScoreThreshold(), 1.0f);
        EXPECT_THROW(startConfiguration.getGroundMwirDetector().getGroups("Person").setScoreThreshold(0.1f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundMwirDetector().getGroups("Person").setScoreThreshold(1.0f + 1), std::exception);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Groups__Person___ScoreThreshold_Person_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").setScoreThreshold(0.1f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").getScoreThreshold(), 0.1f);
        pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").setScoreThreshold(1.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").getScoreThreshold(), 1.0f);
    }

    // Test for MinWidth_Person_ in GroundMwirDetector
    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Groups__Person___MinWidth_Person_Default) {
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Person").getMinWidth(), 0.0f);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Groups__Person___MinWidth_Person_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").getMinWidth(), 0.0f);
    }

    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Groups__Person___MinWidth_Person_Range) {
        startConfiguration.getGroundMwirDetector().getGroups("Person").setMinWidth(0.0f);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Person").getMinWidth(), 0.0f);
        startConfiguration.getGroundMwirDetector().getGroups("Person").setMinWidth(8192.0f);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Person").getMinWidth(), 8192.0f);
        EXPECT_THROW(startConfiguration.getGroundMwirDetector().getGroups("Person").setMinWidth(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundMwirDetector().getGroups("Person").setMinWidth(8192.0f + 1), std::exception);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Groups__Person___MinWidth_Person_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").setMinWidth(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").getMinWidth(), 0.0f);
        pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").setMinWidth(8192.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").getMinWidth(), 8192.0f);
    }

    // Test for MaxWidth_Person_ in GroundMwirDetector
    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Groups__Person___MaxWidth_Person_Default) {
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Person").getMaxWidth(), 1000.0f);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Groups__Person___MaxWidth_Person_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").getMaxWidth(), 1000.0f);
    }

    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Groups__Person___MaxWidth_Person_Range) {
        startConfiguration.getGroundMwirDetector().getGroups("Person").setMaxWidth(0.0f);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Person").getMaxWidth(), 0.0f);
        startConfiguration.getGroundMwirDetector().getGroups("Person").setMaxWidth(8192.0f);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Person").getMaxWidth(), 8192.0f);
        EXPECT_THROW(startConfiguration.getGroundMwirDetector().getGroups("Person").setMaxWidth(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundMwirDetector().getGroups("Person").setMaxWidth(8192.0f + 1), std::exception);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Groups__Person___MaxWidth_Person_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").setMaxWidth(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").getMaxWidth(), 0.0f);
        pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").setMaxWidth(8192.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").getMaxWidth(), 8192.0f);
    }

    // Test for MinHeight_Person_ in GroundMwirDetector
    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Groups__Person___MinHeight_Person_Default) {
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Person").getMinHeight(), 0.0f);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Groups__Person___MinHeight_Person_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").getMinHeight(), 0.0f);
    }

    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Groups__Person___MinHeight_Person_Range) {
        startConfiguration.getGroundMwirDetector().getGroups("Person").setMinHeight(0.0f);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Person").getMinHeight(), 0.0f);
        startConfiguration.getGroundMwirDetector().getGroups("Person").setMinHeight(8192.0f);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Person").getMinHeight(), 8192.0f);
        EXPECT_THROW(startConfiguration.getGroundMwirDetector().getGroups("Person").setMinHeight(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundMwirDetector().getGroups("Person").setMinHeight(8192.0f + 1), std::exception);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Groups__Person___MinHeight_Person_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").setMinHeight(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").getMinHeight(), 0.0f);
        pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").setMinHeight(8192.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").getMinHeight(), 8192.0f);
    }

    // Test for MaxHeight_Person_ in GroundMwirDetector
    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Groups__Person___MaxHeight_Person_Default) {
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Person").getMaxHeight(), 1000.0f);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Groups__Person___MaxHeight_Person_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").getMaxHeight(), 1000.0f);
    }

    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Groups__Person___MaxHeight_Person_Range) {
        startConfiguration.getGroundMwirDetector().getGroups("Person").setMaxHeight(0.0f);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Person").getMaxHeight(), 0.0f);
        startConfiguration.getGroundMwirDetector().getGroups("Person").setMaxHeight(8192.0f);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Person").getMaxHeight(), 8192.0f);
        EXPECT_THROW(startConfiguration.getGroundMwirDetector().getGroups("Person").setMaxHeight(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundMwirDetector().getGroups("Person").setMaxHeight(8192.0f + 1), std::exception);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Groups__Person___MaxHeight_Person_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").setMaxHeight(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").getMaxHeight(), 0.0f);
        pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").setMaxHeight(8192.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").getMaxHeight(), 8192.0f);
    }

    // Test for MinAspectRatio_Person_ in GroundMwirDetector
    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Groups__Person___MinAspectRatio_Person_Default) {
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Person").getMinAspectRatio(), 0.1f);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Groups__Person___MinAspectRatio_Person_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").getMinAspectRatio(), 0.1f);
    }

    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Groups__Person___MinAspectRatio_Person_Range) {
        startConfiguration.getGroundMwirDetector().getGroups("Person").setMinAspectRatio(0.0f);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Person").getMinAspectRatio(), 0.0f);
        startConfiguration.getGroundMwirDetector().getGroups("Person").setMinAspectRatio(1000.0f);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Person").getMinAspectRatio(), 1000.0f);
        EXPECT_THROW(startConfiguration.getGroundMwirDetector().getGroups("Person").setMinAspectRatio(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundMwirDetector().getGroups("Person").setMinAspectRatio(1000.0f + 1), std::exception);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Groups__Person___MinAspectRatio_Person_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").setMinAspectRatio(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").getMinAspectRatio(), 0.0f);
        pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").setMinAspectRatio(1000.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").getMinAspectRatio(), 1000.0f);
    }

    // Test for MaxAspectRatio_Person_ in GroundMwirDetector
    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Groups__Person___MaxAspectRatio_Person_Default) {
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Person").getMaxAspectRatio(), 10.0f);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Groups__Person___MaxAspectRatio_Person_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").getMaxAspectRatio(), 10.0f);
    }

    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Groups__Person___MaxAspectRatio_Person_Range) {
        startConfiguration.getGroundMwirDetector().getGroups("Person").setMaxAspectRatio(0.0f);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Person").getMaxAspectRatio(), 0.0f);
        startConfiguration.getGroundMwirDetector().getGroups("Person").setMaxAspectRatio(1000.0f);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Person").getMaxAspectRatio(), 1000.0f);
        EXPECT_THROW(startConfiguration.getGroundMwirDetector().getGroups("Person").setMaxAspectRatio(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundMwirDetector().getGroups("Person").setMaxAspectRatio(1000.0f + 1), std::exception);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Groups__Person___MaxAspectRatio_Person_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").setMaxAspectRatio(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").getMaxAspectRatio(), 0.0f);
        pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").setMaxAspectRatio(1000.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Person").getMaxAspectRatio(), 1000.0f);
    }

    // Test for ScoreThreshold_Vehicle_ in GroundMwirDetector
    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Groups__Vehicle___ScoreThreshold_Vehicle_Default) {
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").getScoreThreshold(), 0.1f);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Groups__Vehicle___ScoreThreshold_Vehicle_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").getScoreThreshold(), 0.1f);
    }

    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Groups__Vehicle___ScoreThreshold_Vehicle_Range) {
        startConfiguration.getGroundMwirDetector().getGroups("Vehicle").setScoreThreshold(0.1f);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").getScoreThreshold(), 0.1f);
        startConfiguration.getGroundMwirDetector().getGroups("Vehicle").setScoreThreshold(1.0f);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").getScoreThreshold(), 1.0f);
        EXPECT_THROW(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").setScoreThreshold(0.1f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").setScoreThreshold(1.0f + 1), std::exception);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Groups__Vehicle___ScoreThreshold_Vehicle_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").setScoreThreshold(0.1f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").getScoreThreshold(), 0.1f);
        pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").setScoreThreshold(1.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").getScoreThreshold(), 1.0f);
    }

    // Test for MinWidth_Vehicle_ in GroundMwirDetector
    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Groups__Vehicle___MinWidth_Vehicle_Default) {
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").getMinWidth(), 0.0f);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Groups__Vehicle___MinWidth_Vehicle_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").getMinWidth(), 0.0f);
    }

    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Groups__Vehicle___MinWidth_Vehicle_Range) {
        startConfiguration.getGroundMwirDetector().getGroups("Vehicle").setMinWidth(0.0f);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").getMinWidth(), 0.0f);
        startConfiguration.getGroundMwirDetector().getGroups("Vehicle").setMinWidth(8192.0f);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").getMinWidth(), 8192.0f);
        EXPECT_THROW(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").setMinWidth(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").setMinWidth(8192.0f + 1), std::exception);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Groups__Vehicle___MinWidth_Vehicle_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").setMinWidth(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").getMinWidth(), 0.0f);
        pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").setMinWidth(8192.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").getMinWidth(), 8192.0f);
    }

    // Test for MaxWidth_Vehicle_ in GroundMwirDetector
    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Groups__Vehicle___MaxWidth_Vehicle_Default) {
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").getMaxWidth(), 1000.0f);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Groups__Vehicle___MaxWidth_Vehicle_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").getMaxWidth(), 1000.0f);
    }

    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Groups__Vehicle___MaxWidth_Vehicle_Range) {
        startConfiguration.getGroundMwirDetector().getGroups("Vehicle").setMaxWidth(0.0f);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").getMaxWidth(), 0.0f);
        startConfiguration.getGroundMwirDetector().getGroups("Vehicle").setMaxWidth(8192.0f);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").getMaxWidth(), 8192.0f);
        EXPECT_THROW(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").setMaxWidth(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").setMaxWidth(8192.0f + 1), std::exception);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Groups__Vehicle___MaxWidth_Vehicle_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").setMaxWidth(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").getMaxWidth(), 0.0f);
        pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").setMaxWidth(8192.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").getMaxWidth(), 8192.0f);
    }

    // Test for MinHeight_Vehicle_ in GroundMwirDetector
    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Groups__Vehicle___MinHeight_Vehicle_Default) {
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").getMinHeight(), 0.0f);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Groups__Vehicle___MinHeight_Vehicle_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").getMinHeight(), 0.0f);
    }

    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Groups__Vehicle___MinHeight_Vehicle_Range) {
        startConfiguration.getGroundMwirDetector().getGroups("Vehicle").setMinHeight(0.0f);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").getMinHeight(), 0.0f);
        startConfiguration.getGroundMwirDetector().getGroups("Vehicle").setMinHeight(8192.0f);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").getMinHeight(), 8192.0f);
        EXPECT_THROW(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").setMinHeight(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").setMinHeight(8192.0f + 1), std::exception);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Groups__Vehicle___MinHeight_Vehicle_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").setMinHeight(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").getMinHeight(), 0.0f);
        pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").setMinHeight(8192.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").getMinHeight(), 8192.0f);
    }

    // Test for MaxHeight_Vehicle_ in GroundMwirDetector
    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Groups__Vehicle___MaxHeight_Vehicle_Default) {
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").getMaxHeight(), 1000.0f);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Groups__Vehicle___MaxHeight_Vehicle_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").getMaxHeight(), 1000.0f);
    }

    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Groups__Vehicle___MaxHeight_Vehicle_Range) {
        startConfiguration.getGroundMwirDetector().getGroups("Vehicle").setMaxHeight(0.0f);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").getMaxHeight(), 0.0f);
        startConfiguration.getGroundMwirDetector().getGroups("Vehicle").setMaxHeight(8192.0f);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").getMaxHeight(), 8192.0f);
        EXPECT_THROW(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").setMaxHeight(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").setMaxHeight(8192.0f + 1), std::exception);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Groups__Vehicle___MaxHeight_Vehicle_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").setMaxHeight(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").getMaxHeight(), 0.0f);
        pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").setMaxHeight(8192.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").getMaxHeight(), 8192.0f);
    }

    // Test for MinAspectRatio_Vehicle_ in GroundMwirDetector
    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Groups__Vehicle___MinAspectRatio_Vehicle_Default) {
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").getMinAspectRatio(), 0.1f);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Groups__Vehicle___MinAspectRatio_Vehicle_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").getMinAspectRatio(), 0.1f);
    }

    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Groups__Vehicle___MinAspectRatio_Vehicle_Range) {
        startConfiguration.getGroundMwirDetector().getGroups("Vehicle").setMinAspectRatio(0.0f);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").getMinAspectRatio(), 0.0f);
        startConfiguration.getGroundMwirDetector().getGroups("Vehicle").setMinAspectRatio(1000.0f);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").getMinAspectRatio(), 1000.0f);
        EXPECT_THROW(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").setMinAspectRatio(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").setMinAspectRatio(1000.0f + 1), std::exception);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Groups__Vehicle___MinAspectRatio_Vehicle_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").setMinAspectRatio(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").getMinAspectRatio(), 0.0f);
        pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").setMinAspectRatio(1000.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").getMinAspectRatio(), 1000.0f);
    }

    // Test for MaxAspectRatio_Vehicle_ in GroundMwirDetector
    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Groups__Vehicle___MaxAspectRatio_Vehicle_Default) {
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").getMaxAspectRatio(), 10.0f);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Groups__Vehicle___MaxAspectRatio_Vehicle_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").getMaxAspectRatio(), 10.0f);
    }

    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_Groups__Vehicle___MaxAspectRatio_Vehicle_Range) {
        startConfiguration.getGroundMwirDetector().getGroups("Vehicle").setMaxAspectRatio(0.0f);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").getMaxAspectRatio(), 0.0f);
        startConfiguration.getGroundMwirDetector().getGroups("Vehicle").setMaxAspectRatio(1000.0f);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").getMaxAspectRatio(), 1000.0f);
        EXPECT_THROW(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").setMaxAspectRatio(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundMwirDetector().getGroups("Vehicle").setMaxAspectRatio(1000.0f + 1), std::exception);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_Groups__Vehicle___MaxAspectRatio_Vehicle_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").setMaxAspectRatio(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").getMaxAspectRatio(), 0.0f);
        pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").setMaxAspectRatio(1000.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getGroups("Vehicle").getMaxAspectRatio(), 1000.0f);
    }

    // Test for AveragePixelValue0 in GroundMwirDetector
    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_AveragePixelValue0Default) {
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getAveragePixelValue(0), 0);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_AveragePixelValue0Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getAveragePixelValue(0), 0);
    }

    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_AveragePixelValue0Random) {
        startConfiguration.getGroundMwirDetector().setAveragePixelValue(0, 795.73f);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getAveragePixelValue(0), 795.73f);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_AveragePixelValue0Random) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundMwirDetector().setAveragePixelValue(0, 795.73f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getAveragePixelValue(0), 795.73f);
    }

    // Test for PixelValueStandardDeviation0 in GroundMwirDetector
    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_PixelValueStandardDeviation0Default) {
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getPixelValueStandardDeviation(0), 0);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_PixelValueStandardDeviation0Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getPixelValueStandardDeviation(0), 0);
    }

    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_PixelValueStandardDeviation0Random) {
        startConfiguration.getGroundMwirDetector().setPixelValueStandardDeviation(0, 571.69f);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getPixelValueStandardDeviation(0), 571.69f);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_PixelValueStandardDeviation0Random) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundMwirDetector().setPixelValueStandardDeviation(0, 571.69f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getPixelValueStandardDeviation(0), 571.69f);
    }

    // Test for MaxDetections in GroundMwirDetector
    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_MaxDetectionsDefault) {
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getMaxDetections(), 100);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_MaxDetectionsDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getMaxDetections(), 100);
    }

    TEST_F(GroundMwirDetectorTest, GroundMwirDetector_MaxDetectionsRandom) {
        startConfiguration.getGroundMwirDetector().setMaxDetections(35);
        EXPECT_EQ(startConfiguration.getGroundMwirDetector().getMaxDetections(), 35);
    }

    TEST_F(GroundMwirDetectorTest, Update_GroundMwirDetector_MaxDetectionsRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundMwirDetector().setMaxDetections(35);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundMwirDetector().getMaxDetections(), 35);
    }

// Test suit for Vmd
class VmdTest : public ::testing::Test {
protected:
    void SetUp() override {
        startConfiguration = pPipeline->createStartStreamConfiguration();
        if (::testing::GTEST_FLAG(update_tests)) {
            tmpStartConfiguration = startConfiguration;
            tmpStartConfiguration.getRawSource(); // Touch Raw Source
            tmpStartConfiguration.getRawSource().setReadTimeoutInSec(0); // Wait forever
            pStream = pPipeline->startStream(tmpStartConfiguration);
            waitForStreamStarted(pStream, data);
        }

    }

    void TearDown() override {
        if (::testing::GTEST_FLAG(update_tests)) {
            pStream.reset();
            waitForStreamStopped(data);
        }

    }

};

    // Test for Enable in Vmd
    TEST_F(VmdTest, Vmd_EnableDefault) {
        EXPECT_EQ(startConfiguration.getVmd().getEnable(), false);
    }

    TEST_F(VmdTest, Update_Vmd_EnableDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getVmd().getEnable(), false);
    }

    TEST_F(VmdTest, Vmd_EnableRandom) {
        startConfiguration.getVmd().setEnable(true);
        EXPECT_EQ(startConfiguration.getVmd().getEnable(), true);
    }

    TEST_F(VmdTest, Update_Vmd_EnableRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getVmd().setEnable(true);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVmd().getEnable(), true);
    }

    // Test for ScoreThreshold in Vmd
    TEST_F(VmdTest, Vmd_ScoreThresholdDefault) {
        EXPECT_EQ(startConfiguration.getVmd().getScoreThreshold(), 0.0f);
    }

    TEST_F(VmdTest, Update_Vmd_ScoreThresholdDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getVmd().getScoreThreshold(), 0.0f);
    }

    TEST_F(VmdTest, Vmd_ScoreThresholdRange) {
        startConfiguration.getVmd().setScoreThreshold(0.0f);
        EXPECT_EQ(startConfiguration.getVmd().getScoreThreshold(), 0.0f);
        startConfiguration.getVmd().setScoreThreshold(1.0f);
        EXPECT_EQ(startConfiguration.getVmd().getScoreThreshold(), 1.0f);
        EXPECT_THROW(startConfiguration.getVmd().setScoreThreshold(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getVmd().setScoreThreshold(1.0f + 1), std::exception);
    }

    TEST_F(VmdTest, Update_Vmd_ScoreThresholdRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getVmd().setScoreThreshold(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVmd().getScoreThreshold(), 0.0f);
        pStream->getConfiguration().getVmd().setScoreThreshold(1.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVmd().getScoreThreshold(), 1.0f);
    }

    // Test for MinWidth in Vmd
    TEST_F(VmdTest, Vmd_MinWidthDefault) {
        EXPECT_EQ(startConfiguration.getVmd().getMinWidth(), 0.0f);
    }

    TEST_F(VmdTest, Update_Vmd_MinWidthDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getVmd().getMinWidth(), 0.0f);
    }

    TEST_F(VmdTest, Vmd_MinWidthRange) {
        startConfiguration.getVmd().setMinWidth(0.0f);
        EXPECT_EQ(startConfiguration.getVmd().getMinWidth(), 0.0f);
        startConfiguration.getVmd().setMinWidth(8192.0f);
        EXPECT_EQ(startConfiguration.getVmd().getMinWidth(), 8192.0f);
        EXPECT_THROW(startConfiguration.getVmd().setMinWidth(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getVmd().setMinWidth(8192.0f + 1), std::exception);
    }

    TEST_F(VmdTest, Update_Vmd_MinWidthRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getVmd().setMinWidth(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVmd().getMinWidth(), 0.0f);
        pStream->getConfiguration().getVmd().setMinWidth(8192.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVmd().getMinWidth(), 8192.0f);
    }

    // Test for MaxWidth in Vmd
    TEST_F(VmdTest, Vmd_MaxWidthDefault) {
        EXPECT_EQ(startConfiguration.getVmd().getMaxWidth(), 1000.0f);
    }

    TEST_F(VmdTest, Update_Vmd_MaxWidthDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getVmd().getMaxWidth(), 1000.0f);
    }

    TEST_F(VmdTest, Vmd_MaxWidthRange) {
        startConfiguration.getVmd().setMaxWidth(0.0f);
        EXPECT_EQ(startConfiguration.getVmd().getMaxWidth(), 0.0f);
        startConfiguration.getVmd().setMaxWidth(8192.0f);
        EXPECT_EQ(startConfiguration.getVmd().getMaxWidth(), 8192.0f);
        EXPECT_THROW(startConfiguration.getVmd().setMaxWidth(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getVmd().setMaxWidth(8192.0f + 1), std::exception);
    }

    TEST_F(VmdTest, Update_Vmd_MaxWidthRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getVmd().setMaxWidth(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVmd().getMaxWidth(), 0.0f);
        pStream->getConfiguration().getVmd().setMaxWidth(8192.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVmd().getMaxWidth(), 8192.0f);
    }

    // Test for MinHeight in Vmd
    TEST_F(VmdTest, Vmd_MinHeightDefault) {
        EXPECT_EQ(startConfiguration.getVmd().getMinHeight(), 0.0f);
    }

    TEST_F(VmdTest, Update_Vmd_MinHeightDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getVmd().getMinHeight(), 0.0f);
    }

    TEST_F(VmdTest, Vmd_MinHeightRange) {
        startConfiguration.getVmd().setMinHeight(0.0f);
        EXPECT_EQ(startConfiguration.getVmd().getMinHeight(), 0.0f);
        startConfiguration.getVmd().setMinHeight(8192.0f);
        EXPECT_EQ(startConfiguration.getVmd().getMinHeight(), 8192.0f);
        EXPECT_THROW(startConfiguration.getVmd().setMinHeight(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getVmd().setMinHeight(8192.0f + 1), std::exception);
    }

    TEST_F(VmdTest, Update_Vmd_MinHeightRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getVmd().setMinHeight(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVmd().getMinHeight(), 0.0f);
        pStream->getConfiguration().getVmd().setMinHeight(8192.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVmd().getMinHeight(), 8192.0f);
    }

    // Test for MaxHeight in Vmd
    TEST_F(VmdTest, Vmd_MaxHeightDefault) {
        EXPECT_EQ(startConfiguration.getVmd().getMaxHeight(), 1000.0f);
    }

    TEST_F(VmdTest, Update_Vmd_MaxHeightDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getVmd().getMaxHeight(), 1000.0f);
    }

    TEST_F(VmdTest, Vmd_MaxHeightRange) {
        startConfiguration.getVmd().setMaxHeight(0.0f);
        EXPECT_EQ(startConfiguration.getVmd().getMaxHeight(), 0.0f);
        startConfiguration.getVmd().setMaxHeight(8192.0f);
        EXPECT_EQ(startConfiguration.getVmd().getMaxHeight(), 8192.0f);
        EXPECT_THROW(startConfiguration.getVmd().setMaxHeight(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getVmd().setMaxHeight(8192.0f + 1), std::exception);
    }

    TEST_F(VmdTest, Update_Vmd_MaxHeightRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getVmd().setMaxHeight(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVmd().getMaxHeight(), 0.0f);
        pStream->getConfiguration().getVmd().setMaxHeight(8192.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVmd().getMaxHeight(), 8192.0f);
    }

// Test suit for GroundRgbPersonClassifier
class GroundRgbPersonClassifierTest : public ::testing::Test {
protected:
    void SetUp() override {
        startConfiguration = pPipeline->createStartStreamConfiguration();
        if (::testing::GTEST_FLAG(update_tests)) {
            tmpStartConfiguration = startConfiguration;
            tmpStartConfiguration.getRawSource(); // Touch Raw Source
            tmpStartConfiguration.getRawSource().setReadTimeoutInSec(0); // Wait forever
            pStream = pPipeline->startStream(tmpStartConfiguration);
            waitForStreamStarted(pStream, data);
        }

    }

    void TearDown() override {
        if (::testing::GTEST_FLAG(update_tests)) {
            pStream.reset();
            waitForStreamStopped(data);
        }

    }

};

    // Test for Enable in GroundRgbPersonClassifier
    TEST_F(GroundRgbPersonClassifierTest, GroundRgbPersonClassifier_EnableDefault) {
        EXPECT_EQ(startConfiguration.getGroundRgbPersonClassifier().getEnable(), false);
    }

    TEST_F(GroundRgbPersonClassifierTest, Update_GroundRgbPersonClassifier_EnableDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbPersonClassifier().getEnable(), false);
    }

    TEST_F(GroundRgbPersonClassifierTest, GroundRgbPersonClassifier_EnableRandom) {
        startConfiguration.getGroundRgbPersonClassifier().setEnable(false);
        EXPECT_EQ(startConfiguration.getGroundRgbPersonClassifier().getEnable(), false);
    }

    TEST_F(GroundRgbPersonClassifierTest, Update_GroundRgbPersonClassifier_EnableRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbPersonClassifier().setEnable(false);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbPersonClassifier().getEnable(), false);
    }

    // Test for Width in GroundRgbPersonClassifier
    TEST_F(GroundRgbPersonClassifierTest, GroundRgbPersonClassifier_AdjustCropInPercentsOverride_WidthDefault) {
        EXPECT_EQ(startConfiguration.getGroundRgbPersonClassifier().getAdjustCropInPercentsOverride().getWidth(), -1001);
    }

    TEST_F(GroundRgbPersonClassifierTest, Update_GroundRgbPersonClassifier_AdjustCropInPercentsOverride_WidthDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbPersonClassifier().getAdjustCropInPercentsOverride().getWidth(), -1001);
    }

    TEST_F(GroundRgbPersonClassifierTest, GroundRgbPersonClassifier_AdjustCropInPercentsOverride_WidthRange) {
        startConfiguration.getGroundRgbPersonClassifier().getAdjustCropInPercentsOverride().setWidth(-1001);
        EXPECT_EQ(startConfiguration.getGroundRgbPersonClassifier().getAdjustCropInPercentsOverride().getWidth(), -1001);
        startConfiguration.getGroundRgbPersonClassifier().getAdjustCropInPercentsOverride().setWidth(1000);
        EXPECT_EQ(startConfiguration.getGroundRgbPersonClassifier().getAdjustCropInPercentsOverride().getWidth(), 1000);
        EXPECT_THROW(startConfiguration.getGroundRgbPersonClassifier().getAdjustCropInPercentsOverride().setWidth(-1001 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundRgbPersonClassifier().getAdjustCropInPercentsOverride().setWidth(1000 + 1), std::exception);
    }

    TEST_F(GroundRgbPersonClassifierTest, Update_GroundRgbPersonClassifier_AdjustCropInPercentsOverride_WidthRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbPersonClassifier().getAdjustCropInPercentsOverride().setWidth(-1001);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbPersonClassifier().getAdjustCropInPercentsOverride().getWidth(), -1001);
        pStream->getConfiguration().getGroundRgbPersonClassifier().getAdjustCropInPercentsOverride().setWidth(1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbPersonClassifier().getAdjustCropInPercentsOverride().getWidth(), 1000);
    }

    // Test for Height in GroundRgbPersonClassifier
    TEST_F(GroundRgbPersonClassifierTest, GroundRgbPersonClassifier_AdjustCropInPercentsOverride_HeightDefault) {
        EXPECT_EQ(startConfiguration.getGroundRgbPersonClassifier().getAdjustCropInPercentsOverride().getHeight(), -1001);
    }

    TEST_F(GroundRgbPersonClassifierTest, Update_GroundRgbPersonClassifier_AdjustCropInPercentsOverride_HeightDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbPersonClassifier().getAdjustCropInPercentsOverride().getHeight(), -1001);
    }

    TEST_F(GroundRgbPersonClassifierTest, GroundRgbPersonClassifier_AdjustCropInPercentsOverride_HeightRange) {
        startConfiguration.getGroundRgbPersonClassifier().getAdjustCropInPercentsOverride().setHeight(-1001);
        EXPECT_EQ(startConfiguration.getGroundRgbPersonClassifier().getAdjustCropInPercentsOverride().getHeight(), -1001);
        startConfiguration.getGroundRgbPersonClassifier().getAdjustCropInPercentsOverride().setHeight(1000);
        EXPECT_EQ(startConfiguration.getGroundRgbPersonClassifier().getAdjustCropInPercentsOverride().getHeight(), 1000);
        EXPECT_THROW(startConfiguration.getGroundRgbPersonClassifier().getAdjustCropInPercentsOverride().setHeight(-1001 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundRgbPersonClassifier().getAdjustCropInPercentsOverride().setHeight(1000 + 1), std::exception);
    }

    TEST_F(GroundRgbPersonClassifierTest, Update_GroundRgbPersonClassifier_AdjustCropInPercentsOverride_HeightRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbPersonClassifier().getAdjustCropInPercentsOverride().setHeight(-1001);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbPersonClassifier().getAdjustCropInPercentsOverride().getHeight(), -1001);
        pStream->getConfiguration().getGroundRgbPersonClassifier().getAdjustCropInPercentsOverride().setHeight(1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbPersonClassifier().getAdjustCropInPercentsOverride().getHeight(), 1000);
    }

    // Test for ScoreThreshold in GroundRgbPersonClassifier
    TEST_F(GroundRgbPersonClassifierTest, GroundRgbPersonClassifier_Filter_ScoreThresholdDefault) {
        EXPECT_EQ(startConfiguration.getGroundRgbPersonClassifier().getFilter().getScoreThreshold(), 0.0f);
    }

    TEST_F(GroundRgbPersonClassifierTest, Update_GroundRgbPersonClassifier_Filter_ScoreThresholdDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().getScoreThreshold(), 0.0f);
    }

    TEST_F(GroundRgbPersonClassifierTest, GroundRgbPersonClassifier_Filter_ScoreThresholdRange) {
        startConfiguration.getGroundRgbPersonClassifier().getFilter().setScoreThreshold(0.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbPersonClassifier().getFilter().getScoreThreshold(), 0.0f);
        startConfiguration.getGroundRgbPersonClassifier().getFilter().setScoreThreshold(1.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbPersonClassifier().getFilter().getScoreThreshold(), 1.0f);
        EXPECT_THROW(startConfiguration.getGroundRgbPersonClassifier().getFilter().setScoreThreshold(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundRgbPersonClassifier().getFilter().setScoreThreshold(1.0f + 1), std::exception);
    }

    TEST_F(GroundRgbPersonClassifierTest, Update_GroundRgbPersonClassifier_Filter_ScoreThresholdRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().setScoreThreshold(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().getScoreThreshold(), 0.0f);
        pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().setScoreThreshold(1.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().getScoreThreshold(), 1.0f);
    }

    // Test for MinWidth in GroundRgbPersonClassifier
    TEST_F(GroundRgbPersonClassifierTest, GroundRgbPersonClassifier_Filter_MinWidthDefault) {
        EXPECT_EQ(startConfiguration.getGroundRgbPersonClassifier().getFilter().getMinWidth(), 0.0f);
    }

    TEST_F(GroundRgbPersonClassifierTest, Update_GroundRgbPersonClassifier_Filter_MinWidthDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().getMinWidth(), 0.0f);
    }

    TEST_F(GroundRgbPersonClassifierTest, GroundRgbPersonClassifier_Filter_MinWidthRange) {
        startConfiguration.getGroundRgbPersonClassifier().getFilter().setMinWidth(0.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbPersonClassifier().getFilter().getMinWidth(), 0.0f);
        startConfiguration.getGroundRgbPersonClassifier().getFilter().setMinWidth(8192.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbPersonClassifier().getFilter().getMinWidth(), 8192.0f);
        EXPECT_THROW(startConfiguration.getGroundRgbPersonClassifier().getFilter().setMinWidth(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundRgbPersonClassifier().getFilter().setMinWidth(8192.0f + 1), std::exception);
    }

    TEST_F(GroundRgbPersonClassifierTest, Update_GroundRgbPersonClassifier_Filter_MinWidthRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().setMinWidth(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().getMinWidth(), 0.0f);
        pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().setMinWidth(8192.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().getMinWidth(), 8192.0f);
    }

    // Test for MaxWidth in GroundRgbPersonClassifier
    TEST_F(GroundRgbPersonClassifierTest, GroundRgbPersonClassifier_Filter_MaxWidthDefault) {
        EXPECT_EQ(startConfiguration.getGroundRgbPersonClassifier().getFilter().getMaxWidth(), 8192.0f);
    }

    TEST_F(GroundRgbPersonClassifierTest, Update_GroundRgbPersonClassifier_Filter_MaxWidthDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().getMaxWidth(), 8192.0f);
    }

    TEST_F(GroundRgbPersonClassifierTest, GroundRgbPersonClassifier_Filter_MaxWidthRange) {
        startConfiguration.getGroundRgbPersonClassifier().getFilter().setMaxWidth(0.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbPersonClassifier().getFilter().getMaxWidth(), 0.0f);
        startConfiguration.getGroundRgbPersonClassifier().getFilter().setMaxWidth(8192.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbPersonClassifier().getFilter().getMaxWidth(), 8192.0f);
        EXPECT_THROW(startConfiguration.getGroundRgbPersonClassifier().getFilter().setMaxWidth(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundRgbPersonClassifier().getFilter().setMaxWidth(8192.0f + 1), std::exception);
    }

    TEST_F(GroundRgbPersonClassifierTest, Update_GroundRgbPersonClassifier_Filter_MaxWidthRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().setMaxWidth(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().getMaxWidth(), 0.0f);
        pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().setMaxWidth(8192.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().getMaxWidth(), 8192.0f);
    }

    // Test for MinHeight in GroundRgbPersonClassifier
    TEST_F(GroundRgbPersonClassifierTest, GroundRgbPersonClassifier_Filter_MinHeightDefault) {
        EXPECT_EQ(startConfiguration.getGroundRgbPersonClassifier().getFilter().getMinHeight(), 0.0f);
    }

    TEST_F(GroundRgbPersonClassifierTest, Update_GroundRgbPersonClassifier_Filter_MinHeightDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().getMinHeight(), 0.0f);
    }

    TEST_F(GroundRgbPersonClassifierTest, GroundRgbPersonClassifier_Filter_MinHeightRange) {
        startConfiguration.getGroundRgbPersonClassifier().getFilter().setMinHeight(0.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbPersonClassifier().getFilter().getMinHeight(), 0.0f);
        startConfiguration.getGroundRgbPersonClassifier().getFilter().setMinHeight(8192.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbPersonClassifier().getFilter().getMinHeight(), 8192.0f);
        EXPECT_THROW(startConfiguration.getGroundRgbPersonClassifier().getFilter().setMinHeight(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundRgbPersonClassifier().getFilter().setMinHeight(8192.0f + 1), std::exception);
    }

    TEST_F(GroundRgbPersonClassifierTest, Update_GroundRgbPersonClassifier_Filter_MinHeightRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().setMinHeight(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().getMinHeight(), 0.0f);
        pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().setMinHeight(8192.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().getMinHeight(), 8192.0f);
    }

    // Test for MaxHeight in GroundRgbPersonClassifier
    TEST_F(GroundRgbPersonClassifierTest, GroundRgbPersonClassifier_Filter_MaxHeightDefault) {
        EXPECT_EQ(startConfiguration.getGroundRgbPersonClassifier().getFilter().getMaxHeight(), 8192.0f);
    }

    TEST_F(GroundRgbPersonClassifierTest, Update_GroundRgbPersonClassifier_Filter_MaxHeightDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().getMaxHeight(), 8192.0f);
    }

    TEST_F(GroundRgbPersonClassifierTest, GroundRgbPersonClassifier_Filter_MaxHeightRange) {
        startConfiguration.getGroundRgbPersonClassifier().getFilter().setMaxHeight(0.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbPersonClassifier().getFilter().getMaxHeight(), 0.0f);
        startConfiguration.getGroundRgbPersonClassifier().getFilter().setMaxHeight(8192.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbPersonClassifier().getFilter().getMaxHeight(), 8192.0f);
        EXPECT_THROW(startConfiguration.getGroundRgbPersonClassifier().getFilter().setMaxHeight(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundRgbPersonClassifier().getFilter().setMaxHeight(8192.0f + 1), std::exception);
    }

    TEST_F(GroundRgbPersonClassifierTest, Update_GroundRgbPersonClassifier_Filter_MaxHeightRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().setMaxHeight(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().getMaxHeight(), 0.0f);
        pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().setMaxHeight(8192.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().getMaxHeight(), 8192.0f);
    }

    // Test for MinAspectRatio in GroundRgbPersonClassifier
    TEST_F(GroundRgbPersonClassifierTest, GroundRgbPersonClassifier_Filter_MinAspectRatioDefault) {
        EXPECT_EQ(startConfiguration.getGroundRgbPersonClassifier().getFilter().getMinAspectRatio(), 0.01f);
    }

    TEST_F(GroundRgbPersonClassifierTest, Update_GroundRgbPersonClassifier_Filter_MinAspectRatioDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().getMinAspectRatio(), 0.01f);
    }

    TEST_F(GroundRgbPersonClassifierTest, GroundRgbPersonClassifier_Filter_MinAspectRatioRange) {
        startConfiguration.getGroundRgbPersonClassifier().getFilter().setMinAspectRatio(0.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbPersonClassifier().getFilter().getMinAspectRatio(), 0.0f);
        startConfiguration.getGroundRgbPersonClassifier().getFilter().setMinAspectRatio(1000.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbPersonClassifier().getFilter().getMinAspectRatio(), 1000.0f);
        EXPECT_THROW(startConfiguration.getGroundRgbPersonClassifier().getFilter().setMinAspectRatio(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundRgbPersonClassifier().getFilter().setMinAspectRatio(1000.0f + 1), std::exception);
    }

    TEST_F(GroundRgbPersonClassifierTest, Update_GroundRgbPersonClassifier_Filter_MinAspectRatioRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().setMinAspectRatio(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().getMinAspectRatio(), 0.0f);
        pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().setMinAspectRatio(1000.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().getMinAspectRatio(), 1000.0f);
    }

    // Test for MaxAspectRatio in GroundRgbPersonClassifier
    TEST_F(GroundRgbPersonClassifierTest, GroundRgbPersonClassifier_Filter_MaxAspectRatioDefault) {
        EXPECT_EQ(startConfiguration.getGroundRgbPersonClassifier().getFilter().getMaxAspectRatio(), 1000.0f);
    }

    TEST_F(GroundRgbPersonClassifierTest, Update_GroundRgbPersonClassifier_Filter_MaxAspectRatioDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().getMaxAspectRatio(), 1000.0f);
    }

    TEST_F(GroundRgbPersonClassifierTest, GroundRgbPersonClassifier_Filter_MaxAspectRatioRange) {
        startConfiguration.getGroundRgbPersonClassifier().getFilter().setMaxAspectRatio(0.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbPersonClassifier().getFilter().getMaxAspectRatio(), 0.0f);
        startConfiguration.getGroundRgbPersonClassifier().getFilter().setMaxAspectRatio(1000.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbPersonClassifier().getFilter().getMaxAspectRatio(), 1000.0f);
        EXPECT_THROW(startConfiguration.getGroundRgbPersonClassifier().getFilter().setMaxAspectRatio(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundRgbPersonClassifier().getFilter().setMaxAspectRatio(1000.0f + 1), std::exception);
    }

    TEST_F(GroundRgbPersonClassifierTest, Update_GroundRgbPersonClassifier_Filter_MaxAspectRatioRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().setMaxAspectRatio(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().getMaxAspectRatio(), 0.0f);
        pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().setMaxAspectRatio(1000.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbPersonClassifier().getFilter().getMaxAspectRatio(), 1000.0f);
    }

// Test suit for GroundRgbVehicleClassifier
class GroundRgbVehicleClassifierTest : public ::testing::Test {
protected:
    void SetUp() override {
        startConfiguration = pPipeline->createStartStreamConfiguration();
        if (::testing::GTEST_FLAG(update_tests)) {
            tmpStartConfiguration = startConfiguration;
            tmpStartConfiguration.getRawSource(); // Touch Raw Source
            tmpStartConfiguration.getRawSource().setReadTimeoutInSec(0); // Wait forever
            pStream = pPipeline->startStream(tmpStartConfiguration);
            waitForStreamStarted(pStream, data);
        }

    }

    void TearDown() override {
        if (::testing::GTEST_FLAG(update_tests)) {
            pStream.reset();
            waitForStreamStopped(data);
        }

    }

};

    // Test for Enable in GroundRgbVehicleClassifier
    TEST_F(GroundRgbVehicleClassifierTest, GroundRgbVehicleClassifier_EnableDefault) {
        EXPECT_EQ(startConfiguration.getGroundRgbVehicleClassifier().getEnable(), false);
    }

    TEST_F(GroundRgbVehicleClassifierTest, Update_GroundRgbVehicleClassifier_EnableDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbVehicleClassifier().getEnable(), false);
    }

    TEST_F(GroundRgbVehicleClassifierTest, GroundRgbVehicleClassifier_EnableRandom) {
        startConfiguration.getGroundRgbVehicleClassifier().setEnable(false);
        EXPECT_EQ(startConfiguration.getGroundRgbVehicleClassifier().getEnable(), false);
    }

    TEST_F(GroundRgbVehicleClassifierTest, Update_GroundRgbVehicleClassifier_EnableRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbVehicleClassifier().setEnable(false);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbVehicleClassifier().getEnable(), false);
    }

    // Test for Width in GroundRgbVehicleClassifier
    TEST_F(GroundRgbVehicleClassifierTest, GroundRgbVehicleClassifier_AdjustCropInPercentsOverride_WidthDefault) {
        EXPECT_EQ(startConfiguration.getGroundRgbVehicleClassifier().getAdjustCropInPercentsOverride().getWidth(), -1001);
    }

    TEST_F(GroundRgbVehicleClassifierTest, Update_GroundRgbVehicleClassifier_AdjustCropInPercentsOverride_WidthDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbVehicleClassifier().getAdjustCropInPercentsOverride().getWidth(), -1001);
    }

    TEST_F(GroundRgbVehicleClassifierTest, GroundRgbVehicleClassifier_AdjustCropInPercentsOverride_WidthRange) {
        startConfiguration.getGroundRgbVehicleClassifier().getAdjustCropInPercentsOverride().setWidth(-1001);
        EXPECT_EQ(startConfiguration.getGroundRgbVehicleClassifier().getAdjustCropInPercentsOverride().getWidth(), -1001);
        startConfiguration.getGroundRgbVehicleClassifier().getAdjustCropInPercentsOverride().setWidth(1000);
        EXPECT_EQ(startConfiguration.getGroundRgbVehicleClassifier().getAdjustCropInPercentsOverride().getWidth(), 1000);
        EXPECT_THROW(startConfiguration.getGroundRgbVehicleClassifier().getAdjustCropInPercentsOverride().setWidth(-1001 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundRgbVehicleClassifier().getAdjustCropInPercentsOverride().setWidth(1000 + 1), std::exception);
    }

    TEST_F(GroundRgbVehicleClassifierTest, Update_GroundRgbVehicleClassifier_AdjustCropInPercentsOverride_WidthRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbVehicleClassifier().getAdjustCropInPercentsOverride().setWidth(-1001);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbVehicleClassifier().getAdjustCropInPercentsOverride().getWidth(), -1001);
        pStream->getConfiguration().getGroundRgbVehicleClassifier().getAdjustCropInPercentsOverride().setWidth(1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbVehicleClassifier().getAdjustCropInPercentsOverride().getWidth(), 1000);
    }

    // Test for Height in GroundRgbVehicleClassifier
    TEST_F(GroundRgbVehicleClassifierTest, GroundRgbVehicleClassifier_AdjustCropInPercentsOverride_HeightDefault) {
        EXPECT_EQ(startConfiguration.getGroundRgbVehicleClassifier().getAdjustCropInPercentsOverride().getHeight(), -1001);
    }

    TEST_F(GroundRgbVehicleClassifierTest, Update_GroundRgbVehicleClassifier_AdjustCropInPercentsOverride_HeightDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbVehicleClassifier().getAdjustCropInPercentsOverride().getHeight(), -1001);
    }

    TEST_F(GroundRgbVehicleClassifierTest, GroundRgbVehicleClassifier_AdjustCropInPercentsOverride_HeightRange) {
        startConfiguration.getGroundRgbVehicleClassifier().getAdjustCropInPercentsOverride().setHeight(-1001);
        EXPECT_EQ(startConfiguration.getGroundRgbVehicleClassifier().getAdjustCropInPercentsOverride().getHeight(), -1001);
        startConfiguration.getGroundRgbVehicleClassifier().getAdjustCropInPercentsOverride().setHeight(1000);
        EXPECT_EQ(startConfiguration.getGroundRgbVehicleClassifier().getAdjustCropInPercentsOverride().getHeight(), 1000);
        EXPECT_THROW(startConfiguration.getGroundRgbVehicleClassifier().getAdjustCropInPercentsOverride().setHeight(-1001 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundRgbVehicleClassifier().getAdjustCropInPercentsOverride().setHeight(1000 + 1), std::exception);
    }

    TEST_F(GroundRgbVehicleClassifierTest, Update_GroundRgbVehicleClassifier_AdjustCropInPercentsOverride_HeightRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbVehicleClassifier().getAdjustCropInPercentsOverride().setHeight(-1001);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbVehicleClassifier().getAdjustCropInPercentsOverride().getHeight(), -1001);
        pStream->getConfiguration().getGroundRgbVehicleClassifier().getAdjustCropInPercentsOverride().setHeight(1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbVehicleClassifier().getAdjustCropInPercentsOverride().getHeight(), 1000);
    }

    // Test for ScoreThreshold in GroundRgbVehicleClassifier
    TEST_F(GroundRgbVehicleClassifierTest, GroundRgbVehicleClassifier_Filter_ScoreThresholdDefault) {
        EXPECT_EQ(startConfiguration.getGroundRgbVehicleClassifier().getFilter().getScoreThreshold(), 0.0f);
    }

    TEST_F(GroundRgbVehicleClassifierTest, Update_GroundRgbVehicleClassifier_Filter_ScoreThresholdDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().getScoreThreshold(), 0.0f);
    }

    TEST_F(GroundRgbVehicleClassifierTest, GroundRgbVehicleClassifier_Filter_ScoreThresholdRange) {
        startConfiguration.getGroundRgbVehicleClassifier().getFilter().setScoreThreshold(0.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbVehicleClassifier().getFilter().getScoreThreshold(), 0.0f);
        startConfiguration.getGroundRgbVehicleClassifier().getFilter().setScoreThreshold(1.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbVehicleClassifier().getFilter().getScoreThreshold(), 1.0f);
        EXPECT_THROW(startConfiguration.getGroundRgbVehicleClassifier().getFilter().setScoreThreshold(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundRgbVehicleClassifier().getFilter().setScoreThreshold(1.0f + 1), std::exception);
    }

    TEST_F(GroundRgbVehicleClassifierTest, Update_GroundRgbVehicleClassifier_Filter_ScoreThresholdRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().setScoreThreshold(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().getScoreThreshold(), 0.0f);
        pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().setScoreThreshold(1.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().getScoreThreshold(), 1.0f);
    }

    // Test for MinWidth in GroundRgbVehicleClassifier
    TEST_F(GroundRgbVehicleClassifierTest, GroundRgbVehicleClassifier_Filter_MinWidthDefault) {
        EXPECT_EQ(startConfiguration.getGroundRgbVehicleClassifier().getFilter().getMinWidth(), 0.0f);
    }

    TEST_F(GroundRgbVehicleClassifierTest, Update_GroundRgbVehicleClassifier_Filter_MinWidthDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().getMinWidth(), 0.0f);
    }

    TEST_F(GroundRgbVehicleClassifierTest, GroundRgbVehicleClassifier_Filter_MinWidthRange) {
        startConfiguration.getGroundRgbVehicleClassifier().getFilter().setMinWidth(0.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbVehicleClassifier().getFilter().getMinWidth(), 0.0f);
        startConfiguration.getGroundRgbVehicleClassifier().getFilter().setMinWidth(8192.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbVehicleClassifier().getFilter().getMinWidth(), 8192.0f);
        EXPECT_THROW(startConfiguration.getGroundRgbVehicleClassifier().getFilter().setMinWidth(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundRgbVehicleClassifier().getFilter().setMinWidth(8192.0f + 1), std::exception);
    }

    TEST_F(GroundRgbVehicleClassifierTest, Update_GroundRgbVehicleClassifier_Filter_MinWidthRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().setMinWidth(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().getMinWidth(), 0.0f);
        pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().setMinWidth(8192.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().getMinWidth(), 8192.0f);
    }

    // Test for MaxWidth in GroundRgbVehicleClassifier
    TEST_F(GroundRgbVehicleClassifierTest, GroundRgbVehicleClassifier_Filter_MaxWidthDefault) {
        EXPECT_EQ(startConfiguration.getGroundRgbVehicleClassifier().getFilter().getMaxWidth(), 8192.0f);
    }

    TEST_F(GroundRgbVehicleClassifierTest, Update_GroundRgbVehicleClassifier_Filter_MaxWidthDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().getMaxWidth(), 8192.0f);
    }

    TEST_F(GroundRgbVehicleClassifierTest, GroundRgbVehicleClassifier_Filter_MaxWidthRange) {
        startConfiguration.getGroundRgbVehicleClassifier().getFilter().setMaxWidth(0.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbVehicleClassifier().getFilter().getMaxWidth(), 0.0f);
        startConfiguration.getGroundRgbVehicleClassifier().getFilter().setMaxWidth(8192.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbVehicleClassifier().getFilter().getMaxWidth(), 8192.0f);
        EXPECT_THROW(startConfiguration.getGroundRgbVehicleClassifier().getFilter().setMaxWidth(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundRgbVehicleClassifier().getFilter().setMaxWidth(8192.0f + 1), std::exception);
    }

    TEST_F(GroundRgbVehicleClassifierTest, Update_GroundRgbVehicleClassifier_Filter_MaxWidthRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().setMaxWidth(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().getMaxWidth(), 0.0f);
        pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().setMaxWidth(8192.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().getMaxWidth(), 8192.0f);
    }

    // Test for MinHeight in GroundRgbVehicleClassifier
    TEST_F(GroundRgbVehicleClassifierTest, GroundRgbVehicleClassifier_Filter_MinHeightDefault) {
        EXPECT_EQ(startConfiguration.getGroundRgbVehicleClassifier().getFilter().getMinHeight(), 0.0f);
    }

    TEST_F(GroundRgbVehicleClassifierTest, Update_GroundRgbVehicleClassifier_Filter_MinHeightDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().getMinHeight(), 0.0f);
    }

    TEST_F(GroundRgbVehicleClassifierTest, GroundRgbVehicleClassifier_Filter_MinHeightRange) {
        startConfiguration.getGroundRgbVehicleClassifier().getFilter().setMinHeight(0.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbVehicleClassifier().getFilter().getMinHeight(), 0.0f);
        startConfiguration.getGroundRgbVehicleClassifier().getFilter().setMinHeight(8192.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbVehicleClassifier().getFilter().getMinHeight(), 8192.0f);
        EXPECT_THROW(startConfiguration.getGroundRgbVehicleClassifier().getFilter().setMinHeight(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundRgbVehicleClassifier().getFilter().setMinHeight(8192.0f + 1), std::exception);
    }

    TEST_F(GroundRgbVehicleClassifierTest, Update_GroundRgbVehicleClassifier_Filter_MinHeightRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().setMinHeight(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().getMinHeight(), 0.0f);
        pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().setMinHeight(8192.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().getMinHeight(), 8192.0f);
    }

    // Test for MaxHeight in GroundRgbVehicleClassifier
    TEST_F(GroundRgbVehicleClassifierTest, GroundRgbVehicleClassifier_Filter_MaxHeightDefault) {
        EXPECT_EQ(startConfiguration.getGroundRgbVehicleClassifier().getFilter().getMaxHeight(), 8192.0f);
    }

    TEST_F(GroundRgbVehicleClassifierTest, Update_GroundRgbVehicleClassifier_Filter_MaxHeightDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().getMaxHeight(), 8192.0f);
    }

    TEST_F(GroundRgbVehicleClassifierTest, GroundRgbVehicleClassifier_Filter_MaxHeightRange) {
        startConfiguration.getGroundRgbVehicleClassifier().getFilter().setMaxHeight(0.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbVehicleClassifier().getFilter().getMaxHeight(), 0.0f);
        startConfiguration.getGroundRgbVehicleClassifier().getFilter().setMaxHeight(8192.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbVehicleClassifier().getFilter().getMaxHeight(), 8192.0f);
        EXPECT_THROW(startConfiguration.getGroundRgbVehicleClassifier().getFilter().setMaxHeight(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundRgbVehicleClassifier().getFilter().setMaxHeight(8192.0f + 1), std::exception);
    }

    TEST_F(GroundRgbVehicleClassifierTest, Update_GroundRgbVehicleClassifier_Filter_MaxHeightRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().setMaxHeight(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().getMaxHeight(), 0.0f);
        pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().setMaxHeight(8192.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().getMaxHeight(), 8192.0f);
    }

    // Test for MinAspectRatio in GroundRgbVehicleClassifier
    TEST_F(GroundRgbVehicleClassifierTest, GroundRgbVehicleClassifier_Filter_MinAspectRatioDefault) {
        EXPECT_EQ(startConfiguration.getGroundRgbVehicleClassifier().getFilter().getMinAspectRatio(), 0.01f);
    }

    TEST_F(GroundRgbVehicleClassifierTest, Update_GroundRgbVehicleClassifier_Filter_MinAspectRatioDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().getMinAspectRatio(), 0.01f);
    }

    TEST_F(GroundRgbVehicleClassifierTest, GroundRgbVehicleClassifier_Filter_MinAspectRatioRange) {
        startConfiguration.getGroundRgbVehicleClassifier().getFilter().setMinAspectRatio(0.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbVehicleClassifier().getFilter().getMinAspectRatio(), 0.0f);
        startConfiguration.getGroundRgbVehicleClassifier().getFilter().setMinAspectRatio(1000.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbVehicleClassifier().getFilter().getMinAspectRatio(), 1000.0f);
        EXPECT_THROW(startConfiguration.getGroundRgbVehicleClassifier().getFilter().setMinAspectRatio(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundRgbVehicleClassifier().getFilter().setMinAspectRatio(1000.0f + 1), std::exception);
    }

    TEST_F(GroundRgbVehicleClassifierTest, Update_GroundRgbVehicleClassifier_Filter_MinAspectRatioRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().setMinAspectRatio(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().getMinAspectRatio(), 0.0f);
        pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().setMinAspectRatio(1000.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().getMinAspectRatio(), 1000.0f);
    }

    // Test for MaxAspectRatio in GroundRgbVehicleClassifier
    TEST_F(GroundRgbVehicleClassifierTest, GroundRgbVehicleClassifier_Filter_MaxAspectRatioDefault) {
        EXPECT_EQ(startConfiguration.getGroundRgbVehicleClassifier().getFilter().getMaxAspectRatio(), 1000.0f);
    }

    TEST_F(GroundRgbVehicleClassifierTest, Update_GroundRgbVehicleClassifier_Filter_MaxAspectRatioDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().getMaxAspectRatio(), 1000.0f);
    }

    TEST_F(GroundRgbVehicleClassifierTest, GroundRgbVehicleClassifier_Filter_MaxAspectRatioRange) {
        startConfiguration.getGroundRgbVehicleClassifier().getFilter().setMaxAspectRatio(0.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbVehicleClassifier().getFilter().getMaxAspectRatio(), 0.0f);
        startConfiguration.getGroundRgbVehicleClassifier().getFilter().setMaxAspectRatio(1000.0f);
        EXPECT_EQ(startConfiguration.getGroundRgbVehicleClassifier().getFilter().getMaxAspectRatio(), 1000.0f);
        EXPECT_THROW(startConfiguration.getGroundRgbVehicleClassifier().getFilter().setMaxAspectRatio(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGroundRgbVehicleClassifier().getFilter().setMaxAspectRatio(1000.0f + 1), std::exception);
    }

    TEST_F(GroundRgbVehicleClassifierTest, Update_GroundRgbVehicleClassifier_Filter_MaxAspectRatioRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().setMaxAspectRatio(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().getMaxAspectRatio(), 0.0f);
        pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().setMaxAspectRatio(1000.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getGroundRgbVehicleClassifier().getFilter().getMaxAspectRatio(), 1000.0f);
    }

// Test suit for SingleObjectTracker
class SingleObjectTrackerTest : public ::testing::Test {
protected:
    void SetUp() override {
        startConfiguration = pPipeline->createStartStreamConfiguration();
        if (::testing::GTEST_FLAG(update_tests)) {
            tmpStartConfiguration = startConfiguration;
            tmpStartConfiguration.getRawSource(); // Touch Raw Source
            tmpStartConfiguration.getRawSource().setReadTimeoutInSec(0); // Wait forever
            pStream = pPipeline->startStream(tmpStartConfiguration);
            waitForStreamStarted(pStream, data);
        }

    }

    void TearDown() override {
        if (::testing::GTEST_FLAG(update_tests)) {
            pStream.reset();
            waitForStreamStopped(data);
        }

    }

};

    // Test for UpdateScoreThreshold in SingleObjectTracker
    TEST_F(SingleObjectTrackerTest, SingleObjectTracker_UpdateScoreThresholdDefault) {
        EXPECT_EQ(startConfiguration.getSingleObjectTracker().getUpdateScoreThreshold(), 0.9);
    }

    TEST_F(SingleObjectTrackerTest, Update_SingleObjectTracker_UpdateScoreThresholdDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getSingleObjectTracker().getUpdateScoreThreshold(), 0.9);
    }

    TEST_F(SingleObjectTrackerTest, SingleObjectTracker_UpdateScoreThresholdRandom) {
        startConfiguration.getSingleObjectTracker().setUpdateScoreThreshold(0.35f);
        EXPECT_EQ(startConfiguration.getSingleObjectTracker().getUpdateScoreThreshold(), 0.35f);
    }

    TEST_F(SingleObjectTrackerTest, Update_SingleObjectTracker_UpdateScoreThresholdRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getSingleObjectTracker().setUpdateScoreThreshold(0.35f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getSingleObjectTracker().getUpdateScoreThreshold(), 0.35f);
    }

// Test suit for TrackerRate
class TrackerRateTest : public ::testing::Test {
protected:
    void SetUp() override {
        startConfiguration = pPipeline->createStartStreamConfiguration();
        if (::testing::GTEST_FLAG(update_tests)) {
            tmpStartConfiguration = startConfiguration;
            tmpStartConfiguration.getRawSource(); // Touch Raw Source
            tmpStartConfiguration.getRawSource().setReadTimeoutInSec(0); // Wait forever
            pStream = pPipeline->startStream(tmpStartConfiguration);
            waitForStreamStarted(pStream, data);
        }

    }

    void TearDown() override {
        if (::testing::GTEST_FLAG(update_tests)) {
            pStream.reset();
            waitForStreamStopped(data);
        }

    }

};

    // Test for OutputFramerate in TrackerRate
    TEST_F(TrackerRateTest, TrackerRate_OutputFramerateDefault) {
        EXPECT_EQ(startConfiguration.getTrackerRate().getOutputFramerate(), 0);
    }

    TEST_F(TrackerRateTest, Update_TrackerRate_OutputFramerateDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getTrackerRate().getOutputFramerate(), 0);
    }

    TEST_F(TrackerRateTest, TrackerRate_OutputFramerateRandom) {
        startConfiguration.getTrackerRate().setOutputFramerate(20);
        EXPECT_EQ(startConfiguration.getTrackerRate().getOutputFramerate(), 20);
    }

    TEST_F(TrackerRateTest, Update_TrackerRate_OutputFramerateRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getTrackerRate().setOutputFramerate(20);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getTrackerRate().getOutputFramerate(), 20);
    }

// Test suit for PersonTracker
class PersonTrackerTest : public ::testing::Test {
protected:
    void SetUp() override {
        startConfiguration = pPipeline->createStartStreamConfiguration();
        if (::testing::GTEST_FLAG(update_tests)) {
            tmpStartConfiguration = startConfiguration;
            tmpStartConfiguration.getRawSource(); // Touch Raw Source
            tmpStartConfiguration.getRawSource().setReadTimeoutInSec(0); // Wait forever
            pStream = pPipeline->startStream(tmpStartConfiguration);
            waitForStreamStarted(pStream, data);
        }

    }

    void TearDown() override {
        if (::testing::GTEST_FLAG(update_tests)) {
            pStream.reset();
            waitForStreamStopped(data);
        }

    }

};

    // Test for Enable in PersonTracker
    TEST_F(PersonTrackerTest, PersonTracker_EnableDefault) {
        EXPECT_EQ(startConfiguration.getPersonTracker().getEnable(), true);
    }

    TEST_F(PersonTrackerTest, Update_PersonTracker_EnableDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getPersonTracker().getEnable(), true);
    }

    TEST_F(PersonTrackerTest, PersonTracker_EnableRandom) {
        startConfiguration.getPersonTracker().setEnable(true);
        EXPECT_EQ(startConfiguration.getPersonTracker().getEnable(), true);
    }

    TEST_F(PersonTrackerTest, Update_PersonTracker_EnableRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getPersonTracker().setEnable(true);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getPersonTracker().getEnable(), true);
    }

    // Test for MaxTimeSinceUpdateToReportMs in PersonTracker
    TEST_F(PersonTrackerTest, PersonTracker_MaxTimeSinceUpdateToReportMsDefault) {
        EXPECT_EQ(startConfiguration.getPersonTracker().getMaxTimeSinceUpdateToReportMs(), 1000);
    }

    TEST_F(PersonTrackerTest, Update_PersonTracker_MaxTimeSinceUpdateToReportMsDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getPersonTracker().getMaxTimeSinceUpdateToReportMs(), 1000);
    }

    TEST_F(PersonTrackerTest, PersonTracker_MaxTimeSinceUpdateToReportMsRandom) {
        startConfiguration.getPersonTracker().setMaxTimeSinceUpdateToReportMs(21126);
        EXPECT_EQ(startConfiguration.getPersonTracker().getMaxTimeSinceUpdateToReportMs(), 21126);
    }

    TEST_F(PersonTrackerTest, Update_PersonTracker_MaxTimeSinceUpdateToReportMsRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getPersonTracker().setMaxTimeSinceUpdateToReportMs(21126);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getPersonTracker().getMaxTimeSinceUpdateToReportMs(), 21126);
    }

    // Test for InitTrackSize in PersonTracker
    TEST_F(PersonTrackerTest, PersonTracker_InitTrackSizeDefault) {
        EXPECT_EQ(startConfiguration.getPersonTracker().getInitTrackSize(), 4);
    }

    TEST_F(PersonTrackerTest, Update_PersonTracker_InitTrackSizeDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getPersonTracker().getInitTrackSize(), 4);
    }

    TEST_F(PersonTrackerTest, PersonTracker_InitTrackSizeRange) {
        startConfiguration.getPersonTracker().setInitTrackSize(1);
        EXPECT_EQ(startConfiguration.getPersonTracker().getInitTrackSize(), 1);
        startConfiguration.getPersonTracker().setInitTrackSize(100);
        EXPECT_EQ(startConfiguration.getPersonTracker().getInitTrackSize(), 100);
        EXPECT_THROW(startConfiguration.getPersonTracker().setInitTrackSize(1 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getPersonTracker().setInitTrackSize(100 + 1), std::exception);
    }

    TEST_F(PersonTrackerTest, Update_PersonTracker_InitTrackSizeRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getPersonTracker().setInitTrackSize(1);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getPersonTracker().getInitTrackSize(), 1);
        pStream->getConfiguration().getPersonTracker().setInitTrackSize(100);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getPersonTracker().getInitTrackSize(), 100);
    }

    // Test for InitThreshold in PersonTracker
    TEST_F(PersonTrackerTest, PersonTracker_InitThresholdDefault) {
        EXPECT_EQ(startConfiguration.getPersonTracker().getInitThreshold(), 0.5f);
    }

    TEST_F(PersonTrackerTest, Update_PersonTracker_InitThresholdDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getPersonTracker().getInitThreshold(), 0.5f);
    }

    TEST_F(PersonTrackerTest, PersonTracker_InitThresholdRange) {
        startConfiguration.getPersonTracker().setInitThreshold(0.0f);
        EXPECT_EQ(startConfiguration.getPersonTracker().getInitThreshold(), 0.0f);
        startConfiguration.getPersonTracker().setInitThreshold(1.0f);
        EXPECT_EQ(startConfiguration.getPersonTracker().getInitThreshold(), 1.0f);
        EXPECT_THROW(startConfiguration.getPersonTracker().setInitThreshold(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getPersonTracker().setInitThreshold(1.0f + 1), std::exception);
    }

    TEST_F(PersonTrackerTest, Update_PersonTracker_InitThresholdRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getPersonTracker().setInitThreshold(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getPersonTracker().getInitThreshold(), 0.0f);
        pStream->getConfiguration().getPersonTracker().setInitThreshold(1.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getPersonTracker().getInitThreshold(), 1.0f);
    }

    // Test for InitMetric in PersonTracker
    TEST_F(PersonTrackerTest, PersonTracker_InitMetricDefault) {
        EXPECT_EQ(startConfiguration.getPersonTracker().getInitMetric(), sdk::InitScoreMetric::Median);
    }

    TEST_F(PersonTrackerTest, Update_PersonTracker_InitMetricDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getPersonTracker().getInitMetric(), sdk::InitScoreMetric::Median);
    }

    // Test for InitMetric in PersonTracker (enum)
    TEST_F(PersonTrackerTest, PersonTracker_InitMetricEnum) {
        startConfiguration.getPersonTracker().setInitMetric(sdk::InitScoreMetric::Average);
        EXPECT_EQ(startConfiguration.getPersonTracker().getInitMetric(), sdk::InitScoreMetric::Average) << testing::PrintToString(sdk::InitScoreMetric::Average);
        startConfiguration.getPersonTracker().setInitMetric(sdk::InitScoreMetric::Median);
        EXPECT_EQ(startConfiguration.getPersonTracker().getInitMetric(), sdk::InitScoreMetric::Median) << testing::PrintToString(sdk::InitScoreMetric::Median);
    }

    TEST_F(PersonTrackerTest, Update_PersonTracker_InitMetricEnum) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getPersonTracker().setInitMetric(sdk::InitScoreMetric::Average);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getPersonTracker().getInitMetric(), sdk::InitScoreMetric::Average) << testing::PrintToString(sdk::InitScoreMetric::Average);
        pStream->getConfiguration().getPersonTracker().setInitMetric(sdk::InitScoreMetric::Median);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getPersonTracker().getInitMetric(), sdk::InitScoreMetric::Median) << testing::PrintToString(sdk::InitScoreMetric::Median);
    }

    // Test for MaxPredictedTimeMs in PersonTracker
    TEST_F(PersonTrackerTest, PersonTracker_MaxPredictedTimeMsDefault) {
        EXPECT_EQ(startConfiguration.getPersonTracker().getMaxPredictedTimeMs(), 1000);
    }

    TEST_F(PersonTrackerTest, Update_PersonTracker_MaxPredictedTimeMsDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getPersonTracker().getMaxPredictedTimeMs(), 1000);
    }

    TEST_F(PersonTrackerTest, PersonTracker_MaxPredictedTimeMsRandom) {
        startConfiguration.getPersonTracker().setMaxPredictedTimeMs(14090);
        EXPECT_EQ(startConfiguration.getPersonTracker().getMaxPredictedTimeMs(), 14090);
    }

    TEST_F(PersonTrackerTest, Update_PersonTracker_MaxPredictedTimeMsRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getPersonTracker().setMaxPredictedTimeMs(14090);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getPersonTracker().getMaxPredictedTimeMs(), 14090);
    }

    // Test for TrackFeaturesHistorySize in PersonTracker
    TEST_F(PersonTrackerTest, PersonTracker_TrackFeaturesHistorySizeDefault) {
        EXPECT_EQ(startConfiguration.getPersonTracker().getTrackFeaturesHistorySize(), 50);
    }

    TEST_F(PersonTrackerTest, Update_PersonTracker_TrackFeaturesHistorySizeDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getPersonTracker().getTrackFeaturesHistorySize(), 50);
    }

    TEST_F(PersonTrackerTest, PersonTracker_TrackFeaturesHistorySizeRange) {
        startConfiguration.getPersonTracker().setTrackFeaturesHistorySize(1);
        EXPECT_EQ(startConfiguration.getPersonTracker().getTrackFeaturesHistorySize(), 1);
        startConfiguration.getPersonTracker().setTrackFeaturesHistorySize(1000);
        EXPECT_EQ(startConfiguration.getPersonTracker().getTrackFeaturesHistorySize(), 1000);
        EXPECT_THROW(startConfiguration.getPersonTracker().setTrackFeaturesHistorySize(1 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getPersonTracker().setTrackFeaturesHistorySize(1000 + 1), std::exception);
    }

    TEST_F(PersonTrackerTest, Update_PersonTracker_TrackFeaturesHistorySizeRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getPersonTracker().setTrackFeaturesHistorySize(1);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getPersonTracker().getTrackFeaturesHistorySize(), 1);
        pStream->getConfiguration().getPersonTracker().setTrackFeaturesHistorySize(1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getPersonTracker().getTrackFeaturesHistorySize(), 1000);
    }

    // Test for FeatureWeight in PersonTracker
    TEST_F(PersonTrackerTest, PersonTracker_FeatureWeightDefault) {
        EXPECT_EQ(startConfiguration.getPersonTracker().getFeatureWeight(), 0.0f);
    }

    TEST_F(PersonTrackerTest, Update_PersonTracker_FeatureWeightDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getPersonTracker().getFeatureWeight(), 0.0f);
    }

    TEST_F(PersonTrackerTest, PersonTracker_FeatureWeightRange) {
        startConfiguration.getPersonTracker().setFeatureWeight(-1.0f);
        EXPECT_EQ(startConfiguration.getPersonTracker().getFeatureWeight(), -1.0f);
        startConfiguration.getPersonTracker().setFeatureWeight(1.0f);
        EXPECT_EQ(startConfiguration.getPersonTracker().getFeatureWeight(), 1.0f);
        EXPECT_THROW(startConfiguration.getPersonTracker().setFeatureWeight(-1.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getPersonTracker().setFeatureWeight(1.0f + 1), std::exception);
    }

    TEST_F(PersonTrackerTest, Update_PersonTracker_FeatureWeightRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getPersonTracker().setFeatureWeight(-1.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getPersonTracker().getFeatureWeight(), -1.0f);
        pStream->getConfiguration().getPersonTracker().setFeatureWeight(1.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getPersonTracker().getFeatureWeight(), 1.0f);
    }

    // Test for MaxCosineDistance in PersonTracker
    TEST_F(PersonTrackerTest, PersonTracker_MaxCosineDistanceDefault) {
        EXPECT_EQ(startConfiguration.getPersonTracker().getMaxCosineDistance(), 0.6f);
    }

    TEST_F(PersonTrackerTest, Update_PersonTracker_MaxCosineDistanceDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getPersonTracker().getMaxCosineDistance(), 0.6f);
    }

    TEST_F(PersonTrackerTest, PersonTracker_MaxCosineDistanceRange) {
        startConfiguration.getPersonTracker().setMaxCosineDistance(0.0f);
        EXPECT_EQ(startConfiguration.getPersonTracker().getMaxCosineDistance(), 0.0f);
        startConfiguration.getPersonTracker().setMaxCosineDistance(1.0f);
        EXPECT_EQ(startConfiguration.getPersonTracker().getMaxCosineDistance(), 1.0f);
        EXPECT_THROW(startConfiguration.getPersonTracker().setMaxCosineDistance(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getPersonTracker().setMaxCosineDistance(1.0f + 1), std::exception);
    }

    TEST_F(PersonTrackerTest, Update_PersonTracker_MaxCosineDistanceRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getPersonTracker().setMaxCosineDistance(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getPersonTracker().getMaxCosineDistance(), 0.0f);
        pStream->getConfiguration().getPersonTracker().setMaxCosineDistance(1.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getPersonTracker().getMaxCosineDistance(), 1.0f);
    }

    // Test for MaxMahalanobisDistance in PersonTracker
    TEST_F(PersonTrackerTest, PersonTracker_MaxMahalanobisDistanceDefault) {
        EXPECT_EQ(startConfiguration.getPersonTracker().getMaxMahalanobisDistance(), 10.0f);
    }

    TEST_F(PersonTrackerTest, Update_PersonTracker_MaxMahalanobisDistanceDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getPersonTracker().getMaxMahalanobisDistance(), 10.0f);
    }

    TEST_F(PersonTrackerTest, PersonTracker_MaxMahalanobisDistanceRange) {
        startConfiguration.getPersonTracker().setMaxMahalanobisDistance(0.0f);
        EXPECT_EQ(startConfiguration.getPersonTracker().getMaxMahalanobisDistance(), 0.0f);
        startConfiguration.getPersonTracker().setMaxMahalanobisDistance(100.0f);
        EXPECT_EQ(startConfiguration.getPersonTracker().getMaxMahalanobisDistance(), 100.0f);
        EXPECT_THROW(startConfiguration.getPersonTracker().setMaxMahalanobisDistance(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getPersonTracker().setMaxMahalanobisDistance(100.0f + 1), std::exception);
    }

    TEST_F(PersonTrackerTest, Update_PersonTracker_MaxMahalanobisDistanceRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getPersonTracker().setMaxMahalanobisDistance(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getPersonTracker().getMaxMahalanobisDistance(), 0.0f);
        pStream->getConfiguration().getPersonTracker().setMaxMahalanobisDistance(100.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getPersonTracker().getMaxMahalanobisDistance(), 100.0f);
    }

    // Test for MinIouThreshold in PersonTracker
    TEST_F(PersonTrackerTest, PersonTracker_MinIouThresholdDefault) {
        EXPECT_EQ(startConfiguration.getPersonTracker().getMinIouThreshold(), 0.1f);
    }

    TEST_F(PersonTrackerTest, Update_PersonTracker_MinIouThresholdDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getPersonTracker().getMinIouThreshold(), 0.1f);
    }

    TEST_F(PersonTrackerTest, PersonTracker_MinIouThresholdRange) {
        startConfiguration.getPersonTracker().setMinIouThreshold(0.0f);
        EXPECT_EQ(startConfiguration.getPersonTracker().getMinIouThreshold(), 0.0f);
        startConfiguration.getPersonTracker().setMinIouThreshold(1.0f);
        EXPECT_EQ(startConfiguration.getPersonTracker().getMinIouThreshold(), 1.0f);
        EXPECT_THROW(startConfiguration.getPersonTracker().setMinIouThreshold(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getPersonTracker().setMinIouThreshold(1.0f + 1), std::exception);
    }

    TEST_F(PersonTrackerTest, Update_PersonTracker_MinIouThresholdRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getPersonTracker().setMinIouThreshold(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getPersonTracker().getMinIouThreshold(), 0.0f);
        pStream->getConfiguration().getPersonTracker().setMinIouThreshold(1.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getPersonTracker().getMinIouThreshold(), 1.0f);
    }

// Test suit for VehicleTracker
class VehicleTrackerTest : public ::testing::Test {
protected:
    void SetUp() override {
        startConfiguration = pPipeline->createStartStreamConfiguration();
        if (::testing::GTEST_FLAG(update_tests)) {
            tmpStartConfiguration = startConfiguration;
            tmpStartConfiguration.getRawSource(); // Touch Raw Source
            tmpStartConfiguration.getRawSource().setReadTimeoutInSec(0); // Wait forever
            pStream = pPipeline->startStream(tmpStartConfiguration);
            waitForStreamStarted(pStream, data);
        }

    }

    void TearDown() override {
        if (::testing::GTEST_FLAG(update_tests)) {
            pStream.reset();
            waitForStreamStopped(data);
        }

    }

};

    // Test for Enable in VehicleTracker
    TEST_F(VehicleTrackerTest, VehicleTracker_EnableDefault) {
        EXPECT_EQ(startConfiguration.getVehicleTracker().getEnable(), true);
    }

    TEST_F(VehicleTrackerTest, Update_VehicleTracker_EnableDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getVehicleTracker().getEnable(), true);
    }

    TEST_F(VehicleTrackerTest, VehicleTracker_EnableRandom) {
        startConfiguration.getVehicleTracker().setEnable(true);
        EXPECT_EQ(startConfiguration.getVehicleTracker().getEnable(), true);
    }

    TEST_F(VehicleTrackerTest, Update_VehicleTracker_EnableRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getVehicleTracker().setEnable(true);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVehicleTracker().getEnable(), true);
    }

    // Test for MaxTimeSinceUpdateToReportMs in VehicleTracker
    TEST_F(VehicleTrackerTest, VehicleTracker_MaxTimeSinceUpdateToReportMsDefault) {
        EXPECT_EQ(startConfiguration.getVehicleTracker().getMaxTimeSinceUpdateToReportMs(), 1000);
    }

    TEST_F(VehicleTrackerTest, Update_VehicleTracker_MaxTimeSinceUpdateToReportMsDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getVehicleTracker().getMaxTimeSinceUpdateToReportMs(), 1000);
    }

    TEST_F(VehicleTrackerTest, VehicleTracker_MaxTimeSinceUpdateToReportMsRandom) {
        startConfiguration.getVehicleTracker().setMaxTimeSinceUpdateToReportMs(46854);
        EXPECT_EQ(startConfiguration.getVehicleTracker().getMaxTimeSinceUpdateToReportMs(), 46854);
    }

    TEST_F(VehicleTrackerTest, Update_VehicleTracker_MaxTimeSinceUpdateToReportMsRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getVehicleTracker().setMaxTimeSinceUpdateToReportMs(46854);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVehicleTracker().getMaxTimeSinceUpdateToReportMs(), 46854);
    }

    // Test for InitTrackSize in VehicleTracker
    TEST_F(VehicleTrackerTest, VehicleTracker_InitTrackSizeDefault) {
        EXPECT_EQ(startConfiguration.getVehicleTracker().getInitTrackSize(), 8);
    }

    TEST_F(VehicleTrackerTest, Update_VehicleTracker_InitTrackSizeDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getVehicleTracker().getInitTrackSize(), 8);
    }

    TEST_F(VehicleTrackerTest, VehicleTracker_InitTrackSizeRange) {
        startConfiguration.getVehicleTracker().setInitTrackSize(1);
        EXPECT_EQ(startConfiguration.getVehicleTracker().getInitTrackSize(), 1);
        startConfiguration.getVehicleTracker().setInitTrackSize(100);
        EXPECT_EQ(startConfiguration.getVehicleTracker().getInitTrackSize(), 100);
        EXPECT_THROW(startConfiguration.getVehicleTracker().setInitTrackSize(1 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getVehicleTracker().setInitTrackSize(100 + 1), std::exception);
    }

    TEST_F(VehicleTrackerTest, Update_VehicleTracker_InitTrackSizeRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getVehicleTracker().setInitTrackSize(1);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVehicleTracker().getInitTrackSize(), 1);
        pStream->getConfiguration().getVehicleTracker().setInitTrackSize(100);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVehicleTracker().getInitTrackSize(), 100);
    }

    // Test for InitThreshold in VehicleTracker
    TEST_F(VehicleTrackerTest, VehicleTracker_InitThresholdDefault) {
        EXPECT_EQ(startConfiguration.getVehicleTracker().getInitThreshold(), 0.2f);
    }

    TEST_F(VehicleTrackerTest, Update_VehicleTracker_InitThresholdDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getVehicleTracker().getInitThreshold(), 0.2f);
    }

    TEST_F(VehicleTrackerTest, VehicleTracker_InitThresholdRange) {
        startConfiguration.getVehicleTracker().setInitThreshold(0.0f);
        EXPECT_EQ(startConfiguration.getVehicleTracker().getInitThreshold(), 0.0f);
        startConfiguration.getVehicleTracker().setInitThreshold(1.0f);
        EXPECT_EQ(startConfiguration.getVehicleTracker().getInitThreshold(), 1.0f);
        EXPECT_THROW(startConfiguration.getVehicleTracker().setInitThreshold(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getVehicleTracker().setInitThreshold(1.0f + 1), std::exception);
    }

    TEST_F(VehicleTrackerTest, Update_VehicleTracker_InitThresholdRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getVehicleTracker().setInitThreshold(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVehicleTracker().getInitThreshold(), 0.0f);
        pStream->getConfiguration().getVehicleTracker().setInitThreshold(1.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVehicleTracker().getInitThreshold(), 1.0f);
    }

    // Test for InitMetric in VehicleTracker
    TEST_F(VehicleTrackerTest, VehicleTracker_InitMetricDefault) {
        EXPECT_EQ(startConfiguration.getVehicleTracker().getInitMetric(), sdk::InitScoreMetric::Median);
    }

    TEST_F(VehicleTrackerTest, Update_VehicleTracker_InitMetricDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getVehicleTracker().getInitMetric(), sdk::InitScoreMetric::Median);
    }

    // Test for InitMetric in VehicleTracker (enum)
    TEST_F(VehicleTrackerTest, VehicleTracker_InitMetricEnum) {
        startConfiguration.getVehicleTracker().setInitMetric(sdk::InitScoreMetric::Average);
        EXPECT_EQ(startConfiguration.getVehicleTracker().getInitMetric(), sdk::InitScoreMetric::Average) << testing::PrintToString(sdk::InitScoreMetric::Average);
        startConfiguration.getVehicleTracker().setInitMetric(sdk::InitScoreMetric::Median);
        EXPECT_EQ(startConfiguration.getVehicleTracker().getInitMetric(), sdk::InitScoreMetric::Median) << testing::PrintToString(sdk::InitScoreMetric::Median);
    }

    TEST_F(VehicleTrackerTest, Update_VehicleTracker_InitMetricEnum) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getVehicleTracker().setInitMetric(sdk::InitScoreMetric::Average);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVehicleTracker().getInitMetric(), sdk::InitScoreMetric::Average) << testing::PrintToString(sdk::InitScoreMetric::Average);
        pStream->getConfiguration().getVehicleTracker().setInitMetric(sdk::InitScoreMetric::Median);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVehicleTracker().getInitMetric(), sdk::InitScoreMetric::Median) << testing::PrintToString(sdk::InitScoreMetric::Median);
    }

    // Test for MaxPredictedTimeMs in VehicleTracker
    TEST_F(VehicleTrackerTest, VehicleTracker_MaxPredictedTimeMsDefault) {
        EXPECT_EQ(startConfiguration.getVehicleTracker().getMaxPredictedTimeMs(), 1000);
    }

    TEST_F(VehicleTrackerTest, Update_VehicleTracker_MaxPredictedTimeMsDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getVehicleTracker().getMaxPredictedTimeMs(), 1000);
    }

    TEST_F(VehicleTrackerTest, VehicleTracker_MaxPredictedTimeMsRandom) {
        startConfiguration.getVehicleTracker().setMaxPredictedTimeMs(43586);
        EXPECT_EQ(startConfiguration.getVehicleTracker().getMaxPredictedTimeMs(), 43586);
    }

    TEST_F(VehicleTrackerTest, Update_VehicleTracker_MaxPredictedTimeMsRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getVehicleTracker().setMaxPredictedTimeMs(43586);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVehicleTracker().getMaxPredictedTimeMs(), 43586);
    }

    // Test for TrackFeaturesHistorySize in VehicleTracker
    TEST_F(VehicleTrackerTest, VehicleTracker_TrackFeaturesHistorySizeDefault) {
        EXPECT_EQ(startConfiguration.getVehicleTracker().getTrackFeaturesHistorySize(), 1);
    }

    TEST_F(VehicleTrackerTest, Update_VehicleTracker_TrackFeaturesHistorySizeDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getVehicleTracker().getTrackFeaturesHistorySize(), 1);
    }

    TEST_F(VehicleTrackerTest, VehicleTracker_TrackFeaturesHistorySizeRange) {
        startConfiguration.getVehicleTracker().setTrackFeaturesHistorySize(1);
        EXPECT_EQ(startConfiguration.getVehicleTracker().getTrackFeaturesHistorySize(), 1);
        startConfiguration.getVehicleTracker().setTrackFeaturesHistorySize(1000);
        EXPECT_EQ(startConfiguration.getVehicleTracker().getTrackFeaturesHistorySize(), 1000);
        EXPECT_THROW(startConfiguration.getVehicleTracker().setTrackFeaturesHistorySize(1 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getVehicleTracker().setTrackFeaturesHistorySize(1000 + 1), std::exception);
    }

    TEST_F(VehicleTrackerTest, Update_VehicleTracker_TrackFeaturesHistorySizeRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getVehicleTracker().setTrackFeaturesHistorySize(1);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVehicleTracker().getTrackFeaturesHistorySize(), 1);
        pStream->getConfiguration().getVehicleTracker().setTrackFeaturesHistorySize(1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVehicleTracker().getTrackFeaturesHistorySize(), 1000);
    }

    // Test for FeatureWeight in VehicleTracker
    TEST_F(VehicleTrackerTest, VehicleTracker_FeatureWeightDefault) {
        EXPECT_EQ(startConfiguration.getVehicleTracker().getFeatureWeight(), 0.0f);
    }

    TEST_F(VehicleTrackerTest, Update_VehicleTracker_FeatureWeightDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getVehicleTracker().getFeatureWeight(), 0.0f);
    }

    TEST_F(VehicleTrackerTest, VehicleTracker_FeatureWeightRange) {
        startConfiguration.getVehicleTracker().setFeatureWeight(-1.0f);
        EXPECT_EQ(startConfiguration.getVehicleTracker().getFeatureWeight(), -1.0f);
        startConfiguration.getVehicleTracker().setFeatureWeight(1.0f);
        EXPECT_EQ(startConfiguration.getVehicleTracker().getFeatureWeight(), 1.0f);
        EXPECT_THROW(startConfiguration.getVehicleTracker().setFeatureWeight(-1.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getVehicleTracker().setFeatureWeight(1.0f + 1), std::exception);
    }

    TEST_F(VehicleTrackerTest, Update_VehicleTracker_FeatureWeightRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getVehicleTracker().setFeatureWeight(-1.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVehicleTracker().getFeatureWeight(), -1.0f);
        pStream->getConfiguration().getVehicleTracker().setFeatureWeight(1.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVehicleTracker().getFeatureWeight(), 1.0f);
    }

    // Test for MaxCosineDistance in VehicleTracker
    TEST_F(VehicleTrackerTest, VehicleTracker_MaxCosineDistanceDefault) {
        EXPECT_EQ(startConfiguration.getVehicleTracker().getMaxCosineDistance(), 0.15f);
    }

    TEST_F(VehicleTrackerTest, Update_VehicleTracker_MaxCosineDistanceDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getVehicleTracker().getMaxCosineDistance(), 0.15f);
    }

    TEST_F(VehicleTrackerTest, VehicleTracker_MaxCosineDistanceRange) {
        startConfiguration.getVehicleTracker().setMaxCosineDistance(0.0f);
        EXPECT_EQ(startConfiguration.getVehicleTracker().getMaxCosineDistance(), 0.0f);
        startConfiguration.getVehicleTracker().setMaxCosineDistance(1.0f);
        EXPECT_EQ(startConfiguration.getVehicleTracker().getMaxCosineDistance(), 1.0f);
        EXPECT_THROW(startConfiguration.getVehicleTracker().setMaxCosineDistance(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getVehicleTracker().setMaxCosineDistance(1.0f + 1), std::exception);
    }

    TEST_F(VehicleTrackerTest, Update_VehicleTracker_MaxCosineDistanceRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getVehicleTracker().setMaxCosineDistance(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVehicleTracker().getMaxCosineDistance(), 0.0f);
        pStream->getConfiguration().getVehicleTracker().setMaxCosineDistance(1.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVehicleTracker().getMaxCosineDistance(), 1.0f);
    }

    // Test for MaxMahalanobisDistance in VehicleTracker
    TEST_F(VehicleTrackerTest, VehicleTracker_MaxMahalanobisDistanceDefault) {
        EXPECT_EQ(startConfiguration.getVehicleTracker().getMaxMahalanobisDistance(), 12.0f);
    }

    TEST_F(VehicleTrackerTest, Update_VehicleTracker_MaxMahalanobisDistanceDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getVehicleTracker().getMaxMahalanobisDistance(), 12.0f);
    }

    TEST_F(VehicleTrackerTest, VehicleTracker_MaxMahalanobisDistanceRange) {
        startConfiguration.getVehicleTracker().setMaxMahalanobisDistance(0.0f);
        EXPECT_EQ(startConfiguration.getVehicleTracker().getMaxMahalanobisDistance(), 0.0f);
        startConfiguration.getVehicleTracker().setMaxMahalanobisDistance(100.0f);
        EXPECT_EQ(startConfiguration.getVehicleTracker().getMaxMahalanobisDistance(), 100.0f);
        EXPECT_THROW(startConfiguration.getVehicleTracker().setMaxMahalanobisDistance(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getVehicleTracker().setMaxMahalanobisDistance(100.0f + 1), std::exception);
    }

    TEST_F(VehicleTrackerTest, Update_VehicleTracker_MaxMahalanobisDistanceRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getVehicleTracker().setMaxMahalanobisDistance(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVehicleTracker().getMaxMahalanobisDistance(), 0.0f);
        pStream->getConfiguration().getVehicleTracker().setMaxMahalanobisDistance(100.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVehicleTracker().getMaxMahalanobisDistance(), 100.0f);
    }

    // Test for MinIouThreshold in VehicleTracker
    TEST_F(VehicleTrackerTest, VehicleTracker_MinIouThresholdDefault) {
        EXPECT_EQ(startConfiguration.getVehicleTracker().getMinIouThreshold(), 0.1f);
    }

    TEST_F(VehicleTrackerTest, Update_VehicleTracker_MinIouThresholdDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getVehicleTracker().getMinIouThreshold(), 0.1f);
    }

    TEST_F(VehicleTrackerTest, VehicleTracker_MinIouThresholdRange) {
        startConfiguration.getVehicleTracker().setMinIouThreshold(0.0f);
        EXPECT_EQ(startConfiguration.getVehicleTracker().getMinIouThreshold(), 0.0f);
        startConfiguration.getVehicleTracker().setMinIouThreshold(1.0f);
        EXPECT_EQ(startConfiguration.getVehicleTracker().getMinIouThreshold(), 1.0f);
        EXPECT_THROW(startConfiguration.getVehicleTracker().setMinIouThreshold(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getVehicleTracker().setMinIouThreshold(1.0f + 1), std::exception);
    }

    TEST_F(VehicleTrackerTest, Update_VehicleTracker_MinIouThresholdRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getVehicleTracker().setMinIouThreshold(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVehicleTracker().getMinIouThreshold(), 0.0f);
        pStream->getConfiguration().getVehicleTracker().setMinIouThreshold(1.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVehicleTracker().getMinIouThreshold(), 1.0f);
    }

// Test suit for VmdTracker
class VmdTrackerTest : public ::testing::Test {
protected:
    void SetUp() override {
        startConfiguration = pPipeline->createStartStreamConfiguration();
        if (::testing::GTEST_FLAG(update_tests)) {
            tmpStartConfiguration = startConfiguration;
            tmpStartConfiguration.getRawSource(); // Touch Raw Source
            tmpStartConfiguration.getRawSource().setReadTimeoutInSec(0); // Wait forever
            pStream = pPipeline->startStream(tmpStartConfiguration);
            waitForStreamStarted(pStream, data);
        }

    }

    void TearDown() override {
        if (::testing::GTEST_FLAG(update_tests)) {
            pStream.reset();
            waitForStreamStopped(data);
        }

    }

};

    // Test for Enable in VmdTracker
    TEST_F(VmdTrackerTest, VmdTracker_EnableDefault) {
        EXPECT_EQ(startConfiguration.getVmdTracker().getEnable(), true);
    }

    TEST_F(VmdTrackerTest, Update_VmdTracker_EnableDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getVmdTracker().getEnable(), true);
    }

    TEST_F(VmdTrackerTest, VmdTracker_EnableRandom) {
        startConfiguration.getVmdTracker().setEnable(false);
        EXPECT_EQ(startConfiguration.getVmdTracker().getEnable(), false);
    }

    TEST_F(VmdTrackerTest, Update_VmdTracker_EnableRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getVmdTracker().setEnable(false);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVmdTracker().getEnable(), false);
    }

    // Test for MaxTimeSinceUpdateToReportMs in VmdTracker
    TEST_F(VmdTrackerTest, VmdTracker_MaxTimeSinceUpdateToReportMsDefault) {
        EXPECT_EQ(startConfiguration.getVmdTracker().getMaxTimeSinceUpdateToReportMs(), 1000);
    }

    TEST_F(VmdTrackerTest, Update_VmdTracker_MaxTimeSinceUpdateToReportMsDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getVmdTracker().getMaxTimeSinceUpdateToReportMs(), 1000);
    }

    TEST_F(VmdTrackerTest, VmdTracker_MaxTimeSinceUpdateToReportMsRandom) {
        startConfiguration.getVmdTracker().setMaxTimeSinceUpdateToReportMs(28207);
        EXPECT_EQ(startConfiguration.getVmdTracker().getMaxTimeSinceUpdateToReportMs(), 28207);
    }

    TEST_F(VmdTrackerTest, Update_VmdTracker_MaxTimeSinceUpdateToReportMsRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getVmdTracker().setMaxTimeSinceUpdateToReportMs(28207);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVmdTracker().getMaxTimeSinceUpdateToReportMs(), 28207);
    }

    // Test for InitTrackSize in VmdTracker
    TEST_F(VmdTrackerTest, VmdTracker_InitTrackSizeDefault) {
        EXPECT_EQ(startConfiguration.getVmdTracker().getInitTrackSize(), 8);
    }

    TEST_F(VmdTrackerTest, Update_VmdTracker_InitTrackSizeDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getVmdTracker().getInitTrackSize(), 8);
    }

    TEST_F(VmdTrackerTest, VmdTracker_InitTrackSizeRange) {
        startConfiguration.getVmdTracker().setInitTrackSize(1);
        EXPECT_EQ(startConfiguration.getVmdTracker().getInitTrackSize(), 1);
        startConfiguration.getVmdTracker().setInitTrackSize(100);
        EXPECT_EQ(startConfiguration.getVmdTracker().getInitTrackSize(), 100);
        EXPECT_THROW(startConfiguration.getVmdTracker().setInitTrackSize(1 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getVmdTracker().setInitTrackSize(100 + 1), std::exception);
    }

    TEST_F(VmdTrackerTest, Update_VmdTracker_InitTrackSizeRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getVmdTracker().setInitTrackSize(1);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVmdTracker().getInitTrackSize(), 1);
        pStream->getConfiguration().getVmdTracker().setInitTrackSize(100);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVmdTracker().getInitTrackSize(), 100);
    }

    // Test for InitThreshold in VmdTracker
    TEST_F(VmdTrackerTest, VmdTracker_InitThresholdDefault) {
        EXPECT_EQ(startConfiguration.getVmdTracker().getInitThreshold(), 0.2f);
    }

    TEST_F(VmdTrackerTest, Update_VmdTracker_InitThresholdDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getVmdTracker().getInitThreshold(), 0.2f);
    }

    TEST_F(VmdTrackerTest, VmdTracker_InitThresholdRange) {
        startConfiguration.getVmdTracker().setInitThreshold(0.0f);
        EXPECT_EQ(startConfiguration.getVmdTracker().getInitThreshold(), 0.0f);
        startConfiguration.getVmdTracker().setInitThreshold(1.0f);
        EXPECT_EQ(startConfiguration.getVmdTracker().getInitThreshold(), 1.0f);
        EXPECT_THROW(startConfiguration.getVmdTracker().setInitThreshold(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getVmdTracker().setInitThreshold(1.0f + 1), std::exception);
    }

    TEST_F(VmdTrackerTest, Update_VmdTracker_InitThresholdRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getVmdTracker().setInitThreshold(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVmdTracker().getInitThreshold(), 0.0f);
        pStream->getConfiguration().getVmdTracker().setInitThreshold(1.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVmdTracker().getInitThreshold(), 1.0f);
    }

    // Test for InitMetric in VmdTracker
    TEST_F(VmdTrackerTest, VmdTracker_InitMetricDefault) {
        EXPECT_EQ(startConfiguration.getVmdTracker().getInitMetric(), sdk::InitScoreMetric::Median);
    }

    TEST_F(VmdTrackerTest, Update_VmdTracker_InitMetricDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getVmdTracker().getInitMetric(), sdk::InitScoreMetric::Median);
    }

    // Test for InitMetric in VmdTracker (enum)
    TEST_F(VmdTrackerTest, VmdTracker_InitMetricEnum) {
        startConfiguration.getVmdTracker().setInitMetric(sdk::InitScoreMetric::Average);
        EXPECT_EQ(startConfiguration.getVmdTracker().getInitMetric(), sdk::InitScoreMetric::Average) << testing::PrintToString(sdk::InitScoreMetric::Average);
        startConfiguration.getVmdTracker().setInitMetric(sdk::InitScoreMetric::Median);
        EXPECT_EQ(startConfiguration.getVmdTracker().getInitMetric(), sdk::InitScoreMetric::Median) << testing::PrintToString(sdk::InitScoreMetric::Median);
    }

    TEST_F(VmdTrackerTest, Update_VmdTracker_InitMetricEnum) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getVmdTracker().setInitMetric(sdk::InitScoreMetric::Average);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVmdTracker().getInitMetric(), sdk::InitScoreMetric::Average) << testing::PrintToString(sdk::InitScoreMetric::Average);
        pStream->getConfiguration().getVmdTracker().setInitMetric(sdk::InitScoreMetric::Median);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVmdTracker().getInitMetric(), sdk::InitScoreMetric::Median) << testing::PrintToString(sdk::InitScoreMetric::Median);
    }

    // Test for MaxPredictedTimeMs in VmdTracker
    TEST_F(VmdTrackerTest, VmdTracker_MaxPredictedTimeMsDefault) {
        EXPECT_EQ(startConfiguration.getVmdTracker().getMaxPredictedTimeMs(), 1000);
    }

    TEST_F(VmdTrackerTest, Update_VmdTracker_MaxPredictedTimeMsDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getVmdTracker().getMaxPredictedTimeMs(), 1000);
    }

    TEST_F(VmdTrackerTest, VmdTracker_MaxPredictedTimeMsRandom) {
        startConfiguration.getVmdTracker().setMaxPredictedTimeMs(53225);
        EXPECT_EQ(startConfiguration.getVmdTracker().getMaxPredictedTimeMs(), 53225);
    }

    TEST_F(VmdTrackerTest, Update_VmdTracker_MaxPredictedTimeMsRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getVmdTracker().setMaxPredictedTimeMs(53225);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVmdTracker().getMaxPredictedTimeMs(), 53225);
    }

    // Test for TrackFeaturesHistorySize in VmdTracker
    TEST_F(VmdTrackerTest, VmdTracker_TrackFeaturesHistorySizeDefault) {
        EXPECT_EQ(startConfiguration.getVmdTracker().getTrackFeaturesHistorySize(), 1);
    }

    TEST_F(VmdTrackerTest, Update_VmdTracker_TrackFeaturesHistorySizeDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getVmdTracker().getTrackFeaturesHistorySize(), 1);
    }

    TEST_F(VmdTrackerTest, VmdTracker_TrackFeaturesHistorySizeRange) {
        startConfiguration.getVmdTracker().setTrackFeaturesHistorySize(1);
        EXPECT_EQ(startConfiguration.getVmdTracker().getTrackFeaturesHistorySize(), 1);
        startConfiguration.getVmdTracker().setTrackFeaturesHistorySize(1000);
        EXPECT_EQ(startConfiguration.getVmdTracker().getTrackFeaturesHistorySize(), 1000);
        EXPECT_THROW(startConfiguration.getVmdTracker().setTrackFeaturesHistorySize(1 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getVmdTracker().setTrackFeaturesHistorySize(1000 + 1), std::exception);
    }

    TEST_F(VmdTrackerTest, Update_VmdTracker_TrackFeaturesHistorySizeRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getVmdTracker().setTrackFeaturesHistorySize(1);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVmdTracker().getTrackFeaturesHistorySize(), 1);
        pStream->getConfiguration().getVmdTracker().setTrackFeaturesHistorySize(1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVmdTracker().getTrackFeaturesHistorySize(), 1000);
    }

    // Test for FeatureWeight in VmdTracker
    TEST_F(VmdTrackerTest, VmdTracker_FeatureWeightDefault) {
        EXPECT_EQ(startConfiguration.getVmdTracker().getFeatureWeight(), 0.0f);
    }

    TEST_F(VmdTrackerTest, Update_VmdTracker_FeatureWeightDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getVmdTracker().getFeatureWeight(), 0.0f);
    }

    TEST_F(VmdTrackerTest, VmdTracker_FeatureWeightRange) {
        startConfiguration.getVmdTracker().setFeatureWeight(-1.0f);
        EXPECT_EQ(startConfiguration.getVmdTracker().getFeatureWeight(), -1.0f);
        startConfiguration.getVmdTracker().setFeatureWeight(1.0f);
        EXPECT_EQ(startConfiguration.getVmdTracker().getFeatureWeight(), 1.0f);
        EXPECT_THROW(startConfiguration.getVmdTracker().setFeatureWeight(-1.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getVmdTracker().setFeatureWeight(1.0f + 1), std::exception);
    }

    TEST_F(VmdTrackerTest, Update_VmdTracker_FeatureWeightRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getVmdTracker().setFeatureWeight(-1.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVmdTracker().getFeatureWeight(), -1.0f);
        pStream->getConfiguration().getVmdTracker().setFeatureWeight(1.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVmdTracker().getFeatureWeight(), 1.0f);
    }

    // Test for MaxCosineDistance in VmdTracker
    TEST_F(VmdTrackerTest, VmdTracker_MaxCosineDistanceDefault) {
        EXPECT_EQ(startConfiguration.getVmdTracker().getMaxCosineDistance(), 0.15f);
    }

    TEST_F(VmdTrackerTest, Update_VmdTracker_MaxCosineDistanceDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getVmdTracker().getMaxCosineDistance(), 0.15f);
    }

    TEST_F(VmdTrackerTest, VmdTracker_MaxCosineDistanceRange) {
        startConfiguration.getVmdTracker().setMaxCosineDistance(0.0f);
        EXPECT_EQ(startConfiguration.getVmdTracker().getMaxCosineDistance(), 0.0f);
        startConfiguration.getVmdTracker().setMaxCosineDistance(1.0f);
        EXPECT_EQ(startConfiguration.getVmdTracker().getMaxCosineDistance(), 1.0f);
        EXPECT_THROW(startConfiguration.getVmdTracker().setMaxCosineDistance(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getVmdTracker().setMaxCosineDistance(1.0f + 1), std::exception);
    }

    TEST_F(VmdTrackerTest, Update_VmdTracker_MaxCosineDistanceRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getVmdTracker().setMaxCosineDistance(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVmdTracker().getMaxCosineDistance(), 0.0f);
        pStream->getConfiguration().getVmdTracker().setMaxCosineDistance(1.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVmdTracker().getMaxCosineDistance(), 1.0f);
    }

    // Test for MaxMahalanobisDistance in VmdTracker
    TEST_F(VmdTrackerTest, VmdTracker_MaxMahalanobisDistanceDefault) {
        EXPECT_EQ(startConfiguration.getVmdTracker().getMaxMahalanobisDistance(), 12.0f);
    }

    TEST_F(VmdTrackerTest, Update_VmdTracker_MaxMahalanobisDistanceDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getVmdTracker().getMaxMahalanobisDistance(), 12.0f);
    }

    TEST_F(VmdTrackerTest, VmdTracker_MaxMahalanobisDistanceRange) {
        startConfiguration.getVmdTracker().setMaxMahalanobisDistance(0.0f);
        EXPECT_EQ(startConfiguration.getVmdTracker().getMaxMahalanobisDistance(), 0.0f);
        startConfiguration.getVmdTracker().setMaxMahalanobisDistance(100.0f);
        EXPECT_EQ(startConfiguration.getVmdTracker().getMaxMahalanobisDistance(), 100.0f);
        EXPECT_THROW(startConfiguration.getVmdTracker().setMaxMahalanobisDistance(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getVmdTracker().setMaxMahalanobisDistance(100.0f + 1), std::exception);
    }

    TEST_F(VmdTrackerTest, Update_VmdTracker_MaxMahalanobisDistanceRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getVmdTracker().setMaxMahalanobisDistance(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVmdTracker().getMaxMahalanobisDistance(), 0.0f);
        pStream->getConfiguration().getVmdTracker().setMaxMahalanobisDistance(100.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVmdTracker().getMaxMahalanobisDistance(), 100.0f);
    }

    // Test for MinIouThreshold in VmdTracker
    TEST_F(VmdTrackerTest, VmdTracker_MinIouThresholdDefault) {
        EXPECT_EQ(startConfiguration.getVmdTracker().getMinIouThreshold(), 0.1f);
    }

    TEST_F(VmdTrackerTest, Update_VmdTracker_MinIouThresholdDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getVmdTracker().getMinIouThreshold(), 0.1f);
    }

    TEST_F(VmdTrackerTest, VmdTracker_MinIouThresholdRange) {
        startConfiguration.getVmdTracker().setMinIouThreshold(0.0f);
        EXPECT_EQ(startConfiguration.getVmdTracker().getMinIouThreshold(), 0.0f);
        startConfiguration.getVmdTracker().setMinIouThreshold(1.0f);
        EXPECT_EQ(startConfiguration.getVmdTracker().getMinIouThreshold(), 1.0f);
        EXPECT_THROW(startConfiguration.getVmdTracker().setMinIouThreshold(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getVmdTracker().setMinIouThreshold(1.0f + 1), std::exception);
    }

    TEST_F(VmdTrackerTest, Update_VmdTracker_MinIouThresholdRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getVmdTracker().setMinIouThreshold(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVmdTracker().getMinIouThreshold(), 0.0f);
        pStream->getConfiguration().getVmdTracker().setMinIouThreshold(1.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getVmdTracker().getMinIouThreshold(), 1.0f);
    }

// Test suit for TrackerPostprocessor
class TrackerPostprocessorTest : public ::testing::Test {
protected:
    void SetUp() override {
        startConfiguration = pPipeline->createStartStreamConfiguration();
        if (::testing::GTEST_FLAG(update_tests)) {
            tmpStartConfiguration = startConfiguration;
            tmpStartConfiguration.getRawSource(); // Touch Raw Source
            tmpStartConfiguration.getRawSource().setReadTimeoutInSec(0); // Wait forever
            pStream = pPipeline->startStream(tmpStartConfiguration);
            waitForStreamStarted(pStream, data);
        }

    }

    void TearDown() override {
        if (::testing::GTEST_FLAG(update_tests)) {
            pStream.reset();
            waitForStreamStopped(data);
        }

    }

};

    // Test for OutputFilter0 in TrackerPostprocessor
    TEST_F(TrackerPostprocessorTest, TrackerPostprocessor_OutputFilter0Default) {
        EXPECT_EQ(startConfiguration.getTrackerPostprocessor().getOutputFilter(0), "*");
    }

    TEST_F(TrackerPostprocessorTest, Update_TrackerPostprocessor_OutputFilter0Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getTrackerPostprocessor().getOutputFilter(0), "*");
    }

    TEST_F(TrackerPostprocessorTest, TrackerPostprocessor_OutputFilter0Random) {
        startConfiguration.getTrackerPostprocessor().setOutputFilter(0, "0jMHqjlH1t");
        EXPECT_EQ(startConfiguration.getTrackerPostprocessor().getOutputFilter(0), "0jMHqjlH1t");
    }

    TEST_F(TrackerPostprocessorTest, Update_TrackerPostprocessor_OutputFilter0Random) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getTrackerPostprocessor().setOutputFilter(0, "0jMHqjlH1t");
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getTrackerPostprocessor().getOutputFilter(0), "0jMHqjlH1t");
    }

// Test suit for RgbReid
class RgbReidTest : public ::testing::Test {
protected:
    void SetUp() override {
        startConfiguration = pPipeline->createStartStreamConfiguration();
        startConfiguration.getRgbReid().getLongTermFeatureExtractorManager().getImageQualityAssessor().appendFilters(sdk::ImageFilter::Unspecified);
        if (::testing::GTEST_FLAG(update_tests)) {
            tmpStartConfiguration = startConfiguration;
            tmpStartConfiguration.getRawSource(); // Touch Raw Source
            tmpStartConfiguration.getRawSource().setReadTimeoutInSec(0); // Wait forever
            pStream = pPipeline->startStream(tmpStartConfiguration);
            waitForStreamStarted(pStream, data);
        }

    }

    void TearDown() override {
        if (::testing::GTEST_FLAG(update_tests)) {
            pStream.reset();
            waitForStreamStopped(data);
        }

    }

};

    // Test for Enable in RgbReid
    TEST_F(RgbReidTest, RgbReid_EnableDefault) {
        EXPECT_EQ(startConfiguration.getRgbReid().getEnable(), false);
    }

    TEST_F(RgbReidTest, Update_RgbReid_EnableDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getRgbReid().getEnable(), false);
    }

    TEST_F(RgbReidTest, RgbReid_EnableRandom) {
        startConfiguration.getRgbReid().setEnable(false);
        EXPECT_EQ(startConfiguration.getRgbReid().getEnable(), false);
    }

    TEST_F(RgbReidTest, Update_RgbReid_EnableRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getRgbReid().setEnable(false);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getRgbReid().getEnable(), false);
    }

    // Test for Mode in RgbReid
    TEST_F(RgbReidTest, RgbReid_ModeDefault) {
        EXPECT_EQ(startConfiguration.getRgbReid().getMode(), sdk::ReidMode::Automatic);
    }

    TEST_F(RgbReidTest, Update_RgbReid_ModeDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getRgbReid().getMode(), sdk::ReidMode::Automatic);
    }

    // Test for Mode in RgbReid (enum)
    TEST_F(RgbReidTest, RgbReid_ModeEnum) {
        startConfiguration.getRgbReid().setMode(sdk::ReidMode::Automatic);
        EXPECT_EQ(startConfiguration.getRgbReid().getMode(), sdk::ReidMode::Automatic) << testing::PrintToString(sdk::ReidMode::Automatic);
        startConfiguration.getRgbReid().setMode(sdk::ReidMode::Manual);
        EXPECT_EQ(startConfiguration.getRgbReid().getMode(), sdk::ReidMode::Manual) << testing::PrintToString(sdk::ReidMode::Manual);
    }

    TEST_F(RgbReidTest, Update_RgbReid_ModeEnum) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getRgbReid().setMode(sdk::ReidMode::Automatic);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getRgbReid().getMode(), sdk::ReidMode::Automatic) << testing::PrintToString(sdk::ReidMode::Automatic);
        pStream->getConfiguration().getRgbReid().setMode(sdk::ReidMode::Manual);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getRgbReid().getMode(), sdk::ReidMode::Manual) << testing::PrintToString(sdk::ReidMode::Manual);
    }

    // Test for EnableCalibration in RgbReid
    TEST_F(RgbReidTest, RgbReid_EnableCalibrationDefault) {
        EXPECT_EQ(startConfiguration.getRgbReid().getEnableCalibration(), true);
    }

    TEST_F(RgbReidTest, RgbReid_EnableCalibrationRandom) {
        startConfiguration.getRgbReid().setEnableCalibration(false);
        EXPECT_EQ(startConfiguration.getRgbReid().getEnableCalibration(), false);
    }

    // Test for ReidOnce in RgbReid
    TEST_F(RgbReidTest, RgbReid_ReidOnceDefault) {
        EXPECT_EQ(startConfiguration.getRgbReid().getReidOnce(), true);
    }

    TEST_F(RgbReidTest, RgbReid_ReidOnceRandom) {
        startConfiguration.getRgbReid().setReidOnce(false);
        EXPECT_EQ(startConfiguration.getRgbReid().getReidOnce(), false);
    }

    // Test for Enable in RgbReid
    TEST_F(RgbReidTest, RgbReid_CloseIdentitiesFilter_EnableDefault) {
        EXPECT_EQ(startConfiguration.getRgbReid().getCloseIdentitiesFilter().getEnable(), true);
    }

    TEST_F(RgbReidTest, RgbReid_CloseIdentitiesFilter_EnableRandom) {
        startConfiguration.getRgbReid().getCloseIdentitiesFilter().setEnable(false);
        EXPECT_EQ(startConfiguration.getRgbReid().getCloseIdentitiesFilter().getEnable(), false);
    }

    // Test for Threshold in RgbReid
    TEST_F(RgbReidTest, RgbReid_CloseIdentitiesFilter_ThresholdDefault) {
        EXPECT_EQ(startConfiguration.getRgbReid().getCloseIdentitiesFilter().getThreshold(), 0.35);
    }

    TEST_F(RgbReidTest, RgbReid_CloseIdentitiesFilter_ThresholdRandom) {
        startConfiguration.getRgbReid().getCloseIdentitiesFilter().setThreshold(237.35f);
        EXPECT_EQ(startConfiguration.getRgbReid().getCloseIdentitiesFilter().getThreshold(), 237.35f);
    }

    // Test for MaxAgeInGallery in RgbReid
    TEST_F(RgbReidTest, RgbReid_Gallery_MaxAgeInGalleryDefault) {
        EXPECT_EQ(startConfiguration.getRgbReid().getGallery().getMaxAgeInGallery(), 1000);
    }

    TEST_F(RgbReidTest, RgbReid_Gallery_MaxAgeInGalleryRandom) {
        startConfiguration.getRgbReid().getGallery().setMaxAgeInGallery(941);
        EXPECT_EQ(startConfiguration.getRgbReid().getGallery().getMaxAgeInGallery(), 941);
    }

    // Test for MaxObjectsInGallery in RgbReid
    TEST_F(RgbReidTest, RgbReid_Gallery_MaxObjectsInGalleryDefault) {
        EXPECT_EQ(startConfiguration.getRgbReid().getGallery().getMaxObjectsInGallery(), 20);
    }

    TEST_F(RgbReidTest, RgbReid_Gallery_MaxObjectsInGalleryRandom) {
        startConfiguration.getRgbReid().getGallery().setMaxObjectsInGallery(572);
        EXPECT_EQ(startConfiguration.getRgbReid().getGallery().getMaxObjectsInGallery(), 572);
    }

    // Test for TimeAwareMatching in RgbReid
    TEST_F(RgbReidTest, RgbReid_Matcher_TimeAwareMatchingDefault) {
        EXPECT_EQ(startConfiguration.getRgbReid().getMatcher().getTimeAwareMatching(), true);
    }

    TEST_F(RgbReidTest, RgbReid_Matcher_TimeAwareMatchingRandom) {
        startConfiguration.getRgbReid().getMatcher().setTimeAwareMatching(false);
        EXPECT_EQ(startConfiguration.getRgbReid().getMatcher().getTimeAwareMatching(), false);
    }

    // Test for CandidatesCreationType in RgbReid
    TEST_F(RgbReidTest, RgbReid_Matcher_MatchingScheme_CandidatesCreationTypeDefault) {
        EXPECT_EQ(startConfiguration.getRgbReid().getMatcher().getMatchingScheme().getCandidatesCreationType(), sdk::CandidatesCreationType::MinOrAverage);
    }

    // Test for CandidatesCreationType in RgbReid (enum)
    TEST_F(RgbReidTest, RgbReid_Matcher_MatchingScheme_CandidatesCreationTypeEnum) {
        startConfiguration.getRgbReid().getMatcher().getMatchingScheme().setCandidatesCreationType(sdk::CandidatesCreationType::JustMin);
        EXPECT_EQ(startConfiguration.getRgbReid().getMatcher().getMatchingScheme().getCandidatesCreationType(), sdk::CandidatesCreationType::JustMin) << testing::PrintToString(sdk::CandidatesCreationType::JustMin);
        startConfiguration.getRgbReid().getMatcher().getMatchingScheme().setCandidatesCreationType(sdk::CandidatesCreationType::JustAverage);
        EXPECT_EQ(startConfiguration.getRgbReid().getMatcher().getMatchingScheme().getCandidatesCreationType(), sdk::CandidatesCreationType::JustAverage) << testing::PrintToString(sdk::CandidatesCreationType::JustAverage);
        startConfiguration.getRgbReid().getMatcher().getMatchingScheme().setCandidatesCreationType(sdk::CandidatesCreationType::MinAndAverage);
        EXPECT_EQ(startConfiguration.getRgbReid().getMatcher().getMatchingScheme().getCandidatesCreationType(), sdk::CandidatesCreationType::MinAndAverage) << testing::PrintToString(sdk::CandidatesCreationType::MinAndAverage);
        startConfiguration.getRgbReid().getMatcher().getMatchingScheme().setCandidatesCreationType(sdk::CandidatesCreationType::MinOrAverage);
        EXPECT_EQ(startConfiguration.getRgbReid().getMatcher().getMatchingScheme().getCandidatesCreationType(), sdk::CandidatesCreationType::MinOrAverage) << testing::PrintToString(sdk::CandidatesCreationType::MinOrAverage);
    }

    // Test for MinThreshold in RgbReid
    TEST_F(RgbReidTest, RgbReid_Matcher_MatchingScheme_MinThresholdDefault) {
        EXPECT_EQ(startConfiguration.getRgbReid().getMatcher().getMatchingScheme().getMinThreshold(), 0.3);
    }

    TEST_F(RgbReidTest, RgbReid_Matcher_MatchingScheme_MinThresholdRandom) {
        startConfiguration.getRgbReid().getMatcher().getMatchingScheme().setMinThreshold(13.56f);
        EXPECT_EQ(startConfiguration.getRgbReid().getMatcher().getMatchingScheme().getMinThreshold(), 13.56f);
    }

    // Test for AverageThreshold in RgbReid
    TEST_F(RgbReidTest, RgbReid_Matcher_MatchingScheme_AverageThresholdDefault) {
        EXPECT_EQ(startConfiguration.getRgbReid().getMatcher().getMatchingScheme().getAverageThreshold(), 0.5);
    }

    TEST_F(RgbReidTest, RgbReid_Matcher_MatchingScheme_AverageThresholdRandom) {
        startConfiguration.getRgbReid().getMatcher().getMatchingScheme().setAverageThreshold(885.46f);
        EXPECT_EQ(startConfiguration.getRgbReid().getMatcher().getMatchingScheme().getAverageThreshold(), 885.46f);
    }

    // Test for DistanceMargin in RgbReid
    TEST_F(RgbReidTest, RgbReid_Matcher_MatchingScheme_DistanceMarginDefault) {
        EXPECT_EQ(startConfiguration.getRgbReid().getMatcher().getMatchingScheme().getDistanceMargin(), 0.15);
    }

    TEST_F(RgbReidTest, RgbReid_Matcher_MatchingScheme_DistanceMarginRandom) {
        startConfiguration.getRgbReid().getMatcher().getMatchingScheme().setDistanceMargin(154.7f);
        EXPECT_EQ(startConfiguration.getRgbReid().getMatcher().getMatchingScheme().getDistanceMargin(), 154.7f);
    }

    // Test for MinCountForAverageThresholdUsage in RgbReid
    TEST_F(RgbReidTest, RgbReid_Matcher_MatchingScheme_MinCountForAverageThresholdUsageDefault) {
        EXPECT_EQ(startConfiguration.getRgbReid().getMatcher().getMatchingScheme().getMinCountForAverageThresholdUsage(), 4);
    }

    TEST_F(RgbReidTest, RgbReid_Matcher_MatchingScheme_MinCountForAverageThresholdUsageRandom) {
        startConfiguration.getRgbReid().getMatcher().getMatchingScheme().setMinCountForAverageThresholdUsage(261);
        EXPECT_EQ(startConfiguration.getRgbReid().getMatcher().getMatchingScheme().getMinCountForAverageThresholdUsage(), 261);
    }

    // Test for MaxClusters in RgbReid
    TEST_F(RgbReidTest, RgbReid_ComparativeFeatureManager_MaxClustersDefault) {
        EXPECT_EQ(startConfiguration.getRgbReid().getComparativeFeatureManager().getMaxClusters(), 15);
    }

    TEST_F(RgbReidTest, RgbReid_ComparativeFeatureManager_MaxClustersRandom) {
        startConfiguration.getRgbReid().getComparativeFeatureManager().setMaxClusters(254);
        EXPECT_EQ(startConfiguration.getRgbReid().getComparativeFeatureManager().getMaxClusters(), 254);
    }

    // Test for SimilarityThreshold in RgbReid
    TEST_F(RgbReidTest, RgbReid_ComparativeFeatureManager_SimilarityThresholdDefault) {
        EXPECT_EQ(startConfiguration.getRgbReid().getComparativeFeatureManager().getSimilarityThreshold(), 0.09);
    }

    TEST_F(RgbReidTest, RgbReid_ComparativeFeatureManager_SimilarityThresholdRandom) {
        startConfiguration.getRgbReid().getComparativeFeatureManager().setSimilarityThreshold(595.27f);
        EXPECT_EQ(startConfiguration.getRgbReid().getComparativeFeatureManager().getSimilarityThreshold(), 595.27f);
    }

    // Test for MinCountForClusterValidity in RgbReid
    TEST_F(RgbReidTest, RgbReid_ComparativeFeatureManager_MinCountForClusterValidityDefault) {
        EXPECT_EQ(startConfiguration.getRgbReid().getComparativeFeatureManager().getMinCountForClusterValidity(), 6);
    }

    TEST_F(RgbReidTest, RgbReid_ComparativeFeatureManager_MinCountForClusterValidityRandom) {
        startConfiguration.getRgbReid().getComparativeFeatureManager().setMinCountForClusterValidity(981);
        EXPECT_EQ(startConfiguration.getRgbReid().getComparativeFeatureManager().getMinCountForClusterValidity(), 981);
    }

    // Test for Enable in RgbReid
    TEST_F(RgbReidTest, RgbReid_LongTermFeatureExtractorManager_ImageQualityAssessor_EnableDefault) {
        EXPECT_EQ(startConfiguration.getRgbReid().getLongTermFeatureExtractorManager().getImageQualityAssessor().getEnable(), false);
    }

    TEST_F(RgbReidTest, RgbReid_LongTermFeatureExtractorManager_ImageQualityAssessor_EnableRandom) {
        startConfiguration.getRgbReid().getLongTermFeatureExtractorManager().getImageQualityAssessor().setEnable(true);
        EXPECT_EQ(startConfiguration.getRgbReid().getLongTermFeatureExtractorManager().getImageQualityAssessor().getEnable(), true);
    }

    // Test for Filters0 in RgbReid
    TEST_F(RgbReidTest, RgbReid_LongTermFeatureExtractorManager_ImageQualityAssessor_Filters0Default) {
        EXPECT_EQ(startConfiguration.getRgbReid().getLongTermFeatureExtractorManager().getImageQualityAssessor().getFilters(0), sdk::ImageFilter::Unspecified);
    }

    // Test for Filters0 in RgbReid (enum)
    TEST_F(RgbReidTest, RgbReid_LongTermFeatureExtractorManager_ImageQualityAssessor_Filters0Enum) {
        startConfiguration.getRgbReid().getLongTermFeatureExtractorManager().getImageQualityAssessor().setFilters(0, sdk::ImageFilter::AreaSizeFilter);
        EXPECT_EQ(startConfiguration.getRgbReid().getLongTermFeatureExtractorManager().getImageQualityAssessor().getFilters(0), sdk::ImageFilter::AreaSizeFilter) << testing::PrintToString(sdk::ImageFilter::AreaSizeFilter);
        startConfiguration.getRgbReid().getLongTermFeatureExtractorManager().getImageQualityAssessor().setFilters(0, sdk::ImageFilter::LaplacianFilter);
        EXPECT_EQ(startConfiguration.getRgbReid().getLongTermFeatureExtractorManager().getImageQualityAssessor().getFilters(0), sdk::ImageFilter::LaplacianFilter) << testing::PrintToString(sdk::ImageFilter::LaplacianFilter);
    }

    // Test for ImageCenterPercentage in RgbReid
    TEST_F(RgbReidTest, RgbReid_LongTermFeatureExtractorManager_ImageQualityAssessor_LaplacianFilter_ImageCenterPercentageDefault) {
        EXPECT_EQ(startConfiguration.getRgbReid().getLongTermFeatureExtractorManager().getImageQualityAssessor().getLaplacianFilter().getImageCenterPercentage(), 0.5);
    }

    TEST_F(RgbReidTest, RgbReid_LongTermFeatureExtractorManager_ImageQualityAssessor_LaplacianFilter_ImageCenterPercentageRandom) {
        startConfiguration.getRgbReid().getLongTermFeatureExtractorManager().getImageQualityAssessor().getLaplacianFilter().setImageCenterPercentage(947.06f);
        EXPECT_EQ(startConfiguration.getRgbReid().getLongTermFeatureExtractorManager().getImageQualityAssessor().getLaplacianFilter().getImageCenterPercentage(), 947.06f);
    }

    // Test for TimeSinceUpdateThreshold in RgbReid
    TEST_F(RgbReidTest, RgbReid_LongTermFeatureExtractorManager_TimeSinceUpdateThresholdDefault) {
        EXPECT_EQ(startConfiguration.getRgbReid().getLongTermFeatureExtractorManager().getTimeSinceUpdateThreshold(), 1);
    }

    TEST_F(RgbReidTest, RgbReid_LongTermFeatureExtractorManager_TimeSinceUpdateThresholdRandom) {
        startConfiguration.getRgbReid().getLongTermFeatureExtractorManager().setTimeSinceUpdateThreshold(263);
        EXPECT_EQ(startConfiguration.getRgbReid().getLongTermFeatureExtractorManager().getTimeSinceUpdateThreshold(), 263);
    }

    // Test for IouThreshold in RgbReid
    TEST_F(RgbReidTest, RgbReid_LongTermFeatureExtractorManager_IouThresholdDefault) {
        EXPECT_EQ(startConfiguration.getRgbReid().getLongTermFeatureExtractorManager().getIouThreshold(), 0.4);
    }

    TEST_F(RgbReidTest, RgbReid_LongTermFeatureExtractorManager_IouThresholdRandom) {
        startConfiguration.getRgbReid().getLongTermFeatureExtractorManager().setIouThreshold(108.23f);
        EXPECT_EQ(startConfiguration.getRgbReid().getLongTermFeatureExtractorManager().getIouThreshold(), 108.23f);
    }

    // Test for MaxFeaturesToExtractPerStep in RgbReid
    TEST_F(RgbReidTest, RgbReid_LongTermFeatureExtractorManager_MaxFeaturesToExtractPerStepDefault) {
        EXPECT_EQ(startConfiguration.getRgbReid().getLongTermFeatureExtractorManager().getMaxFeaturesToExtractPerStep(), 10);
    }

    TEST_F(RgbReidTest, RgbReid_LongTermFeatureExtractorManager_MaxFeaturesToExtractPerStepRandom) {
        startConfiguration.getRgbReid().getLongTermFeatureExtractorManager().setMaxFeaturesToExtractPerStep(339);
        EXPECT_EQ(startConfiguration.getRgbReid().getLongTermFeatureExtractorManager().getMaxFeaturesToExtractPerStep(), 339);
    }

// Test suit for TracksPublisher
class TracksPublisherTest : public ::testing::Test {
protected:
    void SetUp() override {
        startConfiguration = pPipeline->createStartStreamConfiguration();
        if (::testing::GTEST_FLAG(update_tests)) {
            tmpStartConfiguration = startConfiguration;
            tmpStartConfiguration.getRawSource(); // Touch Raw Source
            tmpStartConfiguration.getRawSource().setReadTimeoutInSec(0); // Wait forever
            pStream = pPipeline->startStream(tmpStartConfiguration);
            waitForStreamStarted(pStream, data);
        }

    }

    void TearDown() override {
        if (::testing::GTEST_FLAG(update_tests)) {
            pStream.reset();
            waitForStreamStopped(data);
        }

    }

};

    // Test for SourceData in TracksPublisher
    TEST_F(TracksPublisherTest, TracksPublisher_SourceDataDefault) {
        EXPECT_EQ(startConfiguration.getTracksPublisher().getSourceData(), sdk::PublisherDataType::Tracks);
    }

    TEST_F(TracksPublisherTest, Update_TracksPublisher_SourceDataDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getTracksPublisher().getSourceData(), sdk::PublisherDataType::Tracks);
    }

    // Test for SourceData in TracksPublisher (enum)
    TEST_F(TracksPublisherTest, TracksPublisher_SourceDataEnum) {
        startConfiguration.getTracksPublisher().setSourceData(sdk::PublisherDataType::Disabled);
        EXPECT_EQ(startConfiguration.getTracksPublisher().getSourceData(), sdk::PublisherDataType::Disabled) << testing::PrintToString(sdk::PublisherDataType::Disabled);
        startConfiguration.getTracksPublisher().setSourceData(sdk::PublisherDataType::Detections);
        EXPECT_EQ(startConfiguration.getTracksPublisher().getSourceData(), sdk::PublisherDataType::Detections) << testing::PrintToString(sdk::PublisherDataType::Detections);
        startConfiguration.getTracksPublisher().setSourceData(sdk::PublisherDataType::Tracks);
        EXPECT_EQ(startConfiguration.getTracksPublisher().getSourceData(), sdk::PublisherDataType::Tracks) << testing::PrintToString(sdk::PublisherDataType::Tracks);
    }

    TEST_F(TracksPublisherTest, Update_TracksPublisher_SourceDataEnum) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getTracksPublisher().setSourceData(sdk::PublisherDataType::Disabled);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getTracksPublisher().getSourceData(), sdk::PublisherDataType::Disabled) << testing::PrintToString(sdk::PublisherDataType::Disabled);
        pStream->getConfiguration().getTracksPublisher().setSourceData(sdk::PublisherDataType::Detections);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getTracksPublisher().getSourceData(), sdk::PublisherDataType::Detections) << testing::PrintToString(sdk::PublisherDataType::Detections);
        pStream->getConfiguration().getTracksPublisher().setSourceData(sdk::PublisherDataType::Tracks);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getTracksPublisher().getSourceData(), sdk::PublisherDataType::Tracks) << testing::PrintToString(sdk::PublisherDataType::Tracks);
    }

// Test suit for VehicleTelemetry
class VehicleTelemetryTest : public ::testing::Test {
protected:
    void SetUp() override {
        startConfiguration = pPipeline->createStartStreamConfiguration();
    }

};

    // Test for SamplingFrequencyMs in VehicleTelemetry
    TEST_F(VehicleTelemetryTest, VehicleTelemetry_SamplingFrequencyMsDefault) {
        EXPECT_EQ(startConfiguration.getVehicleTelemetry().getSamplingFrequencyMs(), 30);
    }

    TEST_F(VehicleTelemetryTest, VehicleTelemetry_SamplingFrequencyMsRange) {
        startConfiguration.getVehicleTelemetry().setSamplingFrequencyMs(10);
        EXPECT_EQ(startConfiguration.getVehicleTelemetry().getSamplingFrequencyMs(), 10);
        startConfiguration.getVehicleTelemetry().setSamplingFrequencyMs(10000);
        EXPECT_EQ(startConfiguration.getVehicleTelemetry().getSamplingFrequencyMs(), 10000);
        EXPECT_THROW(startConfiguration.getVehicleTelemetry().setSamplingFrequencyMs(10 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getVehicleTelemetry().setSamplingFrequencyMs(10000 + 1), std::exception);
    }

// Test suit for CefRenderer
class CefRendererTest : public ::testing::Test {
protected:
    void SetUp() override {
        startConfiguration = pPipeline->createStartStreamConfiguration();
        if (::testing::GTEST_FLAG(update_tests)) {
            tmpStartConfiguration = startConfiguration;
            tmpStartConfiguration.getRawSource(); // Touch Raw Source
            tmpStartConfiguration.getRawSource().setReadTimeoutInSec(0); // Wait forever
            pStream = pPipeline->startStream(tmpStartConfiguration);
            waitForStreamStarted(pStream, data);
        }

    }

    void TearDown() override {
        if (::testing::GTEST_FLAG(update_tests)) {
            pStream.reset();
            waitForStreamStopped(data);
        }

    }

};

    // Test for Enable in CefRenderer
    TEST_F(CefRendererTest, CefRenderer_EnableDefault) {
        EXPECT_EQ(startConfiguration.getCefRenderer().getEnable(), true);
    }

    TEST_F(CefRendererTest, Update_CefRenderer_EnableDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCefRenderer().getEnable(), true);
    }

    TEST_F(CefRendererTest, CefRenderer_EnableRandom) {
        startConfiguration.getCefRenderer().setEnable(true);
        EXPECT_EQ(startConfiguration.getCefRenderer().getEnable(), true);
    }

    TEST_F(CefRendererTest, Update_CefRenderer_EnableRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCefRenderer().setEnable(true);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCefRenderer().getEnable(), true);
    }

    // Test for TargetWidth in CefRenderer
    TEST_F(CefRendererTest, CefRenderer_TargetWidthDefault) {
        EXPECT_EQ(startConfiguration.getCefRenderer().getTargetWidth(), 1280);
    }

    TEST_F(CefRendererTest, Update_CefRenderer_TargetWidthDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCefRenderer().getTargetWidth(), 1280);
    }

    TEST_F(CefRendererTest, CefRenderer_TargetWidthRandom) {
        startConfiguration.getCefRenderer().setTargetWidth(7867);
        EXPECT_EQ(startConfiguration.getCefRenderer().getTargetWidth(), 7867);
    }

    TEST_F(CefRendererTest, Update_CefRenderer_TargetWidthRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCefRenderer().setTargetWidth(7867);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCefRenderer().getTargetWidth(), 7867);
    }

    // Test for TargetHeight in CefRenderer
    TEST_F(CefRendererTest, CefRenderer_TargetHeightDefault) {
        EXPECT_EQ(startConfiguration.getCefRenderer().getTargetHeight(), 720);
    }

    TEST_F(CefRendererTest, Update_CefRenderer_TargetHeightDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCefRenderer().getTargetHeight(), 720);
    }

    TEST_F(CefRendererTest, CefRenderer_TargetHeightRandom) {
        startConfiguration.getCefRenderer().setTargetHeight(211);
        EXPECT_EQ(startConfiguration.getCefRenderer().getTargetHeight(), 211);
    }

    TEST_F(CefRendererTest, Update_CefRenderer_TargetHeightRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCefRenderer().setTargetHeight(211);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCefRenderer().getTargetHeight(), 211);
    }

    // Test for BrowserFrameRate in CefRenderer
    TEST_F(CefRendererTest, CefRenderer_BrowserFrameRateDefault) {
        EXPECT_EQ(startConfiguration.getCefRenderer().getBrowserFrameRate(), 30);
    }

    TEST_F(CefRendererTest, Update_CefRenderer_BrowserFrameRateDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCefRenderer().getBrowserFrameRate(), 30);
    }

    TEST_F(CefRendererTest, CefRenderer_BrowserFrameRateRange) {
        startConfiguration.getCefRenderer().setBrowserFrameRate(1);
        EXPECT_EQ(startConfiguration.getCefRenderer().getBrowserFrameRate(), 1);
        startConfiguration.getCefRenderer().setBrowserFrameRate(60);
        EXPECT_EQ(startConfiguration.getCefRenderer().getBrowserFrameRate(), 60);
        EXPECT_THROW(startConfiguration.getCefRenderer().setBrowserFrameRate(1 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCefRenderer().setBrowserFrameRate(60 + 1), std::exception);
    }

    TEST_F(CefRendererTest, Update_CefRenderer_BrowserFrameRateRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCefRenderer().setBrowserFrameRate(1);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCefRenderer().getBrowserFrameRate(), 1);
        pStream->getConfiguration().getCefRenderer().setBrowserFrameRate(60);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCefRenderer().getBrowserFrameRate(), 60);
    }

// Test suit for CvRenderer
class CvRendererTest : public ::testing::Test {
protected:
    void SetUp() override {
        startConfiguration = pPipeline->createStartStreamConfiguration();
        if (::testing::GTEST_FLAG(update_tests)) {
            tmpStartConfiguration = startConfiguration;
            tmpStartConfiguration.getRawSource(); // Touch Raw Source
            tmpStartConfiguration.getRawSource().setReadTimeoutInSec(0); // Wait forever
            pStream = pPipeline->startStream(tmpStartConfiguration);
            waitForStreamStarted(pStream, data);
        }

    }

    void TearDown() override {
        if (::testing::GTEST_FLAG(update_tests)) {
            pStream.reset();
            waitForStreamStopped(data);
        }

    }

};

    // Test for TargetWidth in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_TargetWidthDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getTargetWidth(), 1280);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_TargetWidthDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getTargetWidth(), 1280);
    }

    TEST_F(CvRendererTest, CvRenderer_TargetWidthRandom) {
        startConfiguration.getCvRenderer().setTargetWidth(3459);
        EXPECT_EQ(startConfiguration.getCvRenderer().getTargetWidth(), 3459);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_TargetWidthRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().setTargetWidth(3459);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getTargetWidth(), 3459);
    }

    // Test for TargetHeight in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_TargetHeightDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getTargetHeight(), 720);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_TargetHeightDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getTargetHeight(), 720);
    }

    TEST_F(CvRendererTest, CvRenderer_TargetHeightRandom) {
        startConfiguration.getCvRenderer().setTargetHeight(1502);
        EXPECT_EQ(startConfiguration.getCvRenderer().getTargetHeight(), 1502);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_TargetHeightRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().setTargetHeight(1502);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getTargetHeight(), 1502);
    }

    // Test for SkipAllRendering in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_SkipAllRenderingDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getSkipAllRendering(), false);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_SkipAllRenderingDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getSkipAllRendering(), false);
    }

    TEST_F(CvRendererTest, CvRenderer_SkipAllRenderingRandom) {
        startConfiguration.getCvRenderer().setSkipAllRendering(true);
        EXPECT_EQ(startConfiguration.getCvRenderer().getSkipAllRendering(), true);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_SkipAllRenderingRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().setSkipAllRendering(true);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getSkipAllRendering(), true);
    }

    // Test for DrawDetections in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_DrawDetectionsDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getDrawDetections(), false);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_DrawDetectionsDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getDrawDetections(), false);
    }

    TEST_F(CvRendererTest, CvRenderer_DrawDetectionsRandom) {
        startConfiguration.getCvRenderer().setDrawDetections(false);
        EXPECT_EQ(startConfiguration.getCvRenderer().getDrawDetections(), false);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_DrawDetectionsRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().setDrawDetections(false);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getDrawDetections(), false);
    }

    // Test for DrawTracks in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_DrawTracksDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getDrawTracks(), true);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_DrawTracksDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getDrawTracks(), true);
    }

    TEST_F(CvRendererTest, CvRenderer_DrawTracksRandom) {
        startConfiguration.getCvRenderer().setDrawTracks(true);
        EXPECT_EQ(startConfiguration.getCvRenderer().getDrawTracks(), true);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_DrawTracksRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().setDrawTracks(true);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getDrawTracks(), true);
    }

    // Test for MarkPredictedTracks in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_MarkPredictedTracksDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getMarkPredictedTracks(), false);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_MarkPredictedTracksDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getMarkPredictedTracks(), false);
    }

    TEST_F(CvRendererTest, CvRenderer_MarkPredictedTracksRandom) {
        startConfiguration.getCvRenderer().setMarkPredictedTracks(true);
        EXPECT_EQ(startConfiguration.getCvRenderer().getMarkPredictedTracks(), true);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_MarkPredictedTracksRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().setMarkPredictedTracks(true);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getMarkPredictedTracks(), true);
    }

    // Test for PrintClass in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_PrintClassDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getPrintClass(), false);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_PrintClassDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getPrintClass(), false);
    }

    TEST_F(CvRendererTest, CvRenderer_PrintClassRandom) {
        startConfiguration.getCvRenderer().setPrintClass(false);
        EXPECT_EQ(startConfiguration.getCvRenderer().getPrintClass(), false);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_PrintClassRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().setPrintClass(false);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getPrintClass(), false);
    }

    // Test for PrintScore in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_PrintScoreDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getPrintScore(), false);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_PrintScoreDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getPrintScore(), false);
    }

    TEST_F(CvRendererTest, CvRenderer_PrintScoreRandom) {
        startConfiguration.getCvRenderer().setPrintScore(false);
        EXPECT_EQ(startConfiguration.getCvRenderer().getPrintScore(), false);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_PrintScoreRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().setPrintScore(false);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getPrintScore(), false);
    }

    // Test for PrintTrackId in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_PrintTrackIdDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getPrintTrackId(), true);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_PrintTrackIdDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getPrintTrackId(), true);
    }

    TEST_F(CvRendererTest, CvRenderer_PrintTrackIdRandom) {
        startConfiguration.getCvRenderer().setPrintTrackId(true);
        EXPECT_EQ(startConfiguration.getCvRenderer().getPrintTrackId(), true);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_PrintTrackIdRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().setPrintTrackId(true);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getPrintTrackId(), true);
    }

    // Test for ColorTrack in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_ColorTrackDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getColorTrack(), false);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_ColorTrackDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getColorTrack(), false);
    }

    TEST_F(CvRendererTest, CvRenderer_ColorTrackRandom) {
        startConfiguration.getCvRenderer().setColorTrack(false);
        EXPECT_EQ(startConfiguration.getCvRenderer().getColorTrack(), false);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_ColorTrackRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().setColorTrack(false);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getColorTrack(), false);
    }

    // Test for DrawTrackVelocity in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_DrawTrackVelocityDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getDrawTrackVelocity(), false);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_DrawTrackVelocityDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getDrawTrackVelocity(), false);
    }

    TEST_F(CvRendererTest, CvRenderer_DrawTrackVelocityRandom) {
        startConfiguration.getCvRenderer().setDrawTrackVelocity(false);
        EXPECT_EQ(startConfiguration.getCvRenderer().getDrawTrackVelocity(), false);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_DrawTrackVelocityRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().setDrawTrackVelocity(false);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getDrawTrackVelocity(), false);
    }

    // Test for TrackVelocityFactor in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_TrackVelocityFactorDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getTrackVelocityFactor(), 1.0f);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_TrackVelocityFactorDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getTrackVelocityFactor(), 1.0f);
    }

    TEST_F(CvRendererTest, CvRenderer_TrackVelocityFactorRange) {
        startConfiguration.getCvRenderer().setTrackVelocityFactor(0.0f);
        EXPECT_EQ(startConfiguration.getCvRenderer().getTrackVelocityFactor(), 0.0f);
        startConfiguration.getCvRenderer().setTrackVelocityFactor(1000.0f);
        EXPECT_EQ(startConfiguration.getCvRenderer().getTrackVelocityFactor(), 1000.0f);
        EXPECT_THROW(startConfiguration.getCvRenderer().setTrackVelocityFactor(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().setTrackVelocityFactor(1000.0f + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_TrackVelocityFactorRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().setTrackVelocityFactor(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getTrackVelocityFactor(), 0.0f);
        pStream->getConfiguration().getCvRenderer().setTrackVelocityFactor(1000.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getTrackVelocityFactor(), 1000.0f);
    }

    // Test for PrintDistance in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_PrintDistanceDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getPrintDistance(), false);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_PrintDistanceDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getPrintDistance(), false);
    }

    TEST_F(CvRendererTest, CvRenderer_PrintDistanceRandom) {
        startConfiguration.getCvRenderer().setPrintDistance(false);
        EXPECT_EQ(startConfiguration.getCvRenderer().getPrintDistance(), false);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_PrintDistanceRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().setPrintDistance(false);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getPrintDistance(), false);
    }

    // Test for PrintAttributes in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_PrintAttributesDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getPrintAttributes(), false);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_PrintAttributesDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getPrintAttributes(), false);
    }

    TEST_F(CvRendererTest, CvRenderer_PrintAttributesRandom) {
        startConfiguration.getCvRenderer().setPrintAttributes(false);
        EXPECT_EQ(startConfiguration.getCvRenderer().getPrintAttributes(), false);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_PrintAttributesRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().setPrintAttributes(false);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getPrintAttributes(), false);
    }

    // Test for PrintDebugStatus in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_PrintDebugStatusDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getPrintDebugStatus(), false);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_PrintDebugStatusDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getPrintDebugStatus(), false);
    }

    TEST_F(CvRendererTest, CvRenderer_PrintDebugStatusRandom) {
        startConfiguration.getCvRenderer().setPrintDebugStatus(true);
        EXPECT_EQ(startConfiguration.getCvRenderer().getPrintDebugStatus(), true);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_PrintDebugStatusRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().setPrintDebugStatus(true);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getPrintDebugStatus(), true);
    }

    // Test for DrawCenterOfMass in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_DrawCenterOfMassDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getDrawCenterOfMass(), false);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_DrawCenterOfMassDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getDrawCenterOfMass(), false);
    }

    TEST_F(CvRendererTest, CvRenderer_DrawCenterOfMassRandom) {
        startConfiguration.getCvRenderer().setDrawCenterOfMass(false);
        EXPECT_EQ(startConfiguration.getCvRenderer().getDrawCenterOfMass(), false);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_DrawCenterOfMassRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().setDrawCenterOfMass(false);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getDrawCenterOfMass(), false);
    }

    // Test for CenterOfMassRadius in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_CenterOfMassRadiusDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getCenterOfMassRadius(), 3);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_CenterOfMassRadiusDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getCenterOfMassRadius(), 3);
    }

    TEST_F(CvRendererTest, CvRenderer_CenterOfMassRadiusRange) {
        startConfiguration.getCvRenderer().setCenterOfMassRadius(1);
        EXPECT_EQ(startConfiguration.getCvRenderer().getCenterOfMassRadius(), 1);
        startConfiguration.getCvRenderer().setCenterOfMassRadius(10);
        EXPECT_EQ(startConfiguration.getCvRenderer().getCenterOfMassRadius(), 10);
        EXPECT_THROW(startConfiguration.getCvRenderer().setCenterOfMassRadius(1 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().setCenterOfMassRadius(10 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_CenterOfMassRadiusRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().setCenterOfMassRadius(1);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getCenterOfMassRadius(), 1);
        pStream->getConfiguration().getCvRenderer().setCenterOfMassRadius(10);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getCenterOfMassRadius(), 10);
    }

    // Test for SkipRendering in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_ReidHotCold_SkipRenderingDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getReidHotCold().getSkipRendering(), false);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_ReidHotCold_SkipRenderingDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getReidHotCold().getSkipRendering(), false);
    }

    TEST_F(CvRendererTest, CvRenderer_ReidHotCold_SkipRenderingRandom) {
        startConfiguration.getCvRenderer().getReidHotCold().setSkipRendering(false);
        EXPECT_EQ(startConfiguration.getCvRenderer().getReidHotCold().getSkipRendering(), false);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_ReidHotCold_SkipRenderingRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getReidHotCold().setSkipRendering(false);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getReidHotCold().getSkipRendering(), false);
    }

    // Test for PrintScore in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_ReidHotCold_PrintScoreDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getReidHotCold().getPrintScore(), false);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_ReidHotCold_PrintScoreDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getReidHotCold().getPrintScore(), false);
    }

    TEST_F(CvRendererTest, CvRenderer_ReidHotCold_PrintScoreRandom) {
        startConfiguration.getCvRenderer().getReidHotCold().setPrintScore(true);
        EXPECT_EQ(startConfiguration.getCvRenderer().getReidHotCold().getPrintScore(), true);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_ReidHotCold_PrintScoreRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getReidHotCold().setPrintScore(true);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getReidHotCold().getPrintScore(), true);
    }

    // Test for MinScoreToRender in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_ReidHotCold_MinScoreToRenderDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getReidHotCold().getMinScoreToRender(), 0.1);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_ReidHotCold_MinScoreToRenderDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getReidHotCold().getMinScoreToRender(), 0.1);
    }

    TEST_F(CvRendererTest, CvRenderer_ReidHotCold_MinScoreToRenderRandom) {
        startConfiguration.getCvRenderer().getReidHotCold().setMinScoreToRender(0.39f);
        EXPECT_EQ(startConfiguration.getCvRenderer().getReidHotCold().getMinScoreToRender(), 0.39f);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_ReidHotCold_MinScoreToRenderRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getReidHotCold().setMinScoreToRender(0.39f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getReidHotCold().getMinScoreToRender(), 0.39f);
    }

    // Test for ColorLineThickness in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_ReidHotCold_ColorLineThicknessDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getReidHotCold().getColorLineThickness(), 2);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_ReidHotCold_ColorLineThicknessDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getReidHotCold().getColorLineThickness(), 2);
    }

    TEST_F(CvRendererTest, CvRenderer_ReidHotCold_ColorLineThicknessRange) {
        startConfiguration.getCvRenderer().getReidHotCold().setColorLineThickness(1);
        EXPECT_EQ(startConfiguration.getCvRenderer().getReidHotCold().getColorLineThickness(), 1);
        startConfiguration.getCvRenderer().getReidHotCold().setColorLineThickness(100);
        EXPECT_EQ(startConfiguration.getCvRenderer().getReidHotCold().getColorLineThickness(), 100);
        EXPECT_THROW(startConfiguration.getCvRenderer().getReidHotCold().setColorLineThickness(1 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getReidHotCold().setColorLineThickness(100 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_ReidHotCold_ColorLineThicknessRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getReidHotCold().setColorLineThickness(1);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getReidHotCold().getColorLineThickness(), 1);
        pStream->getConfiguration().getCvRenderer().getReidHotCold().setColorLineThickness(100);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getReidHotCold().getColorLineThickness(), 100);
    }

    // Test for ColorLineDistance in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_ReidHotCold_ColorLineDistanceDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getReidHotCold().getColorLineDistance(), 3);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_ReidHotCold_ColorLineDistanceDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getReidHotCold().getColorLineDistance(), 3);
    }

    TEST_F(CvRendererTest, CvRenderer_ReidHotCold_ColorLineDistanceRange) {
        startConfiguration.getCvRenderer().getReidHotCold().setColorLineDistance(-101);
        EXPECT_EQ(startConfiguration.getCvRenderer().getReidHotCold().getColorLineDistance(), -101);
        startConfiguration.getCvRenderer().getReidHotCold().setColorLineDistance(100);
        EXPECT_EQ(startConfiguration.getCvRenderer().getReidHotCold().getColorLineDistance(), 100);
        EXPECT_THROW(startConfiguration.getCvRenderer().getReidHotCold().setColorLineDistance(-101 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getReidHotCold().setColorLineDistance(100 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_ReidHotCold_ColorLineDistanceRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getReidHotCold().setColorLineDistance(-101);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getReidHotCold().getColorLineDistance(), -101);
        pStream->getConfiguration().getCvRenderer().getReidHotCold().setColorLineDistance(100);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getReidHotCold().getColorLineDistance(), 100);
    }

    // Test for ColorMap in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_ReidHotCold_ColorMapDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Viridis);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_ReidHotCold_ColorMapDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Viridis);
    }

    // Test for ColorMap in CvRenderer (enum)
    TEST_F(CvRendererTest, CvRenderer_ReidHotCold_ColorMapEnum) {
        startConfiguration.getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Bone);
        EXPECT_EQ(startConfiguration.getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Bone) << testing::PrintToString(sdk::ColorMap::Bone);
        startConfiguration.getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Jet);
        EXPECT_EQ(startConfiguration.getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Jet) << testing::PrintToString(sdk::ColorMap::Jet);
        startConfiguration.getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Winter);
        EXPECT_EQ(startConfiguration.getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Winter) << testing::PrintToString(sdk::ColorMap::Winter);
        startConfiguration.getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Rainbow);
        EXPECT_EQ(startConfiguration.getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Rainbow) << testing::PrintToString(sdk::ColorMap::Rainbow);
        startConfiguration.getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Ocean);
        EXPECT_EQ(startConfiguration.getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Ocean) << testing::PrintToString(sdk::ColorMap::Ocean);
        startConfiguration.getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Summer);
        EXPECT_EQ(startConfiguration.getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Summer) << testing::PrintToString(sdk::ColorMap::Summer);
        startConfiguration.getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Spring);
        EXPECT_EQ(startConfiguration.getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Spring) << testing::PrintToString(sdk::ColorMap::Spring);
        startConfiguration.getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Cool);
        EXPECT_EQ(startConfiguration.getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Cool) << testing::PrintToString(sdk::ColorMap::Cool);
        startConfiguration.getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Hsv);
        EXPECT_EQ(startConfiguration.getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Hsv) << testing::PrintToString(sdk::ColorMap::Hsv);
        startConfiguration.getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Pink);
        EXPECT_EQ(startConfiguration.getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Pink) << testing::PrintToString(sdk::ColorMap::Pink);
        startConfiguration.getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Hot);
        EXPECT_EQ(startConfiguration.getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Hot) << testing::PrintToString(sdk::ColorMap::Hot);
        startConfiguration.getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Parula);
        EXPECT_EQ(startConfiguration.getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Parula) << testing::PrintToString(sdk::ColorMap::Parula);
        startConfiguration.getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Magma);
        EXPECT_EQ(startConfiguration.getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Magma) << testing::PrintToString(sdk::ColorMap::Magma);
        startConfiguration.getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Inferno);
        EXPECT_EQ(startConfiguration.getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Inferno) << testing::PrintToString(sdk::ColorMap::Inferno);
        startConfiguration.getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Plasma);
        EXPECT_EQ(startConfiguration.getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Plasma) << testing::PrintToString(sdk::ColorMap::Plasma);
        startConfiguration.getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Viridis);
        EXPECT_EQ(startConfiguration.getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Viridis) << testing::PrintToString(sdk::ColorMap::Viridis);
        startConfiguration.getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Cividis);
        EXPECT_EQ(startConfiguration.getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Cividis) << testing::PrintToString(sdk::ColorMap::Cividis);
        startConfiguration.getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Twilight);
        EXPECT_EQ(startConfiguration.getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Twilight) << testing::PrintToString(sdk::ColorMap::Twilight);
        startConfiguration.getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::TwilightShifted);
        EXPECT_EQ(startConfiguration.getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::TwilightShifted) << testing::PrintToString(sdk::ColorMap::TwilightShifted);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_ReidHotCold_ColorMapEnum) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Bone);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Bone) << testing::PrintToString(sdk::ColorMap::Bone);
        pStream->getConfiguration().getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Jet);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Jet) << testing::PrintToString(sdk::ColorMap::Jet);
        pStream->getConfiguration().getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Winter);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Winter) << testing::PrintToString(sdk::ColorMap::Winter);
        pStream->getConfiguration().getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Rainbow);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Rainbow) << testing::PrintToString(sdk::ColorMap::Rainbow);
        pStream->getConfiguration().getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Ocean);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Ocean) << testing::PrintToString(sdk::ColorMap::Ocean);
        pStream->getConfiguration().getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Summer);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Summer) << testing::PrintToString(sdk::ColorMap::Summer);
        pStream->getConfiguration().getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Spring);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Spring) << testing::PrintToString(sdk::ColorMap::Spring);
        pStream->getConfiguration().getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Cool);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Cool) << testing::PrintToString(sdk::ColorMap::Cool);
        pStream->getConfiguration().getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Hsv);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Hsv) << testing::PrintToString(sdk::ColorMap::Hsv);
        pStream->getConfiguration().getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Pink);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Pink) << testing::PrintToString(sdk::ColorMap::Pink);
        pStream->getConfiguration().getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Hot);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Hot) << testing::PrintToString(sdk::ColorMap::Hot);
        pStream->getConfiguration().getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Parula);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Parula) << testing::PrintToString(sdk::ColorMap::Parula);
        pStream->getConfiguration().getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Magma);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Magma) << testing::PrintToString(sdk::ColorMap::Magma);
        pStream->getConfiguration().getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Inferno);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Inferno) << testing::PrintToString(sdk::ColorMap::Inferno);
        pStream->getConfiguration().getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Plasma);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Plasma) << testing::PrintToString(sdk::ColorMap::Plasma);
        pStream->getConfiguration().getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Viridis);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Viridis) << testing::PrintToString(sdk::ColorMap::Viridis);
        pStream->getConfiguration().getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Cividis);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Cividis) << testing::PrintToString(sdk::ColorMap::Cividis);
        pStream->getConfiguration().getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::Twilight);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::Twilight) << testing::PrintToString(sdk::ColorMap::Twilight);
        pStream->getConfiguration().getCvRenderer().getReidHotCold().setColorMap(sdk::ColorMap::TwilightShifted);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getReidHotCold().getColorMap(), sdk::ColorMap::TwilightShifted) << testing::PrintToString(sdk::ColorMap::TwilightShifted);
    }

    // Test for SkipRendering in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Cross_SkipRenderingDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getCross().getSkipRendering(), true);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Cross_SkipRenderingDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getCross().getSkipRendering(), true);
    }

    TEST_F(CvRendererTest, CvRenderer_Cross_SkipRenderingRandom) {
        startConfiguration.getCvRenderer().getCross().setSkipRendering(false);
        EXPECT_EQ(startConfiguration.getCvRenderer().getCross().getSkipRendering(), false);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Cross_SkipRenderingRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getCross().setSkipRendering(false);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getCross().getSkipRendering(), false);
    }

    // Test for Color in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Cross_ColorDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getCross().getColor(), 16777215);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Cross_ColorDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getCross().getColor(), 16777215);
    }

    TEST_F(CvRendererTest, CvRenderer_Cross_ColorRandom) {
        startConfiguration.getCvRenderer().getCross().setColor(10502400);
        EXPECT_EQ(startConfiguration.getCvRenderer().getCross().getColor(), 10502400);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Cross_ColorRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getCross().setColor(10502400);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getCross().getColor(), 10502400);
    }

    // Test for SizeInPercents in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Cross_SizeInPercentsDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getCross().getSizeInPercents(), 10);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Cross_SizeInPercentsDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getCross().getSizeInPercents(), 10);
    }

    TEST_F(CvRendererTest, CvRenderer_Cross_SizeInPercentsRandom) {
        startConfiguration.getCvRenderer().getCross().setSizeInPercents(56);
        EXPECT_EQ(startConfiguration.getCvRenderer().getCross().getSizeInPercents(), 56);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Cross_SizeInPercentsRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getCross().setSizeInPercents(56);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getCross().getSizeInPercents(), 56);
    }

    // Test for Thickness in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Cross_ThicknessDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getCross().getThickness(), 1);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Cross_ThicknessDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getCross().getThickness(), 1);
    }

    TEST_F(CvRendererTest, CvRenderer_Cross_ThicknessRange) {
        startConfiguration.getCvRenderer().getCross().setThickness(1);
        EXPECT_EQ(startConfiguration.getCvRenderer().getCross().getThickness(), 1);
        startConfiguration.getCvRenderer().getCross().setThickness(100);
        EXPECT_EQ(startConfiguration.getCvRenderer().getCross().getThickness(), 100);
        EXPECT_THROW(startConfiguration.getCvRenderer().getCross().setThickness(1 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getCross().setThickness(100 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Cross_ThicknessRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getCross().setThickness(1);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getCross().getThickness(), 1);
        pStream->getConfiguration().getCvRenderer().getCross().setThickness(100);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getCross().getThickness(), 100);
    }

    // Test for SkipRendering in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_DetectorRoi_SkipRenderingDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getDetectorRoi().getSkipRendering(), false);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_DetectorRoi_SkipRenderingDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getDetectorRoi().getSkipRendering(), false);
    }

    TEST_F(CvRendererTest, CvRenderer_DetectorRoi_SkipRenderingRandom) {
        startConfiguration.getCvRenderer().getDetectorRoi().setSkipRendering(true);
        EXPECT_EQ(startConfiguration.getCvRenderer().getDetectorRoi().getSkipRendering(), true);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_DetectorRoi_SkipRenderingRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getDetectorRoi().setSkipRendering(true);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getDetectorRoi().getSkipRendering(), true);
    }

    // Test for Color in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_DetectorRoi_ColorDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getDetectorRoi().getColor(), 16776960);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_DetectorRoi_ColorDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getDetectorRoi().getColor(), 16776960);
    }

    TEST_F(CvRendererTest, CvRenderer_DetectorRoi_ColorRandom) {
        startConfiguration.getCvRenderer().getDetectorRoi().setColor(500384);
        EXPECT_EQ(startConfiguration.getCvRenderer().getDetectorRoi().getColor(), 500384);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_DetectorRoi_ColorRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getDetectorRoi().setColor(500384);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getDetectorRoi().getColor(), 500384);
    }

    // Test for LineThickness in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_DetectorRoi_LineThicknessDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getDetectorRoi().getLineThickness(), 1);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_DetectorRoi_LineThicknessDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getDetectorRoi().getLineThickness(), 1);
    }

    TEST_F(CvRendererTest, CvRenderer_DetectorRoi_LineThicknessRange) {
        startConfiguration.getCvRenderer().getDetectorRoi().setLineThickness(1);
        EXPECT_EQ(startConfiguration.getCvRenderer().getDetectorRoi().getLineThickness(), 1);
        startConfiguration.getCvRenderer().getDetectorRoi().setLineThickness(100);
        EXPECT_EQ(startConfiguration.getCvRenderer().getDetectorRoi().getLineThickness(), 100);
        EXPECT_THROW(startConfiguration.getCvRenderer().getDetectorRoi().setLineThickness(1 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getDetectorRoi().setLineThickness(100 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_DetectorRoi_LineThicknessRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getDetectorRoi().setLineThickness(1);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getDetectorRoi().getLineThickness(), 1);
        pStream->getConfiguration().getCvRenderer().getDetectorRoi().setLineThickness(100);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getDetectorRoi().getLineThickness(), 100);
    }

    // Test for HideOutside in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_DetectorRoi_HideOutsideDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getDetectorRoi().getHideOutside(), false);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_DetectorRoi_HideOutsideDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getDetectorRoi().getHideOutside(), false);
    }

    TEST_F(CvRendererTest, CvRenderer_DetectorRoi_HideOutsideRandom) {
        startConfiguration.getCvRenderer().getDetectorRoi().setHideOutside(false);
        EXPECT_EQ(startConfiguration.getCvRenderer().getDetectorRoi().getHideOutside(), false);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_DetectorRoi_HideOutsideRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getDetectorRoi().setHideOutside(false);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getDetectorRoi().getHideOutside(), false);
    }

    // Test for SkipRendering__ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes_____SkipRendering__Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("").getSkipRendering(), false);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes_____SkipRendering__Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").getSkipRendering(), false);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes_____SkipRendering__Random) {
        startConfiguration.getCvRenderer().getBoundingBoxes("").setSkipRendering(true);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("").getSkipRendering(), true);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes_____SkipRendering__Random) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").setSkipRendering(true);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").getSkipRendering(), true);
    }

    // Test for BoxColor__ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes_____BoxColor__Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("").getBoxColor(), 16777215);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes_____BoxColor__Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").getBoxColor(), 16777215);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes_____BoxColor__Random) {
        startConfiguration.getCvRenderer().getBoundingBoxes("").setBoxColor(2686306);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("").getBoxColor(), 2686306);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes_____BoxColor__Random) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").setBoxColor(2686306);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").getBoxColor(), 2686306);
    }

    // Test for LineThickness__ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes_____LineThickness__Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("").getLineThickness(), 1);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes_____LineThickness__Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").getLineThickness(), 1);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes_____LineThickness__Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("").setLineThickness(1);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("").getLineThickness(), 1);
        startConfiguration.getCvRenderer().getBoundingBoxes("").setLineThickness(100);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("").getLineThickness(), 100);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("").setLineThickness(1 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("").setLineThickness(100 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes_____LineThickness__Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").setLineThickness(1);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").getLineThickness(), 1);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").setLineThickness(100);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").getLineThickness(), 100);
    }

    // Test for TextOffsetX__ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes_____TextOffsetX__Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("").getTextOffsetX(), 0);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes_____TextOffsetX__Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").getTextOffsetX(), 0);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes_____TextOffsetX__Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("").setTextOffsetX(-1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("").getTextOffsetX(), -1000);
        startConfiguration.getCvRenderer().getBoundingBoxes("").setTextOffsetX(1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("").getTextOffsetX(), 1000);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("").setTextOffsetX(-1000 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("").setTextOffsetX(1000 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes_____TextOffsetX__Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").setTextOffsetX(-1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").getTextOffsetX(), -1000);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").setTextOffsetX(1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").getTextOffsetX(), 1000);
    }

    // Test for TextOffsetY__ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes_____TextOffsetY__Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("").getTextOffsetY(), -8);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes_____TextOffsetY__Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").getTextOffsetY(), -8);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes_____TextOffsetY__Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("").setTextOffsetY(-1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("").getTextOffsetY(), -1000);
        startConfiguration.getCvRenderer().getBoundingBoxes("").setTextOffsetY(1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("").getTextOffsetY(), 1000);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("").setTextOffsetY(-1000 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("").setTextOffsetY(1000 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes_____TextOffsetY__Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").setTextOffsetY(-1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").getTextOffsetY(), -1000);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").setTextOffsetY(1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").getTextOffsetY(), 1000);
    }

    // Test for BottomTextOffsetY__ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes_____BottomTextOffsetY__Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("").getBottomTextOffsetY(), 15);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes_____BottomTextOffsetY__Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").getBottomTextOffsetY(), 15);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes_____BottomTextOffsetY__Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("").setBottomTextOffsetY(-1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("").getBottomTextOffsetY(), -1000);
        startConfiguration.getCvRenderer().getBoundingBoxes("").setBottomTextOffsetY(1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("").getBottomTextOffsetY(), 1000);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("").setBottomTextOffsetY(-1000 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("").setBottomTextOffsetY(1000 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes_____BottomTextOffsetY__Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").setBottomTextOffsetY(-1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").getBottomTextOffsetY(), -1000);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").setBottomTextOffsetY(1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").getBottomTextOffsetY(), 1000);
    }

    // Test for FontColor__ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes_____FontColor__Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("").getFontColor(), 0);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes_____FontColor__Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").getFontColor(), 0);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes_____FontColor__Random) {
        startConfiguration.getCvRenderer().getBoundingBoxes("").setFontColor(2279772);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("").getFontColor(), 2279772);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes_____FontColor__Random) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").setFontColor(2279772);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").getFontColor(), 2279772);
    }

    // Test for FontScale__ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes_____FontScale__Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("").getFontScale(), 0.5f);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes_____FontScale__Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").getFontScale(), 0.5f);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes_____FontScale__Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("").setFontScale(0.1f);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("").getFontScale(), 0.1f);
        startConfiguration.getCvRenderer().getBoundingBoxes("").setFontScale(100.0f);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("").getFontScale(), 100.0f);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("").setFontScale(0.1f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("").setFontScale(100.0f + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes_____FontScale__Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").setFontScale(0.1f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").getFontScale(), 0.1f);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").setFontScale(100.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").getFontScale(), 100.0f);
    }

    // Test for FontThickness__ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes_____FontThickness__Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("").getFontThickness(), 1);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes_____FontThickness__Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").getFontThickness(), 1);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes_____FontThickness__Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("").setFontThickness(1);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("").getFontThickness(), 1);
        startConfiguration.getCvRenderer().getBoundingBoxes("").setFontThickness(100);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("").getFontThickness(), 100);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("").setFontThickness(1 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("").setFontThickness(100 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes_____FontThickness__Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").setFontThickness(1);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").getFontThickness(), 1);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").setFontThickness(100);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("").getFontThickness(), 100);
    }

    // Test for SkipRendering_Person_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Person___SkipRendering_Person_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Person").getSkipRendering(), false);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Person___SkipRendering_Person_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").getSkipRendering(), false);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Person___SkipRendering_Person_Random) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Person").setSkipRendering(true);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Person").getSkipRendering(), true);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Person___SkipRendering_Person_Random) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").setSkipRendering(true);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").getSkipRendering(), true);
    }

    // Test for BoxColor_Person_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Person___BoxColor_Person_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Person").getBoxColor(), 16711680);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Person___BoxColor_Person_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").getBoxColor(), 16711680);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Person___BoxColor_Person_Random) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Person").setBoxColor(2373491);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Person").getBoxColor(), 2373491);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Person___BoxColor_Person_Random) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").setBoxColor(2373491);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").getBoxColor(), 2373491);
    }

    // Test for LineThickness_Person_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Person___LineThickness_Person_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Person").getLineThickness(), 1);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Person___LineThickness_Person_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").getLineThickness(), 1);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Person___LineThickness_Person_Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Person").setLineThickness(1);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Person").getLineThickness(), 1);
        startConfiguration.getCvRenderer().getBoundingBoxes("Person").setLineThickness(100);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Person").getLineThickness(), 100);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Person").setLineThickness(1 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Person").setLineThickness(100 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Person___LineThickness_Person_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").setLineThickness(1);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").getLineThickness(), 1);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").setLineThickness(100);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").getLineThickness(), 100);
    }

    // Test for TextOffsetX_Person_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Person___TextOffsetX_Person_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Person").getTextOffsetX(), 0);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Person___TextOffsetX_Person_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").getTextOffsetX(), 0);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Person___TextOffsetX_Person_Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Person").setTextOffsetX(-1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Person").getTextOffsetX(), -1000);
        startConfiguration.getCvRenderer().getBoundingBoxes("Person").setTextOffsetX(1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Person").getTextOffsetX(), 1000);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Person").setTextOffsetX(-1000 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Person").setTextOffsetX(1000 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Person___TextOffsetX_Person_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").setTextOffsetX(-1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").getTextOffsetX(), -1000);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").setTextOffsetX(1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").getTextOffsetX(), 1000);
    }

    // Test for TextOffsetY_Person_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Person___TextOffsetY_Person_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Person").getTextOffsetY(), -8);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Person___TextOffsetY_Person_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").getTextOffsetY(), -8);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Person___TextOffsetY_Person_Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Person").setTextOffsetY(-1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Person").getTextOffsetY(), -1000);
        startConfiguration.getCvRenderer().getBoundingBoxes("Person").setTextOffsetY(1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Person").getTextOffsetY(), 1000);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Person").setTextOffsetY(-1000 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Person").setTextOffsetY(1000 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Person___TextOffsetY_Person_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").setTextOffsetY(-1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").getTextOffsetY(), -1000);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").setTextOffsetY(1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").getTextOffsetY(), 1000);
    }

    // Test for BottomTextOffsetY_Person_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Person___BottomTextOffsetY_Person_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Person").getBottomTextOffsetY(), 15);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Person___BottomTextOffsetY_Person_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").getBottomTextOffsetY(), 15);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Person___BottomTextOffsetY_Person_Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Person").setBottomTextOffsetY(-1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Person").getBottomTextOffsetY(), -1000);
        startConfiguration.getCvRenderer().getBoundingBoxes("Person").setBottomTextOffsetY(1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Person").getBottomTextOffsetY(), 1000);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Person").setBottomTextOffsetY(-1000 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Person").setBottomTextOffsetY(1000 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Person___BottomTextOffsetY_Person_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").setBottomTextOffsetY(-1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").getBottomTextOffsetY(), -1000);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").setBottomTextOffsetY(1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").getBottomTextOffsetY(), 1000);
    }

    // Test for FontColor_Person_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Person___FontColor_Person_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Person").getFontColor(), 0);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Person___FontColor_Person_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").getFontColor(), 0);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Person___FontColor_Person_Random) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Person").setFontColor(6345512);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Person").getFontColor(), 6345512);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Person___FontColor_Person_Random) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").setFontColor(6345512);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").getFontColor(), 6345512);
    }

    // Test for FontScale_Person_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Person___FontScale_Person_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Person").getFontScale(), 0.5f);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Person___FontScale_Person_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").getFontScale(), 0.5f);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Person___FontScale_Person_Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Person").setFontScale(0.1f);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Person").getFontScale(), 0.1f);
        startConfiguration.getCvRenderer().getBoundingBoxes("Person").setFontScale(100.0f);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Person").getFontScale(), 100.0f);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Person").setFontScale(0.1f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Person").setFontScale(100.0f + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Person___FontScale_Person_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").setFontScale(0.1f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").getFontScale(), 0.1f);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").setFontScale(100.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").getFontScale(), 100.0f);
    }

    // Test for FontThickness_Person_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Person___FontThickness_Person_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Person").getFontThickness(), 1);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Person___FontThickness_Person_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").getFontThickness(), 1);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Person___FontThickness_Person_Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Person").setFontThickness(1);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Person").getFontThickness(), 1);
        startConfiguration.getCvRenderer().getBoundingBoxes("Person").setFontThickness(100);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Person").getFontThickness(), 100);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Person").setFontThickness(1 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Person").setFontThickness(100 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Person___FontThickness_Person_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").setFontThickness(1);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").getFontThickness(), 1);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").setFontThickness(100);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Person").getFontThickness(), 100);
    }

    // Test for SkipRendering_Vehicle_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle___SkipRendering_Vehicle_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").getSkipRendering(), false);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle___SkipRendering_Vehicle_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").getSkipRendering(), false);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle___SkipRendering_Vehicle_Random) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").setSkipRendering(true);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").getSkipRendering(), true);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle___SkipRendering_Vehicle_Random) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").setSkipRendering(true);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").getSkipRendering(), true);
    }

    // Test for BoxColor_Vehicle_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle___BoxColor_Vehicle_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").getBoxColor(), 16744448);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle___BoxColor_Vehicle_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").getBoxColor(), 16744448);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle___BoxColor_Vehicle_Random) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").setBoxColor(6608272);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").getBoxColor(), 6608272);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle___BoxColor_Vehicle_Random) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").setBoxColor(6608272);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").getBoxColor(), 6608272);
    }

    // Test for LineThickness_Vehicle_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle___LineThickness_Vehicle_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").getLineThickness(), 1);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle___LineThickness_Vehicle_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").getLineThickness(), 1);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle___LineThickness_Vehicle_Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").setLineThickness(1);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").getLineThickness(), 1);
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").setLineThickness(100);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").getLineThickness(), 100);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").setLineThickness(1 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").setLineThickness(100 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle___LineThickness_Vehicle_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").setLineThickness(1);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").getLineThickness(), 1);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").setLineThickness(100);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").getLineThickness(), 100);
    }

    // Test for TextOffsetX_Vehicle_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle___TextOffsetX_Vehicle_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").getTextOffsetX(), 0);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle___TextOffsetX_Vehicle_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").getTextOffsetX(), 0);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle___TextOffsetX_Vehicle_Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").setTextOffsetX(-1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").getTextOffsetX(), -1000);
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").setTextOffsetX(1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").getTextOffsetX(), 1000);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").setTextOffsetX(-1000 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").setTextOffsetX(1000 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle___TextOffsetX_Vehicle_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").setTextOffsetX(-1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").getTextOffsetX(), -1000);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").setTextOffsetX(1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").getTextOffsetX(), 1000);
    }

    // Test for TextOffsetY_Vehicle_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle___TextOffsetY_Vehicle_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").getTextOffsetY(), -8);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle___TextOffsetY_Vehicle_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").getTextOffsetY(), -8);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle___TextOffsetY_Vehicle_Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").setTextOffsetY(-1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").getTextOffsetY(), -1000);
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").setTextOffsetY(1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").getTextOffsetY(), 1000);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").setTextOffsetY(-1000 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").setTextOffsetY(1000 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle___TextOffsetY_Vehicle_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").setTextOffsetY(-1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").getTextOffsetY(), -1000);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").setTextOffsetY(1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").getTextOffsetY(), 1000);
    }

    // Test for BottomTextOffsetY_Vehicle_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle___BottomTextOffsetY_Vehicle_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").getBottomTextOffsetY(), 15);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle___BottomTextOffsetY_Vehicle_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").getBottomTextOffsetY(), 15);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle___BottomTextOffsetY_Vehicle_Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").setBottomTextOffsetY(-1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").getBottomTextOffsetY(), -1000);
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").setBottomTextOffsetY(1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").getBottomTextOffsetY(), 1000);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").setBottomTextOffsetY(-1000 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").setBottomTextOffsetY(1000 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle___BottomTextOffsetY_Vehicle_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").setBottomTextOffsetY(-1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").getBottomTextOffsetY(), -1000);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").setBottomTextOffsetY(1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").getBottomTextOffsetY(), 1000);
    }

    // Test for FontColor_Vehicle_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle___FontColor_Vehicle_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").getFontColor(), 0);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle___FontColor_Vehicle_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").getFontColor(), 0);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle___FontColor_Vehicle_Random) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").setFontColor(16093165);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").getFontColor(), 16093165);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle___FontColor_Vehicle_Random) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").setFontColor(16093165);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").getFontColor(), 16093165);
    }

    // Test for FontScale_Vehicle_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle___FontScale_Vehicle_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").getFontScale(), 0.5f);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle___FontScale_Vehicle_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").getFontScale(), 0.5f);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle___FontScale_Vehicle_Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").setFontScale(0.1f);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").getFontScale(), 0.1f);
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").setFontScale(100.0f);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").getFontScale(), 100.0f);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").setFontScale(0.1f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").setFontScale(100.0f + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle___FontScale_Vehicle_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").setFontScale(0.1f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").getFontScale(), 0.1f);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").setFontScale(100.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").getFontScale(), 100.0f);
    }

    // Test for FontThickness_Vehicle_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle___FontThickness_Vehicle_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").getFontThickness(), 1);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle___FontThickness_Vehicle_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").getFontThickness(), 1);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle___FontThickness_Vehicle_Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").setFontThickness(1);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").getFontThickness(), 1);
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").setFontThickness(100);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").getFontThickness(), 100);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").setFontThickness(1 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle").setFontThickness(100 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle___FontThickness_Vehicle_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").setFontThickness(1);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").getFontThickness(), 1);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").setFontThickness(100);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle").getFontThickness(), 100);
    }

    // Test for SkipRendering_Vehicle_heavy_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_heavy___SkipRendering_Vehicle_heavy_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").getSkipRendering(), false);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_heavy___SkipRendering_Vehicle_heavy_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").getSkipRendering(), false);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_heavy___SkipRendering_Vehicle_heavy_Random) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").setSkipRendering(false);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").getSkipRendering(), false);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_heavy___SkipRendering_Vehicle_heavy_Random) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").setSkipRendering(false);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").getSkipRendering(), false);
    }

    // Test for BoxColor_Vehicle_heavy_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_heavy___BoxColor_Vehicle_heavy_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").getBoxColor(), 16744448);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_heavy___BoxColor_Vehicle_heavy_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").getBoxColor(), 16744448);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_heavy___BoxColor_Vehicle_heavy_Random) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").setBoxColor(15077369);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").getBoxColor(), 15077369);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_heavy___BoxColor_Vehicle_heavy_Random) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").setBoxColor(15077369);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").getBoxColor(), 15077369);
    }

    // Test for LineThickness_Vehicle_heavy_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_heavy___LineThickness_Vehicle_heavy_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").getLineThickness(), 1);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_heavy___LineThickness_Vehicle_heavy_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").getLineThickness(), 1);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_heavy___LineThickness_Vehicle_heavy_Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").setLineThickness(1);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").getLineThickness(), 1);
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").setLineThickness(100);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").getLineThickness(), 100);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").setLineThickness(1 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").setLineThickness(100 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_heavy___LineThickness_Vehicle_heavy_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").setLineThickness(1);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").getLineThickness(), 1);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").setLineThickness(100);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").getLineThickness(), 100);
    }

    // Test for TextOffsetX_Vehicle_heavy_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_heavy___TextOffsetX_Vehicle_heavy_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").getTextOffsetX(), 0);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_heavy___TextOffsetX_Vehicle_heavy_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").getTextOffsetX(), 0);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_heavy___TextOffsetX_Vehicle_heavy_Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").setTextOffsetX(-1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").getTextOffsetX(), -1000);
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").setTextOffsetX(1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").getTextOffsetX(), 1000);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").setTextOffsetX(-1000 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").setTextOffsetX(1000 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_heavy___TextOffsetX_Vehicle_heavy_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").setTextOffsetX(-1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").getTextOffsetX(), -1000);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").setTextOffsetX(1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").getTextOffsetX(), 1000);
    }

    // Test for TextOffsetY_Vehicle_heavy_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_heavy___TextOffsetY_Vehicle_heavy_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").getTextOffsetY(), -8);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_heavy___TextOffsetY_Vehicle_heavy_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").getTextOffsetY(), -8);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_heavy___TextOffsetY_Vehicle_heavy_Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").setTextOffsetY(-1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").getTextOffsetY(), -1000);
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").setTextOffsetY(1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").getTextOffsetY(), 1000);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").setTextOffsetY(-1000 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").setTextOffsetY(1000 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_heavy___TextOffsetY_Vehicle_heavy_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").setTextOffsetY(-1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").getTextOffsetY(), -1000);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").setTextOffsetY(1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").getTextOffsetY(), 1000);
    }

    // Test for BottomTextOffsetY_Vehicle_heavy_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_heavy___BottomTextOffsetY_Vehicle_heavy_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").getBottomTextOffsetY(), 15);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_heavy___BottomTextOffsetY_Vehicle_heavy_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").getBottomTextOffsetY(), 15);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_heavy___BottomTextOffsetY_Vehicle_heavy_Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").setBottomTextOffsetY(-1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").getBottomTextOffsetY(), -1000);
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").setBottomTextOffsetY(1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").getBottomTextOffsetY(), 1000);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").setBottomTextOffsetY(-1000 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").setBottomTextOffsetY(1000 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_heavy___BottomTextOffsetY_Vehicle_heavy_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").setBottomTextOffsetY(-1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").getBottomTextOffsetY(), -1000);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").setBottomTextOffsetY(1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").getBottomTextOffsetY(), 1000);
    }

    // Test for FontColor_Vehicle_heavy_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_heavy___FontColor_Vehicle_heavy_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").getFontColor(), 0);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_heavy___FontColor_Vehicle_heavy_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").getFontColor(), 0);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_heavy___FontColor_Vehicle_heavy_Random) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").setFontColor(1000244);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").getFontColor(), 1000244);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_heavy___FontColor_Vehicle_heavy_Random) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").setFontColor(1000244);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").getFontColor(), 1000244);
    }

    // Test for FontScale_Vehicle_heavy_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_heavy___FontScale_Vehicle_heavy_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").getFontScale(), 0.5f);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_heavy___FontScale_Vehicle_heavy_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").getFontScale(), 0.5f);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_heavy___FontScale_Vehicle_heavy_Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").setFontScale(0.1f);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").getFontScale(), 0.1f);
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").setFontScale(100.0f);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").getFontScale(), 100.0f);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").setFontScale(0.1f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").setFontScale(100.0f + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_heavy___FontScale_Vehicle_heavy_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").setFontScale(0.1f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").getFontScale(), 0.1f);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").setFontScale(100.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").getFontScale(), 100.0f);
    }

    // Test for FontThickness_Vehicle_heavy_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_heavy___FontThickness_Vehicle_heavy_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").getFontThickness(), 1);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_heavy___FontThickness_Vehicle_heavy_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").getFontThickness(), 1);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_heavy___FontThickness_Vehicle_heavy_Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").setFontThickness(1);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").getFontThickness(), 1);
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").setFontThickness(100);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").getFontThickness(), 100);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").setFontThickness(1 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/heavy").setFontThickness(100 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_heavy___FontThickness_Vehicle_heavy_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").setFontThickness(1);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").getFontThickness(), 1);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").setFontThickness(100);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/heavy").getFontThickness(), 100);
    }

    // Test for SkipRendering_TwoWheeled_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__TwoWheeled___SkipRendering_TwoWheeled_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").getSkipRendering(), false);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__TwoWheeled___SkipRendering_TwoWheeled_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").getSkipRendering(), false);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__TwoWheeled___SkipRendering_TwoWheeled_Random) {
        startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").setSkipRendering(true);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").getSkipRendering(), true);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__TwoWheeled___SkipRendering_TwoWheeled_Random) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").setSkipRendering(true);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").getSkipRendering(), true);
    }

    // Test for BoxColor_TwoWheeled_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__TwoWheeled___BoxColor_TwoWheeled_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").getBoxColor(), 16711935);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__TwoWheeled___BoxColor_TwoWheeled_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").getBoxColor(), 16711935);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__TwoWheeled___BoxColor_TwoWheeled_Random) {
        startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").setBoxColor(10413938);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").getBoxColor(), 10413938);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__TwoWheeled___BoxColor_TwoWheeled_Random) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").setBoxColor(10413938);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").getBoxColor(), 10413938);
    }

    // Test for LineThickness_TwoWheeled_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__TwoWheeled___LineThickness_TwoWheeled_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").getLineThickness(), 1);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__TwoWheeled___LineThickness_TwoWheeled_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").getLineThickness(), 1);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__TwoWheeled___LineThickness_TwoWheeled_Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").setLineThickness(1);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").getLineThickness(), 1);
        startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").setLineThickness(100);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").getLineThickness(), 100);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").setLineThickness(1 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").setLineThickness(100 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__TwoWheeled___LineThickness_TwoWheeled_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").setLineThickness(1);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").getLineThickness(), 1);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").setLineThickness(100);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").getLineThickness(), 100);
    }

    // Test for TextOffsetX_TwoWheeled_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__TwoWheeled___TextOffsetX_TwoWheeled_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").getTextOffsetX(), 0);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__TwoWheeled___TextOffsetX_TwoWheeled_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").getTextOffsetX(), 0);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__TwoWheeled___TextOffsetX_TwoWheeled_Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").setTextOffsetX(-1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").getTextOffsetX(), -1000);
        startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").setTextOffsetX(1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").getTextOffsetX(), 1000);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").setTextOffsetX(-1000 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").setTextOffsetX(1000 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__TwoWheeled___TextOffsetX_TwoWheeled_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").setTextOffsetX(-1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").getTextOffsetX(), -1000);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").setTextOffsetX(1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").getTextOffsetX(), 1000);
    }

    // Test for TextOffsetY_TwoWheeled_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__TwoWheeled___TextOffsetY_TwoWheeled_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").getTextOffsetY(), -8);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__TwoWheeled___TextOffsetY_TwoWheeled_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").getTextOffsetY(), -8);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__TwoWheeled___TextOffsetY_TwoWheeled_Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").setTextOffsetY(-1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").getTextOffsetY(), -1000);
        startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").setTextOffsetY(1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").getTextOffsetY(), 1000);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").setTextOffsetY(-1000 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").setTextOffsetY(1000 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__TwoWheeled___TextOffsetY_TwoWheeled_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").setTextOffsetY(-1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").getTextOffsetY(), -1000);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").setTextOffsetY(1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").getTextOffsetY(), 1000);
    }

    // Test for BottomTextOffsetY_TwoWheeled_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__TwoWheeled___BottomTextOffsetY_TwoWheeled_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").getBottomTextOffsetY(), 15);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__TwoWheeled___BottomTextOffsetY_TwoWheeled_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").getBottomTextOffsetY(), 15);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__TwoWheeled___BottomTextOffsetY_TwoWheeled_Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").setBottomTextOffsetY(-1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").getBottomTextOffsetY(), -1000);
        startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").setBottomTextOffsetY(1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").getBottomTextOffsetY(), 1000);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").setBottomTextOffsetY(-1000 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").setBottomTextOffsetY(1000 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__TwoWheeled___BottomTextOffsetY_TwoWheeled_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").setBottomTextOffsetY(-1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").getBottomTextOffsetY(), -1000);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").setBottomTextOffsetY(1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").getBottomTextOffsetY(), 1000);
    }

    // Test for FontColor_TwoWheeled_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__TwoWheeled___FontColor_TwoWheeled_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").getFontColor(), 0);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__TwoWheeled___FontColor_TwoWheeled_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").getFontColor(), 0);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__TwoWheeled___FontColor_TwoWheeled_Random) {
        startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").setFontColor(8639119);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").getFontColor(), 8639119);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__TwoWheeled___FontColor_TwoWheeled_Random) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").setFontColor(8639119);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").getFontColor(), 8639119);
    }

    // Test for FontScale_TwoWheeled_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__TwoWheeled___FontScale_TwoWheeled_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").getFontScale(), 0.5f);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__TwoWheeled___FontScale_TwoWheeled_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").getFontScale(), 0.5f);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__TwoWheeled___FontScale_TwoWheeled_Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").setFontScale(0.1f);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").getFontScale(), 0.1f);
        startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").setFontScale(100.0f);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").getFontScale(), 100.0f);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").setFontScale(0.1f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").setFontScale(100.0f + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__TwoWheeled___FontScale_TwoWheeled_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").setFontScale(0.1f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").getFontScale(), 0.1f);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").setFontScale(100.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").getFontScale(), 100.0f);
    }

    // Test for FontThickness_TwoWheeled_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__TwoWheeled___FontThickness_TwoWheeled_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").getFontThickness(), 1);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__TwoWheeled___FontThickness_TwoWheeled_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").getFontThickness(), 1);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__TwoWheeled___FontThickness_TwoWheeled_Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").setFontThickness(1);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").getFontThickness(), 1);
        startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").setFontThickness(100);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").getFontThickness(), 100);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").setFontThickness(1 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("TwoWheeled").setFontThickness(100 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__TwoWheeled___FontThickness_TwoWheeled_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").setFontThickness(1);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").getFontThickness(), 1);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").setFontThickness(100);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("TwoWheeled").getFontThickness(), 100);
    }

    // Test for SkipRendering_Vehicle_light_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_light___SkipRendering_Vehicle_light_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").getSkipRendering(), false);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_light___SkipRendering_Vehicle_light_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").getSkipRendering(), false);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_light___SkipRendering_Vehicle_light_Random) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").setSkipRendering(true);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").getSkipRendering(), true);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_light___SkipRendering_Vehicle_light_Random) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").setSkipRendering(true);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").getSkipRendering(), true);
    }

    // Test for BoxColor_Vehicle_light_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_light___BoxColor_Vehicle_light_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").getBoxColor(), 9127187);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_light___BoxColor_Vehicle_light_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").getBoxColor(), 9127187);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_light___BoxColor_Vehicle_light_Random) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").setBoxColor(11821103);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").getBoxColor(), 11821103);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_light___BoxColor_Vehicle_light_Random) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").setBoxColor(11821103);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").getBoxColor(), 11821103);
    }

    // Test for LineThickness_Vehicle_light_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_light___LineThickness_Vehicle_light_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").getLineThickness(), 1);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_light___LineThickness_Vehicle_light_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").getLineThickness(), 1);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_light___LineThickness_Vehicle_light_Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").setLineThickness(1);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").getLineThickness(), 1);
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").setLineThickness(100);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").getLineThickness(), 100);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").setLineThickness(1 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").setLineThickness(100 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_light___LineThickness_Vehicle_light_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").setLineThickness(1);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").getLineThickness(), 1);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").setLineThickness(100);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").getLineThickness(), 100);
    }

    // Test for TextOffsetX_Vehicle_light_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_light___TextOffsetX_Vehicle_light_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").getTextOffsetX(), 0);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_light___TextOffsetX_Vehicle_light_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").getTextOffsetX(), 0);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_light___TextOffsetX_Vehicle_light_Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").setTextOffsetX(-1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").getTextOffsetX(), -1000);
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").setTextOffsetX(1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").getTextOffsetX(), 1000);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").setTextOffsetX(-1000 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").setTextOffsetX(1000 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_light___TextOffsetX_Vehicle_light_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").setTextOffsetX(-1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").getTextOffsetX(), -1000);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").setTextOffsetX(1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").getTextOffsetX(), 1000);
    }

    // Test for TextOffsetY_Vehicle_light_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_light___TextOffsetY_Vehicle_light_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").getTextOffsetY(), -8);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_light___TextOffsetY_Vehicle_light_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").getTextOffsetY(), -8);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_light___TextOffsetY_Vehicle_light_Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").setTextOffsetY(-1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").getTextOffsetY(), -1000);
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").setTextOffsetY(1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").getTextOffsetY(), 1000);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").setTextOffsetY(-1000 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").setTextOffsetY(1000 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_light___TextOffsetY_Vehicle_light_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").setTextOffsetY(-1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").getTextOffsetY(), -1000);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").setTextOffsetY(1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").getTextOffsetY(), 1000);
    }

    // Test for BottomTextOffsetY_Vehicle_light_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_light___BottomTextOffsetY_Vehicle_light_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").getBottomTextOffsetY(), 15);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_light___BottomTextOffsetY_Vehicle_light_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").getBottomTextOffsetY(), 15);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_light___BottomTextOffsetY_Vehicle_light_Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").setBottomTextOffsetY(-1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").getBottomTextOffsetY(), -1000);
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").setBottomTextOffsetY(1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").getBottomTextOffsetY(), 1000);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").setBottomTextOffsetY(-1000 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").setBottomTextOffsetY(1000 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_light___BottomTextOffsetY_Vehicle_light_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").setBottomTextOffsetY(-1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").getBottomTextOffsetY(), -1000);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").setBottomTextOffsetY(1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").getBottomTextOffsetY(), 1000);
    }

    // Test for FontColor_Vehicle_light_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_light___FontColor_Vehicle_light_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").getFontColor(), 0);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_light___FontColor_Vehicle_light_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").getFontColor(), 0);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_light___FontColor_Vehicle_light_Random) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").setFontColor(1498286);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").getFontColor(), 1498286);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_light___FontColor_Vehicle_light_Random) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").setFontColor(1498286);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").getFontColor(), 1498286);
    }

    // Test for FontScale_Vehicle_light_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_light___FontScale_Vehicle_light_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").getFontScale(), 0.5f);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_light___FontScale_Vehicle_light_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").getFontScale(), 0.5f);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_light___FontScale_Vehicle_light_Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").setFontScale(0.1f);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").getFontScale(), 0.1f);
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").setFontScale(100.0f);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").getFontScale(), 100.0f);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").setFontScale(0.1f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").setFontScale(100.0f + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_light___FontScale_Vehicle_light_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").setFontScale(0.1f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").getFontScale(), 0.1f);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").setFontScale(100.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").getFontScale(), 100.0f);
    }

    // Test for FontThickness_Vehicle_light_ in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_light___FontThickness_Vehicle_light_Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").getFontThickness(), 1);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_light___FontThickness_Vehicle_light_Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").getFontThickness(), 1);
    }

    TEST_F(CvRendererTest, CvRenderer_BoundingBoxes__Vehicle_light___FontThickness_Vehicle_light_Range) {
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").setFontThickness(1);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").getFontThickness(), 1);
        startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").setFontThickness(100);
        EXPECT_EQ(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").getFontThickness(), 100);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").setFontThickness(1 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getBoundingBoxes("Vehicle/light").setFontThickness(100 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_BoundingBoxes__Vehicle_light___FontThickness_Vehicle_light_Range) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").setFontThickness(1);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").getFontThickness(), 1);
        pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").setFontThickness(100);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getBoundingBoxes("Vehicle/light").getFontThickness(), 100);
    }

    // Test for SkipRendering in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Osd_SkipRenderingDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getSkipRendering(), true);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_SkipRenderingDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getSkipRendering(), true);
    }

    TEST_F(CvRendererTest, CvRenderer_Osd_SkipRenderingRandom) {
        startConfiguration.getCvRenderer().getOsd().setSkipRendering(false);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getSkipRendering(), false);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_SkipRenderingRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getOsd().setSkipRendering(false);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getSkipRendering(), false);
    }

    // Test for Corner in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Osd_CornerDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getCorner(), sdk::Corner::TopLeft);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_CornerDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getCorner(), sdk::Corner::TopLeft);
    }

    // Test for Corner in CvRenderer (enum)
    TEST_F(CvRendererTest, CvRenderer_Osd_CornerEnum) {
        startConfiguration.getCvRenderer().getOsd().setCorner(sdk::Corner::TopLeft);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getCorner(), sdk::Corner::TopLeft) << testing::PrintToString(sdk::Corner::TopLeft);
        startConfiguration.getCvRenderer().getOsd().setCorner(sdk::Corner::TopRight);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getCorner(), sdk::Corner::TopRight) << testing::PrintToString(sdk::Corner::TopRight);
        startConfiguration.getCvRenderer().getOsd().setCorner(sdk::Corner::BottomLeft);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getCorner(), sdk::Corner::BottomLeft) << testing::PrintToString(sdk::Corner::BottomLeft);
        startConfiguration.getCvRenderer().getOsd().setCorner(sdk::Corner::BottomRight);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getCorner(), sdk::Corner::BottomRight) << testing::PrintToString(sdk::Corner::BottomRight);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_CornerEnum) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getOsd().setCorner(sdk::Corner::TopLeft);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getCorner(), sdk::Corner::TopLeft) << testing::PrintToString(sdk::Corner::TopLeft);
        pStream->getConfiguration().getCvRenderer().getOsd().setCorner(sdk::Corner::TopRight);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getCorner(), sdk::Corner::TopRight) << testing::PrintToString(sdk::Corner::TopRight);
        pStream->getConfiguration().getCvRenderer().getOsd().setCorner(sdk::Corner::BottomLeft);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getCorner(), sdk::Corner::BottomLeft) << testing::PrintToString(sdk::Corner::BottomLeft);
        pStream->getConfiguration().getCvRenderer().getOsd().setCorner(sdk::Corner::BottomRight);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getCorner(), sdk::Corner::BottomRight) << testing::PrintToString(sdk::Corner::BottomRight);
    }

    // Test for Values0 in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Osd_Values0Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(0), sdk::OsdValue::Version);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_Values0Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(0), sdk::OsdValue::Version);
    }

    // Test for Values0 in CvRenderer (enum)
    TEST_F(CvRendererTest, CvRenderer_Osd_Values0Enum) {
        startConfiguration.getCvRenderer().getOsd().setValues(0, sdk::OsdValue::Version);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(0), sdk::OsdValue::Version) << testing::PrintToString(sdk::OsdValue::Version);
        startConfiguration.getCvRenderer().getOsd().setValues(0, sdk::OsdValue::StreamId);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(0), sdk::OsdValue::StreamId) << testing::PrintToString(sdk::OsdValue::StreamId);
        startConfiguration.getCvRenderer().getOsd().setValues(0, sdk::OsdValue::InputDescription);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(0), sdk::OsdValue::InputDescription) << testing::PrintToString(sdk::OsdValue::InputDescription);
        startConfiguration.getCvRenderer().getOsd().setValues(0, sdk::OsdValue::FrameId);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(0), sdk::OsdValue::FrameId) << testing::PrintToString(sdk::OsdValue::FrameId);
        startConfiguration.getCvRenderer().getOsd().setValues(0, sdk::OsdValue::Fps);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(0), sdk::OsdValue::Fps) << testing::PrintToString(sdk::OsdValue::Fps);
        startConfiguration.getCvRenderer().getOsd().setValues(0, sdk::OsdValue::Pts);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(0), sdk::OsdValue::Pts) << testing::PrintToString(sdk::OsdValue::Pts);
        startConfiguration.getCvRenderer().getOsd().setValues(0, sdk::OsdValue::Latency);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(0), sdk::OsdValue::Latency) << testing::PrintToString(sdk::OsdValue::Latency);
        startConfiguration.getCvRenderer().getOsd().setValues(0, sdk::OsdValue::TelemetryPlatform);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(0), sdk::OsdValue::TelemetryPlatform) << testing::PrintToString(sdk::OsdValue::TelemetryPlatform);
        startConfiguration.getCvRenderer().getOsd().setValues(0, sdk::OsdValue::TelemetryPayload);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(0), sdk::OsdValue::TelemetryPayload) << testing::PrintToString(sdk::OsdValue::TelemetryPayload);
        startConfiguration.getCvRenderer().getOsd().setValues(0, sdk::OsdValue::FrameRegistration);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(0), sdk::OsdValue::FrameRegistration) << testing::PrintToString(sdk::OsdValue::FrameRegistration);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_Values0Enum) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(0, sdk::OsdValue::Version);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(0), sdk::OsdValue::Version) << testing::PrintToString(sdk::OsdValue::Version);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(0, sdk::OsdValue::StreamId);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(0), sdk::OsdValue::StreamId) << testing::PrintToString(sdk::OsdValue::StreamId);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(0, sdk::OsdValue::InputDescription);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(0), sdk::OsdValue::InputDescription) << testing::PrintToString(sdk::OsdValue::InputDescription);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(0, sdk::OsdValue::FrameId);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(0), sdk::OsdValue::FrameId) << testing::PrintToString(sdk::OsdValue::FrameId);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(0, sdk::OsdValue::Fps);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(0), sdk::OsdValue::Fps) << testing::PrintToString(sdk::OsdValue::Fps);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(0, sdk::OsdValue::Pts);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(0), sdk::OsdValue::Pts) << testing::PrintToString(sdk::OsdValue::Pts);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(0, sdk::OsdValue::Latency);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(0), sdk::OsdValue::Latency) << testing::PrintToString(sdk::OsdValue::Latency);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(0, sdk::OsdValue::TelemetryPlatform);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(0), sdk::OsdValue::TelemetryPlatform) << testing::PrintToString(sdk::OsdValue::TelemetryPlatform);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(0, sdk::OsdValue::TelemetryPayload);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(0), sdk::OsdValue::TelemetryPayload) << testing::PrintToString(sdk::OsdValue::TelemetryPayload);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(0, sdk::OsdValue::FrameRegistration);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(0), sdk::OsdValue::FrameRegistration) << testing::PrintToString(sdk::OsdValue::FrameRegistration);
    }

    // Test for Values1 in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Osd_Values1Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(1), sdk::OsdValue::StreamId);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_Values1Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(1), sdk::OsdValue::StreamId);
    }

    // Test for Values1 in CvRenderer (enum)
    TEST_F(CvRendererTest, CvRenderer_Osd_Values1Enum) {
        startConfiguration.getCvRenderer().getOsd().setValues(1, sdk::OsdValue::Version);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(1), sdk::OsdValue::Version) << testing::PrintToString(sdk::OsdValue::Version);
        startConfiguration.getCvRenderer().getOsd().setValues(1, sdk::OsdValue::StreamId);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(1), sdk::OsdValue::StreamId) << testing::PrintToString(sdk::OsdValue::StreamId);
        startConfiguration.getCvRenderer().getOsd().setValues(1, sdk::OsdValue::InputDescription);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(1), sdk::OsdValue::InputDescription) << testing::PrintToString(sdk::OsdValue::InputDescription);
        startConfiguration.getCvRenderer().getOsd().setValues(1, sdk::OsdValue::FrameId);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(1), sdk::OsdValue::FrameId) << testing::PrintToString(sdk::OsdValue::FrameId);
        startConfiguration.getCvRenderer().getOsd().setValues(1, sdk::OsdValue::Fps);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(1), sdk::OsdValue::Fps) << testing::PrintToString(sdk::OsdValue::Fps);
        startConfiguration.getCvRenderer().getOsd().setValues(1, sdk::OsdValue::Pts);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(1), sdk::OsdValue::Pts) << testing::PrintToString(sdk::OsdValue::Pts);
        startConfiguration.getCvRenderer().getOsd().setValues(1, sdk::OsdValue::Latency);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(1), sdk::OsdValue::Latency) << testing::PrintToString(sdk::OsdValue::Latency);
        startConfiguration.getCvRenderer().getOsd().setValues(1, sdk::OsdValue::TelemetryPlatform);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(1), sdk::OsdValue::TelemetryPlatform) << testing::PrintToString(sdk::OsdValue::TelemetryPlatform);
        startConfiguration.getCvRenderer().getOsd().setValues(1, sdk::OsdValue::TelemetryPayload);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(1), sdk::OsdValue::TelemetryPayload) << testing::PrintToString(sdk::OsdValue::TelemetryPayload);
        startConfiguration.getCvRenderer().getOsd().setValues(1, sdk::OsdValue::FrameRegistration);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(1), sdk::OsdValue::FrameRegistration) << testing::PrintToString(sdk::OsdValue::FrameRegistration);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_Values1Enum) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(1, sdk::OsdValue::Version);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(1), sdk::OsdValue::Version) << testing::PrintToString(sdk::OsdValue::Version);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(1, sdk::OsdValue::StreamId);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(1), sdk::OsdValue::StreamId) << testing::PrintToString(sdk::OsdValue::StreamId);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(1, sdk::OsdValue::InputDescription);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(1), sdk::OsdValue::InputDescription) << testing::PrintToString(sdk::OsdValue::InputDescription);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(1, sdk::OsdValue::FrameId);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(1), sdk::OsdValue::FrameId) << testing::PrintToString(sdk::OsdValue::FrameId);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(1, sdk::OsdValue::Fps);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(1), sdk::OsdValue::Fps) << testing::PrintToString(sdk::OsdValue::Fps);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(1, sdk::OsdValue::Pts);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(1), sdk::OsdValue::Pts) << testing::PrintToString(sdk::OsdValue::Pts);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(1, sdk::OsdValue::Latency);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(1), sdk::OsdValue::Latency) << testing::PrintToString(sdk::OsdValue::Latency);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(1, sdk::OsdValue::TelemetryPlatform);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(1), sdk::OsdValue::TelemetryPlatform) << testing::PrintToString(sdk::OsdValue::TelemetryPlatform);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(1, sdk::OsdValue::TelemetryPayload);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(1), sdk::OsdValue::TelemetryPayload) << testing::PrintToString(sdk::OsdValue::TelemetryPayload);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(1, sdk::OsdValue::FrameRegistration);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(1), sdk::OsdValue::FrameRegistration) << testing::PrintToString(sdk::OsdValue::FrameRegistration);
    }

    // Test for Values2 in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Osd_Values2Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(2), sdk::OsdValue::InputDescription);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_Values2Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(2), sdk::OsdValue::InputDescription);
    }

    // Test for Values2 in CvRenderer (enum)
    TEST_F(CvRendererTest, CvRenderer_Osd_Values2Enum) {
        startConfiguration.getCvRenderer().getOsd().setValues(2, sdk::OsdValue::Version);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(2), sdk::OsdValue::Version) << testing::PrintToString(sdk::OsdValue::Version);
        startConfiguration.getCvRenderer().getOsd().setValues(2, sdk::OsdValue::StreamId);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(2), sdk::OsdValue::StreamId) << testing::PrintToString(sdk::OsdValue::StreamId);
        startConfiguration.getCvRenderer().getOsd().setValues(2, sdk::OsdValue::InputDescription);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(2), sdk::OsdValue::InputDescription) << testing::PrintToString(sdk::OsdValue::InputDescription);
        startConfiguration.getCvRenderer().getOsd().setValues(2, sdk::OsdValue::FrameId);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(2), sdk::OsdValue::FrameId) << testing::PrintToString(sdk::OsdValue::FrameId);
        startConfiguration.getCvRenderer().getOsd().setValues(2, sdk::OsdValue::Fps);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(2), sdk::OsdValue::Fps) << testing::PrintToString(sdk::OsdValue::Fps);
        startConfiguration.getCvRenderer().getOsd().setValues(2, sdk::OsdValue::Pts);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(2), sdk::OsdValue::Pts) << testing::PrintToString(sdk::OsdValue::Pts);
        startConfiguration.getCvRenderer().getOsd().setValues(2, sdk::OsdValue::Latency);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(2), sdk::OsdValue::Latency) << testing::PrintToString(sdk::OsdValue::Latency);
        startConfiguration.getCvRenderer().getOsd().setValues(2, sdk::OsdValue::TelemetryPlatform);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(2), sdk::OsdValue::TelemetryPlatform) << testing::PrintToString(sdk::OsdValue::TelemetryPlatform);
        startConfiguration.getCvRenderer().getOsd().setValues(2, sdk::OsdValue::TelemetryPayload);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(2), sdk::OsdValue::TelemetryPayload) << testing::PrintToString(sdk::OsdValue::TelemetryPayload);
        startConfiguration.getCvRenderer().getOsd().setValues(2, sdk::OsdValue::FrameRegistration);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(2), sdk::OsdValue::FrameRegistration) << testing::PrintToString(sdk::OsdValue::FrameRegistration);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_Values2Enum) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(2, sdk::OsdValue::Version);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(2), sdk::OsdValue::Version) << testing::PrintToString(sdk::OsdValue::Version);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(2, sdk::OsdValue::StreamId);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(2), sdk::OsdValue::StreamId) << testing::PrintToString(sdk::OsdValue::StreamId);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(2, sdk::OsdValue::InputDescription);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(2), sdk::OsdValue::InputDescription) << testing::PrintToString(sdk::OsdValue::InputDescription);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(2, sdk::OsdValue::FrameId);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(2), sdk::OsdValue::FrameId) << testing::PrintToString(sdk::OsdValue::FrameId);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(2, sdk::OsdValue::Fps);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(2), sdk::OsdValue::Fps) << testing::PrintToString(sdk::OsdValue::Fps);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(2, sdk::OsdValue::Pts);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(2), sdk::OsdValue::Pts) << testing::PrintToString(sdk::OsdValue::Pts);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(2, sdk::OsdValue::Latency);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(2), sdk::OsdValue::Latency) << testing::PrintToString(sdk::OsdValue::Latency);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(2, sdk::OsdValue::TelemetryPlatform);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(2), sdk::OsdValue::TelemetryPlatform) << testing::PrintToString(sdk::OsdValue::TelemetryPlatform);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(2, sdk::OsdValue::TelemetryPayload);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(2), sdk::OsdValue::TelemetryPayload) << testing::PrintToString(sdk::OsdValue::TelemetryPayload);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(2, sdk::OsdValue::FrameRegistration);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(2), sdk::OsdValue::FrameRegistration) << testing::PrintToString(sdk::OsdValue::FrameRegistration);
    }

    // Test for Values3 in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Osd_Values3Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(3), sdk::OsdValue::FrameId);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_Values3Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(3), sdk::OsdValue::FrameId);
    }

    // Test for Values3 in CvRenderer (enum)
    TEST_F(CvRendererTest, CvRenderer_Osd_Values3Enum) {
        startConfiguration.getCvRenderer().getOsd().setValues(3, sdk::OsdValue::Version);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(3), sdk::OsdValue::Version) << testing::PrintToString(sdk::OsdValue::Version);
        startConfiguration.getCvRenderer().getOsd().setValues(3, sdk::OsdValue::StreamId);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(3), sdk::OsdValue::StreamId) << testing::PrintToString(sdk::OsdValue::StreamId);
        startConfiguration.getCvRenderer().getOsd().setValues(3, sdk::OsdValue::InputDescription);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(3), sdk::OsdValue::InputDescription) << testing::PrintToString(sdk::OsdValue::InputDescription);
        startConfiguration.getCvRenderer().getOsd().setValues(3, sdk::OsdValue::FrameId);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(3), sdk::OsdValue::FrameId) << testing::PrintToString(sdk::OsdValue::FrameId);
        startConfiguration.getCvRenderer().getOsd().setValues(3, sdk::OsdValue::Fps);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(3), sdk::OsdValue::Fps) << testing::PrintToString(sdk::OsdValue::Fps);
        startConfiguration.getCvRenderer().getOsd().setValues(3, sdk::OsdValue::Pts);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(3), sdk::OsdValue::Pts) << testing::PrintToString(sdk::OsdValue::Pts);
        startConfiguration.getCvRenderer().getOsd().setValues(3, sdk::OsdValue::Latency);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(3), sdk::OsdValue::Latency) << testing::PrintToString(sdk::OsdValue::Latency);
        startConfiguration.getCvRenderer().getOsd().setValues(3, sdk::OsdValue::TelemetryPlatform);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(3), sdk::OsdValue::TelemetryPlatform) << testing::PrintToString(sdk::OsdValue::TelemetryPlatform);
        startConfiguration.getCvRenderer().getOsd().setValues(3, sdk::OsdValue::TelemetryPayload);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(3), sdk::OsdValue::TelemetryPayload) << testing::PrintToString(sdk::OsdValue::TelemetryPayload);
        startConfiguration.getCvRenderer().getOsd().setValues(3, sdk::OsdValue::FrameRegistration);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(3), sdk::OsdValue::FrameRegistration) << testing::PrintToString(sdk::OsdValue::FrameRegistration);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_Values3Enum) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(3, sdk::OsdValue::Version);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(3), sdk::OsdValue::Version) << testing::PrintToString(sdk::OsdValue::Version);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(3, sdk::OsdValue::StreamId);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(3), sdk::OsdValue::StreamId) << testing::PrintToString(sdk::OsdValue::StreamId);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(3, sdk::OsdValue::InputDescription);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(3), sdk::OsdValue::InputDescription) << testing::PrintToString(sdk::OsdValue::InputDescription);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(3, sdk::OsdValue::FrameId);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(3), sdk::OsdValue::FrameId) << testing::PrintToString(sdk::OsdValue::FrameId);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(3, sdk::OsdValue::Fps);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(3), sdk::OsdValue::Fps) << testing::PrintToString(sdk::OsdValue::Fps);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(3, sdk::OsdValue::Pts);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(3), sdk::OsdValue::Pts) << testing::PrintToString(sdk::OsdValue::Pts);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(3, sdk::OsdValue::Latency);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(3), sdk::OsdValue::Latency) << testing::PrintToString(sdk::OsdValue::Latency);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(3, sdk::OsdValue::TelemetryPlatform);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(3), sdk::OsdValue::TelemetryPlatform) << testing::PrintToString(sdk::OsdValue::TelemetryPlatform);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(3, sdk::OsdValue::TelemetryPayload);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(3), sdk::OsdValue::TelemetryPayload) << testing::PrintToString(sdk::OsdValue::TelemetryPayload);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(3, sdk::OsdValue::FrameRegistration);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(3), sdk::OsdValue::FrameRegistration) << testing::PrintToString(sdk::OsdValue::FrameRegistration);
    }

    // Test for Values4 in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Osd_Values4Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(4), sdk::OsdValue::Pts);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_Values4Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(4), sdk::OsdValue::Pts);
    }

    // Test for Values4 in CvRenderer (enum)
    TEST_F(CvRendererTest, CvRenderer_Osd_Values4Enum) {
        startConfiguration.getCvRenderer().getOsd().setValues(4, sdk::OsdValue::Version);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(4), sdk::OsdValue::Version) << testing::PrintToString(sdk::OsdValue::Version);
        startConfiguration.getCvRenderer().getOsd().setValues(4, sdk::OsdValue::StreamId);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(4), sdk::OsdValue::StreamId) << testing::PrintToString(sdk::OsdValue::StreamId);
        startConfiguration.getCvRenderer().getOsd().setValues(4, sdk::OsdValue::InputDescription);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(4), sdk::OsdValue::InputDescription) << testing::PrintToString(sdk::OsdValue::InputDescription);
        startConfiguration.getCvRenderer().getOsd().setValues(4, sdk::OsdValue::FrameId);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(4), sdk::OsdValue::FrameId) << testing::PrintToString(sdk::OsdValue::FrameId);
        startConfiguration.getCvRenderer().getOsd().setValues(4, sdk::OsdValue::Fps);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(4), sdk::OsdValue::Fps) << testing::PrintToString(sdk::OsdValue::Fps);
        startConfiguration.getCvRenderer().getOsd().setValues(4, sdk::OsdValue::Pts);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(4), sdk::OsdValue::Pts) << testing::PrintToString(sdk::OsdValue::Pts);
        startConfiguration.getCvRenderer().getOsd().setValues(4, sdk::OsdValue::Latency);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(4), sdk::OsdValue::Latency) << testing::PrintToString(sdk::OsdValue::Latency);
        startConfiguration.getCvRenderer().getOsd().setValues(4, sdk::OsdValue::TelemetryPlatform);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(4), sdk::OsdValue::TelemetryPlatform) << testing::PrintToString(sdk::OsdValue::TelemetryPlatform);
        startConfiguration.getCvRenderer().getOsd().setValues(4, sdk::OsdValue::TelemetryPayload);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(4), sdk::OsdValue::TelemetryPayload) << testing::PrintToString(sdk::OsdValue::TelemetryPayload);
        startConfiguration.getCvRenderer().getOsd().setValues(4, sdk::OsdValue::FrameRegistration);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(4), sdk::OsdValue::FrameRegistration) << testing::PrintToString(sdk::OsdValue::FrameRegistration);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_Values4Enum) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(4, sdk::OsdValue::Version);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(4), sdk::OsdValue::Version) << testing::PrintToString(sdk::OsdValue::Version);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(4, sdk::OsdValue::StreamId);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(4), sdk::OsdValue::StreamId) << testing::PrintToString(sdk::OsdValue::StreamId);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(4, sdk::OsdValue::InputDescription);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(4), sdk::OsdValue::InputDescription) << testing::PrintToString(sdk::OsdValue::InputDescription);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(4, sdk::OsdValue::FrameId);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(4), sdk::OsdValue::FrameId) << testing::PrintToString(sdk::OsdValue::FrameId);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(4, sdk::OsdValue::Fps);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(4), sdk::OsdValue::Fps) << testing::PrintToString(sdk::OsdValue::Fps);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(4, sdk::OsdValue::Pts);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(4), sdk::OsdValue::Pts) << testing::PrintToString(sdk::OsdValue::Pts);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(4, sdk::OsdValue::Latency);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(4), sdk::OsdValue::Latency) << testing::PrintToString(sdk::OsdValue::Latency);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(4, sdk::OsdValue::TelemetryPlatform);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(4), sdk::OsdValue::TelemetryPlatform) << testing::PrintToString(sdk::OsdValue::TelemetryPlatform);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(4, sdk::OsdValue::TelemetryPayload);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(4), sdk::OsdValue::TelemetryPayload) << testing::PrintToString(sdk::OsdValue::TelemetryPayload);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(4, sdk::OsdValue::FrameRegistration);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(4), sdk::OsdValue::FrameRegistration) << testing::PrintToString(sdk::OsdValue::FrameRegistration);
    }

    // Test for Values5 in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Osd_Values5Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(5), sdk::OsdValue::Fps);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_Values5Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(5), sdk::OsdValue::Fps);
    }

    // Test for Values5 in CvRenderer (enum)
    TEST_F(CvRendererTest, CvRenderer_Osd_Values5Enum) {
        startConfiguration.getCvRenderer().getOsd().setValues(5, sdk::OsdValue::Version);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(5), sdk::OsdValue::Version) << testing::PrintToString(sdk::OsdValue::Version);
        startConfiguration.getCvRenderer().getOsd().setValues(5, sdk::OsdValue::StreamId);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(5), sdk::OsdValue::StreamId) << testing::PrintToString(sdk::OsdValue::StreamId);
        startConfiguration.getCvRenderer().getOsd().setValues(5, sdk::OsdValue::InputDescription);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(5), sdk::OsdValue::InputDescription) << testing::PrintToString(sdk::OsdValue::InputDescription);
        startConfiguration.getCvRenderer().getOsd().setValues(5, sdk::OsdValue::FrameId);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(5), sdk::OsdValue::FrameId) << testing::PrintToString(sdk::OsdValue::FrameId);
        startConfiguration.getCvRenderer().getOsd().setValues(5, sdk::OsdValue::Fps);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(5), sdk::OsdValue::Fps) << testing::PrintToString(sdk::OsdValue::Fps);
        startConfiguration.getCvRenderer().getOsd().setValues(5, sdk::OsdValue::Pts);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(5), sdk::OsdValue::Pts) << testing::PrintToString(sdk::OsdValue::Pts);
        startConfiguration.getCvRenderer().getOsd().setValues(5, sdk::OsdValue::Latency);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(5), sdk::OsdValue::Latency) << testing::PrintToString(sdk::OsdValue::Latency);
        startConfiguration.getCvRenderer().getOsd().setValues(5, sdk::OsdValue::TelemetryPlatform);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(5), sdk::OsdValue::TelemetryPlatform) << testing::PrintToString(sdk::OsdValue::TelemetryPlatform);
        startConfiguration.getCvRenderer().getOsd().setValues(5, sdk::OsdValue::TelemetryPayload);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(5), sdk::OsdValue::TelemetryPayload) << testing::PrintToString(sdk::OsdValue::TelemetryPayload);
        startConfiguration.getCvRenderer().getOsd().setValues(5, sdk::OsdValue::FrameRegistration);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(5), sdk::OsdValue::FrameRegistration) << testing::PrintToString(sdk::OsdValue::FrameRegistration);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_Values5Enum) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(5, sdk::OsdValue::Version);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(5), sdk::OsdValue::Version) << testing::PrintToString(sdk::OsdValue::Version);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(5, sdk::OsdValue::StreamId);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(5), sdk::OsdValue::StreamId) << testing::PrintToString(sdk::OsdValue::StreamId);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(5, sdk::OsdValue::InputDescription);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(5), sdk::OsdValue::InputDescription) << testing::PrintToString(sdk::OsdValue::InputDescription);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(5, sdk::OsdValue::FrameId);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(5), sdk::OsdValue::FrameId) << testing::PrintToString(sdk::OsdValue::FrameId);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(5, sdk::OsdValue::Fps);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(5), sdk::OsdValue::Fps) << testing::PrintToString(sdk::OsdValue::Fps);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(5, sdk::OsdValue::Pts);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(5), sdk::OsdValue::Pts) << testing::PrintToString(sdk::OsdValue::Pts);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(5, sdk::OsdValue::Latency);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(5), sdk::OsdValue::Latency) << testing::PrintToString(sdk::OsdValue::Latency);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(5, sdk::OsdValue::TelemetryPlatform);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(5), sdk::OsdValue::TelemetryPlatform) << testing::PrintToString(sdk::OsdValue::TelemetryPlatform);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(5, sdk::OsdValue::TelemetryPayload);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(5), sdk::OsdValue::TelemetryPayload) << testing::PrintToString(sdk::OsdValue::TelemetryPayload);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(5, sdk::OsdValue::FrameRegistration);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(5), sdk::OsdValue::FrameRegistration) << testing::PrintToString(sdk::OsdValue::FrameRegistration);
    }

    // Test for Values6 in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Osd_Values6Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(6), sdk::OsdValue::Latency);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_Values6Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(6), sdk::OsdValue::Latency);
    }

    // Test for Values6 in CvRenderer (enum)
    TEST_F(CvRendererTest, CvRenderer_Osd_Values6Enum) {
        startConfiguration.getCvRenderer().getOsd().setValues(6, sdk::OsdValue::Version);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(6), sdk::OsdValue::Version) << testing::PrintToString(sdk::OsdValue::Version);
        startConfiguration.getCvRenderer().getOsd().setValues(6, sdk::OsdValue::StreamId);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(6), sdk::OsdValue::StreamId) << testing::PrintToString(sdk::OsdValue::StreamId);
        startConfiguration.getCvRenderer().getOsd().setValues(6, sdk::OsdValue::InputDescription);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(6), sdk::OsdValue::InputDescription) << testing::PrintToString(sdk::OsdValue::InputDescription);
        startConfiguration.getCvRenderer().getOsd().setValues(6, sdk::OsdValue::FrameId);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(6), sdk::OsdValue::FrameId) << testing::PrintToString(sdk::OsdValue::FrameId);
        startConfiguration.getCvRenderer().getOsd().setValues(6, sdk::OsdValue::Fps);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(6), sdk::OsdValue::Fps) << testing::PrintToString(sdk::OsdValue::Fps);
        startConfiguration.getCvRenderer().getOsd().setValues(6, sdk::OsdValue::Pts);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(6), sdk::OsdValue::Pts) << testing::PrintToString(sdk::OsdValue::Pts);
        startConfiguration.getCvRenderer().getOsd().setValues(6, sdk::OsdValue::Latency);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(6), sdk::OsdValue::Latency) << testing::PrintToString(sdk::OsdValue::Latency);
        startConfiguration.getCvRenderer().getOsd().setValues(6, sdk::OsdValue::TelemetryPlatform);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(6), sdk::OsdValue::TelemetryPlatform) << testing::PrintToString(sdk::OsdValue::TelemetryPlatform);
        startConfiguration.getCvRenderer().getOsd().setValues(6, sdk::OsdValue::TelemetryPayload);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(6), sdk::OsdValue::TelemetryPayload) << testing::PrintToString(sdk::OsdValue::TelemetryPayload);
        startConfiguration.getCvRenderer().getOsd().setValues(6, sdk::OsdValue::FrameRegistration);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(6), sdk::OsdValue::FrameRegistration) << testing::PrintToString(sdk::OsdValue::FrameRegistration);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_Values6Enum) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(6, sdk::OsdValue::Version);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(6), sdk::OsdValue::Version) << testing::PrintToString(sdk::OsdValue::Version);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(6, sdk::OsdValue::StreamId);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(6), sdk::OsdValue::StreamId) << testing::PrintToString(sdk::OsdValue::StreamId);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(6, sdk::OsdValue::InputDescription);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(6), sdk::OsdValue::InputDescription) << testing::PrintToString(sdk::OsdValue::InputDescription);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(6, sdk::OsdValue::FrameId);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(6), sdk::OsdValue::FrameId) << testing::PrintToString(sdk::OsdValue::FrameId);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(6, sdk::OsdValue::Fps);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(6), sdk::OsdValue::Fps) << testing::PrintToString(sdk::OsdValue::Fps);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(6, sdk::OsdValue::Pts);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(6), sdk::OsdValue::Pts) << testing::PrintToString(sdk::OsdValue::Pts);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(6, sdk::OsdValue::Latency);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(6), sdk::OsdValue::Latency) << testing::PrintToString(sdk::OsdValue::Latency);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(6, sdk::OsdValue::TelemetryPlatform);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(6), sdk::OsdValue::TelemetryPlatform) << testing::PrintToString(sdk::OsdValue::TelemetryPlatform);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(6, sdk::OsdValue::TelemetryPayload);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(6), sdk::OsdValue::TelemetryPayload) << testing::PrintToString(sdk::OsdValue::TelemetryPayload);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(6, sdk::OsdValue::FrameRegistration);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(6), sdk::OsdValue::FrameRegistration) << testing::PrintToString(sdk::OsdValue::FrameRegistration);
    }

    // Test for Values7 in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Osd_Values7Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(7), sdk::OsdValue::TelemetryPlatform);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_Values7Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(7), sdk::OsdValue::TelemetryPlatform);
    }

    // Test for Values7 in CvRenderer (enum)
    TEST_F(CvRendererTest, CvRenderer_Osd_Values7Enum) {
        startConfiguration.getCvRenderer().getOsd().setValues(7, sdk::OsdValue::Version);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(7), sdk::OsdValue::Version) << testing::PrintToString(sdk::OsdValue::Version);
        startConfiguration.getCvRenderer().getOsd().setValues(7, sdk::OsdValue::StreamId);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(7), sdk::OsdValue::StreamId) << testing::PrintToString(sdk::OsdValue::StreamId);
        startConfiguration.getCvRenderer().getOsd().setValues(7, sdk::OsdValue::InputDescription);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(7), sdk::OsdValue::InputDescription) << testing::PrintToString(sdk::OsdValue::InputDescription);
        startConfiguration.getCvRenderer().getOsd().setValues(7, sdk::OsdValue::FrameId);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(7), sdk::OsdValue::FrameId) << testing::PrintToString(sdk::OsdValue::FrameId);
        startConfiguration.getCvRenderer().getOsd().setValues(7, sdk::OsdValue::Fps);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(7), sdk::OsdValue::Fps) << testing::PrintToString(sdk::OsdValue::Fps);
        startConfiguration.getCvRenderer().getOsd().setValues(7, sdk::OsdValue::Pts);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(7), sdk::OsdValue::Pts) << testing::PrintToString(sdk::OsdValue::Pts);
        startConfiguration.getCvRenderer().getOsd().setValues(7, sdk::OsdValue::Latency);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(7), sdk::OsdValue::Latency) << testing::PrintToString(sdk::OsdValue::Latency);
        startConfiguration.getCvRenderer().getOsd().setValues(7, sdk::OsdValue::TelemetryPlatform);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(7), sdk::OsdValue::TelemetryPlatform) << testing::PrintToString(sdk::OsdValue::TelemetryPlatform);
        startConfiguration.getCvRenderer().getOsd().setValues(7, sdk::OsdValue::TelemetryPayload);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(7), sdk::OsdValue::TelemetryPayload) << testing::PrintToString(sdk::OsdValue::TelemetryPayload);
        startConfiguration.getCvRenderer().getOsd().setValues(7, sdk::OsdValue::FrameRegistration);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(7), sdk::OsdValue::FrameRegistration) << testing::PrintToString(sdk::OsdValue::FrameRegistration);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_Values7Enum) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(7, sdk::OsdValue::Version);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(7), sdk::OsdValue::Version) << testing::PrintToString(sdk::OsdValue::Version);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(7, sdk::OsdValue::StreamId);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(7), sdk::OsdValue::StreamId) << testing::PrintToString(sdk::OsdValue::StreamId);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(7, sdk::OsdValue::InputDescription);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(7), sdk::OsdValue::InputDescription) << testing::PrintToString(sdk::OsdValue::InputDescription);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(7, sdk::OsdValue::FrameId);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(7), sdk::OsdValue::FrameId) << testing::PrintToString(sdk::OsdValue::FrameId);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(7, sdk::OsdValue::Fps);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(7), sdk::OsdValue::Fps) << testing::PrintToString(sdk::OsdValue::Fps);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(7, sdk::OsdValue::Pts);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(7), sdk::OsdValue::Pts) << testing::PrintToString(sdk::OsdValue::Pts);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(7, sdk::OsdValue::Latency);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(7), sdk::OsdValue::Latency) << testing::PrintToString(sdk::OsdValue::Latency);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(7, sdk::OsdValue::TelemetryPlatform);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(7), sdk::OsdValue::TelemetryPlatform) << testing::PrintToString(sdk::OsdValue::TelemetryPlatform);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(7, sdk::OsdValue::TelemetryPayload);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(7), sdk::OsdValue::TelemetryPayload) << testing::PrintToString(sdk::OsdValue::TelemetryPayload);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(7, sdk::OsdValue::FrameRegistration);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(7), sdk::OsdValue::FrameRegistration) << testing::PrintToString(sdk::OsdValue::FrameRegistration);
    }

    // Test for Values8 in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Osd_Values8Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(8), sdk::OsdValue::TelemetryPayload);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_Values8Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(8), sdk::OsdValue::TelemetryPayload);
    }

    // Test for Values8 in CvRenderer (enum)
    TEST_F(CvRendererTest, CvRenderer_Osd_Values8Enum) {
        startConfiguration.getCvRenderer().getOsd().setValues(8, sdk::OsdValue::Version);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(8), sdk::OsdValue::Version) << testing::PrintToString(sdk::OsdValue::Version);
        startConfiguration.getCvRenderer().getOsd().setValues(8, sdk::OsdValue::StreamId);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(8), sdk::OsdValue::StreamId) << testing::PrintToString(sdk::OsdValue::StreamId);
        startConfiguration.getCvRenderer().getOsd().setValues(8, sdk::OsdValue::InputDescription);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(8), sdk::OsdValue::InputDescription) << testing::PrintToString(sdk::OsdValue::InputDescription);
        startConfiguration.getCvRenderer().getOsd().setValues(8, sdk::OsdValue::FrameId);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(8), sdk::OsdValue::FrameId) << testing::PrintToString(sdk::OsdValue::FrameId);
        startConfiguration.getCvRenderer().getOsd().setValues(8, sdk::OsdValue::Fps);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(8), sdk::OsdValue::Fps) << testing::PrintToString(sdk::OsdValue::Fps);
        startConfiguration.getCvRenderer().getOsd().setValues(8, sdk::OsdValue::Pts);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(8), sdk::OsdValue::Pts) << testing::PrintToString(sdk::OsdValue::Pts);
        startConfiguration.getCvRenderer().getOsd().setValues(8, sdk::OsdValue::Latency);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(8), sdk::OsdValue::Latency) << testing::PrintToString(sdk::OsdValue::Latency);
        startConfiguration.getCvRenderer().getOsd().setValues(8, sdk::OsdValue::TelemetryPlatform);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(8), sdk::OsdValue::TelemetryPlatform) << testing::PrintToString(sdk::OsdValue::TelemetryPlatform);
        startConfiguration.getCvRenderer().getOsd().setValues(8, sdk::OsdValue::TelemetryPayload);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(8), sdk::OsdValue::TelemetryPayload) << testing::PrintToString(sdk::OsdValue::TelemetryPayload);
        startConfiguration.getCvRenderer().getOsd().setValues(8, sdk::OsdValue::FrameRegistration);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(8), sdk::OsdValue::FrameRegistration) << testing::PrintToString(sdk::OsdValue::FrameRegistration);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_Values8Enum) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(8, sdk::OsdValue::Version);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(8), sdk::OsdValue::Version) << testing::PrintToString(sdk::OsdValue::Version);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(8, sdk::OsdValue::StreamId);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(8), sdk::OsdValue::StreamId) << testing::PrintToString(sdk::OsdValue::StreamId);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(8, sdk::OsdValue::InputDescription);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(8), sdk::OsdValue::InputDescription) << testing::PrintToString(sdk::OsdValue::InputDescription);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(8, sdk::OsdValue::FrameId);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(8), sdk::OsdValue::FrameId) << testing::PrintToString(sdk::OsdValue::FrameId);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(8, sdk::OsdValue::Fps);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(8), sdk::OsdValue::Fps) << testing::PrintToString(sdk::OsdValue::Fps);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(8, sdk::OsdValue::Pts);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(8), sdk::OsdValue::Pts) << testing::PrintToString(sdk::OsdValue::Pts);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(8, sdk::OsdValue::Latency);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(8), sdk::OsdValue::Latency) << testing::PrintToString(sdk::OsdValue::Latency);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(8, sdk::OsdValue::TelemetryPlatform);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(8), sdk::OsdValue::TelemetryPlatform) << testing::PrintToString(sdk::OsdValue::TelemetryPlatform);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(8, sdk::OsdValue::TelemetryPayload);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(8), sdk::OsdValue::TelemetryPayload) << testing::PrintToString(sdk::OsdValue::TelemetryPayload);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(8, sdk::OsdValue::FrameRegistration);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(8), sdk::OsdValue::FrameRegistration) << testing::PrintToString(sdk::OsdValue::FrameRegistration);
    }

    // Test for Values9 in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Osd_Values9Default) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(9), sdk::OsdValue::FrameRegistration);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_Values9Default) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(9), sdk::OsdValue::FrameRegistration);
    }

    // Test for Values9 in CvRenderer (enum)
    TEST_F(CvRendererTest, CvRenderer_Osd_Values9Enum) {
        startConfiguration.getCvRenderer().getOsd().setValues(9, sdk::OsdValue::Version);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(9), sdk::OsdValue::Version) << testing::PrintToString(sdk::OsdValue::Version);
        startConfiguration.getCvRenderer().getOsd().setValues(9, sdk::OsdValue::StreamId);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(9), sdk::OsdValue::StreamId) << testing::PrintToString(sdk::OsdValue::StreamId);
        startConfiguration.getCvRenderer().getOsd().setValues(9, sdk::OsdValue::InputDescription);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(9), sdk::OsdValue::InputDescription) << testing::PrintToString(sdk::OsdValue::InputDescription);
        startConfiguration.getCvRenderer().getOsd().setValues(9, sdk::OsdValue::FrameId);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(9), sdk::OsdValue::FrameId) << testing::PrintToString(sdk::OsdValue::FrameId);
        startConfiguration.getCvRenderer().getOsd().setValues(9, sdk::OsdValue::Fps);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(9), sdk::OsdValue::Fps) << testing::PrintToString(sdk::OsdValue::Fps);
        startConfiguration.getCvRenderer().getOsd().setValues(9, sdk::OsdValue::Pts);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(9), sdk::OsdValue::Pts) << testing::PrintToString(sdk::OsdValue::Pts);
        startConfiguration.getCvRenderer().getOsd().setValues(9, sdk::OsdValue::Latency);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(9), sdk::OsdValue::Latency) << testing::PrintToString(sdk::OsdValue::Latency);
        startConfiguration.getCvRenderer().getOsd().setValues(9, sdk::OsdValue::TelemetryPlatform);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(9), sdk::OsdValue::TelemetryPlatform) << testing::PrintToString(sdk::OsdValue::TelemetryPlatform);
        startConfiguration.getCvRenderer().getOsd().setValues(9, sdk::OsdValue::TelemetryPayload);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(9), sdk::OsdValue::TelemetryPayload) << testing::PrintToString(sdk::OsdValue::TelemetryPayload);
        startConfiguration.getCvRenderer().getOsd().setValues(9, sdk::OsdValue::FrameRegistration);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getValues(9), sdk::OsdValue::FrameRegistration) << testing::PrintToString(sdk::OsdValue::FrameRegistration);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_Values9Enum) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(9, sdk::OsdValue::Version);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(9), sdk::OsdValue::Version) << testing::PrintToString(sdk::OsdValue::Version);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(9, sdk::OsdValue::StreamId);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(9), sdk::OsdValue::StreamId) << testing::PrintToString(sdk::OsdValue::StreamId);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(9, sdk::OsdValue::InputDescription);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(9), sdk::OsdValue::InputDescription) << testing::PrintToString(sdk::OsdValue::InputDescription);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(9, sdk::OsdValue::FrameId);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(9), sdk::OsdValue::FrameId) << testing::PrintToString(sdk::OsdValue::FrameId);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(9, sdk::OsdValue::Fps);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(9), sdk::OsdValue::Fps) << testing::PrintToString(sdk::OsdValue::Fps);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(9, sdk::OsdValue::Pts);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(9), sdk::OsdValue::Pts) << testing::PrintToString(sdk::OsdValue::Pts);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(9, sdk::OsdValue::Latency);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(9), sdk::OsdValue::Latency) << testing::PrintToString(sdk::OsdValue::Latency);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(9, sdk::OsdValue::TelemetryPlatform);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(9), sdk::OsdValue::TelemetryPlatform) << testing::PrintToString(sdk::OsdValue::TelemetryPlatform);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(9, sdk::OsdValue::TelemetryPayload);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(9), sdk::OsdValue::TelemetryPayload) << testing::PrintToString(sdk::OsdValue::TelemetryPayload);
        pStream->getConfiguration().getCvRenderer().getOsd().setValues(9, sdk::OsdValue::FrameRegistration);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getValues(9), sdk::OsdValue::FrameRegistration) << testing::PrintToString(sdk::OsdValue::FrameRegistration);
    }

    // Test for MarginX in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Osd_MarginXDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getMarginX(), 10);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_MarginXDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getMarginX(), 10);
    }

    TEST_F(CvRendererTest, CvRenderer_Osd_MarginXRandom) {
        startConfiguration.getCvRenderer().getOsd().setMarginX(771);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getMarginX(), 771);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_MarginXRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getOsd().setMarginX(771);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getMarginX(), 771);
    }

    // Test for MarginY in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Osd_MarginYDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getMarginY(), 10);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_MarginYDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getMarginY(), 10);
    }

    TEST_F(CvRendererTest, CvRenderer_Osd_MarginYRandom) {
        startConfiguration.getCvRenderer().getOsd().setMarginY(228);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getMarginY(), 228);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_MarginYRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getOsd().setMarginY(228);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getMarginY(), 228);
    }

    // Test for LineDistance in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Osd_LineDistanceDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getLineDistance(), 10);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_LineDistanceDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getLineDistance(), 10);
    }

    TEST_F(CvRendererTest, CvRenderer_Osd_LineDistanceRandom) {
        startConfiguration.getCvRenderer().getOsd().setLineDistance(70);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getLineDistance(), 70);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_LineDistanceRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getOsd().setLineDistance(70);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getLineDistance(), 70);
    }

    // Test for BackColor in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Osd_BackColorDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getBackColor(), 0);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_BackColorDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getBackColor(), 0);
    }

    TEST_F(CvRendererTest, CvRenderer_Osd_BackColorRandom) {
        startConfiguration.getCvRenderer().getOsd().setBackColor(10245086);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getBackColor(), 10245086);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_BackColorRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getOsd().setBackColor(10245086);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getBackColor(), 10245086);
    }

    // Test for BackTransparency in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Osd_BackTransparencyDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getBackTransparency(), 0.7f);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_BackTransparencyDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getBackTransparency(), 0.7f);
    }

    TEST_F(CvRendererTest, CvRenderer_Osd_BackTransparencyRange) {
        startConfiguration.getCvRenderer().getOsd().setBackTransparency(0.0f);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getBackTransparency(), 0.0f);
        startConfiguration.getCvRenderer().getOsd().setBackTransparency(1.0f);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getBackTransparency(), 1.0f);
        EXPECT_THROW(startConfiguration.getCvRenderer().getOsd().setBackTransparency(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getOsd().setBackTransparency(1.0f + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_BackTransparencyRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getOsd().setBackTransparency(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getBackTransparency(), 0.0f);
        pStream->getConfiguration().getCvRenderer().getOsd().setBackTransparency(1.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getBackTransparency(), 1.0f);
    }

    // Test for FontColor in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Osd_FontColorDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getFontColor(), 16711935);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_FontColorDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getFontColor(), 16711935);
    }

    TEST_F(CvRendererTest, CvRenderer_Osd_FontColorRandom) {
        startConfiguration.getCvRenderer().getOsd().setFontColor(4618275);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getFontColor(), 4618275);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_FontColorRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getOsd().setFontColor(4618275);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getFontColor(), 4618275);
    }

    // Test for FontScale in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Osd_FontScaleDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getFontScale(), 0.5f);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_FontScaleDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getFontScale(), 0.5f);
    }

    TEST_F(CvRendererTest, CvRenderer_Osd_FontScaleRange) {
        startConfiguration.getCvRenderer().getOsd().setFontScale(0.1f);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getFontScale(), 0.1f);
        startConfiguration.getCvRenderer().getOsd().setFontScale(100.0f);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getFontScale(), 100.0f);
        EXPECT_THROW(startConfiguration.getCvRenderer().getOsd().setFontScale(0.1f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getOsd().setFontScale(100.0f + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_FontScaleRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getOsd().setFontScale(0.1f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getFontScale(), 0.1f);
        pStream->getConfiguration().getCvRenderer().getOsd().setFontScale(100.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getFontScale(), 100.0f);
    }

    // Test for FontThickness in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Osd_FontThicknessDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getFontThickness(), 1);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_FontThicknessDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getFontThickness(), 1);
    }

    TEST_F(CvRendererTest, CvRenderer_Osd_FontThicknessRange) {
        startConfiguration.getCvRenderer().getOsd().setFontThickness(1);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getFontThickness(), 1);
        startConfiguration.getCvRenderer().getOsd().setFontThickness(100);
        EXPECT_EQ(startConfiguration.getCvRenderer().getOsd().getFontThickness(), 100);
        EXPECT_THROW(startConfiguration.getCvRenderer().getOsd().setFontThickness(1 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getOsd().setFontThickness(100 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Osd_FontThicknessRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getOsd().setFontThickness(1);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getFontThickness(), 1);
        pStream->getConfiguration().getCvRenderer().getOsd().setFontThickness(100);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getOsd().getFontThickness(), 100);
    }

    // Test for SkipRendering in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Histogram_SkipRenderingDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getHistogram().getSkipRendering(), true);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Histogram_SkipRenderingDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getHistogram().getSkipRendering(), true);
    }

    TEST_F(CvRendererTest, CvRenderer_Histogram_SkipRenderingRandom) {
        startConfiguration.getCvRenderer().getHistogram().setSkipRendering(true);
        EXPECT_EQ(startConfiguration.getCvRenderer().getHistogram().getSkipRendering(), true);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Histogram_SkipRenderingRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getHistogram().setSkipRendering(true);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getHistogram().getSkipRendering(), true);
    }

    // Test for Corner in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Histogram_CornerDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getHistogram().getCorner(), sdk::Corner::BottomLeft);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Histogram_CornerDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getHistogram().getCorner(), sdk::Corner::BottomLeft);
    }

    // Test for Corner in CvRenderer (enum)
    TEST_F(CvRendererTest, CvRenderer_Histogram_CornerEnum) {
        startConfiguration.getCvRenderer().getHistogram().setCorner(sdk::Corner::TopLeft);
        EXPECT_EQ(startConfiguration.getCvRenderer().getHistogram().getCorner(), sdk::Corner::TopLeft) << testing::PrintToString(sdk::Corner::TopLeft);
        startConfiguration.getCvRenderer().getHistogram().setCorner(sdk::Corner::TopRight);
        EXPECT_EQ(startConfiguration.getCvRenderer().getHistogram().getCorner(), sdk::Corner::TopRight) << testing::PrintToString(sdk::Corner::TopRight);
        startConfiguration.getCvRenderer().getHistogram().setCorner(sdk::Corner::BottomLeft);
        EXPECT_EQ(startConfiguration.getCvRenderer().getHistogram().getCorner(), sdk::Corner::BottomLeft) << testing::PrintToString(sdk::Corner::BottomLeft);
        startConfiguration.getCvRenderer().getHistogram().setCorner(sdk::Corner::BottomRight);
        EXPECT_EQ(startConfiguration.getCvRenderer().getHistogram().getCorner(), sdk::Corner::BottomRight) << testing::PrintToString(sdk::Corner::BottomRight);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Histogram_CornerEnum) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getHistogram().setCorner(sdk::Corner::TopLeft);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getHistogram().getCorner(), sdk::Corner::TopLeft) << testing::PrintToString(sdk::Corner::TopLeft);
        pStream->getConfiguration().getCvRenderer().getHistogram().setCorner(sdk::Corner::TopRight);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getHistogram().getCorner(), sdk::Corner::TopRight) << testing::PrintToString(sdk::Corner::TopRight);
        pStream->getConfiguration().getCvRenderer().getHistogram().setCorner(sdk::Corner::BottomLeft);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getHistogram().getCorner(), sdk::Corner::BottomLeft) << testing::PrintToString(sdk::Corner::BottomLeft);
        pStream->getConfiguration().getCvRenderer().getHistogram().setCorner(sdk::Corner::BottomRight);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getHistogram().getCorner(), sdk::Corner::BottomRight) << testing::PrintToString(sdk::Corner::BottomRight);
    }

    // Test for MarginX in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Histogram_MarginXDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getHistogram().getMarginX(), 10);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Histogram_MarginXDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getHistogram().getMarginX(), 10);
    }

    TEST_F(CvRendererTest, CvRenderer_Histogram_MarginXRandom) {
        startConfiguration.getCvRenderer().getHistogram().setMarginX(731);
        EXPECT_EQ(startConfiguration.getCvRenderer().getHistogram().getMarginX(), 731);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Histogram_MarginXRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getHistogram().setMarginX(731);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getHistogram().getMarginX(), 731);
    }

    // Test for MarginY in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Histogram_MarginYDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getHistogram().getMarginY(), 10);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Histogram_MarginYDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getHistogram().getMarginY(), 10);
    }

    TEST_F(CvRendererTest, CvRenderer_Histogram_MarginYRandom) {
        startConfiguration.getCvRenderer().getHistogram().setMarginY(753);
        EXPECT_EQ(startConfiguration.getCvRenderer().getHistogram().getMarginY(), 753);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Histogram_MarginYRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getHistogram().setMarginY(753);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getHistogram().getMarginY(), 753);
    }

    // Test for Bins in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Histogram_BinsDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getHistogram().getBins(), 100);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Histogram_BinsDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getHistogram().getBins(), 100);
    }

    TEST_F(CvRendererTest, CvRenderer_Histogram_BinsRange) {
        startConfiguration.getCvRenderer().getHistogram().setBins(5);
        EXPECT_EQ(startConfiguration.getCvRenderer().getHistogram().getBins(), 5);
        startConfiguration.getCvRenderer().getHistogram().setBins(1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getHistogram().getBins(), 1000);
        EXPECT_THROW(startConfiguration.getCvRenderer().getHistogram().setBins(5 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getHistogram().setBins(1000 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Histogram_BinsRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getHistogram().setBins(5);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getHistogram().getBins(), 5);
        pStream->getConfiguration().getCvRenderer().getHistogram().setBins(1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getHistogram().getBins(), 1000);
    }

    // Test for Width in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Histogram_WidthDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getHistogram().getWidth(), 300);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Histogram_WidthDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getHistogram().getWidth(), 300);
    }

    TEST_F(CvRendererTest, CvRenderer_Histogram_WidthRange) {
        startConfiguration.getCvRenderer().getHistogram().setWidth(50);
        EXPECT_EQ(startConfiguration.getCvRenderer().getHistogram().getWidth(), 50);
        startConfiguration.getCvRenderer().getHistogram().setWidth(1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getHistogram().getWidth(), 1000);
        EXPECT_THROW(startConfiguration.getCvRenderer().getHistogram().setWidth(50 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getHistogram().setWidth(1000 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Histogram_WidthRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getHistogram().setWidth(50);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getHistogram().getWidth(), 50);
        pStream->getConfiguration().getCvRenderer().getHistogram().setWidth(1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getHistogram().getWidth(), 1000);
    }

    // Test for Height in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Histogram_HeightDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getHistogram().getHeight(), 200);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Histogram_HeightDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getHistogram().getHeight(), 200);
    }

    TEST_F(CvRendererTest, CvRenderer_Histogram_HeightRange) {
        startConfiguration.getCvRenderer().getHistogram().setHeight(50);
        EXPECT_EQ(startConfiguration.getCvRenderer().getHistogram().getHeight(), 50);
        startConfiguration.getCvRenderer().getHistogram().setHeight(1000);
        EXPECT_EQ(startConfiguration.getCvRenderer().getHistogram().getHeight(), 1000);
        EXPECT_THROW(startConfiguration.getCvRenderer().getHistogram().setHeight(50 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getHistogram().setHeight(1000 + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Histogram_HeightRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getHistogram().setHeight(50);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getHistogram().getHeight(), 50);
        pStream->getConfiguration().getCvRenderer().getHistogram().setHeight(1000);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getHistogram().getHeight(), 1000);
    }

    // Test for BackColor in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Histogram_BackColorDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getHistogram().getBackColor(), 0);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Histogram_BackColorDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getHistogram().getBackColor(), 0);
    }

    TEST_F(CvRendererTest, CvRenderer_Histogram_BackColorRandom) {
        startConfiguration.getCvRenderer().getHistogram().setBackColor(11082369);
        EXPECT_EQ(startConfiguration.getCvRenderer().getHistogram().getBackColor(), 11082369);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Histogram_BackColorRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getHistogram().setBackColor(11082369);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getHistogram().getBackColor(), 11082369);
    }

    // Test for BackTransparency in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Histogram_BackTransparencyDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getHistogram().getBackTransparency(), 0.7f);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Histogram_BackTransparencyDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getHistogram().getBackTransparency(), 0.7f);
    }

    TEST_F(CvRendererTest, CvRenderer_Histogram_BackTransparencyRange) {
        startConfiguration.getCvRenderer().getHistogram().setBackTransparency(0.0f);
        EXPECT_EQ(startConfiguration.getCvRenderer().getHistogram().getBackTransparency(), 0.0f);
        startConfiguration.getCvRenderer().getHistogram().setBackTransparency(1.0f);
        EXPECT_EQ(startConfiguration.getCvRenderer().getHistogram().getBackTransparency(), 1.0f);
        EXPECT_THROW(startConfiguration.getCvRenderer().getHistogram().setBackTransparency(0.0f - 1), std::exception);
        EXPECT_THROW(startConfiguration.getCvRenderer().getHistogram().setBackTransparency(1.0f + 1), std::exception);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Histogram_BackTransparencyRange) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getHistogram().setBackTransparency(0.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getHistogram().getBackTransparency(), 0.0f);
        pStream->getConfiguration().getCvRenderer().getHistogram().setBackTransparency(1.0f);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getHistogram().getBackTransparency(), 1.0f);
    }

    // Test for ColorBefore in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Histogram_ColorBeforeDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getHistogram().getColorBefore(), 16776960);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Histogram_ColorBeforeDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getHistogram().getColorBefore(), 16776960);
    }

    TEST_F(CvRendererTest, CvRenderer_Histogram_ColorBeforeRandom) {
        startConfiguration.getCvRenderer().getHistogram().setColorBefore(9665219);
        EXPECT_EQ(startConfiguration.getCvRenderer().getHistogram().getColorBefore(), 9665219);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Histogram_ColorBeforeRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getHistogram().setColorBefore(9665219);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getHistogram().getColorBefore(), 9665219);
    }

    // Test for ColorAfter in CvRenderer
    TEST_F(CvRendererTest, CvRenderer_Histogram_ColorAfterDefault) {
        EXPECT_EQ(startConfiguration.getCvRenderer().getHistogram().getColorAfter(), 65280);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Histogram_ColorAfterDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getHistogram().getColorAfter(), 65280);
    }

    TEST_F(CvRendererTest, CvRenderer_Histogram_ColorAfterRandom) {
        startConfiguration.getCvRenderer().getHistogram().setColorAfter(6025776);
        EXPECT_EQ(startConfiguration.getCvRenderer().getHistogram().getColorAfter(), 6025776);
    }

    TEST_F(CvRendererTest, Update_CvRenderer_Histogram_ColorAfterRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getCvRenderer().getHistogram().setColorAfter(6025776);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getCvRenderer().getHistogram().getColorAfter(), 6025776);
    }

// Test suit for PreviewModule
class PreviewModuleTest : public ::testing::Test {
protected:
    void SetUp() override {
        startConfiguration = pPipeline->createStartStreamConfiguration();
        if (::testing::GTEST_FLAG(update_tests)) {
            tmpStartConfiguration = startConfiguration;
            tmpStartConfiguration.getRawSource(); // Touch Raw Source
            tmpStartConfiguration.getRawSource().setReadTimeoutInSec(0); // Wait forever
            pStream = pPipeline->startStream(tmpStartConfiguration);
            waitForStreamStarted(pStream, data);
        }

    }

    void TearDown() override {
        if (::testing::GTEST_FLAG(update_tests)) {
            pStream.reset();
            waitForStreamStopped(data);
        }

    }

};

    // Test for Enable in PreviewModule
    TEST_F(PreviewModuleTest, PreviewModule_EnableDefault) {
        EXPECT_EQ(startConfiguration.getPreviewModule().getEnable(), false);
    }

    TEST_F(PreviewModuleTest, Update_PreviewModule_EnableDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getPreviewModule().getEnable(), false);
    }

    TEST_F(PreviewModuleTest, PreviewModule_EnableRandom) {
        startConfiguration.getPreviewModule().setEnable(false);
        EXPECT_EQ(startConfiguration.getPreviewModule().getEnable(), false);
    }

    TEST_F(PreviewModuleTest, Update_PreviewModule_EnableRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getPreviewModule().setEnable(false);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getPreviewModule().getEnable(), false);
    }

// Test suit for GstSink
class GstSinkTest : public ::testing::Test {
protected:
    void SetUp() override {
        startConfiguration = pPipeline->createStartStreamConfiguration();
    }

};

    // Test for StopOnError in GstSink
    TEST_F(GstSinkTest, GstSink_StopOnErrorDefault) {
        EXPECT_EQ(startConfiguration.getGstSink().getStopOnError(), true);
    }

    TEST_F(GstSinkTest, GstSink_StopOnErrorRandom) {
        startConfiguration.getGstSink().setStopOnError(true);
        EXPECT_EQ(startConfiguration.getGstSink().getStopOnError(), true);
    }

    // Test for Sink in GstSink
    TEST_F(GstSinkTest, GstSink_SinkDefault) {
        EXPECT_EQ(startConfiguration.getGstSink().getSink(), "rtspclientsink location={}");
    }

    TEST_F(GstSinkTest, GstSink_SinkRandom) {
        startConfiguration.getGstSink().setSink("p98tBWo5Gh");
        EXPECT_EQ(startConfiguration.getGstSink().getSink(), "p98tBWo5Gh");
    }

    // Test for Url in GstSink
    TEST_F(GstSinkTest, GstSink_UrlDefault) {
        EXPECT_EQ(startConfiguration.getGstSink().getUrl(), "");
    }

    TEST_F(GstSinkTest, GstSink_UrlRandom) {
        startConfiguration.getGstSink().setUrl("kTvq5A1P7L");
        EXPECT_EQ(startConfiguration.getGstSink().getUrl(), "kTvq5A1P7L");
    }

    // Test for FrameRate in GstSink
    TEST_F(GstSinkTest, GstSink_FrameRateDefault) {
        EXPECT_EQ(startConfiguration.getGstSink().getFrameRate(), 0);
    }

    TEST_F(GstSinkTest, GstSink_FrameRateRandom) {
        startConfiguration.getGstSink().setFrameRate(55);
        EXPECT_EQ(startConfiguration.getGstSink().getFrameRate(), 55);
    }

    // Test for KlvFormat in GstSink
    TEST_F(GstSinkTest, GstSink_KlvFormatDefault) {
        EXPECT_EQ(startConfiguration.getGstSink().getKlvFormat(), sdk::KlvFormat::Disabled);
    }

    // Test for KlvFormat in GstSink (enum)
    TEST_F(GstSinkTest, GstSink_KlvFormatEnum) {
        startConfiguration.getGstSink().setKlvFormat(sdk::KlvFormat::Disabled);
        EXPECT_EQ(startConfiguration.getGstSink().getKlvFormat(), sdk::KlvFormat::Disabled) << testing::PrintToString(sdk::KlvFormat::Disabled);
        startConfiguration.getGstSink().setKlvFormat(sdk::KlvFormat::UasVmtiLs);
        EXPECT_EQ(startConfiguration.getGstSink().getKlvFormat(), sdk::KlvFormat::UasVmtiLs) << testing::PrintToString(sdk::KlvFormat::UasVmtiLs);
    }

    // Test for WebSocketPort in GstSink
    TEST_F(GstSinkTest, GstSink_WebSocketPortDefault) {
        EXPECT_EQ(startConfiguration.getGstSink().getWebSocketPort(), 8181);
    }

    TEST_F(GstSinkTest, GstSink_WebSocketPortRange) {
        startConfiguration.getGstSink().setWebSocketPort(1024);
        EXPECT_EQ(startConfiguration.getGstSink().getWebSocketPort(), 1024);
        startConfiguration.getGstSink().setWebSocketPort(65535);
        EXPECT_EQ(startConfiguration.getGstSink().getWebSocketPort(), 65535);
        EXPECT_THROW(startConfiguration.getGstSink().setWebSocketPort(1024 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getGstSink().setWebSocketPort(65535 + 1), std::exception);
    }

// Test suit for Recorder
class RecorderTest : public ::testing::Test {
protected:
    void SetUp() override {
        startConfiguration = pPipeline->createStartStreamConfiguration();
        if (::testing::GTEST_FLAG(update_tests)) {
            tmpStartConfiguration = startConfiguration;
            tmpStartConfiguration.getRawSource(); // Touch Raw Source
            tmpStartConfiguration.getRawSource().setReadTimeoutInSec(0); // Wait forever
            pStream = pPipeline->startStream(tmpStartConfiguration);
            waitForStreamStarted(pStream, data);
        }

    }

    void TearDown() override {
        if (::testing::GTEST_FLAG(update_tests)) {
            pStream.reset();
            waitForStreamStopped(data);
        }

    }

};

    // Test for Enable in Recorder
    TEST_F(RecorderTest, Recorder_EnableDefault) {
        EXPECT_EQ(startConfiguration.getRecorder().getEnable(), false);
    }

    TEST_F(RecorderTest, Update_Recorder_EnableDefault) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        EXPECT_EQ(pStream->getConfiguration().getRecorder().getEnable(), false);
    }

    TEST_F(RecorderTest, Recorder_EnableRandom) {
        startConfiguration.getRecorder().setEnable(true);
        EXPECT_EQ(startConfiguration.getRecorder().getEnable(), true);
    }

    TEST_F(RecorderTest, Update_Recorder_EnableRandom) {
        if (!::testing::GTEST_FLAG(update_tests)) {
            GTEST_SKIP();
        }
        pStream->getConfiguration().getRecorder().setEnable(true);
        pStream->update();
        EXPECT_EQ(pStream->getConfiguration().getRecorder().getEnable(), true);
    }

    // Test for FrameIdType in Recorder
    TEST_F(RecorderTest, Recorder_FrameIdTypeDefault) {
        EXPECT_EQ(startConfiguration.getRecorder().getFrameIdType(), sdk::FrameIdType::Increasing);
    }

    // Test for FrameIdType in Recorder (enum)
    TEST_F(RecorderTest, Recorder_FrameIdTypeEnum) {
        startConfiguration.getRecorder().setFrameIdType(sdk::FrameIdType::Original);
        EXPECT_EQ(startConfiguration.getRecorder().getFrameIdType(), sdk::FrameIdType::Original) << testing::PrintToString(sdk::FrameIdType::Original);
        startConfiguration.getRecorder().setFrameIdType(sdk::FrameIdType::Timestamp);
        EXPECT_EQ(startConfiguration.getRecorder().getFrameIdType(), sdk::FrameIdType::Timestamp) << testing::PrintToString(sdk::FrameIdType::Timestamp);
    }

    // Test for DataType0 in Recorder
    TEST_F(RecorderTest, Recorder_Store_0__DataType0Default) {
        EXPECT_EQ(startConfiguration.getRecorder().getStore(0).getDataType(), sdk::DataType::RawFrame);
    }

    // Test for DataType0 in Recorder (enum)
    TEST_F(RecorderTest, Recorder_Store_0__DataType0Enum) {
        startConfiguration.getRecorder().getStore(0).setDataType(sdk::DataType::RawFrame);
        EXPECT_EQ(startConfiguration.getRecorder().getStore(0).getDataType(), sdk::DataType::RawFrame) << testing::PrintToString(sdk::DataType::RawFrame);
        startConfiguration.getRecorder().getStore(0).setDataType(sdk::DataType::PreprocessedFrame);
        EXPECT_EQ(startConfiguration.getRecorder().getStore(0).getDataType(), sdk::DataType::PreprocessedFrame) << testing::PrintToString(sdk::DataType::PreprocessedFrame);
        startConfiguration.getRecorder().getStore(0).setDataType(sdk::DataType::Homography);
        EXPECT_EQ(startConfiguration.getRecorder().getStore(0).getDataType(), sdk::DataType::Homography) << testing::PrintToString(sdk::DataType::Homography);
        startConfiguration.getRecorder().getStore(0).setDataType(sdk::DataType::Detections);
        EXPECT_EQ(startConfiguration.getRecorder().getStore(0).getDataType(), sdk::DataType::Detections) << testing::PrintToString(sdk::DataType::Detections);
        startConfiguration.getRecorder().getStore(0).setDataType(sdk::DataType::Crops);
        EXPECT_EQ(startConfiguration.getRecorder().getStore(0).getDataType(), sdk::DataType::Crops) << testing::PrintToString(sdk::DataType::Crops);
        startConfiguration.getRecorder().getStore(0).setDataType(sdk::DataType::Tracks);
        EXPECT_EQ(startConfiguration.getRecorder().getStore(0).getDataType(), sdk::DataType::Tracks) << testing::PrintToString(sdk::DataType::Tracks);
        startConfiguration.getRecorder().getStore(0).setDataType(sdk::DataType::Features);
        EXPECT_EQ(startConfiguration.getRecorder().getStore(0).getDataType(), sdk::DataType::Features) << testing::PrintToString(sdk::DataType::Features);
        startConfiguration.getRecorder().getStore(0).setDataType(sdk::DataType::Landmarks);
        EXPECT_EQ(startConfiguration.getRecorder().getStore(0).getDataType(), sdk::DataType::Landmarks) << testing::PrintToString(sdk::DataType::Landmarks);
        startConfiguration.getRecorder().getStore(0).setDataType(sdk::DataType::MetadataFrame);
        EXPECT_EQ(startConfiguration.getRecorder().getStore(0).getDataType(), sdk::DataType::MetadataFrame) << testing::PrintToString(sdk::DataType::MetadataFrame);
        startConfiguration.getRecorder().getStore(0).setDataType(sdk::DataType::GraphData);
        EXPECT_EQ(startConfiguration.getRecorder().getStore(0).getDataType(), sdk::DataType::GraphData) << testing::PrintToString(sdk::DataType::GraphData);
        startConfiguration.getRecorder().getStore(0).setDataType(sdk::DataType::DetectorRoi);
        EXPECT_EQ(startConfiguration.getRecorder().getStore(0).getDataType(), sdk::DataType::DetectorRoi) << testing::PrintToString(sdk::DataType::DetectorRoi);
        startConfiguration.getRecorder().getStore(0).setDataType(sdk::DataType::PreprocessorInfo);
        EXPECT_EQ(startConfiguration.getRecorder().getStore(0).getDataType(), sdk::DataType::PreprocessorInfo) << testing::PrintToString(sdk::DataType::PreprocessorInfo);
        startConfiguration.getRecorder().getStore(0).setDataType(sdk::DataType::DetectorInfo);
        EXPECT_EQ(startConfiguration.getRecorder().getStore(0).getDataType(), sdk::DataType::DetectorInfo) << testing::PrintToString(sdk::DataType::DetectorInfo);
        startConfiguration.getRecorder().getStore(0).setDataType(sdk::DataType::PerFrameMetadata);
        EXPECT_EQ(startConfiguration.getRecorder().getStore(0).getDataType(), sdk::DataType::PerFrameMetadata) << testing::PrintToString(sdk::DataType::PerFrameMetadata);
        startConfiguration.getRecorder().getStore(0).setDataType(sdk::DataType::CustomMetadata);
        EXPECT_EQ(startConfiguration.getRecorder().getStore(0).getDataType(), sdk::DataType::CustomMetadata) << testing::PrintToString(sdk::DataType::CustomMetadata);
        startConfiguration.getRecorder().getStore(0).setDataType(sdk::DataType::DebugMetadata);
        EXPECT_EQ(startConfiguration.getRecorder().getStore(0).getDataType(), sdk::DataType::DebugMetadata) << testing::PrintToString(sdk::DataType::DebugMetadata);
    }

    // Test for Tag0 in Recorder
    TEST_F(RecorderTest, Recorder_Store_0__Tag0Default) {
        EXPECT_EQ(startConfiguration.getRecorder().getStore(0).getTag(), "");
    }

    TEST_F(RecorderTest, Recorder_Store_0__Tag0Random) {
        startConfiguration.getRecorder().getStore(0).setTag("4J9eKy8T1o");
        EXPECT_EQ(startConfiguration.getRecorder().getStore(0).getTag(), "4J9eKy8T1o");
    }

    // Test for Path0 in Recorder
    TEST_F(RecorderTest, Recorder_Store_0__Path0Default) {
        EXPECT_EQ(startConfiguration.getRecorder().getStore(0).getPath(), "raw_frames/");
    }

    TEST_F(RecorderTest, Recorder_Store_0__Path0Random) {
        startConfiguration.getRecorder().getStore(0).setPath("lcqgJ7C4fz");
        EXPECT_EQ(startConfiguration.getRecorder().getStore(0).getPath(), "lcqgJ7C4fz");
    }

    // Test for DataType1 in Recorder
    TEST_F(RecorderTest, Recorder_Store_1__DataType1Default) {
        EXPECT_EQ(startConfiguration.getRecorder().getStore(1).getDataType(), sdk::DataType::PerFrameMetadata);
    }

    // Test for DataType1 in Recorder (enum)
    TEST_F(RecorderTest, Recorder_Store_1__DataType1Enum) {
        startConfiguration.getRecorder().getStore(1).setDataType(sdk::DataType::RawFrame);
        EXPECT_EQ(startConfiguration.getRecorder().getStore(1).getDataType(), sdk::DataType::RawFrame) << testing::PrintToString(sdk::DataType::RawFrame);
        startConfiguration.getRecorder().getStore(1).setDataType(sdk::DataType::PreprocessedFrame);
        EXPECT_EQ(startConfiguration.getRecorder().getStore(1).getDataType(), sdk::DataType::PreprocessedFrame) << testing::PrintToString(sdk::DataType::PreprocessedFrame);
        startConfiguration.getRecorder().getStore(1).setDataType(sdk::DataType::Homography);
        EXPECT_EQ(startConfiguration.getRecorder().getStore(1).getDataType(), sdk::DataType::Homography) << testing::PrintToString(sdk::DataType::Homography);
        startConfiguration.getRecorder().getStore(1).setDataType(sdk::DataType::Detections);
        EXPECT_EQ(startConfiguration.getRecorder().getStore(1).getDataType(), sdk::DataType::Detections) << testing::PrintToString(sdk::DataType::Detections);
        startConfiguration.getRecorder().getStore(1).setDataType(sdk::DataType::Crops);
        EXPECT_EQ(startConfiguration.getRecorder().getStore(1).getDataType(), sdk::DataType::Crops) << testing::PrintToString(sdk::DataType::Crops);
        startConfiguration.getRecorder().getStore(1).setDataType(sdk::DataType::Tracks);
        EXPECT_EQ(startConfiguration.getRecorder().getStore(1).getDataType(), sdk::DataType::Tracks) << testing::PrintToString(sdk::DataType::Tracks);
        startConfiguration.getRecorder().getStore(1).setDataType(sdk::DataType::Features);
        EXPECT_EQ(startConfiguration.getRecorder().getStore(1).getDataType(), sdk::DataType::Features) << testing::PrintToString(sdk::DataType::Features);
        startConfiguration.getRecorder().getStore(1).setDataType(sdk::DataType::Landmarks);
        EXPECT_EQ(startConfiguration.getRecorder().getStore(1).getDataType(), sdk::DataType::Landmarks) << testing::PrintToString(sdk::DataType::Landmarks);
        startConfiguration.getRecorder().getStore(1).setDataType(sdk::DataType::MetadataFrame);
        EXPECT_EQ(startConfiguration.getRecorder().getStore(1).getDataType(), sdk::DataType::MetadataFrame) << testing::PrintToString(sdk::DataType::MetadataFrame);
        startConfiguration.getRecorder().getStore(1).setDataType(sdk::DataType::GraphData);
        EXPECT_EQ(startConfiguration.getRecorder().getStore(1).getDataType(), sdk::DataType::GraphData) << testing::PrintToString(sdk::DataType::GraphData);
        startConfiguration.getRecorder().getStore(1).setDataType(sdk::DataType::DetectorRoi);
        EXPECT_EQ(startConfiguration.getRecorder().getStore(1).getDataType(), sdk::DataType::DetectorRoi) << testing::PrintToString(sdk::DataType::DetectorRoi);
        startConfiguration.getRecorder().getStore(1).setDataType(sdk::DataType::PreprocessorInfo);
        EXPECT_EQ(startConfiguration.getRecorder().getStore(1).getDataType(), sdk::DataType::PreprocessorInfo) << testing::PrintToString(sdk::DataType::PreprocessorInfo);
        startConfiguration.getRecorder().getStore(1).setDataType(sdk::DataType::DetectorInfo);
        EXPECT_EQ(startConfiguration.getRecorder().getStore(1).getDataType(), sdk::DataType::DetectorInfo) << testing::PrintToString(sdk::DataType::DetectorInfo);
        startConfiguration.getRecorder().getStore(1).setDataType(sdk::DataType::PerFrameMetadata);
        EXPECT_EQ(startConfiguration.getRecorder().getStore(1).getDataType(), sdk::DataType::PerFrameMetadata) << testing::PrintToString(sdk::DataType::PerFrameMetadata);
        startConfiguration.getRecorder().getStore(1).setDataType(sdk::DataType::CustomMetadata);
        EXPECT_EQ(startConfiguration.getRecorder().getStore(1).getDataType(), sdk::DataType::CustomMetadata) << testing::PrintToString(sdk::DataType::CustomMetadata);
        startConfiguration.getRecorder().getStore(1).setDataType(sdk::DataType::DebugMetadata);
        EXPECT_EQ(startConfiguration.getRecorder().getStore(1).getDataType(), sdk::DataType::DebugMetadata) << testing::PrintToString(sdk::DataType::DebugMetadata);
    }

    // Test for Tag1 in Recorder
    TEST_F(RecorderTest, Recorder_Store_1__Tag1Default) {
        EXPECT_EQ(startConfiguration.getRecorder().getStore(1).getTag(), "");
    }

    TEST_F(RecorderTest, Recorder_Store_1__Tag1Random) {
        startConfiguration.getRecorder().getStore(1).setTag("xvHRI7lijT");
        EXPECT_EQ(startConfiguration.getRecorder().getStore(1).getTag(), "xvHRI7lijT");
    }

    // Test for Path1 in Recorder
    TEST_F(RecorderTest, Recorder_Store_1__Path1Default) {
        EXPECT_EQ(startConfiguration.getRecorder().getStore(1).getPath(), "telemetry.csv");
    }

    TEST_F(RecorderTest, Recorder_Store_1__Path1Random) {
        startConfiguration.getRecorder().getStore(1).setPath("FMMGgsdqwF");
        EXPECT_EQ(startConfiguration.getRecorder().getStore(1).getPath(), "FMMGgsdqwF");
    }

    // Test for SkipFrames in Recorder
    TEST_F(RecorderTest, Recorder_SkipFramesDefault) {
        EXPECT_EQ(startConfiguration.getRecorder().getSkipFrames(), 1);
    }

    TEST_F(RecorderTest, Recorder_SkipFramesRange) {
        startConfiguration.getRecorder().setSkipFrames(1);
        EXPECT_EQ(startConfiguration.getRecorder().getSkipFrames(), 1);
        startConfiguration.getRecorder().setSkipFrames(1000);
        EXPECT_EQ(startConfiguration.getRecorder().getSkipFrames(), 1000);
        EXPECT_THROW(startConfiguration.getRecorder().setSkipFrames(1 - 1), std::exception);
        EXPECT_THROW(startConfiguration.getRecorder().setSkipFrames(1000 + 1), std::exception);
    }

    // Test for PathPrefix in Recorder
    TEST_F(RecorderTest, Recorder_PathPrefixDefault) {
        EXPECT_EQ(startConfiguration.getRecorder().getPathPrefix(), "sightx_recorder");
    }

    TEST_F(RecorderTest, Recorder_PathPrefixRandom) {
        startConfiguration.getRecorder().setPathPrefix("aatT85wWd8");
        EXPECT_EQ(startConfiguration.getRecorder().getPathPrefix(), "aatT85wWd8");
    }

    // Test for FrameFileType in Recorder
    TEST_F(RecorderTest, Recorder_FrameFileTypeDefault) {
        EXPECT_EQ(startConfiguration.getRecorder().getFrameFileType(), "png");
    }

    TEST_F(RecorderTest, Recorder_FrameFileTypeRandom) {
        startConfiguration.getRecorder().setFrameFileType("MaVqLpItQU");
        EXPECT_EQ(startConfiguration.getRecorder().getFrameFileType(), "MaVqLpItQU");
    }

    // Test for VideoFourCc in Recorder
    TEST_F(RecorderTest, Recorder_VideoFourCcDefault) {
        EXPECT_EQ(startConfiguration.getRecorder().getVideoFourCc(), "MPEG");
    }

    TEST_F(RecorderTest, Recorder_VideoFourCcRandom) {
        startConfiguration.getRecorder().setVideoFourCc("QcbDHebtvb");
        EXPECT_EQ(startConfiguration.getRecorder().getVideoFourCc(), "QcbDHebtvb");
    }

    // Test for Quality in Recorder
    TEST_F(RecorderTest, Recorder_QualityDefault) {
        EXPECT_EQ(startConfiguration.getRecorder().getQuality(), -1);
    }

    TEST_F(RecorderTest, Recorder_QualityRandom) {
        startConfiguration.getRecorder().setQuality(465);
        EXPECT_EQ(startConfiguration.getRecorder().getQuality(), 465);
    }

    // Test for VideoFps in Recorder
    TEST_F(RecorderTest, Recorder_VideoFpsDefault) {
        EXPECT_EQ(startConfiguration.getRecorder().getVideoFps(), 25);
    }

    TEST_F(RecorderTest, Recorder_VideoFpsRandom) {
        startConfiguration.getRecorder().setVideoFps(197);
        EXPECT_EQ(startConfiguration.getRecorder().getVideoFps(), 197);
    }

}

namespace general_tests {
// Instantiate general tests
INSTANTIATE_TEST_SUITE_P(GeneralTests, VideoStreams,
  ::testing::Values(sdk::FlowSwitcherFlowId::Rgb, sdk::FlowSwitcherFlowId::Mwir));
}
