#pragma once
#include "PipelineInterface.h"
#include "helper.h"
using namespace sightx;

namespace generated_tests {
    extern std::shared_ptr<sdk::Pipeline> pPipeline;
    void setPipeline(std::shared_ptr<sdk::Pipeline> new_pipeline);
    void setUserData(UserData* data);
} // namespace generated_tests
