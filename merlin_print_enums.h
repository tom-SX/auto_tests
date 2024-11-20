#ifndef ENUM_PRINTING_H
#define ENUM_PRINTING_H

#include <ostream>
#include "PipelineInterface.h"

using namespace sightx;

namespace sightx::sdk {

    void PrintTo(sdk::CandidatesCreationType e, std::ostream* os);
    void PrintTo(sdk::ColorMap e, std::ostream* os);
    void PrintTo(sdk::Corner e, std::ostream* os);
    void PrintTo(sdk::DataType e, std::ostream* os);
    void PrintTo(sdk::DeviceAccess e, std::ostream* os);
    void PrintTo(sdk::FlowSwitcherFlowId e, std::ostream* os);
    void PrintTo(sdk::FrameIdType e, std::ostream* os);
    void PrintTo(sdk::GenicamMode e, std::ostream* os);
    void PrintTo(sdk::ImageFilter e, std::ostream* os);
    void PrintTo(sdk::InitScoreMetric e, std::ostream* os);
    void PrintTo(sdk::KlvFormat e, std::ostream* os);
    void PrintTo(sdk::NormalizationType e, std::ostream* os);
    void PrintTo(sdk::OsdValue e, std::ostream* os);
    void PrintTo(sdk::PayloadChannel e, std::ostream* os);
    void PrintTo(sdk::PayloadMode e, std::ostream* os);
    void PrintTo(sdk::PayloadOrientation e, std::ostream* os);
    void PrintTo(sdk::PayloadType e, std::ostream* os);
    void PrintTo(sdk::PlatformType e, std::ostream* os);
    void PrintTo(sdk::PublisherDataType e, std::ostream* os);
    void PrintTo(sdk::RawSourceMode e, std::ostream* os);
    void PrintTo(sdk::ReidMode e, std::ostream* os);
    void PrintTo(sdk::VideoPassthroughFlow e, std::ostream* os);

}

#endif // ENUM_PRINTING_H
