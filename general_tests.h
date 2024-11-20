#ifndef GENERAL_TESTS_H
#define GENERAL_TESTS_H


#include "gtest/gtest.h"
#include "PipelineInterface.h"

using namespace sightx;

namespace general_tests {

extern std::shared_ptr<sdk::Pipeline> pPipeline;
void setPipeline(std::shared_ptr<sdk::Pipeline> new_pipeline);
void setUserData(UserData* data);
void RunThresholdInRangeTest(float score_value, float threshold_value, std::string class_name_str, int track_id);

// Forward declaration of the test suite
class VideoStreams : public ::testing::TestWithParam<sdk::FlowSwitcherFlowId> {};
class ContinuousTest : public ::testing::Test {};

}  // namespace general_tests

#endif  // GENERAL_TESTS_H
