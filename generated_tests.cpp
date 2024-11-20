#include "gtest/gtest.h"
#include "PipelineInterface.h"

// Test for Mode in RawSource
TEST(RawSourceTest, ModeDefault) {
    RawSource module;
    EXPECT_EQ(module.getMode(), 0);
}

TEST(RawSourceTest, ModeRange) {
    RawSource module;
    module.setMode(0);
    EXPECT_EQ(module.getMode(), 0);
    module.setMode(0);
    EXPECT_EQ(module.getMode(), 0);
    EXPECT_THROW(module.setMode(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setMode(0 + 1), std::out_of_range);
}

// Test for ReadTimeoutInSec in RawSource
TEST(RawSourceTest, ReadTimeoutInSecDefault) {
    RawSource module;
    EXPECT_EQ(module.getReadTimeoutInSec(), 0);
}

TEST(RawSourceTest, ReadTimeoutInSecRange) {
    RawSource module;
    module.setReadTimeoutInSec(0);
    EXPECT_EQ(module.getReadTimeoutInSec(), 0);
    module.setReadTimeoutInSec(0);
    EXPECT_EQ(module.getReadTimeoutInSec(), 0);
    EXPECT_THROW(module.setReadTimeoutInSec(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setReadTimeoutInSec(0 + 1), std::out_of_range);
}

// Test for SingleFrameTimeoutInSec in RawSource
TEST(RawSourceTest, SingleFrameTimeoutInSecDefault) {
    RawSource module;
    EXPECT_EQ(module.getSingleFrameTimeoutInSec(), 0);
}

TEST(RawSourceTest, SingleFrameTimeoutInSecRange) {
    RawSource module;
    module.setSingleFrameTimeoutInSec(0);
    EXPECT_EQ(module.getSingleFrameTimeoutInSec(), 0);
    module.setSingleFrameTimeoutInSec(0);
    EXPECT_EQ(module.getSingleFrameTimeoutInSec(), 0);
    EXPECT_THROW(module.setSingleFrameTimeoutInSec(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setSingleFrameTimeoutInSec(0 + 1), std::out_of_range);
}

// Test for Port in RawSource
TEST(RawSourceTest, PortDefault) {
    RawSource module;
    EXPECT_EQ(module.getPort(), 0);
}

TEST(RawSourceTest, PortRange) {
    RawSource module;
    module.setPort(0);
    EXPECT_EQ(module.getPort(), 0);
    module.setPort(0);
    EXPECT_EQ(module.getPort(), 0);
    EXPECT_THROW(module.setPort(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setPort(0 + 1), std::out_of_range);
}

// Test for Mode in GcSource
TEST(GcSourceTest, ModeDefault) {
    GcSource module;
    EXPECT_EQ(module.getMode(), 0);
}

TEST(GcSourceTest, ModeRange) {
    GcSource module;
    module.setMode(0);
    EXPECT_EQ(module.getMode(), 0);
    module.setMode(0);
    EXPECT_EQ(module.getMode(), 0);
    EXPECT_THROW(module.setMode(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setMode(0 + 1), std::out_of_range);
}

// Test for TimeoutInSec in GcSource
TEST(GcSourceTest, TimeoutInSecDefault) {
    GcSource module;
    EXPECT_EQ(module.getTimeoutInSec(), 0);
}

TEST(GcSourceTest, TimeoutInSecRange) {
    GcSource module;
    module.setTimeoutInSec(0);
    EXPECT_EQ(module.getTimeoutInSec(), 0);
    module.setTimeoutInSec(0);
    EXPECT_EQ(module.getTimeoutInSec(), 0);
    EXPECT_THROW(module.setTimeoutInSec(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setTimeoutInSec(0 + 1), std::out_of_range);
}

// Test for Url in GcSource
TEST(GcSourceTest, UrlDefault) {
    GcSource module;
    EXPECT_EQ(module.getUrl(), 0);
}

TEST(GcSourceTest, UrlRange) {
    GcSource module;
    module.setUrl(0);
    EXPECT_EQ(module.getUrl(), 0);
    module.setUrl(0);
    EXPECT_EQ(module.getUrl(), 0);
    EXPECT_THROW(module.setUrl(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setUrl(0 + 1), std::out_of_range);
}

// Test for DeviceAccessMode in GcSource
TEST(GcSourceTest, DeviceAccessModeDefault) {
    GcSource module;
    EXPECT_EQ(module.getDeviceAccessMode(), 0);
}

TEST(GcSourceTest, DeviceAccessModeRange) {
    GcSource module;
    module.setDeviceAccessMode(0);
    EXPECT_EQ(module.getDeviceAccessMode(), 0);
    module.setDeviceAccessMode(0);
    EXPECT_EQ(module.getDeviceAccessMode(), 0);
    EXPECT_THROW(module.setDeviceAccessMode(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setDeviceAccessMode(0 + 1), std::out_of_range);
}

// Test for GcParameters in GcSource
TEST(GcSourceTest, GcParametersDefault) {
    GcSource module;
    EXPECT_EQ(module.getGcParameters(), 0);
}

TEST(GcSourceTest, GcParametersRange) {
    GcSource module;
    module.setGcParameters(0);
    EXPECT_EQ(module.getGcParameters(), 0);
    module.setGcParameters(0);
    EXPECT_EQ(module.getGcParameters(), 0);
    EXPECT_THROW(module.setGcParameters(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGcParameters(0 + 1), std::out_of_range);
}

// Test for GcParameters[N/A].Name in GcSource
TEST(GcSourceTest, GcParameters[N/A].NameDefault) {
    GcSource module;
    EXPECT_EQ(module.getGcParameters[N/A].Name(), 0);
}

TEST(GcSourceTest, GcParameters[N/A].NameRange) {
    GcSource module;
    module.setGcParameters[N/A].Name(0);
    EXPECT_EQ(module.getGcParameters[N/A].Name(), 0);
    module.setGcParameters[N/A].Name(0);
    EXPECT_EQ(module.getGcParameters[N/A].Name(), 0);
    EXPECT_THROW(module.setGcParameters[N/A].Name(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGcParameters[N/A].Name(0 + 1), std::out_of_range);
}

// Test for GcParameters[N/A].Value in GcSource
TEST(GcSourceTest, GcParameters[N/A].ValueDefault) {
    GcSource module;
    EXPECT_EQ(module.getGcParameters[N/A].Value(), 0);
}

TEST(GcSourceTest, GcParameters[N/A].ValueRange) {
    GcSource module;
    module.setGcParameters[N/A].Value(0);
    EXPECT_EQ(module.getGcParameters[N/A].Value(), 0);
    module.setGcParameters[N/A].Value(0);
    EXPECT_EQ(module.getGcParameters[N/A].Value(), 0);
    EXPECT_THROW(module.setGcParameters[N/A].Value(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGcParameters[N/A].Value(0 + 1), std::out_of_range);
}

// Test for StopOnError in GstSource
TEST(GstSourceTest, StopOnErrorDefault) {
    GstSource module;
    EXPECT_EQ(module.getStopOnError(), 0);
}

TEST(GstSourceTest, StopOnErrorRange) {
    GstSource module;
    module.setStopOnError(0);
    EXPECT_EQ(module.getStopOnError(), 0);
    module.setStopOnError(0);
    EXPECT_EQ(module.getStopOnError(), 0);
    EXPECT_THROW(module.setStopOnError(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setStopOnError(0 + 1), std::out_of_range);
}

// Test for Source in GstSource
TEST(GstSourceTest, SourceDefault) {
    GstSource module;
    EXPECT_EQ(module.getSource(), 0);
}

TEST(GstSourceTest, SourceRange) {
    GstSource module;
    module.setSource(0);
    EXPECT_EQ(module.getSource(), 0);
    module.setSource(0);
    EXPECT_EQ(module.getSource(), 0);
    EXPECT_THROW(module.setSource(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setSource(0 + 1), std::out_of_range);
}

// Test for Url in GstSource
TEST(GstSourceTest, UrlDefault) {
    GstSource module;
    EXPECT_EQ(module.getUrl(), 0);
}

TEST(GstSourceTest, UrlRange) {
    GstSource module;
    module.setUrl(0);
    EXPECT_EQ(module.getUrl(), 0);
    module.setUrl(0);
    EXPECT_EQ(module.getUrl(), 0);
    EXPECT_THROW(module.setUrl(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setUrl(0 + 1), std::out_of_range);
}

// Test for OutputFramerate in FramerateController
TEST(FramerateControllerTest, OutputFramerateDefault) {
    FramerateController module;
    EXPECT_EQ(module.getOutputFramerate(), 0);
}

TEST(FramerateControllerTest, OutputFramerateRange) {
    FramerateController module;
    module.setOutputFramerate(0);
    EXPECT_EQ(module.getOutputFramerate(), 0);
    module.setOutputFramerate(0);
    EXPECT_EQ(module.getOutputFramerate(), 0);
    EXPECT_THROW(module.setOutputFramerate(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setOutputFramerate(0 + 1), std::out_of_range);
}

// Test for Width in Preprocessor
TEST(PreprocessorTest, WidthDefault) {
    Preprocessor module;
    EXPECT_EQ(module.getWidth(), 0);
}

TEST(PreprocessorTest, WidthRange) {
    Preprocessor module;
    module.setWidth(0);
    EXPECT_EQ(module.getWidth(), 0);
    module.setWidth(0);
    EXPECT_EQ(module.getWidth(), 0);
    EXPECT_THROW(module.setWidth(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setWidth(0 + 1), std::out_of_range);
}

// Test for Height in Preprocessor
TEST(PreprocessorTest, HeightDefault) {
    Preprocessor module;
    EXPECT_EQ(module.getHeight(), 0);
}

TEST(PreprocessorTest, HeightRange) {
    Preprocessor module;
    module.setHeight(0);
    EXPECT_EQ(module.getHeight(), 0);
    module.setHeight(0);
    EXPECT_EQ(module.getHeight(), 0);
    EXPECT_THROW(module.setHeight(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setHeight(0 + 1), std::out_of_range);
}

// Test for KeepAspectRatio in Preprocessor
TEST(PreprocessorTest, KeepAspectRatioDefault) {
    Preprocessor module;
    EXPECT_EQ(module.getKeepAspectRatio(), 0);
}

TEST(PreprocessorTest, KeepAspectRatioRange) {
    Preprocessor module;
    module.setKeepAspectRatio(0);
    EXPECT_EQ(module.getKeepAspectRatio(), 0);
    module.setKeepAspectRatio(0);
    EXPECT_EQ(module.getKeepAspectRatio(), 0);
    EXPECT_THROW(module.setKeepAspectRatio(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setKeepAspectRatio(0 + 1), std::out_of_range);
}

// Test for RotateAngle in Preprocessor
TEST(PreprocessorTest, RotateAngleDefault) {
    Preprocessor module;
    EXPECT_EQ(module.getRotateAngle(), 0);
}

TEST(PreprocessorTest, RotateAngleRange) {
    Preprocessor module;
    module.setRotateAngle(0);
    EXPECT_EQ(module.getRotateAngle(), 0);
    module.setRotateAngle(0);
    EXPECT_EQ(module.getRotateAngle(), 0);
    EXPECT_THROW(module.setRotateAngle(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setRotateAngle(0 + 1), std::out_of_range);
}

// Test for Roi in Preprocessor
TEST(PreprocessorTest, RoiDefault) {
    Preprocessor module;
    EXPECT_EQ(module.getRoi(), 0);
}

TEST(PreprocessorTest, RoiRange) {
    Preprocessor module;
    module.setRoi(0);
    EXPECT_EQ(module.getRoi(), 0);
    module.setRoi(0);
    EXPECT_EQ(module.getRoi(), 0);
    EXPECT_THROW(module.setRoi(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setRoi(0 + 1), std::out_of_range);
}

// Test for Roi.X in Preprocessor
TEST(PreprocessorTest, Roi.XDefault) {
    Preprocessor module;
    EXPECT_EQ(module.getRoi.X(), 0);
}

TEST(PreprocessorTest, Roi.XRange) {
    Preprocessor module;
    module.setRoi.X(0);
    EXPECT_EQ(module.getRoi.X(), 0);
    module.setRoi.X(0);
    EXPECT_EQ(module.getRoi.X(), 0);
    EXPECT_THROW(module.setRoi.X(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setRoi.X(0 + 1), std::out_of_range);
}

// Test for Roi.Y in Preprocessor
TEST(PreprocessorTest, Roi.YDefault) {
    Preprocessor module;
    EXPECT_EQ(module.getRoi.Y(), 0);
}

TEST(PreprocessorTest, Roi.YRange) {
    Preprocessor module;
    module.setRoi.Y(0);
    EXPECT_EQ(module.getRoi.Y(), 0);
    module.setRoi.Y(0);
    EXPECT_EQ(module.getRoi.Y(), 0);
    EXPECT_THROW(module.setRoi.Y(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setRoi.Y(0 + 1), std::out_of_range);
}

// Test for Roi.Width in Preprocessor
TEST(PreprocessorTest, Roi.WidthDefault) {
    Preprocessor module;
    EXPECT_EQ(module.getRoi.Width(), 0);
}

TEST(PreprocessorTest, Roi.WidthRange) {
    Preprocessor module;
    module.setRoi.Width(0);
    EXPECT_EQ(module.getRoi.Width(), 0);
    module.setRoi.Width(0);
    EXPECT_EQ(module.getRoi.Width(), 0);
    EXPECT_THROW(module.setRoi.Width(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setRoi.Width(0 + 1), std::out_of_range);
}

// Test for Roi.Height in Preprocessor
TEST(PreprocessorTest, Roi.HeightDefault) {
    Preprocessor module;
    EXPECT_EQ(module.getRoi.Height(), 0);
}

TEST(PreprocessorTest, Roi.HeightRange) {
    Preprocessor module;
    module.setRoi.Height(0);
    EXPECT_EQ(module.getRoi.Height(), 0);
    module.setRoi.Height(0);
    EXPECT_EQ(module.getRoi.Height(), 0);
    EXPECT_THROW(module.setRoi.Height(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setRoi.Height(0 + 1), std::out_of_range);
}

// Test for FlowId in VideoPassthrough
TEST(VideoPassthroughTest, FlowIdDefault) {
    VideoPassthrough module;
    EXPECT_EQ(module.getFlowId(), 0);
}

TEST(VideoPassthroughTest, FlowIdRange) {
    VideoPassthrough module;
    module.setFlowId(0);
    EXPECT_EQ(module.getFlowId(), 0);
    module.setFlowId(0);
    EXPECT_EQ(module.getFlowId(), 0);
    EXPECT_THROW(module.setFlowId(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setFlowId(0 + 1), std::out_of_range);
}

// Test for Enable in FrameRegisterImage
TEST(FrameRegisterImageTest, EnableDefault) {
    FrameRegisterImage module;
    EXPECT_EQ(module.getEnable(), 0);
}

TEST(FrameRegisterImageTest, EnableRange) {
    FrameRegisterImage module;
    module.setEnable(0);
    EXPECT_EQ(module.getEnable(), 0);
    module.setEnable(0);
    EXPECT_EQ(module.getEnable(), 0);
    EXPECT_THROW(module.setEnable(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setEnable(0 + 1), std::out_of_range);
}

// Test for FlowId in FlowSwitcher
TEST(FlowSwitcherTest, FlowIdDefault) {
    FlowSwitcher module;
    EXPECT_EQ(module.getFlowId(), 0);
}

TEST(FlowSwitcherTest, FlowIdRange) {
    FlowSwitcher module;
    module.setFlowId(0);
    EXPECT_EQ(module.getFlowId(), 0);
    module.setFlowId(0);
    EXPECT_EQ(module.getFlowId(), 0);
    EXPECT_THROW(module.setFlowId(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setFlowId(0 + 1), std::out_of_range);
}

// Test for LockOnTrack in LockedOnConfiguration
TEST(LockedOnConfigurationTest, LockOnTrackDefault) {
    LockedOnConfiguration module;
    EXPECT_EQ(module.getLockOnTrack(), 0);
}

TEST(LockedOnConfigurationTest, LockOnTrackRange) {
    LockedOnConfiguration module;
    module.setLockOnTrack(0);
    EXPECT_EQ(module.getLockOnTrack(), 0);
    module.setLockOnTrack(0);
    EXPECT_EQ(module.getLockOnTrack(), 0);
    EXPECT_THROW(module.setLockOnTrack(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setLockOnTrack(0 + 1), std::out_of_range);
}

// Test for Roi in GroundRgbDetector
TEST(GroundRgbDetectorTest, RoiDefault) {
    GroundRgbDetector module;
    EXPECT_EQ(module.getRoi(), 0);
}

TEST(GroundRgbDetectorTest, RoiRange) {
    GroundRgbDetector module;
    module.setRoi(0);
    EXPECT_EQ(module.getRoi(), 0);
    module.setRoi(0);
    EXPECT_EQ(module.getRoi(), 0);
    EXPECT_THROW(module.setRoi(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setRoi(0 + 1), std::out_of_range);
}

// Test for Roi.X in GroundRgbDetector
TEST(GroundRgbDetectorTest, Roi.XDefault) {
    GroundRgbDetector module;
    EXPECT_EQ(module.getRoi.X(), 0);
}

TEST(GroundRgbDetectorTest, Roi.XRange) {
    GroundRgbDetector module;
    module.setRoi.X(0);
    EXPECT_EQ(module.getRoi.X(), 0);
    module.setRoi.X(0);
    EXPECT_EQ(module.getRoi.X(), 0);
    EXPECT_THROW(module.setRoi.X(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setRoi.X(0 + 1), std::out_of_range);
}

// Test for Roi.Y in GroundRgbDetector
TEST(GroundRgbDetectorTest, Roi.YDefault) {
    GroundRgbDetector module;
    EXPECT_EQ(module.getRoi.Y(), 0);
}

TEST(GroundRgbDetectorTest, Roi.YRange) {
    GroundRgbDetector module;
    module.setRoi.Y(0);
    EXPECT_EQ(module.getRoi.Y(), 0);
    module.setRoi.Y(0);
    EXPECT_EQ(module.getRoi.Y(), 0);
    EXPECT_THROW(module.setRoi.Y(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setRoi.Y(0 + 1), std::out_of_range);
}

// Test for Roi.Width in GroundRgbDetector
TEST(GroundRgbDetectorTest, Roi.WidthDefault) {
    GroundRgbDetector module;
    EXPECT_EQ(module.getRoi.Width(), 0);
}

TEST(GroundRgbDetectorTest, Roi.WidthRange) {
    GroundRgbDetector module;
    module.setRoi.Width(0);
    EXPECT_EQ(module.getRoi.Width(), 0);
    module.setRoi.Width(0);
    EXPECT_EQ(module.getRoi.Width(), 0);
    EXPECT_THROW(module.setRoi.Width(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setRoi.Width(0 + 1), std::out_of_range);
}

// Test for Roi.Height in GroundRgbDetector
TEST(GroundRgbDetectorTest, Roi.HeightDefault) {
    GroundRgbDetector module;
    EXPECT_EQ(module.getRoi.Height(), 0);
}

TEST(GroundRgbDetectorTest, Roi.HeightRange) {
    GroundRgbDetector module;
    module.setRoi.Height(0);
    EXPECT_EQ(module.getRoi.Height(), 0);
    module.setRoi.Height(0);
    EXPECT_EQ(module.getRoi.Height(), 0);
    EXPECT_THROW(module.setRoi.Height(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setRoi.Height(0 + 1), std::out_of_range);
}

// Test for Groups in GroundRgbDetector
TEST(GroundRgbDetectorTest, GroupsDefault) {
    GroundRgbDetector module;
    EXPECT_EQ(module.getGroups(), 0);
}

TEST(GroundRgbDetectorTest, GroupsRange) {
    GroundRgbDetector module;
    module.setGroups(0);
    EXPECT_EQ(module.getGroups(), 0);
    module.setGroups(0);
    EXPECT_EQ(module.getGroups(), 0);
    EXPECT_THROW(module.setGroups(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups(0 + 1), std::out_of_range);
}

// Test for Groups["Person"].ScoreThreshold in GroundRgbDetector
TEST(GroundRgbDetectorTest, Groups["Person"].ScoreThresholdDefault) {
    GroundRgbDetector module;
    EXPECT_EQ(module.getGroups["Person"].ScoreThreshold(), 0);
}

TEST(GroundRgbDetectorTest, Groups["Person"].ScoreThresholdRange) {
    GroundRgbDetector module;
    module.setGroups["Person"].ScoreThreshold(0);
    EXPECT_EQ(module.getGroups["Person"].ScoreThreshold(), 0);
    module.setGroups["Person"].ScoreThreshold(0);
    EXPECT_EQ(module.getGroups["Person"].ScoreThreshold(), 0);
    EXPECT_THROW(module.setGroups["Person"].ScoreThreshold(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Person"].ScoreThreshold(0 + 1), std::out_of_range);
}

// Test for Groups["Person"].MinWidth in GroundRgbDetector
TEST(GroundRgbDetectorTest, Groups["Person"].MinWidthDefault) {
    GroundRgbDetector module;
    EXPECT_EQ(module.getGroups["Person"].MinWidth(), 0);
}

TEST(GroundRgbDetectorTest, Groups["Person"].MinWidthRange) {
    GroundRgbDetector module;
    module.setGroups["Person"].MinWidth(0);
    EXPECT_EQ(module.getGroups["Person"].MinWidth(), 0);
    module.setGroups["Person"].MinWidth(0);
    EXPECT_EQ(module.getGroups["Person"].MinWidth(), 0);
    EXPECT_THROW(module.setGroups["Person"].MinWidth(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Person"].MinWidth(0 + 1), std::out_of_range);
}

// Test for Groups["Person"].MaxWidth in GroundRgbDetector
TEST(GroundRgbDetectorTest, Groups["Person"].MaxWidthDefault) {
    GroundRgbDetector module;
    EXPECT_EQ(module.getGroups["Person"].MaxWidth(), 0);
}

TEST(GroundRgbDetectorTest, Groups["Person"].MaxWidthRange) {
    GroundRgbDetector module;
    module.setGroups["Person"].MaxWidth(0);
    EXPECT_EQ(module.getGroups["Person"].MaxWidth(), 0);
    module.setGroups["Person"].MaxWidth(0);
    EXPECT_EQ(module.getGroups["Person"].MaxWidth(), 0);
    EXPECT_THROW(module.setGroups["Person"].MaxWidth(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Person"].MaxWidth(0 + 1), std::out_of_range);
}

// Test for Groups["Person"].MinHeight in GroundRgbDetector
TEST(GroundRgbDetectorTest, Groups["Person"].MinHeightDefault) {
    GroundRgbDetector module;
    EXPECT_EQ(module.getGroups["Person"].MinHeight(), 0);
}

TEST(GroundRgbDetectorTest, Groups["Person"].MinHeightRange) {
    GroundRgbDetector module;
    module.setGroups["Person"].MinHeight(0);
    EXPECT_EQ(module.getGroups["Person"].MinHeight(), 0);
    module.setGroups["Person"].MinHeight(0);
    EXPECT_EQ(module.getGroups["Person"].MinHeight(), 0);
    EXPECT_THROW(module.setGroups["Person"].MinHeight(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Person"].MinHeight(0 + 1), std::out_of_range);
}

// Test for Groups["Person"].MaxHeight in GroundRgbDetector
TEST(GroundRgbDetectorTest, Groups["Person"].MaxHeightDefault) {
    GroundRgbDetector module;
    EXPECT_EQ(module.getGroups["Person"].MaxHeight(), 0);
}

TEST(GroundRgbDetectorTest, Groups["Person"].MaxHeightRange) {
    GroundRgbDetector module;
    module.setGroups["Person"].MaxHeight(0);
    EXPECT_EQ(module.getGroups["Person"].MaxHeight(), 0);
    module.setGroups["Person"].MaxHeight(0);
    EXPECT_EQ(module.getGroups["Person"].MaxHeight(), 0);
    EXPECT_THROW(module.setGroups["Person"].MaxHeight(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Person"].MaxHeight(0 + 1), std::out_of_range);
}

// Test for Groups["Person"].MinAspectRatio in GroundRgbDetector
TEST(GroundRgbDetectorTest, Groups["Person"].MinAspectRatioDefault) {
    GroundRgbDetector module;
    EXPECT_EQ(module.getGroups["Person"].MinAspectRatio(), 0);
}

TEST(GroundRgbDetectorTest, Groups["Person"].MinAspectRatioRange) {
    GroundRgbDetector module;
    module.setGroups["Person"].MinAspectRatio(0);
    EXPECT_EQ(module.getGroups["Person"].MinAspectRatio(), 0);
    module.setGroups["Person"].MinAspectRatio(0);
    EXPECT_EQ(module.getGroups["Person"].MinAspectRatio(), 0);
    EXPECT_THROW(module.setGroups["Person"].MinAspectRatio(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Person"].MinAspectRatio(0 + 1), std::out_of_range);
}

// Test for Groups["Person"].MaxAspectRatio in GroundRgbDetector
TEST(GroundRgbDetectorTest, Groups["Person"].MaxAspectRatioDefault) {
    GroundRgbDetector module;
    EXPECT_EQ(module.getGroups["Person"].MaxAspectRatio(), 0);
}

TEST(GroundRgbDetectorTest, Groups["Person"].MaxAspectRatioRange) {
    GroundRgbDetector module;
    module.setGroups["Person"].MaxAspectRatio(0);
    EXPECT_EQ(module.getGroups["Person"].MaxAspectRatio(), 0);
    module.setGroups["Person"].MaxAspectRatio(0);
    EXPECT_EQ(module.getGroups["Person"].MaxAspectRatio(), 0);
    EXPECT_THROW(module.setGroups["Person"].MaxAspectRatio(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Person"].MaxAspectRatio(0 + 1), std::out_of_range);
}

// Test for Groups["Person"].AttributeGroups in GroundRgbDetector
TEST(GroundRgbDetectorTest, Groups["Person"].AttributeGroupsDefault) {
    GroundRgbDetector module;
    EXPECT_EQ(module.getGroups["Person"].AttributeGroups(), 0);
}

TEST(GroundRgbDetectorTest, Groups["Person"].AttributeGroupsRange) {
    GroundRgbDetector module;
    module.setGroups["Person"].AttributeGroups(0);
    EXPECT_EQ(module.getGroups["Person"].AttributeGroups(), 0);
    module.setGroups["Person"].AttributeGroups(0);
    EXPECT_EQ(module.getGroups["Person"].AttributeGroups(), 0);
    EXPECT_THROW(module.setGroups["Person"].AttributeGroups(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Person"].AttributeGroups(0 + 1), std::out_of_range);
}

// Test for Groups["Person"].AttributeGroups["N/A"].Attributes["N/A"] in GroundRgbDetector
TEST(GroundRgbDetectorTest, Groups["Person"].AttributeGroups["N/A"].Attributes["N/A"]Default) {
    GroundRgbDetector module;
    EXPECT_EQ(module.getGroups["Person"].AttributeGroups["N/A"].Attributes["N/A"](), 0);
}

TEST(GroundRgbDetectorTest, Groups["Person"].AttributeGroups["N/A"].Attributes["N/A"]Range) {
    GroundRgbDetector module;
    module.setGroups["Person"].AttributeGroups["N/A"].Attributes["N/A"](0);
    EXPECT_EQ(module.getGroups["Person"].AttributeGroups["N/A"].Attributes["N/A"](), 0);
    module.setGroups["Person"].AttributeGroups["N/A"].Attributes["N/A"](0);
    EXPECT_EQ(module.getGroups["Person"].AttributeGroups["N/A"].Attributes["N/A"](), 0);
    EXPECT_THROW(module.setGroups["Person"].AttributeGroups["N/A"].Attributes["N/A"](0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Person"].AttributeGroups["N/A"].Attributes["N/A"](0 + 1), std::out_of_range);
}

// Test for Groups["Vehicle"].ScoreThreshold in GroundRgbDetector
TEST(GroundRgbDetectorTest, Groups["Vehicle"].ScoreThresholdDefault) {
    GroundRgbDetector module;
    EXPECT_EQ(module.getGroups["Vehicle"].ScoreThreshold(), 0);
}

TEST(GroundRgbDetectorTest, Groups["Vehicle"].ScoreThresholdRange) {
    GroundRgbDetector module;
    module.setGroups["Vehicle"].ScoreThreshold(0);
    EXPECT_EQ(module.getGroups["Vehicle"].ScoreThreshold(), 0);
    module.setGroups["Vehicle"].ScoreThreshold(0);
    EXPECT_EQ(module.getGroups["Vehicle"].ScoreThreshold(), 0);
    EXPECT_THROW(module.setGroups["Vehicle"].ScoreThreshold(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Vehicle"].ScoreThreshold(0 + 1), std::out_of_range);
}

// Test for Groups["Vehicle"].MinWidth in GroundRgbDetector
TEST(GroundRgbDetectorTest, Groups["Vehicle"].MinWidthDefault) {
    GroundRgbDetector module;
    EXPECT_EQ(module.getGroups["Vehicle"].MinWidth(), 0);
}

TEST(GroundRgbDetectorTest, Groups["Vehicle"].MinWidthRange) {
    GroundRgbDetector module;
    module.setGroups["Vehicle"].MinWidth(0);
    EXPECT_EQ(module.getGroups["Vehicle"].MinWidth(), 0);
    module.setGroups["Vehicle"].MinWidth(0);
    EXPECT_EQ(module.getGroups["Vehicle"].MinWidth(), 0);
    EXPECT_THROW(module.setGroups["Vehicle"].MinWidth(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Vehicle"].MinWidth(0 + 1), std::out_of_range);
}

// Test for Groups["Vehicle"].MaxWidth in GroundRgbDetector
TEST(GroundRgbDetectorTest, Groups["Vehicle"].MaxWidthDefault) {
    GroundRgbDetector module;
    EXPECT_EQ(module.getGroups["Vehicle"].MaxWidth(), 0);
}

TEST(GroundRgbDetectorTest, Groups["Vehicle"].MaxWidthRange) {
    GroundRgbDetector module;
    module.setGroups["Vehicle"].MaxWidth(0);
    EXPECT_EQ(module.getGroups["Vehicle"].MaxWidth(), 0);
    module.setGroups["Vehicle"].MaxWidth(0);
    EXPECT_EQ(module.getGroups["Vehicle"].MaxWidth(), 0);
    EXPECT_THROW(module.setGroups["Vehicle"].MaxWidth(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Vehicle"].MaxWidth(0 + 1), std::out_of_range);
}

// Test for Groups["Vehicle"].MinHeight in GroundRgbDetector
TEST(GroundRgbDetectorTest, Groups["Vehicle"].MinHeightDefault) {
    GroundRgbDetector module;
    EXPECT_EQ(module.getGroups["Vehicle"].MinHeight(), 0);
}

TEST(GroundRgbDetectorTest, Groups["Vehicle"].MinHeightRange) {
    GroundRgbDetector module;
    module.setGroups["Vehicle"].MinHeight(0);
    EXPECT_EQ(module.getGroups["Vehicle"].MinHeight(), 0);
    module.setGroups["Vehicle"].MinHeight(0);
    EXPECT_EQ(module.getGroups["Vehicle"].MinHeight(), 0);
    EXPECT_THROW(module.setGroups["Vehicle"].MinHeight(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Vehicle"].MinHeight(0 + 1), std::out_of_range);
}

// Test for Groups["Vehicle"].MaxHeight in GroundRgbDetector
TEST(GroundRgbDetectorTest, Groups["Vehicle"].MaxHeightDefault) {
    GroundRgbDetector module;
    EXPECT_EQ(module.getGroups["Vehicle"].MaxHeight(), 0);
}

TEST(GroundRgbDetectorTest, Groups["Vehicle"].MaxHeightRange) {
    GroundRgbDetector module;
    module.setGroups["Vehicle"].MaxHeight(0);
    EXPECT_EQ(module.getGroups["Vehicle"].MaxHeight(), 0);
    module.setGroups["Vehicle"].MaxHeight(0);
    EXPECT_EQ(module.getGroups["Vehicle"].MaxHeight(), 0);
    EXPECT_THROW(module.setGroups["Vehicle"].MaxHeight(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Vehicle"].MaxHeight(0 + 1), std::out_of_range);
}

// Test for Groups["Vehicle"].MinAspectRatio in GroundRgbDetector
TEST(GroundRgbDetectorTest, Groups["Vehicle"].MinAspectRatioDefault) {
    GroundRgbDetector module;
    EXPECT_EQ(module.getGroups["Vehicle"].MinAspectRatio(), 0);
}

TEST(GroundRgbDetectorTest, Groups["Vehicle"].MinAspectRatioRange) {
    GroundRgbDetector module;
    module.setGroups["Vehicle"].MinAspectRatio(0);
    EXPECT_EQ(module.getGroups["Vehicle"].MinAspectRatio(), 0);
    module.setGroups["Vehicle"].MinAspectRatio(0);
    EXPECT_EQ(module.getGroups["Vehicle"].MinAspectRatio(), 0);
    EXPECT_THROW(module.setGroups["Vehicle"].MinAspectRatio(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Vehicle"].MinAspectRatio(0 + 1), std::out_of_range);
}

// Test for Groups["Vehicle"].MaxAspectRatio in GroundRgbDetector
TEST(GroundRgbDetectorTest, Groups["Vehicle"].MaxAspectRatioDefault) {
    GroundRgbDetector module;
    EXPECT_EQ(module.getGroups["Vehicle"].MaxAspectRatio(), 0);
}

TEST(GroundRgbDetectorTest, Groups["Vehicle"].MaxAspectRatioRange) {
    GroundRgbDetector module;
    module.setGroups["Vehicle"].MaxAspectRatio(0);
    EXPECT_EQ(module.getGroups["Vehicle"].MaxAspectRatio(), 0);
    module.setGroups["Vehicle"].MaxAspectRatio(0);
    EXPECT_EQ(module.getGroups["Vehicle"].MaxAspectRatio(), 0);
    EXPECT_THROW(module.setGroups["Vehicle"].MaxAspectRatio(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Vehicle"].MaxAspectRatio(0 + 1), std::out_of_range);
}

// Test for Groups["Vehicle"].AttributeGroups in GroundRgbDetector
TEST(GroundRgbDetectorTest, Groups["Vehicle"].AttributeGroupsDefault) {
    GroundRgbDetector module;
    EXPECT_EQ(module.getGroups["Vehicle"].AttributeGroups(), 0);
}

TEST(GroundRgbDetectorTest, Groups["Vehicle"].AttributeGroupsRange) {
    GroundRgbDetector module;
    module.setGroups["Vehicle"].AttributeGroups(0);
    EXPECT_EQ(module.getGroups["Vehicle"].AttributeGroups(), 0);
    module.setGroups["Vehicle"].AttributeGroups(0);
    EXPECT_EQ(module.getGroups["Vehicle"].AttributeGroups(), 0);
    EXPECT_THROW(module.setGroups["Vehicle"].AttributeGroups(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Vehicle"].AttributeGroups(0 + 1), std::out_of_range);
}

// Test for Groups["Vehicle"].AttributeGroups["N/A"].Attributes["N/A"] in GroundRgbDetector
TEST(GroundRgbDetectorTest, Groups["Vehicle"].AttributeGroups["N/A"].Attributes["N/A"]Default) {
    GroundRgbDetector module;
    EXPECT_EQ(module.getGroups["Vehicle"].AttributeGroups["N/A"].Attributes["N/A"](), 0);
}

TEST(GroundRgbDetectorTest, Groups["Vehicle"].AttributeGroups["N/A"].Attributes["N/A"]Range) {
    GroundRgbDetector module;
    module.setGroups["Vehicle"].AttributeGroups["N/A"].Attributes["N/A"](0);
    EXPECT_EQ(module.getGroups["Vehicle"].AttributeGroups["N/A"].Attributes["N/A"](), 0);
    module.setGroups["Vehicle"].AttributeGroups["N/A"].Attributes["N/A"](0);
    EXPECT_EQ(module.getGroups["Vehicle"].AttributeGroups["N/A"].Attributes["N/A"](), 0);
    EXPECT_THROW(module.setGroups["Vehicle"].AttributeGroups["N/A"].Attributes["N/A"](0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Vehicle"].AttributeGroups["N/A"].Attributes["N/A"](0 + 1), std::out_of_range);
}

// Test for AveragePixelValue[N/A] in GroundRgbDetector
TEST(GroundRgbDetectorTest, AveragePixelValue[N/A]Default) {
    GroundRgbDetector module;
    EXPECT_EQ(module.getAveragePixelValue[N/A](), 0);
}

TEST(GroundRgbDetectorTest, AveragePixelValue[N/A]Range) {
    GroundRgbDetector module;
    module.setAveragePixelValue[N/A](0);
    EXPECT_EQ(module.getAveragePixelValue[N/A](), 0);
    module.setAveragePixelValue[N/A](0);
    EXPECT_EQ(module.getAveragePixelValue[N/A](), 0);
    EXPECT_THROW(module.setAveragePixelValue[N/A](0 - 1), std::out_of_range);
    EXPECT_THROW(module.setAveragePixelValue[N/A](0 + 1), std::out_of_range);
}

// Test for PixelValueStandardDeviation[N/A] in GroundRgbDetector
TEST(GroundRgbDetectorTest, PixelValueStandardDeviation[N/A]Default) {
    GroundRgbDetector module;
    EXPECT_EQ(module.getPixelValueStandardDeviation[N/A](), 0);
}

TEST(GroundRgbDetectorTest, PixelValueStandardDeviation[N/A]Range) {
    GroundRgbDetector module;
    module.setPixelValueStandardDeviation[N/A](0);
    EXPECT_EQ(module.getPixelValueStandardDeviation[N/A](), 0);
    module.setPixelValueStandardDeviation[N/A](0);
    EXPECT_EQ(module.getPixelValueStandardDeviation[N/A](), 0);
    EXPECT_THROW(module.setPixelValueStandardDeviation[N/A](0 - 1), std::out_of_range);
    EXPECT_THROW(module.setPixelValueStandardDeviation[N/A](0 + 1), std::out_of_range);
}

// Test for MaxDetections in GroundRgbDetector
TEST(GroundRgbDetectorTest, MaxDetectionsDefault) {
    GroundRgbDetector module;
    EXPECT_EQ(module.getMaxDetections(), 0);
}

TEST(GroundRgbDetectorTest, MaxDetectionsRange) {
    GroundRgbDetector module;
    module.setMaxDetections(0);
    EXPECT_EQ(module.getMaxDetections(), 0);
    module.setMaxDetections(0);
    EXPECT_EQ(module.getMaxDetections(), 0);
    EXPECT_THROW(module.setMaxDetections(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setMaxDetections(0 + 1), std::out_of_range);
}

// Test for Roi in GroundMwirDetector
TEST(GroundMwirDetectorTest, RoiDefault) {
    GroundMwirDetector module;
    EXPECT_EQ(module.getRoi(), 0);
}

TEST(GroundMwirDetectorTest, RoiRange) {
    GroundMwirDetector module;
    module.setRoi(0);
    EXPECT_EQ(module.getRoi(), 0);
    module.setRoi(0);
    EXPECT_EQ(module.getRoi(), 0);
    EXPECT_THROW(module.setRoi(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setRoi(0 + 1), std::out_of_range);
}

// Test for Roi.X in GroundMwirDetector
TEST(GroundMwirDetectorTest, Roi.XDefault) {
    GroundMwirDetector module;
    EXPECT_EQ(module.getRoi.X(), 0);
}

TEST(GroundMwirDetectorTest, Roi.XRange) {
    GroundMwirDetector module;
    module.setRoi.X(0);
    EXPECT_EQ(module.getRoi.X(), 0);
    module.setRoi.X(0);
    EXPECT_EQ(module.getRoi.X(), 0);
    EXPECT_THROW(module.setRoi.X(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setRoi.X(0 + 1), std::out_of_range);
}

// Test for Roi.Y in GroundMwirDetector
TEST(GroundMwirDetectorTest, Roi.YDefault) {
    GroundMwirDetector module;
    EXPECT_EQ(module.getRoi.Y(), 0);
}

TEST(GroundMwirDetectorTest, Roi.YRange) {
    GroundMwirDetector module;
    module.setRoi.Y(0);
    EXPECT_EQ(module.getRoi.Y(), 0);
    module.setRoi.Y(0);
    EXPECT_EQ(module.getRoi.Y(), 0);
    EXPECT_THROW(module.setRoi.Y(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setRoi.Y(0 + 1), std::out_of_range);
}

// Test for Roi.Width in GroundMwirDetector
TEST(GroundMwirDetectorTest, Roi.WidthDefault) {
    GroundMwirDetector module;
    EXPECT_EQ(module.getRoi.Width(), 0);
}

TEST(GroundMwirDetectorTest, Roi.WidthRange) {
    GroundMwirDetector module;
    module.setRoi.Width(0);
    EXPECT_EQ(module.getRoi.Width(), 0);
    module.setRoi.Width(0);
    EXPECT_EQ(module.getRoi.Width(), 0);
    EXPECT_THROW(module.setRoi.Width(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setRoi.Width(0 + 1), std::out_of_range);
}

// Test for Roi.Height in GroundMwirDetector
TEST(GroundMwirDetectorTest, Roi.HeightDefault) {
    GroundMwirDetector module;
    EXPECT_EQ(module.getRoi.Height(), 0);
}

TEST(GroundMwirDetectorTest, Roi.HeightRange) {
    GroundMwirDetector module;
    module.setRoi.Height(0);
    EXPECT_EQ(module.getRoi.Height(), 0);
    module.setRoi.Height(0);
    EXPECT_EQ(module.getRoi.Height(), 0);
    EXPECT_THROW(module.setRoi.Height(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setRoi.Height(0 + 1), std::out_of_range);
}

// Test for Groups in GroundMwirDetector
TEST(GroundMwirDetectorTest, GroupsDefault) {
    GroundMwirDetector module;
    EXPECT_EQ(module.getGroups(), 0);
}

TEST(GroundMwirDetectorTest, GroupsRange) {
    GroundMwirDetector module;
    module.setGroups(0);
    EXPECT_EQ(module.getGroups(), 0);
    module.setGroups(0);
    EXPECT_EQ(module.getGroups(), 0);
    EXPECT_THROW(module.setGroups(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups(0 + 1), std::out_of_range);
}

// Test for Groups["Person"].ScoreThreshold in GroundMwirDetector
TEST(GroundMwirDetectorTest, Groups["Person"].ScoreThresholdDefault) {
    GroundMwirDetector module;
    EXPECT_EQ(module.getGroups["Person"].ScoreThreshold(), 0);
}

TEST(GroundMwirDetectorTest, Groups["Person"].ScoreThresholdRange) {
    GroundMwirDetector module;
    module.setGroups["Person"].ScoreThreshold(0);
    EXPECT_EQ(module.getGroups["Person"].ScoreThreshold(), 0);
    module.setGroups["Person"].ScoreThreshold(0);
    EXPECT_EQ(module.getGroups["Person"].ScoreThreshold(), 0);
    EXPECT_THROW(module.setGroups["Person"].ScoreThreshold(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Person"].ScoreThreshold(0 + 1), std::out_of_range);
}

// Test for Groups["Person"].MinWidth in GroundMwirDetector
TEST(GroundMwirDetectorTest, Groups["Person"].MinWidthDefault) {
    GroundMwirDetector module;
    EXPECT_EQ(module.getGroups["Person"].MinWidth(), 0);
}

TEST(GroundMwirDetectorTest, Groups["Person"].MinWidthRange) {
    GroundMwirDetector module;
    module.setGroups["Person"].MinWidth(0);
    EXPECT_EQ(module.getGroups["Person"].MinWidth(), 0);
    module.setGroups["Person"].MinWidth(0);
    EXPECT_EQ(module.getGroups["Person"].MinWidth(), 0);
    EXPECT_THROW(module.setGroups["Person"].MinWidth(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Person"].MinWidth(0 + 1), std::out_of_range);
}

// Test for Groups["Person"].MaxWidth in GroundMwirDetector
TEST(GroundMwirDetectorTest, Groups["Person"].MaxWidthDefault) {
    GroundMwirDetector module;
    EXPECT_EQ(module.getGroups["Person"].MaxWidth(), 0);
}

TEST(GroundMwirDetectorTest, Groups["Person"].MaxWidthRange) {
    GroundMwirDetector module;
    module.setGroups["Person"].MaxWidth(0);
    EXPECT_EQ(module.getGroups["Person"].MaxWidth(), 0);
    module.setGroups["Person"].MaxWidth(0);
    EXPECT_EQ(module.getGroups["Person"].MaxWidth(), 0);
    EXPECT_THROW(module.setGroups["Person"].MaxWidth(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Person"].MaxWidth(0 + 1), std::out_of_range);
}

// Test for Groups["Person"].MinHeight in GroundMwirDetector
TEST(GroundMwirDetectorTest, Groups["Person"].MinHeightDefault) {
    GroundMwirDetector module;
    EXPECT_EQ(module.getGroups["Person"].MinHeight(), 0);
}

TEST(GroundMwirDetectorTest, Groups["Person"].MinHeightRange) {
    GroundMwirDetector module;
    module.setGroups["Person"].MinHeight(0);
    EXPECT_EQ(module.getGroups["Person"].MinHeight(), 0);
    module.setGroups["Person"].MinHeight(0);
    EXPECT_EQ(module.getGroups["Person"].MinHeight(), 0);
    EXPECT_THROW(module.setGroups["Person"].MinHeight(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Person"].MinHeight(0 + 1), std::out_of_range);
}

// Test for Groups["Person"].MaxHeight in GroundMwirDetector
TEST(GroundMwirDetectorTest, Groups["Person"].MaxHeightDefault) {
    GroundMwirDetector module;
    EXPECT_EQ(module.getGroups["Person"].MaxHeight(), 0);
}

TEST(GroundMwirDetectorTest, Groups["Person"].MaxHeightRange) {
    GroundMwirDetector module;
    module.setGroups["Person"].MaxHeight(0);
    EXPECT_EQ(module.getGroups["Person"].MaxHeight(), 0);
    module.setGroups["Person"].MaxHeight(0);
    EXPECT_EQ(module.getGroups["Person"].MaxHeight(), 0);
    EXPECT_THROW(module.setGroups["Person"].MaxHeight(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Person"].MaxHeight(0 + 1), std::out_of_range);
}

// Test for Groups["Person"].MinAspectRatio in GroundMwirDetector
TEST(GroundMwirDetectorTest, Groups["Person"].MinAspectRatioDefault) {
    GroundMwirDetector module;
    EXPECT_EQ(module.getGroups["Person"].MinAspectRatio(), 0);
}

TEST(GroundMwirDetectorTest, Groups["Person"].MinAspectRatioRange) {
    GroundMwirDetector module;
    module.setGroups["Person"].MinAspectRatio(0);
    EXPECT_EQ(module.getGroups["Person"].MinAspectRatio(), 0);
    module.setGroups["Person"].MinAspectRatio(0);
    EXPECT_EQ(module.getGroups["Person"].MinAspectRatio(), 0);
    EXPECT_THROW(module.setGroups["Person"].MinAspectRatio(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Person"].MinAspectRatio(0 + 1), std::out_of_range);
}

// Test for Groups["Person"].MaxAspectRatio in GroundMwirDetector
TEST(GroundMwirDetectorTest, Groups["Person"].MaxAspectRatioDefault) {
    GroundMwirDetector module;
    EXPECT_EQ(module.getGroups["Person"].MaxAspectRatio(), 0);
}

TEST(GroundMwirDetectorTest, Groups["Person"].MaxAspectRatioRange) {
    GroundMwirDetector module;
    module.setGroups["Person"].MaxAspectRatio(0);
    EXPECT_EQ(module.getGroups["Person"].MaxAspectRatio(), 0);
    module.setGroups["Person"].MaxAspectRatio(0);
    EXPECT_EQ(module.getGroups["Person"].MaxAspectRatio(), 0);
    EXPECT_THROW(module.setGroups["Person"].MaxAspectRatio(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Person"].MaxAspectRatio(0 + 1), std::out_of_range);
}

// Test for Groups["Person"].AttributeGroups in GroundMwirDetector
TEST(GroundMwirDetectorTest, Groups["Person"].AttributeGroupsDefault) {
    GroundMwirDetector module;
    EXPECT_EQ(module.getGroups["Person"].AttributeGroups(), 0);
}

TEST(GroundMwirDetectorTest, Groups["Person"].AttributeGroupsRange) {
    GroundMwirDetector module;
    module.setGroups["Person"].AttributeGroups(0);
    EXPECT_EQ(module.getGroups["Person"].AttributeGroups(), 0);
    module.setGroups["Person"].AttributeGroups(0);
    EXPECT_EQ(module.getGroups["Person"].AttributeGroups(), 0);
    EXPECT_THROW(module.setGroups["Person"].AttributeGroups(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Person"].AttributeGroups(0 + 1), std::out_of_range);
}

// Test for Groups["Person"].AttributeGroups["N/A"].Attributes["N/A"] in GroundMwirDetector
TEST(GroundMwirDetectorTest, Groups["Person"].AttributeGroups["N/A"].Attributes["N/A"]Default) {
    GroundMwirDetector module;
    EXPECT_EQ(module.getGroups["Person"].AttributeGroups["N/A"].Attributes["N/A"](), 0);
}

TEST(GroundMwirDetectorTest, Groups["Person"].AttributeGroups["N/A"].Attributes["N/A"]Range) {
    GroundMwirDetector module;
    module.setGroups["Person"].AttributeGroups["N/A"].Attributes["N/A"](0);
    EXPECT_EQ(module.getGroups["Person"].AttributeGroups["N/A"].Attributes["N/A"](), 0);
    module.setGroups["Person"].AttributeGroups["N/A"].Attributes["N/A"](0);
    EXPECT_EQ(module.getGroups["Person"].AttributeGroups["N/A"].Attributes["N/A"](), 0);
    EXPECT_THROW(module.setGroups["Person"].AttributeGroups["N/A"].Attributes["N/A"](0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Person"].AttributeGroups["N/A"].Attributes["N/A"](0 + 1), std::out_of_range);
}

// Test for Groups["Vehicle"].ScoreThreshold in GroundMwirDetector
TEST(GroundMwirDetectorTest, Groups["Vehicle"].ScoreThresholdDefault) {
    GroundMwirDetector module;
    EXPECT_EQ(module.getGroups["Vehicle"].ScoreThreshold(), 0);
}

TEST(GroundMwirDetectorTest, Groups["Vehicle"].ScoreThresholdRange) {
    GroundMwirDetector module;
    module.setGroups["Vehicle"].ScoreThreshold(0);
    EXPECT_EQ(module.getGroups["Vehicle"].ScoreThreshold(), 0);
    module.setGroups["Vehicle"].ScoreThreshold(0);
    EXPECT_EQ(module.getGroups["Vehicle"].ScoreThreshold(), 0);
    EXPECT_THROW(module.setGroups["Vehicle"].ScoreThreshold(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Vehicle"].ScoreThreshold(0 + 1), std::out_of_range);
}

// Test for Groups["Vehicle"].MinWidth in GroundMwirDetector
TEST(GroundMwirDetectorTest, Groups["Vehicle"].MinWidthDefault) {
    GroundMwirDetector module;
    EXPECT_EQ(module.getGroups["Vehicle"].MinWidth(), 0);
}

TEST(GroundMwirDetectorTest, Groups["Vehicle"].MinWidthRange) {
    GroundMwirDetector module;
    module.setGroups["Vehicle"].MinWidth(0);
    EXPECT_EQ(module.getGroups["Vehicle"].MinWidth(), 0);
    module.setGroups["Vehicle"].MinWidth(0);
    EXPECT_EQ(module.getGroups["Vehicle"].MinWidth(), 0);
    EXPECT_THROW(module.setGroups["Vehicle"].MinWidth(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Vehicle"].MinWidth(0 + 1), std::out_of_range);
}

// Test for Groups["Vehicle"].MaxWidth in GroundMwirDetector
TEST(GroundMwirDetectorTest, Groups["Vehicle"].MaxWidthDefault) {
    GroundMwirDetector module;
    EXPECT_EQ(module.getGroups["Vehicle"].MaxWidth(), 0);
}

TEST(GroundMwirDetectorTest, Groups["Vehicle"].MaxWidthRange) {
    GroundMwirDetector module;
    module.setGroups["Vehicle"].MaxWidth(0);
    EXPECT_EQ(module.getGroups["Vehicle"].MaxWidth(), 0);
    module.setGroups["Vehicle"].MaxWidth(0);
    EXPECT_EQ(module.getGroups["Vehicle"].MaxWidth(), 0);
    EXPECT_THROW(module.setGroups["Vehicle"].MaxWidth(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Vehicle"].MaxWidth(0 + 1), std::out_of_range);
}

// Test for Groups["Vehicle"].MinHeight in GroundMwirDetector
TEST(GroundMwirDetectorTest, Groups["Vehicle"].MinHeightDefault) {
    GroundMwirDetector module;
    EXPECT_EQ(module.getGroups["Vehicle"].MinHeight(), 0);
}

TEST(GroundMwirDetectorTest, Groups["Vehicle"].MinHeightRange) {
    GroundMwirDetector module;
    module.setGroups["Vehicle"].MinHeight(0);
    EXPECT_EQ(module.getGroups["Vehicle"].MinHeight(), 0);
    module.setGroups["Vehicle"].MinHeight(0);
    EXPECT_EQ(module.getGroups["Vehicle"].MinHeight(), 0);
    EXPECT_THROW(module.setGroups["Vehicle"].MinHeight(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Vehicle"].MinHeight(0 + 1), std::out_of_range);
}

// Test for Groups["Vehicle"].MaxHeight in GroundMwirDetector
TEST(GroundMwirDetectorTest, Groups["Vehicle"].MaxHeightDefault) {
    GroundMwirDetector module;
    EXPECT_EQ(module.getGroups["Vehicle"].MaxHeight(), 0);
}

TEST(GroundMwirDetectorTest, Groups["Vehicle"].MaxHeightRange) {
    GroundMwirDetector module;
    module.setGroups["Vehicle"].MaxHeight(0);
    EXPECT_EQ(module.getGroups["Vehicle"].MaxHeight(), 0);
    module.setGroups["Vehicle"].MaxHeight(0);
    EXPECT_EQ(module.getGroups["Vehicle"].MaxHeight(), 0);
    EXPECT_THROW(module.setGroups["Vehicle"].MaxHeight(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Vehicle"].MaxHeight(0 + 1), std::out_of_range);
}

// Test for Groups["Vehicle"].MinAspectRatio in GroundMwirDetector
TEST(GroundMwirDetectorTest, Groups["Vehicle"].MinAspectRatioDefault) {
    GroundMwirDetector module;
    EXPECT_EQ(module.getGroups["Vehicle"].MinAspectRatio(), 0);
}

TEST(GroundMwirDetectorTest, Groups["Vehicle"].MinAspectRatioRange) {
    GroundMwirDetector module;
    module.setGroups["Vehicle"].MinAspectRatio(0);
    EXPECT_EQ(module.getGroups["Vehicle"].MinAspectRatio(), 0);
    module.setGroups["Vehicle"].MinAspectRatio(0);
    EXPECT_EQ(module.getGroups["Vehicle"].MinAspectRatio(), 0);
    EXPECT_THROW(module.setGroups["Vehicle"].MinAspectRatio(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Vehicle"].MinAspectRatio(0 + 1), std::out_of_range);
}

// Test for Groups["Vehicle"].MaxAspectRatio in GroundMwirDetector
TEST(GroundMwirDetectorTest, Groups["Vehicle"].MaxAspectRatioDefault) {
    GroundMwirDetector module;
    EXPECT_EQ(module.getGroups["Vehicle"].MaxAspectRatio(), 0);
}

TEST(GroundMwirDetectorTest, Groups["Vehicle"].MaxAspectRatioRange) {
    GroundMwirDetector module;
    module.setGroups["Vehicle"].MaxAspectRatio(0);
    EXPECT_EQ(module.getGroups["Vehicle"].MaxAspectRatio(), 0);
    module.setGroups["Vehicle"].MaxAspectRatio(0);
    EXPECT_EQ(module.getGroups["Vehicle"].MaxAspectRatio(), 0);
    EXPECT_THROW(module.setGroups["Vehicle"].MaxAspectRatio(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Vehicle"].MaxAspectRatio(0 + 1), std::out_of_range);
}

// Test for Groups["Vehicle"].AttributeGroups in GroundMwirDetector
TEST(GroundMwirDetectorTest, Groups["Vehicle"].AttributeGroupsDefault) {
    GroundMwirDetector module;
    EXPECT_EQ(module.getGroups["Vehicle"].AttributeGroups(), 0);
}

TEST(GroundMwirDetectorTest, Groups["Vehicle"].AttributeGroupsRange) {
    GroundMwirDetector module;
    module.setGroups["Vehicle"].AttributeGroups(0);
    EXPECT_EQ(module.getGroups["Vehicle"].AttributeGroups(), 0);
    module.setGroups["Vehicle"].AttributeGroups(0);
    EXPECT_EQ(module.getGroups["Vehicle"].AttributeGroups(), 0);
    EXPECT_THROW(module.setGroups["Vehicle"].AttributeGroups(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Vehicle"].AttributeGroups(0 + 1), std::out_of_range);
}

// Test for Groups["Vehicle"].AttributeGroups["Type"].Attributes["N/A"] in GroundMwirDetector
TEST(GroundMwirDetectorTest, Groups["Vehicle"].AttributeGroups["Type"].Attributes["N/A"]Default) {
    GroundMwirDetector module;
    EXPECT_EQ(module.getGroups["Vehicle"].AttributeGroups["Type"].Attributes["N/A"](), 0);
}

TEST(GroundMwirDetectorTest, Groups["Vehicle"].AttributeGroups["Type"].Attributes["N/A"]Range) {
    GroundMwirDetector module;
    module.setGroups["Vehicle"].AttributeGroups["Type"].Attributes["N/A"](0);
    EXPECT_EQ(module.getGroups["Vehicle"].AttributeGroups["Type"].Attributes["N/A"](), 0);
    module.setGroups["Vehicle"].AttributeGroups["Type"].Attributes["N/A"](0);
    EXPECT_EQ(module.getGroups["Vehicle"].AttributeGroups["Type"].Attributes["N/A"](), 0);
    EXPECT_THROW(module.setGroups["Vehicle"].AttributeGroups["Type"].Attributes["N/A"](0 - 1), std::out_of_range);
    EXPECT_THROW(module.setGroups["Vehicle"].AttributeGroups["Type"].Attributes["N/A"](0 + 1), std::out_of_range);
}

// Test for AveragePixelValue[N/A] in GroundMwirDetector
TEST(GroundMwirDetectorTest, AveragePixelValue[N/A]Default) {
    GroundMwirDetector module;
    EXPECT_EQ(module.getAveragePixelValue[N/A](), 0);
}

TEST(GroundMwirDetectorTest, AveragePixelValue[N/A]Range) {
    GroundMwirDetector module;
    module.setAveragePixelValue[N/A](0);
    EXPECT_EQ(module.getAveragePixelValue[N/A](), 0);
    module.setAveragePixelValue[N/A](0);
    EXPECT_EQ(module.getAveragePixelValue[N/A](), 0);
    EXPECT_THROW(module.setAveragePixelValue[N/A](0 - 1), std::out_of_range);
    EXPECT_THROW(module.setAveragePixelValue[N/A](0 + 1), std::out_of_range);
}

// Test for PixelValueStandardDeviation[N/A] in GroundMwirDetector
TEST(GroundMwirDetectorTest, PixelValueStandardDeviation[N/A]Default) {
    GroundMwirDetector module;
    EXPECT_EQ(module.getPixelValueStandardDeviation[N/A](), 0);
}

TEST(GroundMwirDetectorTest, PixelValueStandardDeviation[N/A]Range) {
    GroundMwirDetector module;
    module.setPixelValueStandardDeviation[N/A](0);
    EXPECT_EQ(module.getPixelValueStandardDeviation[N/A](), 0);
    module.setPixelValueStandardDeviation[N/A](0);
    EXPECT_EQ(module.getPixelValueStandardDeviation[N/A](), 0);
    EXPECT_THROW(module.setPixelValueStandardDeviation[N/A](0 - 1), std::out_of_range);
    EXPECT_THROW(module.setPixelValueStandardDeviation[N/A](0 + 1), std::out_of_range);
}

// Test for MaxDetections in GroundMwirDetector
TEST(GroundMwirDetectorTest, MaxDetectionsDefault) {
    GroundMwirDetector module;
    EXPECT_EQ(module.getMaxDetections(), 0);
}

TEST(GroundMwirDetectorTest, MaxDetectionsRange) {
    GroundMwirDetector module;
    module.setMaxDetections(0);
    EXPECT_EQ(module.getMaxDetections(), 0);
    module.setMaxDetections(0);
    EXPECT_EQ(module.getMaxDetections(), 0);
    EXPECT_THROW(module.setMaxDetections(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setMaxDetections(0 + 1), std::out_of_range);
}

// Test for Enable in Vmd
TEST(VmdTest, EnableDefault) {
    Vmd module;
    EXPECT_EQ(module.getEnable(), 0);
}

TEST(VmdTest, EnableRange) {
    Vmd module;
    module.setEnable(0);
    EXPECT_EQ(module.getEnable(), 0);
    module.setEnable(0);
    EXPECT_EQ(module.getEnable(), 0);
    EXPECT_THROW(module.setEnable(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setEnable(0 + 1), std::out_of_range);
}

// Test for ScoreThreshold in Vmd
TEST(VmdTest, ScoreThresholdDefault) {
    Vmd module;
    EXPECT_EQ(module.getScoreThreshold(), 0);
}

TEST(VmdTest, ScoreThresholdRange) {
    Vmd module;
    module.setScoreThreshold(0);
    EXPECT_EQ(module.getScoreThreshold(), 0);
    module.setScoreThreshold(0);
    EXPECT_EQ(module.getScoreThreshold(), 0);
    EXPECT_THROW(module.setScoreThreshold(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setScoreThreshold(0 + 1), std::out_of_range);
}

// Test for MinWidth in Vmd
TEST(VmdTest, MinWidthDefault) {
    Vmd module;
    EXPECT_EQ(module.getMinWidth(), 0);
}

TEST(VmdTest, MinWidthRange) {
    Vmd module;
    module.setMinWidth(0);
    EXPECT_EQ(module.getMinWidth(), 0);
    module.setMinWidth(0);
    EXPECT_EQ(module.getMinWidth(), 0);
    EXPECT_THROW(module.setMinWidth(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setMinWidth(0 + 1), std::out_of_range);
}

// Test for MaxWidth in Vmd
TEST(VmdTest, MaxWidthDefault) {
    Vmd module;
    EXPECT_EQ(module.getMaxWidth(), 0);
}

TEST(VmdTest, MaxWidthRange) {
    Vmd module;
    module.setMaxWidth(0);
    EXPECT_EQ(module.getMaxWidth(), 0);
    module.setMaxWidth(0);
    EXPECT_EQ(module.getMaxWidth(), 0);
    EXPECT_THROW(module.setMaxWidth(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setMaxWidth(0 + 1), std::out_of_range);
}

// Test for MinHeight in Vmd
TEST(VmdTest, MinHeightDefault) {
    Vmd module;
    EXPECT_EQ(module.getMinHeight(), 0);
}

TEST(VmdTest, MinHeightRange) {
    Vmd module;
    module.setMinHeight(0);
    EXPECT_EQ(module.getMinHeight(), 0);
    module.setMinHeight(0);
    EXPECT_EQ(module.getMinHeight(), 0);
    EXPECT_THROW(module.setMinHeight(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setMinHeight(0 + 1), std::out_of_range);
}

// Test for MaxHeight in Vmd
TEST(VmdTest, MaxHeightDefault) {
    Vmd module;
    EXPECT_EQ(module.getMaxHeight(), 0);
}

TEST(VmdTest, MaxHeightRange) {
    Vmd module;
    module.setMaxHeight(0);
    EXPECT_EQ(module.getMaxHeight(), 0);
    module.setMaxHeight(0);
    EXPECT_EQ(module.getMaxHeight(), 0);
    EXPECT_THROW(module.setMaxHeight(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setMaxHeight(0 + 1), std::out_of_range);
}

// Test for Enable in GroundRgbPersonClassifier
TEST(GroundRgbPersonClassifierTest, EnableDefault) {
    GroundRgbPersonClassifier module;
    EXPECT_EQ(module.getEnable(), 0);
}

TEST(GroundRgbPersonClassifierTest, EnableRange) {
    GroundRgbPersonClassifier module;
    module.setEnable(0);
    EXPECT_EQ(module.getEnable(), 0);
    module.setEnable(0);
    EXPECT_EQ(module.getEnable(), 0);
    EXPECT_THROW(module.setEnable(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setEnable(0 + 1), std::out_of_range);
}

// Test for AdjustCropInPercentsOverride in GroundRgbPersonClassifier
TEST(GroundRgbPersonClassifierTest, AdjustCropInPercentsOverrideDefault) {
    GroundRgbPersonClassifier module;
    EXPECT_EQ(module.getAdjustCropInPercentsOverride(), 0);
}

TEST(GroundRgbPersonClassifierTest, AdjustCropInPercentsOverrideRange) {
    GroundRgbPersonClassifier module;
    module.setAdjustCropInPercentsOverride(0);
    EXPECT_EQ(module.getAdjustCropInPercentsOverride(), 0);
    module.setAdjustCropInPercentsOverride(0);
    EXPECT_EQ(module.getAdjustCropInPercentsOverride(), 0);
    EXPECT_THROW(module.setAdjustCropInPercentsOverride(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setAdjustCropInPercentsOverride(0 + 1), std::out_of_range);
}

// Test for AdjustCropInPercentsOverride.Width in GroundRgbPersonClassifier
TEST(GroundRgbPersonClassifierTest, AdjustCropInPercentsOverride.WidthDefault) {
    GroundRgbPersonClassifier module;
    EXPECT_EQ(module.getAdjustCropInPercentsOverride.Width(), 0);
}

TEST(GroundRgbPersonClassifierTest, AdjustCropInPercentsOverride.WidthRange) {
    GroundRgbPersonClassifier module;
    module.setAdjustCropInPercentsOverride.Width(0);
    EXPECT_EQ(module.getAdjustCropInPercentsOverride.Width(), 0);
    module.setAdjustCropInPercentsOverride.Width(0);
    EXPECT_EQ(module.getAdjustCropInPercentsOverride.Width(), 0);
    EXPECT_THROW(module.setAdjustCropInPercentsOverride.Width(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setAdjustCropInPercentsOverride.Width(0 + 1), std::out_of_range);
}

// Test for AdjustCropInPercentsOverride.Height in GroundRgbPersonClassifier
TEST(GroundRgbPersonClassifierTest, AdjustCropInPercentsOverride.HeightDefault) {
    GroundRgbPersonClassifier module;
    EXPECT_EQ(module.getAdjustCropInPercentsOverride.Height(), 0);
}

TEST(GroundRgbPersonClassifierTest, AdjustCropInPercentsOverride.HeightRange) {
    GroundRgbPersonClassifier module;
    module.setAdjustCropInPercentsOverride.Height(0);
    EXPECT_EQ(module.getAdjustCropInPercentsOverride.Height(), 0);
    module.setAdjustCropInPercentsOverride.Height(0);
    EXPECT_EQ(module.getAdjustCropInPercentsOverride.Height(), 0);
    EXPECT_THROW(module.setAdjustCropInPercentsOverride.Height(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setAdjustCropInPercentsOverride.Height(0 + 1), std::out_of_range);
}

// Test for Filter in GroundRgbPersonClassifier
TEST(GroundRgbPersonClassifierTest, FilterDefault) {
    GroundRgbPersonClassifier module;
    EXPECT_EQ(module.getFilter(), 0);
}

TEST(GroundRgbPersonClassifierTest, FilterRange) {
    GroundRgbPersonClassifier module;
    module.setFilter(0);
    EXPECT_EQ(module.getFilter(), 0);
    module.setFilter(0);
    EXPECT_EQ(module.getFilter(), 0);
    EXPECT_THROW(module.setFilter(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setFilter(0 + 1), std::out_of_range);
}

// Test for Filter.ScoreThreshold in GroundRgbPersonClassifier
TEST(GroundRgbPersonClassifierTest, Filter.ScoreThresholdDefault) {
    GroundRgbPersonClassifier module;
    EXPECT_EQ(module.getFilter.ScoreThreshold(), 0);
}

TEST(GroundRgbPersonClassifierTest, Filter.ScoreThresholdRange) {
    GroundRgbPersonClassifier module;
    module.setFilter.ScoreThreshold(0);
    EXPECT_EQ(module.getFilter.ScoreThreshold(), 0);
    module.setFilter.ScoreThreshold(0);
    EXPECT_EQ(module.getFilter.ScoreThreshold(), 0);
    EXPECT_THROW(module.setFilter.ScoreThreshold(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setFilter.ScoreThreshold(0 + 1), std::out_of_range);
}

// Test for Filter.MinWidth in GroundRgbPersonClassifier
TEST(GroundRgbPersonClassifierTest, Filter.MinWidthDefault) {
    GroundRgbPersonClassifier module;
    EXPECT_EQ(module.getFilter.MinWidth(), 0);
}

TEST(GroundRgbPersonClassifierTest, Filter.MinWidthRange) {
    GroundRgbPersonClassifier module;
    module.setFilter.MinWidth(0);
    EXPECT_EQ(module.getFilter.MinWidth(), 0);
    module.setFilter.MinWidth(0);
    EXPECT_EQ(module.getFilter.MinWidth(), 0);
    EXPECT_THROW(module.setFilter.MinWidth(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setFilter.MinWidth(0 + 1), std::out_of_range);
}

// Test for Filter.MaxWidth in GroundRgbPersonClassifier
TEST(GroundRgbPersonClassifierTest, Filter.MaxWidthDefault) {
    GroundRgbPersonClassifier module;
    EXPECT_EQ(module.getFilter.MaxWidth(), 0);
}

TEST(GroundRgbPersonClassifierTest, Filter.MaxWidthRange) {
    GroundRgbPersonClassifier module;
    module.setFilter.MaxWidth(0);
    EXPECT_EQ(module.getFilter.MaxWidth(), 0);
    module.setFilter.MaxWidth(0);
    EXPECT_EQ(module.getFilter.MaxWidth(), 0);
    EXPECT_THROW(module.setFilter.MaxWidth(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setFilter.MaxWidth(0 + 1), std::out_of_range);
}

// Test for Filter.MinHeight in GroundRgbPersonClassifier
TEST(GroundRgbPersonClassifierTest, Filter.MinHeightDefault) {
    GroundRgbPersonClassifier module;
    EXPECT_EQ(module.getFilter.MinHeight(), 0);
}

TEST(GroundRgbPersonClassifierTest, Filter.MinHeightRange) {
    GroundRgbPersonClassifier module;
    module.setFilter.MinHeight(0);
    EXPECT_EQ(module.getFilter.MinHeight(), 0);
    module.setFilter.MinHeight(0);
    EXPECT_EQ(module.getFilter.MinHeight(), 0);
    EXPECT_THROW(module.setFilter.MinHeight(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setFilter.MinHeight(0 + 1), std::out_of_range);
}

// Test for Filter.MaxHeight in GroundRgbPersonClassifier
TEST(GroundRgbPersonClassifierTest, Filter.MaxHeightDefault) {
    GroundRgbPersonClassifier module;
    EXPECT_EQ(module.getFilter.MaxHeight(), 0);
}

TEST(GroundRgbPersonClassifierTest, Filter.MaxHeightRange) {
    GroundRgbPersonClassifier module;
    module.setFilter.MaxHeight(0);
    EXPECT_EQ(module.getFilter.MaxHeight(), 0);
    module.setFilter.MaxHeight(0);
    EXPECT_EQ(module.getFilter.MaxHeight(), 0);
    EXPECT_THROW(module.setFilter.MaxHeight(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setFilter.MaxHeight(0 + 1), std::out_of_range);
}

// Test for Filter.MinAspectRatio in GroundRgbPersonClassifier
TEST(GroundRgbPersonClassifierTest, Filter.MinAspectRatioDefault) {
    GroundRgbPersonClassifier module;
    EXPECT_EQ(module.getFilter.MinAspectRatio(), 0);
}

TEST(GroundRgbPersonClassifierTest, Filter.MinAspectRatioRange) {
    GroundRgbPersonClassifier module;
    module.setFilter.MinAspectRatio(0);
    EXPECT_EQ(module.getFilter.MinAspectRatio(), 0);
    module.setFilter.MinAspectRatio(0);
    EXPECT_EQ(module.getFilter.MinAspectRatio(), 0);
    EXPECT_THROW(module.setFilter.MinAspectRatio(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setFilter.MinAspectRatio(0 + 1), std::out_of_range);
}

// Test for Filter.MaxAspectRatio in GroundRgbPersonClassifier
TEST(GroundRgbPersonClassifierTest, Filter.MaxAspectRatioDefault) {
    GroundRgbPersonClassifier module;
    EXPECT_EQ(module.getFilter.MaxAspectRatio(), 0);
}

TEST(GroundRgbPersonClassifierTest, Filter.MaxAspectRatioRange) {
    GroundRgbPersonClassifier module;
    module.setFilter.MaxAspectRatio(0);
    EXPECT_EQ(module.getFilter.MaxAspectRatio(), 0);
    module.setFilter.MaxAspectRatio(0);
    EXPECT_EQ(module.getFilter.MaxAspectRatio(), 0);
    EXPECT_THROW(module.setFilter.MaxAspectRatio(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setFilter.MaxAspectRatio(0 + 1), std::out_of_range);
}

// Test for ScoreThresholds["N/A"] in GroundRgbPersonClassifier
TEST(GroundRgbPersonClassifierTest, ScoreThresholds["N/A"]Default) {
    GroundRgbPersonClassifier module;
    EXPECT_EQ(module.getScoreThresholds["N/A"](), 0);
}

TEST(GroundRgbPersonClassifierTest, ScoreThresholds["N/A"]Range) {
    GroundRgbPersonClassifier module;
    module.setScoreThresholds["N/A"](0);
    EXPECT_EQ(module.getScoreThresholds["N/A"](), 0);
    module.setScoreThresholds["N/A"](0);
    EXPECT_EQ(module.getScoreThresholds["N/A"](), 0);
    EXPECT_THROW(module.setScoreThresholds["N/A"](0 - 1), std::out_of_range);
    EXPECT_THROW(module.setScoreThresholds["N/A"](0 + 1), std::out_of_range);
}

// Test for Enable in GroundRgbVehicleClassifier
TEST(GroundRgbVehicleClassifierTest, EnableDefault) {
    GroundRgbVehicleClassifier module;
    EXPECT_EQ(module.getEnable(), 0);
}

TEST(GroundRgbVehicleClassifierTest, EnableRange) {
    GroundRgbVehicleClassifier module;
    module.setEnable(0);
    EXPECT_EQ(module.getEnable(), 0);
    module.setEnable(0);
    EXPECT_EQ(module.getEnable(), 0);
    EXPECT_THROW(module.setEnable(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setEnable(0 + 1), std::out_of_range);
}

// Test for AdjustCropInPercentsOverride in GroundRgbVehicleClassifier
TEST(GroundRgbVehicleClassifierTest, AdjustCropInPercentsOverrideDefault) {
    GroundRgbVehicleClassifier module;
    EXPECT_EQ(module.getAdjustCropInPercentsOverride(), 0);
}

TEST(GroundRgbVehicleClassifierTest, AdjustCropInPercentsOverrideRange) {
    GroundRgbVehicleClassifier module;
    module.setAdjustCropInPercentsOverride(0);
    EXPECT_EQ(module.getAdjustCropInPercentsOverride(), 0);
    module.setAdjustCropInPercentsOverride(0);
    EXPECT_EQ(module.getAdjustCropInPercentsOverride(), 0);
    EXPECT_THROW(module.setAdjustCropInPercentsOverride(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setAdjustCropInPercentsOverride(0 + 1), std::out_of_range);
}

// Test for AdjustCropInPercentsOverride.Width in GroundRgbVehicleClassifier
TEST(GroundRgbVehicleClassifierTest, AdjustCropInPercentsOverride.WidthDefault) {
    GroundRgbVehicleClassifier module;
    EXPECT_EQ(module.getAdjustCropInPercentsOverride.Width(), 0);
}

TEST(GroundRgbVehicleClassifierTest, AdjustCropInPercentsOverride.WidthRange) {
    GroundRgbVehicleClassifier module;
    module.setAdjustCropInPercentsOverride.Width(0);
    EXPECT_EQ(module.getAdjustCropInPercentsOverride.Width(), 0);
    module.setAdjustCropInPercentsOverride.Width(0);
    EXPECT_EQ(module.getAdjustCropInPercentsOverride.Width(), 0);
    EXPECT_THROW(module.setAdjustCropInPercentsOverride.Width(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setAdjustCropInPercentsOverride.Width(0 + 1), std::out_of_range);
}

// Test for AdjustCropInPercentsOverride.Height in GroundRgbVehicleClassifier
TEST(GroundRgbVehicleClassifierTest, AdjustCropInPercentsOverride.HeightDefault) {
    GroundRgbVehicleClassifier module;
    EXPECT_EQ(module.getAdjustCropInPercentsOverride.Height(), 0);
}

TEST(GroundRgbVehicleClassifierTest, AdjustCropInPercentsOverride.HeightRange) {
    GroundRgbVehicleClassifier module;
    module.setAdjustCropInPercentsOverride.Height(0);
    EXPECT_EQ(module.getAdjustCropInPercentsOverride.Height(), 0);
    module.setAdjustCropInPercentsOverride.Height(0);
    EXPECT_EQ(module.getAdjustCropInPercentsOverride.Height(), 0);
    EXPECT_THROW(module.setAdjustCropInPercentsOverride.Height(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setAdjustCropInPercentsOverride.Height(0 + 1), std::out_of_range);
}

// Test for Filter in GroundRgbVehicleClassifier
TEST(GroundRgbVehicleClassifierTest, FilterDefault) {
    GroundRgbVehicleClassifier module;
    EXPECT_EQ(module.getFilter(), 0);
}

TEST(GroundRgbVehicleClassifierTest, FilterRange) {
    GroundRgbVehicleClassifier module;
    module.setFilter(0);
    EXPECT_EQ(module.getFilter(), 0);
    module.setFilter(0);
    EXPECT_EQ(module.getFilter(), 0);
    EXPECT_THROW(module.setFilter(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setFilter(0 + 1), std::out_of_range);
}

// Test for Filter.ScoreThreshold in GroundRgbVehicleClassifier
TEST(GroundRgbVehicleClassifierTest, Filter.ScoreThresholdDefault) {
    GroundRgbVehicleClassifier module;
    EXPECT_EQ(module.getFilter.ScoreThreshold(), 0);
}

TEST(GroundRgbVehicleClassifierTest, Filter.ScoreThresholdRange) {
    GroundRgbVehicleClassifier module;
    module.setFilter.ScoreThreshold(0);
    EXPECT_EQ(module.getFilter.ScoreThreshold(), 0);
    module.setFilter.ScoreThreshold(0);
    EXPECT_EQ(module.getFilter.ScoreThreshold(), 0);
    EXPECT_THROW(module.setFilter.ScoreThreshold(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setFilter.ScoreThreshold(0 + 1), std::out_of_range);
}

// Test for Filter.MinWidth in GroundRgbVehicleClassifier
TEST(GroundRgbVehicleClassifierTest, Filter.MinWidthDefault) {
    GroundRgbVehicleClassifier module;
    EXPECT_EQ(module.getFilter.MinWidth(), 0);
}

TEST(GroundRgbVehicleClassifierTest, Filter.MinWidthRange) {
    GroundRgbVehicleClassifier module;
    module.setFilter.MinWidth(0);
    EXPECT_EQ(module.getFilter.MinWidth(), 0);
    module.setFilter.MinWidth(0);
    EXPECT_EQ(module.getFilter.MinWidth(), 0);
    EXPECT_THROW(module.setFilter.MinWidth(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setFilter.MinWidth(0 + 1), std::out_of_range);
}

// Test for Filter.MaxWidth in GroundRgbVehicleClassifier
TEST(GroundRgbVehicleClassifierTest, Filter.MaxWidthDefault) {
    GroundRgbVehicleClassifier module;
    EXPECT_EQ(module.getFilter.MaxWidth(), 0);
}

TEST(GroundRgbVehicleClassifierTest, Filter.MaxWidthRange) {
    GroundRgbVehicleClassifier module;
    module.setFilter.MaxWidth(0);
    EXPECT_EQ(module.getFilter.MaxWidth(), 0);
    module.setFilter.MaxWidth(0);
    EXPECT_EQ(module.getFilter.MaxWidth(), 0);
    EXPECT_THROW(module.setFilter.MaxWidth(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setFilter.MaxWidth(0 + 1), std::out_of_range);
}

// Test for Filter.MinHeight in GroundRgbVehicleClassifier
TEST(GroundRgbVehicleClassifierTest, Filter.MinHeightDefault) {
    GroundRgbVehicleClassifier module;
    EXPECT_EQ(module.getFilter.MinHeight(), 0);
}

TEST(GroundRgbVehicleClassifierTest, Filter.MinHeightRange) {
    GroundRgbVehicleClassifier module;
    module.setFilter.MinHeight(0);
    EXPECT_EQ(module.getFilter.MinHeight(), 0);
    module.setFilter.MinHeight(0);
    EXPECT_EQ(module.getFilter.MinHeight(), 0);
    EXPECT_THROW(module.setFilter.MinHeight(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setFilter.MinHeight(0 + 1), std::out_of_range);
}

// Test for Filter.MaxHeight in GroundRgbVehicleClassifier
TEST(GroundRgbVehicleClassifierTest, Filter.MaxHeightDefault) {
    GroundRgbVehicleClassifier module;
    EXPECT_EQ(module.getFilter.MaxHeight(), 0);
}

TEST(GroundRgbVehicleClassifierTest, Filter.MaxHeightRange) {
    GroundRgbVehicleClassifier module;
    module.setFilter.MaxHeight(0);
    EXPECT_EQ(module.getFilter.MaxHeight(), 0);
    module.setFilter.MaxHeight(0);
    EXPECT_EQ(module.getFilter.MaxHeight(), 0);
    EXPECT_THROW(module.setFilter.MaxHeight(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setFilter.MaxHeight(0 + 1), std::out_of_range);
}

// Test for Filter.MinAspectRatio in GroundRgbVehicleClassifier
TEST(GroundRgbVehicleClassifierTest, Filter.MinAspectRatioDefault) {
    GroundRgbVehicleClassifier module;
    EXPECT_EQ(module.getFilter.MinAspectRatio(), 0);
}

TEST(GroundRgbVehicleClassifierTest, Filter.MinAspectRatioRange) {
    GroundRgbVehicleClassifier module;
    module.setFilter.MinAspectRatio(0);
    EXPECT_EQ(module.getFilter.MinAspectRatio(), 0);
    module.setFilter.MinAspectRatio(0);
    EXPECT_EQ(module.getFilter.MinAspectRatio(), 0);
    EXPECT_THROW(module.setFilter.MinAspectRatio(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setFilter.MinAspectRatio(0 + 1), std::out_of_range);
}

// Test for Filter.MaxAspectRatio in GroundRgbVehicleClassifier
TEST(GroundRgbVehicleClassifierTest, Filter.MaxAspectRatioDefault) {
    GroundRgbVehicleClassifier module;
    EXPECT_EQ(module.getFilter.MaxAspectRatio(), 0);
}

TEST(GroundRgbVehicleClassifierTest, Filter.MaxAspectRatioRange) {
    GroundRgbVehicleClassifier module;
    module.setFilter.MaxAspectRatio(0);
    EXPECT_EQ(module.getFilter.MaxAspectRatio(), 0);
    module.setFilter.MaxAspectRatio(0);
    EXPECT_EQ(module.getFilter.MaxAspectRatio(), 0);
    EXPECT_THROW(module.setFilter.MaxAspectRatio(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setFilter.MaxAspectRatio(0 + 1), std::out_of_range);
}

// Test for ScoreThresholds["N/A"] in GroundRgbVehicleClassifier
TEST(GroundRgbVehicleClassifierTest, ScoreThresholds["N/A"]Default) {
    GroundRgbVehicleClassifier module;
    EXPECT_EQ(module.getScoreThresholds["N/A"](), 0);
}

TEST(GroundRgbVehicleClassifierTest, ScoreThresholds["N/A"]Range) {
    GroundRgbVehicleClassifier module;
    module.setScoreThresholds["N/A"](0);
    EXPECT_EQ(module.getScoreThresholds["N/A"](), 0);
    module.setScoreThresholds["N/A"](0);
    EXPECT_EQ(module.getScoreThresholds["N/A"](), 0);
    EXPECT_THROW(module.setScoreThresholds["N/A"](0 - 1), std::out_of_range);
    EXPECT_THROW(module.setScoreThresholds["N/A"](0 + 1), std::out_of_range);
}

// Test for Enable in SingleObjectTracker
TEST(SingleObjectTrackerTest, EnableDefault) {
    SingleObjectTracker module;
    EXPECT_EQ(module.getEnable(), 0);
}

TEST(SingleObjectTrackerTest, EnableRange) {
    SingleObjectTracker module;
    module.setEnable(0);
    EXPECT_EQ(module.getEnable(), 0);
    module.setEnable(0);
    EXPECT_EQ(module.getEnable(), 0);
    EXPECT_THROW(module.setEnable(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setEnable(0 + 1), std::out_of_range);
}

// Test for UpdateScoreThreshold in SingleObjectTracker
TEST(SingleObjectTrackerTest, UpdateScoreThresholdDefault) {
    SingleObjectTracker module;
    EXPECT_EQ(module.getUpdateScoreThreshold(), 0);
}

TEST(SingleObjectTrackerTest, UpdateScoreThresholdRange) {
    SingleObjectTracker module;
    module.setUpdateScoreThreshold(0);
    EXPECT_EQ(module.getUpdateScoreThreshold(), 0);
    module.setUpdateScoreThreshold(0);
    EXPECT_EQ(module.getUpdateScoreThreshold(), 0);
    EXPECT_THROW(module.setUpdateScoreThreshold(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setUpdateScoreThreshold(0 + 1), std::out_of_range);
}

// Test for OutputFramerate in TrackerRate
TEST(TrackerRateTest, OutputFramerateDefault) {
    TrackerRate module;
    EXPECT_EQ(module.getOutputFramerate(), 0);
}

TEST(TrackerRateTest, OutputFramerateRange) {
    TrackerRate module;
    module.setOutputFramerate(0);
    EXPECT_EQ(module.getOutputFramerate(), 0);
    module.setOutputFramerate(0);
    EXPECT_EQ(module.getOutputFramerate(), 0);
    EXPECT_THROW(module.setOutputFramerate(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setOutputFramerate(0 + 1), std::out_of_range);
}

// Test for Enable in PersonTracker
TEST(PersonTrackerTest, EnableDefault) {
    PersonTracker module;
    EXPECT_EQ(module.getEnable(), 0);
}

TEST(PersonTrackerTest, EnableRange) {
    PersonTracker module;
    module.setEnable(0);
    EXPECT_EQ(module.getEnable(), 0);
    module.setEnable(0);
    EXPECT_EQ(module.getEnable(), 0);
    EXPECT_THROW(module.setEnable(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setEnable(0 + 1), std::out_of_range);
}

// Test for MaxTimeSinceUpdateToReportMs in PersonTracker
TEST(PersonTrackerTest, MaxTimeSinceUpdateToReportMsDefault) {
    PersonTracker module;
    EXPECT_EQ(module.getMaxTimeSinceUpdateToReportMs(), 0);
}

TEST(PersonTrackerTest, MaxTimeSinceUpdateToReportMsRange) {
    PersonTracker module;
    module.setMaxTimeSinceUpdateToReportMs(0);
    EXPECT_EQ(module.getMaxTimeSinceUpdateToReportMs(), 0);
    module.setMaxTimeSinceUpdateToReportMs(0);
    EXPECT_EQ(module.getMaxTimeSinceUpdateToReportMs(), 0);
    EXPECT_THROW(module.setMaxTimeSinceUpdateToReportMs(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setMaxTimeSinceUpdateToReportMs(0 + 1), std::out_of_range);
}

// Test for Enable in VehicleTracker
TEST(VehicleTrackerTest, EnableDefault) {
    VehicleTracker module;
    EXPECT_EQ(module.getEnable(), 0);
}

TEST(VehicleTrackerTest, EnableRange) {
    VehicleTracker module;
    module.setEnable(0);
    EXPECT_EQ(module.getEnable(), 0);
    module.setEnable(0);
    EXPECT_EQ(module.getEnable(), 0);
    EXPECT_THROW(module.setEnable(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setEnable(0 + 1), std::out_of_range);
}

// Test for MaxTimeSinceUpdateToReportMs in VehicleTracker
TEST(VehicleTrackerTest, MaxTimeSinceUpdateToReportMsDefault) {
    VehicleTracker module;
    EXPECT_EQ(module.getMaxTimeSinceUpdateToReportMs(), 0);
}

TEST(VehicleTrackerTest, MaxTimeSinceUpdateToReportMsRange) {
    VehicleTracker module;
    module.setMaxTimeSinceUpdateToReportMs(0);
    EXPECT_EQ(module.getMaxTimeSinceUpdateToReportMs(), 0);
    module.setMaxTimeSinceUpdateToReportMs(0);
    EXPECT_EQ(module.getMaxTimeSinceUpdateToReportMs(), 0);
    EXPECT_THROW(module.setMaxTimeSinceUpdateToReportMs(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setMaxTimeSinceUpdateToReportMs(0 + 1), std::out_of_range);
}

// Test for Enable in VmdTracker
TEST(VmdTrackerTest, EnableDefault) {
    VmdTracker module;
    EXPECT_EQ(module.getEnable(), 0);
}

TEST(VmdTrackerTest, EnableRange) {
    VmdTracker module;
    module.setEnable(0);
    EXPECT_EQ(module.getEnable(), 0);
    module.setEnable(0);
    EXPECT_EQ(module.getEnable(), 0);
    EXPECT_THROW(module.setEnable(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setEnable(0 + 1), std::out_of_range);
}

// Test for MaxTimeSinceUpdateToReportMs in VmdTracker
TEST(VmdTrackerTest, MaxTimeSinceUpdateToReportMsDefault) {
    VmdTracker module;
    EXPECT_EQ(module.getMaxTimeSinceUpdateToReportMs(), 0);
}

TEST(VmdTrackerTest, MaxTimeSinceUpdateToReportMsRange) {
    VmdTracker module;
    module.setMaxTimeSinceUpdateToReportMs(0);
    EXPECT_EQ(module.getMaxTimeSinceUpdateToReportMs(), 0);
    module.setMaxTimeSinceUpdateToReportMs(0);
    EXPECT_EQ(module.getMaxTimeSinceUpdateToReportMs(), 0);
    EXPECT_THROW(module.setMaxTimeSinceUpdateToReportMs(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setMaxTimeSinceUpdateToReportMs(0 + 1), std::out_of_range);
}

// Test for OutputFilter[0] in TrackerPostprocessor
TEST(TrackerPostprocessorTest, OutputFilter[0]Default) {
    TrackerPostprocessor module;
    EXPECT_EQ(module.getOutputFilter[0](), 0);
}

TEST(TrackerPostprocessorTest, OutputFilter[0]Range) {
    TrackerPostprocessor module;
    module.setOutputFilter[0](0);
    EXPECT_EQ(module.getOutputFilter[0](), 0);
    module.setOutputFilter[0](0);
    EXPECT_EQ(module.getOutputFilter[0](), 0);
    EXPECT_THROW(module.setOutputFilter[0](0 - 1), std::out_of_range);
    EXPECT_THROW(module.setOutputFilter[0](0 + 1), std::out_of_range);
}

// Test for Enable in RgbReid
TEST(RgbReidTest, EnableDefault) {
    RgbReid module;
    EXPECT_EQ(module.getEnable(), 0);
}

TEST(RgbReidTest, EnableRange) {
    RgbReid module;
    module.setEnable(0);
    EXPECT_EQ(module.getEnable(), 0);
    module.setEnable(0);
    EXPECT_EQ(module.getEnable(), 0);
    EXPECT_THROW(module.setEnable(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setEnable(0 + 1), std::out_of_range);
}

// Test for Mode in RgbReid
TEST(RgbReidTest, ModeDefault) {
    RgbReid module;
    EXPECT_EQ(module.getMode(), 0);
}

TEST(RgbReidTest, ModeRange) {
    RgbReid module;
    module.setMode(0);
    EXPECT_EQ(module.getMode(), 0);
    module.setMode(0);
    EXPECT_EQ(module.getMode(), 0);
    EXPECT_THROW(module.setMode(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setMode(0 + 1), std::out_of_range);
}

// Test for SourceData in TracksPublisher
TEST(TracksPublisherTest, SourceDataDefault) {
    TracksPublisher module;
    EXPECT_EQ(module.getSourceData(), 0);
}

TEST(TracksPublisherTest, SourceDataRange) {
    TracksPublisher module;
    module.setSourceData(0);
    EXPECT_EQ(module.getSourceData(), 0);
    module.setSourceData(0);
    EXPECT_EQ(module.getSourceData(), 0);
    EXPECT_THROW(module.setSourceData(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setSourceData(0 + 1), std::out_of_range);
}

// Test for SamplingFrequencyMs in VehicleTelemetry
TEST(VehicleTelemetryTest, SamplingFrequencyMsDefault) {
    VehicleTelemetry module;
    EXPECT_EQ(module.getSamplingFrequencyMs(), 0);
}

TEST(VehicleTelemetryTest, SamplingFrequencyMsRange) {
    VehicleTelemetry module;
    module.setSamplingFrequencyMs(0);
    EXPECT_EQ(module.getSamplingFrequencyMs(), 0);
    module.setSamplingFrequencyMs(0);
    EXPECT_EQ(module.getSamplingFrequencyMs(), 0);
    EXPECT_THROW(module.setSamplingFrequencyMs(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setSamplingFrequencyMs(0 + 1), std::out_of_range);
}

// Test for TargetWidth in CefRenderer
TEST(CefRendererTest, TargetWidthDefault) {
    CefRenderer module;
    EXPECT_EQ(module.getTargetWidth(), 0);
}

TEST(CefRendererTest, TargetWidthRange) {
    CefRenderer module;
    module.setTargetWidth(0);
    EXPECT_EQ(module.getTargetWidth(), 0);
    module.setTargetWidth(0);
    EXPECT_EQ(module.getTargetWidth(), 0);
    EXPECT_THROW(module.setTargetWidth(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setTargetWidth(0 + 1), std::out_of_range);
}

// Test for TargetHeight in CefRenderer
TEST(CefRendererTest, TargetHeightDefault) {
    CefRenderer module;
    EXPECT_EQ(module.getTargetHeight(), 0);
}

TEST(CefRendererTest, TargetHeightRange) {
    CefRenderer module;
    module.setTargetHeight(0);
    EXPECT_EQ(module.getTargetHeight(), 0);
    module.setTargetHeight(0);
    EXPECT_EQ(module.getTargetHeight(), 0);
    EXPECT_THROW(module.setTargetHeight(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setTargetHeight(0 + 1), std::out_of_range);
}

// Test for BrowserFrameRate in CefRenderer
TEST(CefRendererTest, BrowserFrameRateDefault) {
    CefRenderer module;
    EXPECT_EQ(module.getBrowserFrameRate(), 0);
}

TEST(CefRendererTest, BrowserFrameRateRange) {
    CefRenderer module;
    module.setBrowserFrameRate(0);
    EXPECT_EQ(module.getBrowserFrameRate(), 0);
    module.setBrowserFrameRate(0);
    EXPECT_EQ(module.getBrowserFrameRate(), 0);
    EXPECT_THROW(module.setBrowserFrameRate(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBrowserFrameRate(0 + 1), std::out_of_range);
}

// Test for Normalization in CefRenderer
TEST(CefRendererTest, NormalizationDefault) {
    CefRenderer module;
    EXPECT_EQ(module.getNormalization(), 0);
}

TEST(CefRendererTest, NormalizationRange) {
    CefRenderer module;
    module.setNormalization(0);
    EXPECT_EQ(module.getNormalization(), 0);
    module.setNormalization(0);
    EXPECT_EQ(module.getNormalization(), 0);
    EXPECT_THROW(module.setNormalization(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setNormalization(0 + 1), std::out_of_range);
}

// Test for Normalization.Type in CefRenderer
TEST(CefRendererTest, Normalization.TypeDefault) {
    CefRenderer module;
    EXPECT_EQ(module.getNormalization.Type(), 0);
}

TEST(CefRendererTest, Normalization.TypeRange) {
    CefRenderer module;
    module.setNormalization.Type(0);
    EXPECT_EQ(module.getNormalization.Type(), 0);
    module.setNormalization.Type(0);
    EXPECT_EQ(module.getNormalization.Type(), 0);
    EXPECT_THROW(module.setNormalization.Type(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setNormalization.Type(0 + 1), std::out_of_range);
}

// Test for Normalization.Alpha in CefRenderer
TEST(CefRendererTest, Normalization.AlphaDefault) {
    CefRenderer module;
    EXPECT_EQ(module.getNormalization.Alpha(), 0);
}

TEST(CefRendererTest, Normalization.AlphaRange) {
    CefRenderer module;
    module.setNormalization.Alpha(0);
    EXPECT_EQ(module.getNormalization.Alpha(), 0);
    module.setNormalization.Alpha(0);
    EXPECT_EQ(module.getNormalization.Alpha(), 0);
    EXPECT_THROW(module.setNormalization.Alpha(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setNormalization.Alpha(0 + 1), std::out_of_range);
}

// Test for Normalization.Beta in CefRenderer
TEST(CefRendererTest, Normalization.BetaDefault) {
    CefRenderer module;
    EXPECT_EQ(module.getNormalization.Beta(), 0);
}

TEST(CefRendererTest, Normalization.BetaRange) {
    CefRenderer module;
    module.setNormalization.Beta(0);
    EXPECT_EQ(module.getNormalization.Beta(), 0);
    module.setNormalization.Beta(0);
    EXPECT_EQ(module.getNormalization.Beta(), 0);
    EXPECT_THROW(module.setNormalization.Beta(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setNormalization.Beta(0 + 1), std::out_of_range);
}

// Test for Normalization.StdCropSize in CefRenderer
TEST(CefRendererTest, Normalization.StdCropSizeDefault) {
    CefRenderer module;
    EXPECT_EQ(module.getNormalization.StdCropSize(), 0);
}

TEST(CefRendererTest, Normalization.StdCropSizeRange) {
    CefRenderer module;
    module.setNormalization.StdCropSize(0);
    EXPECT_EQ(module.getNormalization.StdCropSize(), 0);
    module.setNormalization.StdCropSize(0);
    EXPECT_EQ(module.getNormalization.StdCropSize(), 0);
    EXPECT_THROW(module.setNormalization.StdCropSize(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setNormalization.StdCropSize(0 + 1), std::out_of_range);
}

// Test for TargetWidth in CvRenderer
TEST(CvRendererTest, TargetWidthDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getTargetWidth(), 0);
}

TEST(CvRendererTest, TargetWidthRange) {
    CvRenderer module;
    module.setTargetWidth(0);
    EXPECT_EQ(module.getTargetWidth(), 0);
    module.setTargetWidth(0);
    EXPECT_EQ(module.getTargetWidth(), 0);
    EXPECT_THROW(module.setTargetWidth(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setTargetWidth(0 + 1), std::out_of_range);
}

// Test for TargetHeight in CvRenderer
TEST(CvRendererTest, TargetHeightDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getTargetHeight(), 0);
}

TEST(CvRendererTest, TargetHeightRange) {
    CvRenderer module;
    module.setTargetHeight(0);
    EXPECT_EQ(module.getTargetHeight(), 0);
    module.setTargetHeight(0);
    EXPECT_EQ(module.getTargetHeight(), 0);
    EXPECT_THROW(module.setTargetHeight(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setTargetHeight(0 + 1), std::out_of_range);
}

// Test for SkipAllRendering in CvRenderer
TEST(CvRendererTest, SkipAllRenderingDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getSkipAllRendering(), 0);
}

TEST(CvRendererTest, SkipAllRenderingRange) {
    CvRenderer module;
    module.setSkipAllRendering(0);
    EXPECT_EQ(module.getSkipAllRendering(), 0);
    module.setSkipAllRendering(0);
    EXPECT_EQ(module.getSkipAllRendering(), 0);
    EXPECT_THROW(module.setSkipAllRendering(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setSkipAllRendering(0 + 1), std::out_of_range);
}

// Test for Normalization in CvRenderer
TEST(CvRendererTest, NormalizationDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getNormalization(), 0);
}

TEST(CvRendererTest, NormalizationRange) {
    CvRenderer module;
    module.setNormalization(0);
    EXPECT_EQ(module.getNormalization(), 0);
    module.setNormalization(0);
    EXPECT_EQ(module.getNormalization(), 0);
    EXPECT_THROW(module.setNormalization(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setNormalization(0 + 1), std::out_of_range);
}

// Test for Normalization.Type in CvRenderer
TEST(CvRendererTest, Normalization.TypeDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getNormalization.Type(), 0);
}

TEST(CvRendererTest, Normalization.TypeRange) {
    CvRenderer module;
    module.setNormalization.Type(0);
    EXPECT_EQ(module.getNormalization.Type(), 0);
    module.setNormalization.Type(0);
    EXPECT_EQ(module.getNormalization.Type(), 0);
    EXPECT_THROW(module.setNormalization.Type(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setNormalization.Type(0 + 1), std::out_of_range);
}

// Test for Normalization.Alpha in CvRenderer
TEST(CvRendererTest, Normalization.AlphaDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getNormalization.Alpha(), 0);
}

TEST(CvRendererTest, Normalization.AlphaRange) {
    CvRenderer module;
    module.setNormalization.Alpha(0);
    EXPECT_EQ(module.getNormalization.Alpha(), 0);
    module.setNormalization.Alpha(0);
    EXPECT_EQ(module.getNormalization.Alpha(), 0);
    EXPECT_THROW(module.setNormalization.Alpha(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setNormalization.Alpha(0 + 1), std::out_of_range);
}

// Test for Normalization.Beta in CvRenderer
TEST(CvRendererTest, Normalization.BetaDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getNormalization.Beta(), 0);
}

TEST(CvRendererTest, Normalization.BetaRange) {
    CvRenderer module;
    module.setNormalization.Beta(0);
    EXPECT_EQ(module.getNormalization.Beta(), 0);
    module.setNormalization.Beta(0);
    EXPECT_EQ(module.getNormalization.Beta(), 0);
    EXPECT_THROW(module.setNormalization.Beta(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setNormalization.Beta(0 + 1), std::out_of_range);
}

// Test for Normalization.StdCropSize in CvRenderer
TEST(CvRendererTest, Normalization.StdCropSizeDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getNormalization.StdCropSize(), 0);
}

TEST(CvRendererTest, Normalization.StdCropSizeRange) {
    CvRenderer module;
    module.setNormalization.StdCropSize(0);
    EXPECT_EQ(module.getNormalization.StdCropSize(), 0);
    module.setNormalization.StdCropSize(0);
    EXPECT_EQ(module.getNormalization.StdCropSize(), 0);
    EXPECT_THROW(module.setNormalization.StdCropSize(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setNormalization.StdCropSize(0 + 1), std::out_of_range);
}

// Test for DrawDetections in CvRenderer
TEST(CvRendererTest, DrawDetectionsDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getDrawDetections(), 0);
}

TEST(CvRendererTest, DrawDetectionsRange) {
    CvRenderer module;
    module.setDrawDetections(0);
    EXPECT_EQ(module.getDrawDetections(), 0);
    module.setDrawDetections(0);
    EXPECT_EQ(module.getDrawDetections(), 0);
    EXPECT_THROW(module.setDrawDetections(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setDrawDetections(0 + 1), std::out_of_range);
}

// Test for DrawTracks in CvRenderer
TEST(CvRendererTest, DrawTracksDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getDrawTracks(), 0);
}

TEST(CvRendererTest, DrawTracksRange) {
    CvRenderer module;
    module.setDrawTracks(0);
    EXPECT_EQ(module.getDrawTracks(), 0);
    module.setDrawTracks(0);
    EXPECT_EQ(module.getDrawTracks(), 0);
    EXPECT_THROW(module.setDrawTracks(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setDrawTracks(0 + 1), std::out_of_range);
}

// Test for MarkPredictedTracks in CvRenderer
TEST(CvRendererTest, MarkPredictedTracksDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getMarkPredictedTracks(), 0);
}

TEST(CvRendererTest, MarkPredictedTracksRange) {
    CvRenderer module;
    module.setMarkPredictedTracks(0);
    EXPECT_EQ(module.getMarkPredictedTracks(), 0);
    module.setMarkPredictedTracks(0);
    EXPECT_EQ(module.getMarkPredictedTracks(), 0);
    EXPECT_THROW(module.setMarkPredictedTracks(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setMarkPredictedTracks(0 + 1), std::out_of_range);
}

// Test for PrintClass in CvRenderer
TEST(CvRendererTest, PrintClassDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getPrintClass(), 0);
}

TEST(CvRendererTest, PrintClassRange) {
    CvRenderer module;
    module.setPrintClass(0);
    EXPECT_EQ(module.getPrintClass(), 0);
    module.setPrintClass(0);
    EXPECT_EQ(module.getPrintClass(), 0);
    EXPECT_THROW(module.setPrintClass(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setPrintClass(0 + 1), std::out_of_range);
}

// Test for PrintScore in CvRenderer
TEST(CvRendererTest, PrintScoreDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getPrintScore(), 0);
}

TEST(CvRendererTest, PrintScoreRange) {
    CvRenderer module;
    module.setPrintScore(0);
    EXPECT_EQ(module.getPrintScore(), 0);
    module.setPrintScore(0);
    EXPECT_EQ(module.getPrintScore(), 0);
    EXPECT_THROW(module.setPrintScore(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setPrintScore(0 + 1), std::out_of_range);
}

// Test for PrintTrackId in CvRenderer
TEST(CvRendererTest, PrintTrackIdDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getPrintTrackId(), 0);
}

TEST(CvRendererTest, PrintTrackIdRange) {
    CvRenderer module;
    module.setPrintTrackId(0);
    EXPECT_EQ(module.getPrintTrackId(), 0);
    module.setPrintTrackId(0);
    EXPECT_EQ(module.getPrintTrackId(), 0);
    EXPECT_THROW(module.setPrintTrackId(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setPrintTrackId(0 + 1), std::out_of_range);
}

// Test for ColorTrack in CvRenderer
TEST(CvRendererTest, ColorTrackDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getColorTrack(), 0);
}

TEST(CvRendererTest, ColorTrackRange) {
    CvRenderer module;
    module.setColorTrack(0);
    EXPECT_EQ(module.getColorTrack(), 0);
    module.setColorTrack(0);
    EXPECT_EQ(module.getColorTrack(), 0);
    EXPECT_THROW(module.setColorTrack(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setColorTrack(0 + 1), std::out_of_range);
}

// Test for DrawTrackVelocity in CvRenderer
TEST(CvRendererTest, DrawTrackVelocityDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getDrawTrackVelocity(), 0);
}

TEST(CvRendererTest, DrawTrackVelocityRange) {
    CvRenderer module;
    module.setDrawTrackVelocity(0);
    EXPECT_EQ(module.getDrawTrackVelocity(), 0);
    module.setDrawTrackVelocity(0);
    EXPECT_EQ(module.getDrawTrackVelocity(), 0);
    EXPECT_THROW(module.setDrawTrackVelocity(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setDrawTrackVelocity(0 + 1), std::out_of_range);
}

// Test for TrackVelocityFactor in CvRenderer
TEST(CvRendererTest, TrackVelocityFactorDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getTrackVelocityFactor(), 0);
}

TEST(CvRendererTest, TrackVelocityFactorRange) {
    CvRenderer module;
    module.setTrackVelocityFactor(0);
    EXPECT_EQ(module.getTrackVelocityFactor(), 0);
    module.setTrackVelocityFactor(0);
    EXPECT_EQ(module.getTrackVelocityFactor(), 0);
    EXPECT_THROW(module.setTrackVelocityFactor(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setTrackVelocityFactor(0 + 1), std::out_of_range);
}

// Test for PrintDistance in CvRenderer
TEST(CvRendererTest, PrintDistanceDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getPrintDistance(), 0);
}

TEST(CvRendererTest, PrintDistanceRange) {
    CvRenderer module;
    module.setPrintDistance(0);
    EXPECT_EQ(module.getPrintDistance(), 0);
    module.setPrintDistance(0);
    EXPECT_EQ(module.getPrintDistance(), 0);
    EXPECT_THROW(module.setPrintDistance(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setPrintDistance(0 + 1), std::out_of_range);
}

// Test for PrintAttributes in CvRenderer
TEST(CvRendererTest, PrintAttributesDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getPrintAttributes(), 0);
}

TEST(CvRendererTest, PrintAttributesRange) {
    CvRenderer module;
    module.setPrintAttributes(0);
    EXPECT_EQ(module.getPrintAttributes(), 0);
    module.setPrintAttributes(0);
    EXPECT_EQ(module.getPrintAttributes(), 0);
    EXPECT_THROW(module.setPrintAttributes(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setPrintAttributes(0 + 1), std::out_of_range);
}

// Test for PrintReidStatus in CvRenderer
TEST(CvRendererTest, PrintReidStatusDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getPrintReidStatus(), 0);
}

TEST(CvRendererTest, PrintReidStatusRange) {
    CvRenderer module;
    module.setPrintReidStatus(0);
    EXPECT_EQ(module.getPrintReidStatus(), 0);
    module.setPrintReidStatus(0);
    EXPECT_EQ(module.getPrintReidStatus(), 0);
    EXPECT_THROW(module.setPrintReidStatus(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setPrintReidStatus(0 + 1), std::out_of_range);
}

// Test for DrawCenterOfMass in CvRenderer
TEST(CvRendererTest, DrawCenterOfMassDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getDrawCenterOfMass(), 0);
}

TEST(CvRendererTest, DrawCenterOfMassRange) {
    CvRenderer module;
    module.setDrawCenterOfMass(0);
    EXPECT_EQ(module.getDrawCenterOfMass(), 0);
    module.setDrawCenterOfMass(0);
    EXPECT_EQ(module.getDrawCenterOfMass(), 0);
    EXPECT_THROW(module.setDrawCenterOfMass(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setDrawCenterOfMass(0 + 1), std::out_of_range);
}

// Test for CenterOfMassRadius in CvRenderer
TEST(CvRendererTest, CenterOfMassRadiusDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getCenterOfMassRadius(), 0);
}

TEST(CvRendererTest, CenterOfMassRadiusRange) {
    CvRenderer module;
    module.setCenterOfMassRadius(0);
    EXPECT_EQ(module.getCenterOfMassRadius(), 0);
    module.setCenterOfMassRadius(0);
    EXPECT_EQ(module.getCenterOfMassRadius(), 0);
    EXPECT_THROW(module.setCenterOfMassRadius(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setCenterOfMassRadius(0 + 1), std::out_of_range);
}

// Test for ReidHotCold in CvRenderer
TEST(CvRendererTest, ReidHotColdDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getReidHotCold(), 0);
}

TEST(CvRendererTest, ReidHotColdRange) {
    CvRenderer module;
    module.setReidHotCold(0);
    EXPECT_EQ(module.getReidHotCold(), 0);
    module.setReidHotCold(0);
    EXPECT_EQ(module.getReidHotCold(), 0);
    EXPECT_THROW(module.setReidHotCold(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setReidHotCold(0 + 1), std::out_of_range);
}

// Test for ReidHotCold.SkipRendering in CvRenderer
TEST(CvRendererTest, ReidHotCold.SkipRenderingDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getReidHotCold.SkipRendering(), 0);
}

TEST(CvRendererTest, ReidHotCold.SkipRenderingRange) {
    CvRenderer module;
    module.setReidHotCold.SkipRendering(0);
    EXPECT_EQ(module.getReidHotCold.SkipRendering(), 0);
    module.setReidHotCold.SkipRendering(0);
    EXPECT_EQ(module.getReidHotCold.SkipRendering(), 0);
    EXPECT_THROW(module.setReidHotCold.SkipRendering(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setReidHotCold.SkipRendering(0 + 1), std::out_of_range);
}

// Test for ReidHotCold.PrintScore in CvRenderer
TEST(CvRendererTest, ReidHotCold.PrintScoreDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getReidHotCold.PrintScore(), 0);
}

TEST(CvRendererTest, ReidHotCold.PrintScoreRange) {
    CvRenderer module;
    module.setReidHotCold.PrintScore(0);
    EXPECT_EQ(module.getReidHotCold.PrintScore(), 0);
    module.setReidHotCold.PrintScore(0);
    EXPECT_EQ(module.getReidHotCold.PrintScore(), 0);
    EXPECT_THROW(module.setReidHotCold.PrintScore(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setReidHotCold.PrintScore(0 + 1), std::out_of_range);
}

// Test for ReidHotCold.ColorLineThickness in CvRenderer
TEST(CvRendererTest, ReidHotCold.ColorLineThicknessDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getReidHotCold.ColorLineThickness(), 0);
}

TEST(CvRendererTest, ReidHotCold.ColorLineThicknessRange) {
    CvRenderer module;
    module.setReidHotCold.ColorLineThickness(0);
    EXPECT_EQ(module.getReidHotCold.ColorLineThickness(), 0);
    module.setReidHotCold.ColorLineThickness(0);
    EXPECT_EQ(module.getReidHotCold.ColorLineThickness(), 0);
    EXPECT_THROW(module.setReidHotCold.ColorLineThickness(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setReidHotCold.ColorLineThickness(0 + 1), std::out_of_range);
}

// Test for ReidHotCold.ColorLineDistance in CvRenderer
TEST(CvRendererTest, ReidHotCold.ColorLineDistanceDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getReidHotCold.ColorLineDistance(), 0);
}

TEST(CvRendererTest, ReidHotCold.ColorLineDistanceRange) {
    CvRenderer module;
    module.setReidHotCold.ColorLineDistance(0);
    EXPECT_EQ(module.getReidHotCold.ColorLineDistance(), 0);
    module.setReidHotCold.ColorLineDistance(0);
    EXPECT_EQ(module.getReidHotCold.ColorLineDistance(), 0);
    EXPECT_THROW(module.setReidHotCold.ColorLineDistance(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setReidHotCold.ColorLineDistance(0 + 1), std::out_of_range);
}

// Test for ReidHotCold.ColorMap in CvRenderer
TEST(CvRendererTest, ReidHotCold.ColorMapDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getReidHotCold.ColorMap(), 0);
}

TEST(CvRendererTest, ReidHotCold.ColorMapRange) {
    CvRenderer module;
    module.setReidHotCold.ColorMap(0);
    EXPECT_EQ(module.getReidHotCold.ColorMap(), 0);
    module.setReidHotCold.ColorMap(0);
    EXPECT_EQ(module.getReidHotCold.ColorMap(), 0);
    EXPECT_THROW(module.setReidHotCold.ColorMap(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setReidHotCold.ColorMap(0 + 1), std::out_of_range);
}

// Test for Cross in CvRenderer
TEST(CvRendererTest, CrossDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getCross(), 0);
}

TEST(CvRendererTest, CrossRange) {
    CvRenderer module;
    module.setCross(0);
    EXPECT_EQ(module.getCross(), 0);
    module.setCross(0);
    EXPECT_EQ(module.getCross(), 0);
    EXPECT_THROW(module.setCross(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setCross(0 + 1), std::out_of_range);
}

// Test for Cross.SkipRendering in CvRenderer
TEST(CvRendererTest, Cross.SkipRenderingDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getCross.SkipRendering(), 0);
}

TEST(CvRendererTest, Cross.SkipRenderingRange) {
    CvRenderer module;
    module.setCross.SkipRendering(0);
    EXPECT_EQ(module.getCross.SkipRendering(), 0);
    module.setCross.SkipRendering(0);
    EXPECT_EQ(module.getCross.SkipRendering(), 0);
    EXPECT_THROW(module.setCross.SkipRendering(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setCross.SkipRendering(0 + 1), std::out_of_range);
}

// Test for Cross.Color in CvRenderer
TEST(CvRendererTest, Cross.ColorDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getCross.Color(), 0);
}

TEST(CvRendererTest, Cross.ColorRange) {
    CvRenderer module;
    module.setCross.Color(0);
    EXPECT_EQ(module.getCross.Color(), 0);
    module.setCross.Color(0);
    EXPECT_EQ(module.getCross.Color(), 0);
    EXPECT_THROW(module.setCross.Color(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setCross.Color(0 + 1), std::out_of_range);
}

// Test for Cross.SizeInPercents in CvRenderer
TEST(CvRendererTest, Cross.SizeInPercentsDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getCross.SizeInPercents(), 0);
}

TEST(CvRendererTest, Cross.SizeInPercentsRange) {
    CvRenderer module;
    module.setCross.SizeInPercents(0);
    EXPECT_EQ(module.getCross.SizeInPercents(), 0);
    module.setCross.SizeInPercents(0);
    EXPECT_EQ(module.getCross.SizeInPercents(), 0);
    EXPECT_THROW(module.setCross.SizeInPercents(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setCross.SizeInPercents(0 + 1), std::out_of_range);
}

// Test for Cross.Thickness in CvRenderer
TEST(CvRendererTest, Cross.ThicknessDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getCross.Thickness(), 0);
}

TEST(CvRendererTest, Cross.ThicknessRange) {
    CvRenderer module;
    module.setCross.Thickness(0);
    EXPECT_EQ(module.getCross.Thickness(), 0);
    module.setCross.Thickness(0);
    EXPECT_EQ(module.getCross.Thickness(), 0);
    EXPECT_THROW(module.setCross.Thickness(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setCross.Thickness(0 + 1), std::out_of_range);
}

// Test for DetectorRoi in CvRenderer
TEST(CvRendererTest, DetectorRoiDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getDetectorRoi(), 0);
}

TEST(CvRendererTest, DetectorRoiRange) {
    CvRenderer module;
    module.setDetectorRoi(0);
    EXPECT_EQ(module.getDetectorRoi(), 0);
    module.setDetectorRoi(0);
    EXPECT_EQ(module.getDetectorRoi(), 0);
    EXPECT_THROW(module.setDetectorRoi(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setDetectorRoi(0 + 1), std::out_of_range);
}

// Test for DetectorRoi.SkipRendering in CvRenderer
TEST(CvRendererTest, DetectorRoi.SkipRenderingDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getDetectorRoi.SkipRendering(), 0);
}

TEST(CvRendererTest, DetectorRoi.SkipRenderingRange) {
    CvRenderer module;
    module.setDetectorRoi.SkipRendering(0);
    EXPECT_EQ(module.getDetectorRoi.SkipRendering(), 0);
    module.setDetectorRoi.SkipRendering(0);
    EXPECT_EQ(module.getDetectorRoi.SkipRendering(), 0);
    EXPECT_THROW(module.setDetectorRoi.SkipRendering(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setDetectorRoi.SkipRendering(0 + 1), std::out_of_range);
}

// Test for DetectorRoi.Color in CvRenderer
TEST(CvRendererTest, DetectorRoi.ColorDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getDetectorRoi.Color(), 0);
}

TEST(CvRendererTest, DetectorRoi.ColorRange) {
    CvRenderer module;
    module.setDetectorRoi.Color(0);
    EXPECT_EQ(module.getDetectorRoi.Color(), 0);
    module.setDetectorRoi.Color(0);
    EXPECT_EQ(module.getDetectorRoi.Color(), 0);
    EXPECT_THROW(module.setDetectorRoi.Color(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setDetectorRoi.Color(0 + 1), std::out_of_range);
}

// Test for DetectorRoi.LineThickness in CvRenderer
TEST(CvRendererTest, DetectorRoi.LineThicknessDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getDetectorRoi.LineThickness(), 0);
}

TEST(CvRendererTest, DetectorRoi.LineThicknessRange) {
    CvRenderer module;
    module.setDetectorRoi.LineThickness(0);
    EXPECT_EQ(module.getDetectorRoi.LineThickness(), 0);
    module.setDetectorRoi.LineThickness(0);
    EXPECT_EQ(module.getDetectorRoi.LineThickness(), 0);
    EXPECT_THROW(module.setDetectorRoi.LineThickness(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setDetectorRoi.LineThickness(0 + 1), std::out_of_range);
}

// Test for DetectorRoi.HideOutside in CvRenderer
TEST(CvRendererTest, DetectorRoi.HideOutsideDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getDetectorRoi.HideOutside(), 0);
}

TEST(CvRendererTest, DetectorRoi.HideOutsideRange) {
    CvRenderer module;
    module.setDetectorRoi.HideOutside(0);
    EXPECT_EQ(module.getDetectorRoi.HideOutside(), 0);
    module.setDetectorRoi.HideOutside(0);
    EXPECT_EQ(module.getDetectorRoi.HideOutside(), 0);
    EXPECT_THROW(module.setDetectorRoi.HideOutside(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setDetectorRoi.HideOutside(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes in CvRenderer
TEST(CvRendererTest, BoundingBoxesDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes(), 0);
}

TEST(CvRendererTest, BoundingBoxesRange) {
    CvRenderer module;
    module.setBoundingBoxes(0);
    EXPECT_EQ(module.getBoundingBoxes(), 0);
    module.setBoundingBoxes(0);
    EXPECT_EQ(module.getBoundingBoxes(), 0);
    EXPECT_THROW(module.setBoundingBoxes(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes[""].SkipRendering in CvRenderer
TEST(CvRendererTest, BoundingBoxes[""].SkipRenderingDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes[""].SkipRendering(), 0);
}

TEST(CvRendererTest, BoundingBoxes[""].SkipRenderingRange) {
    CvRenderer module;
    module.setBoundingBoxes[""].SkipRendering(0);
    EXPECT_EQ(module.getBoundingBoxes[""].SkipRendering(), 0);
    module.setBoundingBoxes[""].SkipRendering(0);
    EXPECT_EQ(module.getBoundingBoxes[""].SkipRendering(), 0);
    EXPECT_THROW(module.setBoundingBoxes[""].SkipRendering(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes[""].SkipRendering(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes[""].BoxColor in CvRenderer
TEST(CvRendererTest, BoundingBoxes[""].BoxColorDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes[""].BoxColor(), 0);
}

TEST(CvRendererTest, BoundingBoxes[""].BoxColorRange) {
    CvRenderer module;
    module.setBoundingBoxes[""].BoxColor(0);
    EXPECT_EQ(module.getBoundingBoxes[""].BoxColor(), 0);
    module.setBoundingBoxes[""].BoxColor(0);
    EXPECT_EQ(module.getBoundingBoxes[""].BoxColor(), 0);
    EXPECT_THROW(module.setBoundingBoxes[""].BoxColor(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes[""].BoxColor(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes[""].LineThickness in CvRenderer
TEST(CvRendererTest, BoundingBoxes[""].LineThicknessDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes[""].LineThickness(), 0);
}

TEST(CvRendererTest, BoundingBoxes[""].LineThicknessRange) {
    CvRenderer module;
    module.setBoundingBoxes[""].LineThickness(0);
    EXPECT_EQ(module.getBoundingBoxes[""].LineThickness(), 0);
    module.setBoundingBoxes[""].LineThickness(0);
    EXPECT_EQ(module.getBoundingBoxes[""].LineThickness(), 0);
    EXPECT_THROW(module.setBoundingBoxes[""].LineThickness(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes[""].LineThickness(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes[""].TextOffsetX in CvRenderer
TEST(CvRendererTest, BoundingBoxes[""].TextOffsetXDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes[""].TextOffsetX(), 0);
}

TEST(CvRendererTest, BoundingBoxes[""].TextOffsetXRange) {
    CvRenderer module;
    module.setBoundingBoxes[""].TextOffsetX(0);
    EXPECT_EQ(module.getBoundingBoxes[""].TextOffsetX(), 0);
    module.setBoundingBoxes[""].TextOffsetX(0);
    EXPECT_EQ(module.getBoundingBoxes[""].TextOffsetX(), 0);
    EXPECT_THROW(module.setBoundingBoxes[""].TextOffsetX(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes[""].TextOffsetX(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes[""].TextOffsetY in CvRenderer
TEST(CvRendererTest, BoundingBoxes[""].TextOffsetYDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes[""].TextOffsetY(), 0);
}

TEST(CvRendererTest, BoundingBoxes[""].TextOffsetYRange) {
    CvRenderer module;
    module.setBoundingBoxes[""].TextOffsetY(0);
    EXPECT_EQ(module.getBoundingBoxes[""].TextOffsetY(), 0);
    module.setBoundingBoxes[""].TextOffsetY(0);
    EXPECT_EQ(module.getBoundingBoxes[""].TextOffsetY(), 0);
    EXPECT_THROW(module.setBoundingBoxes[""].TextOffsetY(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes[""].TextOffsetY(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes[""].BottomTextOffsetY in CvRenderer
TEST(CvRendererTest, BoundingBoxes[""].BottomTextOffsetYDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes[""].BottomTextOffsetY(), 0);
}

TEST(CvRendererTest, BoundingBoxes[""].BottomTextOffsetYRange) {
    CvRenderer module;
    module.setBoundingBoxes[""].BottomTextOffsetY(0);
    EXPECT_EQ(module.getBoundingBoxes[""].BottomTextOffsetY(), 0);
    module.setBoundingBoxes[""].BottomTextOffsetY(0);
    EXPECT_EQ(module.getBoundingBoxes[""].BottomTextOffsetY(), 0);
    EXPECT_THROW(module.setBoundingBoxes[""].BottomTextOffsetY(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes[""].BottomTextOffsetY(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes[""].FontColor in CvRenderer
TEST(CvRendererTest, BoundingBoxes[""].FontColorDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes[""].FontColor(), 0);
}

TEST(CvRendererTest, BoundingBoxes[""].FontColorRange) {
    CvRenderer module;
    module.setBoundingBoxes[""].FontColor(0);
    EXPECT_EQ(module.getBoundingBoxes[""].FontColor(), 0);
    module.setBoundingBoxes[""].FontColor(0);
    EXPECT_EQ(module.getBoundingBoxes[""].FontColor(), 0);
    EXPECT_THROW(module.setBoundingBoxes[""].FontColor(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes[""].FontColor(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes[""].FontScale in CvRenderer
TEST(CvRendererTest, BoundingBoxes[""].FontScaleDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes[""].FontScale(), 0);
}

TEST(CvRendererTest, BoundingBoxes[""].FontScaleRange) {
    CvRenderer module;
    module.setBoundingBoxes[""].FontScale(0);
    EXPECT_EQ(module.getBoundingBoxes[""].FontScale(), 0);
    module.setBoundingBoxes[""].FontScale(0);
    EXPECT_EQ(module.getBoundingBoxes[""].FontScale(), 0);
    EXPECT_THROW(module.setBoundingBoxes[""].FontScale(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes[""].FontScale(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes[""].FontThickness in CvRenderer
TEST(CvRendererTest, BoundingBoxes[""].FontThicknessDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes[""].FontThickness(), 0);
}

TEST(CvRendererTest, BoundingBoxes[""].FontThicknessRange) {
    CvRenderer module;
    module.setBoundingBoxes[""].FontThickness(0);
    EXPECT_EQ(module.getBoundingBoxes[""].FontThickness(), 0);
    module.setBoundingBoxes[""].FontThickness(0);
    EXPECT_EQ(module.getBoundingBoxes[""].FontThickness(), 0);
    EXPECT_THROW(module.setBoundingBoxes[""].FontThickness(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes[""].FontThickness(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Person"].SkipRendering in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Person"].SkipRenderingDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Person"].SkipRendering(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Person"].SkipRenderingRange) {
    CvRenderer module;
    module.setBoundingBoxes["Person"].SkipRendering(0);
    EXPECT_EQ(module.getBoundingBoxes["Person"].SkipRendering(), 0);
    module.setBoundingBoxes["Person"].SkipRendering(0);
    EXPECT_EQ(module.getBoundingBoxes["Person"].SkipRendering(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Person"].SkipRendering(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Person"].SkipRendering(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Person"].BoxColor in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Person"].BoxColorDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Person"].BoxColor(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Person"].BoxColorRange) {
    CvRenderer module;
    module.setBoundingBoxes["Person"].BoxColor(0);
    EXPECT_EQ(module.getBoundingBoxes["Person"].BoxColor(), 0);
    module.setBoundingBoxes["Person"].BoxColor(0);
    EXPECT_EQ(module.getBoundingBoxes["Person"].BoxColor(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Person"].BoxColor(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Person"].BoxColor(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Person"].LineThickness in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Person"].LineThicknessDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Person"].LineThickness(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Person"].LineThicknessRange) {
    CvRenderer module;
    module.setBoundingBoxes["Person"].LineThickness(0);
    EXPECT_EQ(module.getBoundingBoxes["Person"].LineThickness(), 0);
    module.setBoundingBoxes["Person"].LineThickness(0);
    EXPECT_EQ(module.getBoundingBoxes["Person"].LineThickness(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Person"].LineThickness(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Person"].LineThickness(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Person"].TextOffsetX in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Person"].TextOffsetXDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Person"].TextOffsetX(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Person"].TextOffsetXRange) {
    CvRenderer module;
    module.setBoundingBoxes["Person"].TextOffsetX(0);
    EXPECT_EQ(module.getBoundingBoxes["Person"].TextOffsetX(), 0);
    module.setBoundingBoxes["Person"].TextOffsetX(0);
    EXPECT_EQ(module.getBoundingBoxes["Person"].TextOffsetX(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Person"].TextOffsetX(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Person"].TextOffsetX(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Person"].TextOffsetY in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Person"].TextOffsetYDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Person"].TextOffsetY(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Person"].TextOffsetYRange) {
    CvRenderer module;
    module.setBoundingBoxes["Person"].TextOffsetY(0);
    EXPECT_EQ(module.getBoundingBoxes["Person"].TextOffsetY(), 0);
    module.setBoundingBoxes["Person"].TextOffsetY(0);
    EXPECT_EQ(module.getBoundingBoxes["Person"].TextOffsetY(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Person"].TextOffsetY(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Person"].TextOffsetY(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Person"].BottomTextOffsetY in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Person"].BottomTextOffsetYDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Person"].BottomTextOffsetY(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Person"].BottomTextOffsetYRange) {
    CvRenderer module;
    module.setBoundingBoxes["Person"].BottomTextOffsetY(0);
    EXPECT_EQ(module.getBoundingBoxes["Person"].BottomTextOffsetY(), 0);
    module.setBoundingBoxes["Person"].BottomTextOffsetY(0);
    EXPECT_EQ(module.getBoundingBoxes["Person"].BottomTextOffsetY(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Person"].BottomTextOffsetY(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Person"].BottomTextOffsetY(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Person"].FontColor in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Person"].FontColorDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Person"].FontColor(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Person"].FontColorRange) {
    CvRenderer module;
    module.setBoundingBoxes["Person"].FontColor(0);
    EXPECT_EQ(module.getBoundingBoxes["Person"].FontColor(), 0);
    module.setBoundingBoxes["Person"].FontColor(0);
    EXPECT_EQ(module.getBoundingBoxes["Person"].FontColor(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Person"].FontColor(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Person"].FontColor(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Person"].FontScale in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Person"].FontScaleDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Person"].FontScale(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Person"].FontScaleRange) {
    CvRenderer module;
    module.setBoundingBoxes["Person"].FontScale(0);
    EXPECT_EQ(module.getBoundingBoxes["Person"].FontScale(), 0);
    module.setBoundingBoxes["Person"].FontScale(0);
    EXPECT_EQ(module.getBoundingBoxes["Person"].FontScale(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Person"].FontScale(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Person"].FontScale(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Person"].FontThickness in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Person"].FontThicknessDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Person"].FontThickness(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Person"].FontThicknessRange) {
    CvRenderer module;
    module.setBoundingBoxes["Person"].FontThickness(0);
    EXPECT_EQ(module.getBoundingBoxes["Person"].FontThickness(), 0);
    module.setBoundingBoxes["Person"].FontThickness(0);
    EXPECT_EQ(module.getBoundingBoxes["Person"].FontThickness(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Person"].FontThickness(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Person"].FontThickness(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Vehicle"].SkipRendering in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Vehicle"].SkipRenderingDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Vehicle"].SkipRendering(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Vehicle"].SkipRenderingRange) {
    CvRenderer module;
    module.setBoundingBoxes["Vehicle"].SkipRendering(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle"].SkipRendering(), 0);
    module.setBoundingBoxes["Vehicle"].SkipRendering(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle"].SkipRendering(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle"].SkipRendering(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle"].SkipRendering(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Vehicle"].BoxColor in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Vehicle"].BoxColorDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Vehicle"].BoxColor(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Vehicle"].BoxColorRange) {
    CvRenderer module;
    module.setBoundingBoxes["Vehicle"].BoxColor(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle"].BoxColor(), 0);
    module.setBoundingBoxes["Vehicle"].BoxColor(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle"].BoxColor(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle"].BoxColor(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle"].BoxColor(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Vehicle"].LineThickness in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Vehicle"].LineThicknessDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Vehicle"].LineThickness(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Vehicle"].LineThicknessRange) {
    CvRenderer module;
    module.setBoundingBoxes["Vehicle"].LineThickness(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle"].LineThickness(), 0);
    module.setBoundingBoxes["Vehicle"].LineThickness(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle"].LineThickness(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle"].LineThickness(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle"].LineThickness(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Vehicle"].TextOffsetX in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Vehicle"].TextOffsetXDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Vehicle"].TextOffsetX(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Vehicle"].TextOffsetXRange) {
    CvRenderer module;
    module.setBoundingBoxes["Vehicle"].TextOffsetX(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle"].TextOffsetX(), 0);
    module.setBoundingBoxes["Vehicle"].TextOffsetX(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle"].TextOffsetX(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle"].TextOffsetX(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle"].TextOffsetX(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Vehicle"].TextOffsetY in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Vehicle"].TextOffsetYDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Vehicle"].TextOffsetY(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Vehicle"].TextOffsetYRange) {
    CvRenderer module;
    module.setBoundingBoxes["Vehicle"].TextOffsetY(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle"].TextOffsetY(), 0);
    module.setBoundingBoxes["Vehicle"].TextOffsetY(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle"].TextOffsetY(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle"].TextOffsetY(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle"].TextOffsetY(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Vehicle"].BottomTextOffsetY in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Vehicle"].BottomTextOffsetYDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Vehicle"].BottomTextOffsetY(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Vehicle"].BottomTextOffsetYRange) {
    CvRenderer module;
    module.setBoundingBoxes["Vehicle"].BottomTextOffsetY(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle"].BottomTextOffsetY(), 0);
    module.setBoundingBoxes["Vehicle"].BottomTextOffsetY(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle"].BottomTextOffsetY(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle"].BottomTextOffsetY(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle"].BottomTextOffsetY(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Vehicle"].FontColor in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Vehicle"].FontColorDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Vehicle"].FontColor(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Vehicle"].FontColorRange) {
    CvRenderer module;
    module.setBoundingBoxes["Vehicle"].FontColor(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle"].FontColor(), 0);
    module.setBoundingBoxes["Vehicle"].FontColor(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle"].FontColor(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle"].FontColor(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle"].FontColor(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Vehicle"].FontScale in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Vehicle"].FontScaleDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Vehicle"].FontScale(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Vehicle"].FontScaleRange) {
    CvRenderer module;
    module.setBoundingBoxes["Vehicle"].FontScale(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle"].FontScale(), 0);
    module.setBoundingBoxes["Vehicle"].FontScale(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle"].FontScale(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle"].FontScale(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle"].FontScale(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Vehicle"].FontThickness in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Vehicle"].FontThicknessDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Vehicle"].FontThickness(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Vehicle"].FontThicknessRange) {
    CvRenderer module;
    module.setBoundingBoxes["Vehicle"].FontThickness(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle"].FontThickness(), 0);
    module.setBoundingBoxes["Vehicle"].FontThickness(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle"].FontThickness(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle"].FontThickness(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle"].FontThickness(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Vehicle/heavy"].SkipRendering in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Vehicle/heavy"].SkipRenderingDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/heavy"].SkipRendering(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Vehicle/heavy"].SkipRenderingRange) {
    CvRenderer module;
    module.setBoundingBoxes["Vehicle/heavy"].SkipRendering(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/heavy"].SkipRendering(), 0);
    module.setBoundingBoxes["Vehicle/heavy"].SkipRendering(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/heavy"].SkipRendering(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/heavy"].SkipRendering(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/heavy"].SkipRendering(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Vehicle/heavy"].BoxColor in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Vehicle/heavy"].BoxColorDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/heavy"].BoxColor(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Vehicle/heavy"].BoxColorRange) {
    CvRenderer module;
    module.setBoundingBoxes["Vehicle/heavy"].BoxColor(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/heavy"].BoxColor(), 0);
    module.setBoundingBoxes["Vehicle/heavy"].BoxColor(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/heavy"].BoxColor(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/heavy"].BoxColor(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/heavy"].BoxColor(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Vehicle/heavy"].LineThickness in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Vehicle/heavy"].LineThicknessDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/heavy"].LineThickness(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Vehicle/heavy"].LineThicknessRange) {
    CvRenderer module;
    module.setBoundingBoxes["Vehicle/heavy"].LineThickness(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/heavy"].LineThickness(), 0);
    module.setBoundingBoxes["Vehicle/heavy"].LineThickness(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/heavy"].LineThickness(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/heavy"].LineThickness(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/heavy"].LineThickness(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Vehicle/heavy"].TextOffsetX in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Vehicle/heavy"].TextOffsetXDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/heavy"].TextOffsetX(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Vehicle/heavy"].TextOffsetXRange) {
    CvRenderer module;
    module.setBoundingBoxes["Vehicle/heavy"].TextOffsetX(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/heavy"].TextOffsetX(), 0);
    module.setBoundingBoxes["Vehicle/heavy"].TextOffsetX(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/heavy"].TextOffsetX(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/heavy"].TextOffsetX(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/heavy"].TextOffsetX(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Vehicle/heavy"].TextOffsetY in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Vehicle/heavy"].TextOffsetYDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/heavy"].TextOffsetY(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Vehicle/heavy"].TextOffsetYRange) {
    CvRenderer module;
    module.setBoundingBoxes["Vehicle/heavy"].TextOffsetY(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/heavy"].TextOffsetY(), 0);
    module.setBoundingBoxes["Vehicle/heavy"].TextOffsetY(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/heavy"].TextOffsetY(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/heavy"].TextOffsetY(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/heavy"].TextOffsetY(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Vehicle/heavy"].BottomTextOffsetY in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Vehicle/heavy"].BottomTextOffsetYDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/heavy"].BottomTextOffsetY(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Vehicle/heavy"].BottomTextOffsetYRange) {
    CvRenderer module;
    module.setBoundingBoxes["Vehicle/heavy"].BottomTextOffsetY(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/heavy"].BottomTextOffsetY(), 0);
    module.setBoundingBoxes["Vehicle/heavy"].BottomTextOffsetY(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/heavy"].BottomTextOffsetY(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/heavy"].BottomTextOffsetY(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/heavy"].BottomTextOffsetY(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Vehicle/heavy"].FontColor in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Vehicle/heavy"].FontColorDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/heavy"].FontColor(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Vehicle/heavy"].FontColorRange) {
    CvRenderer module;
    module.setBoundingBoxes["Vehicle/heavy"].FontColor(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/heavy"].FontColor(), 0);
    module.setBoundingBoxes["Vehicle/heavy"].FontColor(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/heavy"].FontColor(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/heavy"].FontColor(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/heavy"].FontColor(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Vehicle/heavy"].FontScale in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Vehicle/heavy"].FontScaleDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/heavy"].FontScale(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Vehicle/heavy"].FontScaleRange) {
    CvRenderer module;
    module.setBoundingBoxes["Vehicle/heavy"].FontScale(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/heavy"].FontScale(), 0);
    module.setBoundingBoxes["Vehicle/heavy"].FontScale(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/heavy"].FontScale(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/heavy"].FontScale(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/heavy"].FontScale(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Vehicle/heavy"].FontThickness in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Vehicle/heavy"].FontThicknessDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/heavy"].FontThickness(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Vehicle/heavy"].FontThicknessRange) {
    CvRenderer module;
    module.setBoundingBoxes["Vehicle/heavy"].FontThickness(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/heavy"].FontThickness(), 0);
    module.setBoundingBoxes["Vehicle/heavy"].FontThickness(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/heavy"].FontThickness(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/heavy"].FontThickness(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/heavy"].FontThickness(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["TwoWheeled"].SkipRendering in CvRenderer
TEST(CvRendererTest, BoundingBoxes["TwoWheeled"].SkipRenderingDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["TwoWheeled"].SkipRendering(), 0);
}

TEST(CvRendererTest, BoundingBoxes["TwoWheeled"].SkipRenderingRange) {
    CvRenderer module;
    module.setBoundingBoxes["TwoWheeled"].SkipRendering(0);
    EXPECT_EQ(module.getBoundingBoxes["TwoWheeled"].SkipRendering(), 0);
    module.setBoundingBoxes["TwoWheeled"].SkipRendering(0);
    EXPECT_EQ(module.getBoundingBoxes["TwoWheeled"].SkipRendering(), 0);
    EXPECT_THROW(module.setBoundingBoxes["TwoWheeled"].SkipRendering(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["TwoWheeled"].SkipRendering(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["TwoWheeled"].BoxColor in CvRenderer
TEST(CvRendererTest, BoundingBoxes["TwoWheeled"].BoxColorDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["TwoWheeled"].BoxColor(), 0);
}

TEST(CvRendererTest, BoundingBoxes["TwoWheeled"].BoxColorRange) {
    CvRenderer module;
    module.setBoundingBoxes["TwoWheeled"].BoxColor(0);
    EXPECT_EQ(module.getBoundingBoxes["TwoWheeled"].BoxColor(), 0);
    module.setBoundingBoxes["TwoWheeled"].BoxColor(0);
    EXPECT_EQ(module.getBoundingBoxes["TwoWheeled"].BoxColor(), 0);
    EXPECT_THROW(module.setBoundingBoxes["TwoWheeled"].BoxColor(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["TwoWheeled"].BoxColor(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["TwoWheeled"].LineThickness in CvRenderer
TEST(CvRendererTest, BoundingBoxes["TwoWheeled"].LineThicknessDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["TwoWheeled"].LineThickness(), 0);
}

TEST(CvRendererTest, BoundingBoxes["TwoWheeled"].LineThicknessRange) {
    CvRenderer module;
    module.setBoundingBoxes["TwoWheeled"].LineThickness(0);
    EXPECT_EQ(module.getBoundingBoxes["TwoWheeled"].LineThickness(), 0);
    module.setBoundingBoxes["TwoWheeled"].LineThickness(0);
    EXPECT_EQ(module.getBoundingBoxes["TwoWheeled"].LineThickness(), 0);
    EXPECT_THROW(module.setBoundingBoxes["TwoWheeled"].LineThickness(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["TwoWheeled"].LineThickness(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["TwoWheeled"].TextOffsetX in CvRenderer
TEST(CvRendererTest, BoundingBoxes["TwoWheeled"].TextOffsetXDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["TwoWheeled"].TextOffsetX(), 0);
}

TEST(CvRendererTest, BoundingBoxes["TwoWheeled"].TextOffsetXRange) {
    CvRenderer module;
    module.setBoundingBoxes["TwoWheeled"].TextOffsetX(0);
    EXPECT_EQ(module.getBoundingBoxes["TwoWheeled"].TextOffsetX(), 0);
    module.setBoundingBoxes["TwoWheeled"].TextOffsetX(0);
    EXPECT_EQ(module.getBoundingBoxes["TwoWheeled"].TextOffsetX(), 0);
    EXPECT_THROW(module.setBoundingBoxes["TwoWheeled"].TextOffsetX(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["TwoWheeled"].TextOffsetX(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["TwoWheeled"].TextOffsetY in CvRenderer
TEST(CvRendererTest, BoundingBoxes["TwoWheeled"].TextOffsetYDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["TwoWheeled"].TextOffsetY(), 0);
}

TEST(CvRendererTest, BoundingBoxes["TwoWheeled"].TextOffsetYRange) {
    CvRenderer module;
    module.setBoundingBoxes["TwoWheeled"].TextOffsetY(0);
    EXPECT_EQ(module.getBoundingBoxes["TwoWheeled"].TextOffsetY(), 0);
    module.setBoundingBoxes["TwoWheeled"].TextOffsetY(0);
    EXPECT_EQ(module.getBoundingBoxes["TwoWheeled"].TextOffsetY(), 0);
    EXPECT_THROW(module.setBoundingBoxes["TwoWheeled"].TextOffsetY(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["TwoWheeled"].TextOffsetY(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["TwoWheeled"].BottomTextOffsetY in CvRenderer
TEST(CvRendererTest, BoundingBoxes["TwoWheeled"].BottomTextOffsetYDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["TwoWheeled"].BottomTextOffsetY(), 0);
}

TEST(CvRendererTest, BoundingBoxes["TwoWheeled"].BottomTextOffsetYRange) {
    CvRenderer module;
    module.setBoundingBoxes["TwoWheeled"].BottomTextOffsetY(0);
    EXPECT_EQ(module.getBoundingBoxes["TwoWheeled"].BottomTextOffsetY(), 0);
    module.setBoundingBoxes["TwoWheeled"].BottomTextOffsetY(0);
    EXPECT_EQ(module.getBoundingBoxes["TwoWheeled"].BottomTextOffsetY(), 0);
    EXPECT_THROW(module.setBoundingBoxes["TwoWheeled"].BottomTextOffsetY(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["TwoWheeled"].BottomTextOffsetY(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["TwoWheeled"].FontColor in CvRenderer
TEST(CvRendererTest, BoundingBoxes["TwoWheeled"].FontColorDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["TwoWheeled"].FontColor(), 0);
}

TEST(CvRendererTest, BoundingBoxes["TwoWheeled"].FontColorRange) {
    CvRenderer module;
    module.setBoundingBoxes["TwoWheeled"].FontColor(0);
    EXPECT_EQ(module.getBoundingBoxes["TwoWheeled"].FontColor(), 0);
    module.setBoundingBoxes["TwoWheeled"].FontColor(0);
    EXPECT_EQ(module.getBoundingBoxes["TwoWheeled"].FontColor(), 0);
    EXPECT_THROW(module.setBoundingBoxes["TwoWheeled"].FontColor(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["TwoWheeled"].FontColor(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["TwoWheeled"].FontScale in CvRenderer
TEST(CvRendererTest, BoundingBoxes["TwoWheeled"].FontScaleDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["TwoWheeled"].FontScale(), 0);
}

TEST(CvRendererTest, BoundingBoxes["TwoWheeled"].FontScaleRange) {
    CvRenderer module;
    module.setBoundingBoxes["TwoWheeled"].FontScale(0);
    EXPECT_EQ(module.getBoundingBoxes["TwoWheeled"].FontScale(), 0);
    module.setBoundingBoxes["TwoWheeled"].FontScale(0);
    EXPECT_EQ(module.getBoundingBoxes["TwoWheeled"].FontScale(), 0);
    EXPECT_THROW(module.setBoundingBoxes["TwoWheeled"].FontScale(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["TwoWheeled"].FontScale(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["TwoWheeled"].FontThickness in CvRenderer
TEST(CvRendererTest, BoundingBoxes["TwoWheeled"].FontThicknessDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["TwoWheeled"].FontThickness(), 0);
}

TEST(CvRendererTest, BoundingBoxes["TwoWheeled"].FontThicknessRange) {
    CvRenderer module;
    module.setBoundingBoxes["TwoWheeled"].FontThickness(0);
    EXPECT_EQ(module.getBoundingBoxes["TwoWheeled"].FontThickness(), 0);
    module.setBoundingBoxes["TwoWheeled"].FontThickness(0);
    EXPECT_EQ(module.getBoundingBoxes["TwoWheeled"].FontThickness(), 0);
    EXPECT_THROW(module.setBoundingBoxes["TwoWheeled"].FontThickness(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["TwoWheeled"].FontThickness(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Vehicle/light"].SkipRendering in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Vehicle/light"].SkipRenderingDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/light"].SkipRendering(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Vehicle/light"].SkipRenderingRange) {
    CvRenderer module;
    module.setBoundingBoxes["Vehicle/light"].SkipRendering(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/light"].SkipRendering(), 0);
    module.setBoundingBoxes["Vehicle/light"].SkipRendering(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/light"].SkipRendering(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/light"].SkipRendering(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/light"].SkipRendering(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Vehicle/light"].BoxColor in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Vehicle/light"].BoxColorDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/light"].BoxColor(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Vehicle/light"].BoxColorRange) {
    CvRenderer module;
    module.setBoundingBoxes["Vehicle/light"].BoxColor(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/light"].BoxColor(), 0);
    module.setBoundingBoxes["Vehicle/light"].BoxColor(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/light"].BoxColor(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/light"].BoxColor(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/light"].BoxColor(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Vehicle/light"].LineThickness in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Vehicle/light"].LineThicknessDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/light"].LineThickness(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Vehicle/light"].LineThicknessRange) {
    CvRenderer module;
    module.setBoundingBoxes["Vehicle/light"].LineThickness(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/light"].LineThickness(), 0);
    module.setBoundingBoxes["Vehicle/light"].LineThickness(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/light"].LineThickness(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/light"].LineThickness(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/light"].LineThickness(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Vehicle/light"].TextOffsetX in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Vehicle/light"].TextOffsetXDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/light"].TextOffsetX(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Vehicle/light"].TextOffsetXRange) {
    CvRenderer module;
    module.setBoundingBoxes["Vehicle/light"].TextOffsetX(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/light"].TextOffsetX(), 0);
    module.setBoundingBoxes["Vehicle/light"].TextOffsetX(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/light"].TextOffsetX(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/light"].TextOffsetX(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/light"].TextOffsetX(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Vehicle/light"].TextOffsetY in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Vehicle/light"].TextOffsetYDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/light"].TextOffsetY(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Vehicle/light"].TextOffsetYRange) {
    CvRenderer module;
    module.setBoundingBoxes["Vehicle/light"].TextOffsetY(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/light"].TextOffsetY(), 0);
    module.setBoundingBoxes["Vehicle/light"].TextOffsetY(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/light"].TextOffsetY(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/light"].TextOffsetY(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/light"].TextOffsetY(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Vehicle/light"].BottomTextOffsetY in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Vehicle/light"].BottomTextOffsetYDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/light"].BottomTextOffsetY(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Vehicle/light"].BottomTextOffsetYRange) {
    CvRenderer module;
    module.setBoundingBoxes["Vehicle/light"].BottomTextOffsetY(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/light"].BottomTextOffsetY(), 0);
    module.setBoundingBoxes["Vehicle/light"].BottomTextOffsetY(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/light"].BottomTextOffsetY(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/light"].BottomTextOffsetY(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/light"].BottomTextOffsetY(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Vehicle/light"].FontColor in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Vehicle/light"].FontColorDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/light"].FontColor(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Vehicle/light"].FontColorRange) {
    CvRenderer module;
    module.setBoundingBoxes["Vehicle/light"].FontColor(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/light"].FontColor(), 0);
    module.setBoundingBoxes["Vehicle/light"].FontColor(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/light"].FontColor(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/light"].FontColor(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/light"].FontColor(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Vehicle/light"].FontScale in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Vehicle/light"].FontScaleDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/light"].FontScale(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Vehicle/light"].FontScaleRange) {
    CvRenderer module;
    module.setBoundingBoxes["Vehicle/light"].FontScale(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/light"].FontScale(), 0);
    module.setBoundingBoxes["Vehicle/light"].FontScale(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/light"].FontScale(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/light"].FontScale(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/light"].FontScale(0 + 1), std::out_of_range);
}

// Test for BoundingBoxes["Vehicle/light"].FontThickness in CvRenderer
TEST(CvRendererTest, BoundingBoxes["Vehicle/light"].FontThicknessDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/light"].FontThickness(), 0);
}

TEST(CvRendererTest, BoundingBoxes["Vehicle/light"].FontThicknessRange) {
    CvRenderer module;
    module.setBoundingBoxes["Vehicle/light"].FontThickness(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/light"].FontThickness(), 0);
    module.setBoundingBoxes["Vehicle/light"].FontThickness(0);
    EXPECT_EQ(module.getBoundingBoxes["Vehicle/light"].FontThickness(), 0);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/light"].FontThickness(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setBoundingBoxes["Vehicle/light"].FontThickness(0 + 1), std::out_of_range);
}

// Test for Osd in CvRenderer
TEST(CvRendererTest, OsdDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getOsd(), 0);
}

TEST(CvRendererTest, OsdRange) {
    CvRenderer module;
    module.setOsd(0);
    EXPECT_EQ(module.getOsd(), 0);
    module.setOsd(0);
    EXPECT_EQ(module.getOsd(), 0);
    EXPECT_THROW(module.setOsd(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setOsd(0 + 1), std::out_of_range);
}

// Test for Osd.SkipRendering in CvRenderer
TEST(CvRendererTest, Osd.SkipRenderingDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getOsd.SkipRendering(), 0);
}

TEST(CvRendererTest, Osd.SkipRenderingRange) {
    CvRenderer module;
    module.setOsd.SkipRendering(0);
    EXPECT_EQ(module.getOsd.SkipRendering(), 0);
    module.setOsd.SkipRendering(0);
    EXPECT_EQ(module.getOsd.SkipRendering(), 0);
    EXPECT_THROW(module.setOsd.SkipRendering(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setOsd.SkipRendering(0 + 1), std::out_of_range);
}

// Test for Osd.Corner in CvRenderer
TEST(CvRendererTest, Osd.CornerDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getOsd.Corner(), 0);
}

TEST(CvRendererTest, Osd.CornerRange) {
    CvRenderer module;
    module.setOsd.Corner(0);
    EXPECT_EQ(module.getOsd.Corner(), 0);
    module.setOsd.Corner(0);
    EXPECT_EQ(module.getOsd.Corner(), 0);
    EXPECT_THROW(module.setOsd.Corner(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setOsd.Corner(0 + 1), std::out_of_range);
}

// Test for Osd.Values[0] in CvRenderer
TEST(CvRendererTest, Osd.Values[0]Default) {
    CvRenderer module;
    EXPECT_EQ(module.getOsd.Values[0](), 0);
}

TEST(CvRendererTest, Osd.Values[0]Range) {
    CvRenderer module;
    module.setOsd.Values[0](0);
    EXPECT_EQ(module.getOsd.Values[0](), 0);
    module.setOsd.Values[0](0);
    EXPECT_EQ(module.getOsd.Values[0](), 0);
    EXPECT_THROW(module.setOsd.Values[0](0 - 1), std::out_of_range);
    EXPECT_THROW(module.setOsd.Values[0](0 + 1), std::out_of_range);
}

// Test for Osd.Values[1] in CvRenderer
TEST(CvRendererTest, Osd.Values[1]Default) {
    CvRenderer module;
    EXPECT_EQ(module.getOsd.Values[1](), 0);
}

TEST(CvRendererTest, Osd.Values[1]Range) {
    CvRenderer module;
    module.setOsd.Values[1](0);
    EXPECT_EQ(module.getOsd.Values[1](), 0);
    module.setOsd.Values[1](0);
    EXPECT_EQ(module.getOsd.Values[1](), 0);
    EXPECT_THROW(module.setOsd.Values[1](0 - 1), std::out_of_range);
    EXPECT_THROW(module.setOsd.Values[1](0 + 1), std::out_of_range);
}

// Test for Osd.Values[2] in CvRenderer
TEST(CvRendererTest, Osd.Values[2]Default) {
    CvRenderer module;
    EXPECT_EQ(module.getOsd.Values[2](), 0);
}

TEST(CvRendererTest, Osd.Values[2]Range) {
    CvRenderer module;
    module.setOsd.Values[2](0);
    EXPECT_EQ(module.getOsd.Values[2](), 0);
    module.setOsd.Values[2](0);
    EXPECT_EQ(module.getOsd.Values[2](), 0);
    EXPECT_THROW(module.setOsd.Values[2](0 - 1), std::out_of_range);
    EXPECT_THROW(module.setOsd.Values[2](0 + 1), std::out_of_range);
}

// Test for Osd.Values[3] in CvRenderer
TEST(CvRendererTest, Osd.Values[3]Default) {
    CvRenderer module;
    EXPECT_EQ(module.getOsd.Values[3](), 0);
}

TEST(CvRendererTest, Osd.Values[3]Range) {
    CvRenderer module;
    module.setOsd.Values[3](0);
    EXPECT_EQ(module.getOsd.Values[3](), 0);
    module.setOsd.Values[3](0);
    EXPECT_EQ(module.getOsd.Values[3](), 0);
    EXPECT_THROW(module.setOsd.Values[3](0 - 1), std::out_of_range);
    EXPECT_THROW(module.setOsd.Values[3](0 + 1), std::out_of_range);
}

// Test for Osd.Values[4] in CvRenderer
TEST(CvRendererTest, Osd.Values[4]Default) {
    CvRenderer module;
    EXPECT_EQ(module.getOsd.Values[4](), 0);
}

TEST(CvRendererTest, Osd.Values[4]Range) {
    CvRenderer module;
    module.setOsd.Values[4](0);
    EXPECT_EQ(module.getOsd.Values[4](), 0);
    module.setOsd.Values[4](0);
    EXPECT_EQ(module.getOsd.Values[4](), 0);
    EXPECT_THROW(module.setOsd.Values[4](0 - 1), std::out_of_range);
    EXPECT_THROW(module.setOsd.Values[4](0 + 1), std::out_of_range);
}

// Test for Osd.Values[5] in CvRenderer
TEST(CvRendererTest, Osd.Values[5]Default) {
    CvRenderer module;
    EXPECT_EQ(module.getOsd.Values[5](), 0);
}

TEST(CvRendererTest, Osd.Values[5]Range) {
    CvRenderer module;
    module.setOsd.Values[5](0);
    EXPECT_EQ(module.getOsd.Values[5](), 0);
    module.setOsd.Values[5](0);
    EXPECT_EQ(module.getOsd.Values[5](), 0);
    EXPECT_THROW(module.setOsd.Values[5](0 - 1), std::out_of_range);
    EXPECT_THROW(module.setOsd.Values[5](0 + 1), std::out_of_range);
}

// Test for Osd.Values[6] in CvRenderer
TEST(CvRendererTest, Osd.Values[6]Default) {
    CvRenderer module;
    EXPECT_EQ(module.getOsd.Values[6](), 0);
}

TEST(CvRendererTest, Osd.Values[6]Range) {
    CvRenderer module;
    module.setOsd.Values[6](0);
    EXPECT_EQ(module.getOsd.Values[6](), 0);
    module.setOsd.Values[6](0);
    EXPECT_EQ(module.getOsd.Values[6](), 0);
    EXPECT_THROW(module.setOsd.Values[6](0 - 1), std::out_of_range);
    EXPECT_THROW(module.setOsd.Values[6](0 + 1), std::out_of_range);
}

// Test for Osd.Values[7] in CvRenderer
TEST(CvRendererTest, Osd.Values[7]Default) {
    CvRenderer module;
    EXPECT_EQ(module.getOsd.Values[7](), 0);
}

TEST(CvRendererTest, Osd.Values[7]Range) {
    CvRenderer module;
    module.setOsd.Values[7](0);
    EXPECT_EQ(module.getOsd.Values[7](), 0);
    module.setOsd.Values[7](0);
    EXPECT_EQ(module.getOsd.Values[7](), 0);
    EXPECT_THROW(module.setOsd.Values[7](0 - 1), std::out_of_range);
    EXPECT_THROW(module.setOsd.Values[7](0 + 1), std::out_of_range);
}

// Test for Osd.Values[8] in CvRenderer
TEST(CvRendererTest, Osd.Values[8]Default) {
    CvRenderer module;
    EXPECT_EQ(module.getOsd.Values[8](), 0);
}

TEST(CvRendererTest, Osd.Values[8]Range) {
    CvRenderer module;
    module.setOsd.Values[8](0);
    EXPECT_EQ(module.getOsd.Values[8](), 0);
    module.setOsd.Values[8](0);
    EXPECT_EQ(module.getOsd.Values[8](), 0);
    EXPECT_THROW(module.setOsd.Values[8](0 - 1), std::out_of_range);
    EXPECT_THROW(module.setOsd.Values[8](0 + 1), std::out_of_range);
}

// Test for Osd.Values[9] in CvRenderer
TEST(CvRendererTest, Osd.Values[9]Default) {
    CvRenderer module;
    EXPECT_EQ(module.getOsd.Values[9](), 0);
}

TEST(CvRendererTest, Osd.Values[9]Range) {
    CvRenderer module;
    module.setOsd.Values[9](0);
    EXPECT_EQ(module.getOsd.Values[9](), 0);
    module.setOsd.Values[9](0);
    EXPECT_EQ(module.getOsd.Values[9](), 0);
    EXPECT_THROW(module.setOsd.Values[9](0 - 1), std::out_of_range);
    EXPECT_THROW(module.setOsd.Values[9](0 + 1), std::out_of_range);
}

// Test for Osd.MarginX in CvRenderer
TEST(CvRendererTest, Osd.MarginXDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getOsd.MarginX(), 0);
}

TEST(CvRendererTest, Osd.MarginXRange) {
    CvRenderer module;
    module.setOsd.MarginX(0);
    EXPECT_EQ(module.getOsd.MarginX(), 0);
    module.setOsd.MarginX(0);
    EXPECT_EQ(module.getOsd.MarginX(), 0);
    EXPECT_THROW(module.setOsd.MarginX(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setOsd.MarginX(0 + 1), std::out_of_range);
}

// Test for Osd.MarginY in CvRenderer
TEST(CvRendererTest, Osd.MarginYDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getOsd.MarginY(), 0);
}

TEST(CvRendererTest, Osd.MarginYRange) {
    CvRenderer module;
    module.setOsd.MarginY(0);
    EXPECT_EQ(module.getOsd.MarginY(), 0);
    module.setOsd.MarginY(0);
    EXPECT_EQ(module.getOsd.MarginY(), 0);
    EXPECT_THROW(module.setOsd.MarginY(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setOsd.MarginY(0 + 1), std::out_of_range);
}

// Test for Osd.LineDistance in CvRenderer
TEST(CvRendererTest, Osd.LineDistanceDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getOsd.LineDistance(), 0);
}

TEST(CvRendererTest, Osd.LineDistanceRange) {
    CvRenderer module;
    module.setOsd.LineDistance(0);
    EXPECT_EQ(module.getOsd.LineDistance(), 0);
    module.setOsd.LineDistance(0);
    EXPECT_EQ(module.getOsd.LineDistance(), 0);
    EXPECT_THROW(module.setOsd.LineDistance(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setOsd.LineDistance(0 + 1), std::out_of_range);
}

// Test for Osd.BackColor in CvRenderer
TEST(CvRendererTest, Osd.BackColorDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getOsd.BackColor(), 0);
}

TEST(CvRendererTest, Osd.BackColorRange) {
    CvRenderer module;
    module.setOsd.BackColor(0);
    EXPECT_EQ(module.getOsd.BackColor(), 0);
    module.setOsd.BackColor(0);
    EXPECT_EQ(module.getOsd.BackColor(), 0);
    EXPECT_THROW(module.setOsd.BackColor(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setOsd.BackColor(0 + 1), std::out_of_range);
}

// Test for Osd.BackTransparency in CvRenderer
TEST(CvRendererTest, Osd.BackTransparencyDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getOsd.BackTransparency(), 0);
}

TEST(CvRendererTest, Osd.BackTransparencyRange) {
    CvRenderer module;
    module.setOsd.BackTransparency(0);
    EXPECT_EQ(module.getOsd.BackTransparency(), 0);
    module.setOsd.BackTransparency(0);
    EXPECT_EQ(module.getOsd.BackTransparency(), 0);
    EXPECT_THROW(module.setOsd.BackTransparency(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setOsd.BackTransparency(0 + 1), std::out_of_range);
}

// Test for Osd.FontColor in CvRenderer
TEST(CvRendererTest, Osd.FontColorDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getOsd.FontColor(), 0);
}

TEST(CvRendererTest, Osd.FontColorRange) {
    CvRenderer module;
    module.setOsd.FontColor(0);
    EXPECT_EQ(module.getOsd.FontColor(), 0);
    module.setOsd.FontColor(0);
    EXPECT_EQ(module.getOsd.FontColor(), 0);
    EXPECT_THROW(module.setOsd.FontColor(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setOsd.FontColor(0 + 1), std::out_of_range);
}

// Test for Osd.FontScale in CvRenderer
TEST(CvRendererTest, Osd.FontScaleDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getOsd.FontScale(), 0);
}

TEST(CvRendererTest, Osd.FontScaleRange) {
    CvRenderer module;
    module.setOsd.FontScale(0);
    EXPECT_EQ(module.getOsd.FontScale(), 0);
    module.setOsd.FontScale(0);
    EXPECT_EQ(module.getOsd.FontScale(), 0);
    EXPECT_THROW(module.setOsd.FontScale(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setOsd.FontScale(0 + 1), std::out_of_range);
}

// Test for Osd.FontThickness in CvRenderer
TEST(CvRendererTest, Osd.FontThicknessDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getOsd.FontThickness(), 0);
}

TEST(CvRendererTest, Osd.FontThicknessRange) {
    CvRenderer module;
    module.setOsd.FontThickness(0);
    EXPECT_EQ(module.getOsd.FontThickness(), 0);
    module.setOsd.FontThickness(0);
    EXPECT_EQ(module.getOsd.FontThickness(), 0);
    EXPECT_THROW(module.setOsd.FontThickness(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setOsd.FontThickness(0 + 1), std::out_of_range);
}

// Test for Histogram in CvRenderer
TEST(CvRendererTest, HistogramDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getHistogram(), 0);
}

TEST(CvRendererTest, HistogramRange) {
    CvRenderer module;
    module.setHistogram(0);
    EXPECT_EQ(module.getHistogram(), 0);
    module.setHistogram(0);
    EXPECT_EQ(module.getHistogram(), 0);
    EXPECT_THROW(module.setHistogram(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setHistogram(0 + 1), std::out_of_range);
}

// Test for Histogram.SkipRendering in CvRenderer
TEST(CvRendererTest, Histogram.SkipRenderingDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getHistogram.SkipRendering(), 0);
}

TEST(CvRendererTest, Histogram.SkipRenderingRange) {
    CvRenderer module;
    module.setHistogram.SkipRendering(0);
    EXPECT_EQ(module.getHistogram.SkipRendering(), 0);
    module.setHistogram.SkipRendering(0);
    EXPECT_EQ(module.getHistogram.SkipRendering(), 0);
    EXPECT_THROW(module.setHistogram.SkipRendering(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setHistogram.SkipRendering(0 + 1), std::out_of_range);
}

// Test for Histogram.Corner in CvRenderer
TEST(CvRendererTest, Histogram.CornerDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getHistogram.Corner(), 0);
}

TEST(CvRendererTest, Histogram.CornerRange) {
    CvRenderer module;
    module.setHistogram.Corner(0);
    EXPECT_EQ(module.getHistogram.Corner(), 0);
    module.setHistogram.Corner(0);
    EXPECT_EQ(module.getHistogram.Corner(), 0);
    EXPECT_THROW(module.setHistogram.Corner(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setHistogram.Corner(0 + 1), std::out_of_range);
}

// Test for Histogram.MarginX in CvRenderer
TEST(CvRendererTest, Histogram.MarginXDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getHistogram.MarginX(), 0);
}

TEST(CvRendererTest, Histogram.MarginXRange) {
    CvRenderer module;
    module.setHistogram.MarginX(0);
    EXPECT_EQ(module.getHistogram.MarginX(), 0);
    module.setHistogram.MarginX(0);
    EXPECT_EQ(module.getHistogram.MarginX(), 0);
    EXPECT_THROW(module.setHistogram.MarginX(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setHistogram.MarginX(0 + 1), std::out_of_range);
}

// Test for Histogram.MarginY in CvRenderer
TEST(CvRendererTest, Histogram.MarginYDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getHistogram.MarginY(), 0);
}

TEST(CvRendererTest, Histogram.MarginYRange) {
    CvRenderer module;
    module.setHistogram.MarginY(0);
    EXPECT_EQ(module.getHistogram.MarginY(), 0);
    module.setHistogram.MarginY(0);
    EXPECT_EQ(module.getHistogram.MarginY(), 0);
    EXPECT_THROW(module.setHistogram.MarginY(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setHistogram.MarginY(0 + 1), std::out_of_range);
}

// Test for Histogram.Bins in CvRenderer
TEST(CvRendererTest, Histogram.BinsDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getHistogram.Bins(), 0);
}

TEST(CvRendererTest, Histogram.BinsRange) {
    CvRenderer module;
    module.setHistogram.Bins(0);
    EXPECT_EQ(module.getHistogram.Bins(), 0);
    module.setHistogram.Bins(0);
    EXPECT_EQ(module.getHistogram.Bins(), 0);
    EXPECT_THROW(module.setHistogram.Bins(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setHistogram.Bins(0 + 1), std::out_of_range);
}

// Test for Histogram.Width in CvRenderer
TEST(CvRendererTest, Histogram.WidthDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getHistogram.Width(), 0);
}

TEST(CvRendererTest, Histogram.WidthRange) {
    CvRenderer module;
    module.setHistogram.Width(0);
    EXPECT_EQ(module.getHistogram.Width(), 0);
    module.setHistogram.Width(0);
    EXPECT_EQ(module.getHistogram.Width(), 0);
    EXPECT_THROW(module.setHistogram.Width(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setHistogram.Width(0 + 1), std::out_of_range);
}

// Test for Histogram.Height in CvRenderer
TEST(CvRendererTest, Histogram.HeightDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getHistogram.Height(), 0);
}

TEST(CvRendererTest, Histogram.HeightRange) {
    CvRenderer module;
    module.setHistogram.Height(0);
    EXPECT_EQ(module.getHistogram.Height(), 0);
    module.setHistogram.Height(0);
    EXPECT_EQ(module.getHistogram.Height(), 0);
    EXPECT_THROW(module.setHistogram.Height(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setHistogram.Height(0 + 1), std::out_of_range);
}

// Test for Histogram.BackColor in CvRenderer
TEST(CvRendererTest, Histogram.BackColorDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getHistogram.BackColor(), 0);
}

TEST(CvRendererTest, Histogram.BackColorRange) {
    CvRenderer module;
    module.setHistogram.BackColor(0);
    EXPECT_EQ(module.getHistogram.BackColor(), 0);
    module.setHistogram.BackColor(0);
    EXPECT_EQ(module.getHistogram.BackColor(), 0);
    EXPECT_THROW(module.setHistogram.BackColor(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setHistogram.BackColor(0 + 1), std::out_of_range);
}

// Test for Histogram.BackTransparency in CvRenderer
TEST(CvRendererTest, Histogram.BackTransparencyDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getHistogram.BackTransparency(), 0);
}

TEST(CvRendererTest, Histogram.BackTransparencyRange) {
    CvRenderer module;
    module.setHistogram.BackTransparency(0);
    EXPECT_EQ(module.getHistogram.BackTransparency(), 0);
    module.setHistogram.BackTransparency(0);
    EXPECT_EQ(module.getHistogram.BackTransparency(), 0);
    EXPECT_THROW(module.setHistogram.BackTransparency(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setHistogram.BackTransparency(0 + 1), std::out_of_range);
}

// Test for Histogram.ColorBefore in CvRenderer
TEST(CvRendererTest, Histogram.ColorBeforeDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getHistogram.ColorBefore(), 0);
}

TEST(CvRendererTest, Histogram.ColorBeforeRange) {
    CvRenderer module;
    module.setHistogram.ColorBefore(0);
    EXPECT_EQ(module.getHistogram.ColorBefore(), 0);
    module.setHistogram.ColorBefore(0);
    EXPECT_EQ(module.getHistogram.ColorBefore(), 0);
    EXPECT_THROW(module.setHistogram.ColorBefore(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setHistogram.ColorBefore(0 + 1), std::out_of_range);
}

// Test for Histogram.ColorAfter in CvRenderer
TEST(CvRendererTest, Histogram.ColorAfterDefault) {
    CvRenderer module;
    EXPECT_EQ(module.getHistogram.ColorAfter(), 0);
}

TEST(CvRendererTest, Histogram.ColorAfterRange) {
    CvRenderer module;
    module.setHistogram.ColorAfter(0);
    EXPECT_EQ(module.getHistogram.ColorAfter(), 0);
    module.setHistogram.ColorAfter(0);
    EXPECT_EQ(module.getHistogram.ColorAfter(), 0);
    EXPECT_THROW(module.setHistogram.ColorAfter(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setHistogram.ColorAfter(0 + 1), std::out_of_range);
}

// Test for Enable in PreviewModule
TEST(PreviewModuleTest, EnableDefault) {
    PreviewModule module;
    EXPECT_EQ(module.getEnable(), 0);
}

TEST(PreviewModuleTest, EnableRange) {
    PreviewModule module;
    module.setEnable(0);
    EXPECT_EQ(module.getEnable(), 0);
    module.setEnable(0);
    EXPECT_EQ(module.getEnable(), 0);
    EXPECT_THROW(module.setEnable(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setEnable(0 + 1), std::out_of_range);
}

// Test for StopOnError in GstSink
TEST(GstSinkTest, StopOnErrorDefault) {
    GstSink module;
    EXPECT_EQ(module.getStopOnError(), 0);
}

TEST(GstSinkTest, StopOnErrorRange) {
    GstSink module;
    module.setStopOnError(0);
    EXPECT_EQ(module.getStopOnError(), 0);
    module.setStopOnError(0);
    EXPECT_EQ(module.getStopOnError(), 0);
    EXPECT_THROW(module.setStopOnError(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setStopOnError(0 + 1), std::out_of_range);
}

// Test for Sink in GstSink
TEST(GstSinkTest, SinkDefault) {
    GstSink module;
    EXPECT_EQ(module.getSink(), 0);
}

TEST(GstSinkTest, SinkRange) {
    GstSink module;
    module.setSink(0);
    EXPECT_EQ(module.getSink(), 0);
    module.setSink(0);
    EXPECT_EQ(module.getSink(), 0);
    EXPECT_THROW(module.setSink(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setSink(0 + 1), std::out_of_range);
}

// Test for Url in GstSink
TEST(GstSinkTest, UrlDefault) {
    GstSink module;
    EXPECT_EQ(module.getUrl(), 0);
}

TEST(GstSinkTest, UrlRange) {
    GstSink module;
    module.setUrl(0);
    EXPECT_EQ(module.getUrl(), 0);
    module.setUrl(0);
    EXPECT_EQ(module.getUrl(), 0);
    EXPECT_THROW(module.setUrl(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setUrl(0 + 1), std::out_of_range);
}

// Test for FrameRate in GstSink
TEST(GstSinkTest, FrameRateDefault) {
    GstSink module;
    EXPECT_EQ(module.getFrameRate(), 0);
}

TEST(GstSinkTest, FrameRateRange) {
    GstSink module;
    module.setFrameRate(0);
    EXPECT_EQ(module.getFrameRate(), 0);
    module.setFrameRate(0);
    EXPECT_EQ(module.getFrameRate(), 0);
    EXPECT_THROW(module.setFrameRate(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setFrameRate(0 + 1), std::out_of_range);
}

// Test for KlvFormat in GstSink
TEST(GstSinkTest, KlvFormatDefault) {
    GstSink module;
    EXPECT_EQ(module.getKlvFormat(), 0);
}

TEST(GstSinkTest, KlvFormatRange) {
    GstSink module;
    module.setKlvFormat(0);
    EXPECT_EQ(module.getKlvFormat(), 0);
    module.setKlvFormat(0);
    EXPECT_EQ(module.getKlvFormat(), 0);
    EXPECT_THROW(module.setKlvFormat(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setKlvFormat(0 + 1), std::out_of_range);
}

// Test for WebSocketPort in GstSink
TEST(GstSinkTest, WebSocketPortDefault) {
    GstSink module;
    EXPECT_EQ(module.getWebSocketPort(), 0);
}

TEST(GstSinkTest, WebSocketPortRange) {
    GstSink module;
    module.setWebSocketPort(0);
    EXPECT_EQ(module.getWebSocketPort(), 0);
    module.setWebSocketPort(0);
    EXPECT_EQ(module.getWebSocketPort(), 0);
    EXPECT_THROW(module.setWebSocketPort(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setWebSocketPort(0 + 1), std::out_of_range);
}

// Test for Enable in Recorder
TEST(RecorderTest, EnableDefault) {
    Recorder module;
    EXPECT_EQ(module.getEnable(), 0);
}

TEST(RecorderTest, EnableRange) {
    Recorder module;
    module.setEnable(0);
    EXPECT_EQ(module.getEnable(), 0);
    module.setEnable(0);
    EXPECT_EQ(module.getEnable(), 0);
    EXPECT_THROW(module.setEnable(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setEnable(0 + 1), std::out_of_range);
}

// Test for UseOriginalFrameIds in Recorder
TEST(RecorderTest, UseOriginalFrameIdsDefault) {
    Recorder module;
    EXPECT_EQ(module.getUseOriginalFrameIds(), 0);
}

TEST(RecorderTest, UseOriginalFrameIdsRange) {
    Recorder module;
    module.setUseOriginalFrameIds(0);
    EXPECT_EQ(module.getUseOriginalFrameIds(), 0);
    module.setUseOriginalFrameIds(0);
    EXPECT_EQ(module.getUseOriginalFrameIds(), 0);
    EXPECT_THROW(module.setUseOriginalFrameIds(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setUseOriginalFrameIds(0 + 1), std::out_of_range);
}

// Test for Store in Recorder
TEST(RecorderTest, StoreDefault) {
    Recorder module;
    EXPECT_EQ(module.getStore(), 0);
}

TEST(RecorderTest, StoreRange) {
    Recorder module;
    module.setStore(0);
    EXPECT_EQ(module.getStore(), 0);
    module.setStore(0);
    EXPECT_EQ(module.getStore(), 0);
    EXPECT_THROW(module.setStore(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setStore(0 + 1), std::out_of_range);
}

// Test for Store[0].DataType in Recorder
TEST(RecorderTest, Store[0].DataTypeDefault) {
    Recorder module;
    EXPECT_EQ(module.getStore[0].DataType(), 0);
}

TEST(RecorderTest, Store[0].DataTypeRange) {
    Recorder module;
    module.setStore[0].DataType(0);
    EXPECT_EQ(module.getStore[0].DataType(), 0);
    module.setStore[0].DataType(0);
    EXPECT_EQ(module.getStore[0].DataType(), 0);
    EXPECT_THROW(module.setStore[0].DataType(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setStore[0].DataType(0 + 1), std::out_of_range);
}

// Test for Store[0].Tag in Recorder
TEST(RecorderTest, Store[0].TagDefault) {
    Recorder module;
    EXPECT_EQ(module.getStore[0].Tag(), 0);
}

TEST(RecorderTest, Store[0].TagRange) {
    Recorder module;
    module.setStore[0].Tag(0);
    EXPECT_EQ(module.getStore[0].Tag(), 0);
    module.setStore[0].Tag(0);
    EXPECT_EQ(module.getStore[0].Tag(), 0);
    EXPECT_THROW(module.setStore[0].Tag(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setStore[0].Tag(0 + 1), std::out_of_range);
}

// Test for Store[0].Path in Recorder
TEST(RecorderTest, Store[0].PathDefault) {
    Recorder module;
    EXPECT_EQ(module.getStore[0].Path(), 0);
}

TEST(RecorderTest, Store[0].PathRange) {
    Recorder module;
    module.setStore[0].Path(0);
    EXPECT_EQ(module.getStore[0].Path(), 0);
    module.setStore[0].Path(0);
    EXPECT_EQ(module.getStore[0].Path(), 0);
    EXPECT_THROW(module.setStore[0].Path(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setStore[0].Path(0 + 1), std::out_of_range);
}

// Test for Store[1].DataType in Recorder
TEST(RecorderTest, Store[1].DataTypeDefault) {
    Recorder module;
    EXPECT_EQ(module.getStore[1].DataType(), 0);
}

TEST(RecorderTest, Store[1].DataTypeRange) {
    Recorder module;
    module.setStore[1].DataType(0);
    EXPECT_EQ(module.getStore[1].DataType(), 0);
    module.setStore[1].DataType(0);
    EXPECT_EQ(module.getStore[1].DataType(), 0);
    EXPECT_THROW(module.setStore[1].DataType(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setStore[1].DataType(0 + 1), std::out_of_range);
}

// Test for Store[1].Tag in Recorder
TEST(RecorderTest, Store[1].TagDefault) {
    Recorder module;
    EXPECT_EQ(module.getStore[1].Tag(), 0);
}

TEST(RecorderTest, Store[1].TagRange) {
    Recorder module;
    module.setStore[1].Tag(0);
    EXPECT_EQ(module.getStore[1].Tag(), 0);
    module.setStore[1].Tag(0);
    EXPECT_EQ(module.getStore[1].Tag(), 0);
    EXPECT_THROW(module.setStore[1].Tag(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setStore[1].Tag(0 + 1), std::out_of_range);
}

// Test for Store[1].Path in Recorder
TEST(RecorderTest, Store[1].PathDefault) {
    Recorder module;
    EXPECT_EQ(module.getStore[1].Path(), 0);
}

TEST(RecorderTest, Store[1].PathRange) {
    Recorder module;
    module.setStore[1].Path(0);
    EXPECT_EQ(module.getStore[1].Path(), 0);
    module.setStore[1].Path(0);
    EXPECT_EQ(module.getStore[1].Path(), 0);
    EXPECT_THROW(module.setStore[1].Path(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setStore[1].Path(0 + 1), std::out_of_range);
}

// Test for SkipFrames in Recorder
TEST(RecorderTest, SkipFramesDefault) {
    Recorder module;
    EXPECT_EQ(module.getSkipFrames(), 0);
}

TEST(RecorderTest, SkipFramesRange) {
    Recorder module;
    module.setSkipFrames(0);
    EXPECT_EQ(module.getSkipFrames(), 0);
    module.setSkipFrames(0);
    EXPECT_EQ(module.getSkipFrames(), 0);
    EXPECT_THROW(module.setSkipFrames(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setSkipFrames(0 + 1), std::out_of_range);
}

// Test for PathPrefix in Recorder
TEST(RecorderTest, PathPrefixDefault) {
    Recorder module;
    EXPECT_EQ(module.getPathPrefix(), 0);
}

TEST(RecorderTest, PathPrefixRange) {
    Recorder module;
    module.setPathPrefix(0);
    EXPECT_EQ(module.getPathPrefix(), 0);
    module.setPathPrefix(0);
    EXPECT_EQ(module.getPathPrefix(), 0);
    EXPECT_THROW(module.setPathPrefix(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setPathPrefix(0 + 1), std::out_of_range);
}

// Test for FrameFileType in Recorder
TEST(RecorderTest, FrameFileTypeDefault) {
    Recorder module;
    EXPECT_EQ(module.getFrameFileType(), 0);
}

TEST(RecorderTest, FrameFileTypeRange) {
    Recorder module;
    module.setFrameFileType(0);
    EXPECT_EQ(module.getFrameFileType(), 0);
    module.setFrameFileType(0);
    EXPECT_EQ(module.getFrameFileType(), 0);
    EXPECT_THROW(module.setFrameFileType(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setFrameFileType(0 + 1), std::out_of_range);
}

// Test for VideoFourCc in Recorder
TEST(RecorderTest, VideoFourCcDefault) {
    Recorder module;
    EXPECT_EQ(module.getVideoFourCc(), 0);
}

TEST(RecorderTest, VideoFourCcRange) {
    Recorder module;
    module.setVideoFourCc(0);
    EXPECT_EQ(module.getVideoFourCc(), 0);
    module.setVideoFourCc(0);
    EXPECT_EQ(module.getVideoFourCc(), 0);
    EXPECT_THROW(module.setVideoFourCc(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setVideoFourCc(0 + 1), std::out_of_range);
}

// Test for Quality in Recorder
TEST(RecorderTest, QualityDefault) {
    Recorder module;
    EXPECT_EQ(module.getQuality(), 0);
}

TEST(RecorderTest, QualityRange) {
    Recorder module;
    module.setQuality(0);
    EXPECT_EQ(module.getQuality(), 0);
    module.setQuality(0);
    EXPECT_EQ(module.getQuality(), 0);
    EXPECT_THROW(module.setQuality(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setQuality(0 + 1), std::out_of_range);
}

// Test for VideoFps in Recorder
TEST(RecorderTest, VideoFpsDefault) {
    Recorder module;
    EXPECT_EQ(module.getVideoFps(), 0);
}

TEST(RecorderTest, VideoFpsRange) {
    Recorder module;
    module.setVideoFps(0);
    EXPECT_EQ(module.getVideoFps(), 0);
    module.setVideoFps(0);
    EXPECT_EQ(module.getVideoFps(), 0);
    EXPECT_THROW(module.setVideoFps(0 - 1), std::out_of_range);
    EXPECT_THROW(module.setVideoFps(0 + 1), std::out_of_range);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
