#include "PipelineInterface.h"
#include <ostream>
#include "merlin_print_enums.h"

using namespace sightx;

namespace sightx::sdk {

   void PrintTo(sdk::CandidatesCreationType e, std::ostream* os) {
    switch (e) {
          case sdk::CandidatesCreationType::JustMin:
            *os << "CandidatesCreationType::JustMin";
            break;
          case sdk::CandidatesCreationType::JustAverage:
            *os << "CandidatesCreationType::JustAverage";
            break;
          case sdk::CandidatesCreationType::MinAndAverage:
            *os << "CandidatesCreationType::MinAndAverage";
            break;
          case sdk::CandidatesCreationType::MinOrAverage:
            *os << "CandidatesCreationType::MinOrAverage";
            break;
           default:
            *os << "UNKNOWN_ENUM_VALUE";
            break;
       }
}

   void PrintTo(sdk::ColorMap e, std::ostream* os) {
    switch (e) {
          case sdk::ColorMap::Bone:
            *os << "ColorMap::Bone";
            break;
          case sdk::ColorMap::Jet:
            *os << "ColorMap::Jet";
            break;
          case sdk::ColorMap::Winter:
            *os << "ColorMap::Winter";
            break;
          case sdk::ColorMap::Rainbow:
            *os << "ColorMap::Rainbow";
            break;
          case sdk::ColorMap::Ocean:
            *os << "ColorMap::Ocean";
            break;
          case sdk::ColorMap::Summer:
            *os << "ColorMap::Summer";
            break;
          case sdk::ColorMap::Spring:
            *os << "ColorMap::Spring";
            break;
          case sdk::ColorMap::Cool:
            *os << "ColorMap::Cool";
            break;
          case sdk::ColorMap::Hsv:
            *os << "ColorMap::Hsv";
            break;
          case sdk::ColorMap::Pink:
            *os << "ColorMap::Pink";
            break;
          case sdk::ColorMap::Hot:
            *os << "ColorMap::Hot";
            break;
          case sdk::ColorMap::Parula:
            *os << "ColorMap::Parula";
            break;
          case sdk::ColorMap::Magma:
            *os << "ColorMap::Magma";
            break;
          case sdk::ColorMap::Inferno:
            *os << "ColorMap::Inferno";
            break;
          case sdk::ColorMap::Plasma:
            *os << "ColorMap::Plasma";
            break;
          case sdk::ColorMap::Viridis:
            *os << "ColorMap::Viridis";
            break;
          case sdk::ColorMap::Cividis:
            *os << "ColorMap::Cividis";
            break;
          case sdk::ColorMap::Twilight:
            *os << "ColorMap::Twilight";
            break;
          case sdk::ColorMap::TwilightShifted:
            *os << "ColorMap::TwilightShifted";
            break;
           default:
            *os << "UNKNOWN_ENUM_VALUE";
            break;
       }
}

   void PrintTo(sdk::Corner e, std::ostream* os) {
    switch (e) {
          case sdk::Corner::TopLeft:
            *os << "Corner::TopLeft";
            break;
          case sdk::Corner::TopRight:
            *os << "Corner::TopRight";
            break;
          case sdk::Corner::BottomLeft:
            *os << "Corner::BottomLeft";
            break;
          case sdk::Corner::BottomRight:
            *os << "Corner::BottomRight";
            break;
           default:
            *os << "UNKNOWN_ENUM_VALUE";
            break;
       }
}

   void PrintTo(sdk::DataType e, std::ostream* os) {
    switch (e) {
          case sdk::DataType::RawFrame:
            *os << "DataType::RawFrame";
            break;
          case sdk::DataType::PreprocessedFrame:
            *os << "DataType::PreprocessedFrame";
            break;
          case sdk::DataType::Homography:
            *os << "DataType::Homography";
            break;
          case sdk::DataType::Detections:
            *os << "DataType::Detections";
            break;
          case sdk::DataType::Crops:
            *os << "DataType::Crops";
            break;
          case sdk::DataType::Tracks:
            *os << "DataType::Tracks";
            break;
          case sdk::DataType::Features:
            *os << "DataType::Features";
            break;
          case sdk::DataType::Landmarks:
            *os << "DataType::Landmarks";
            break;
          case sdk::DataType::MetadataFrame:
            *os << "DataType::MetadataFrame";
            break;
          case sdk::DataType::GraphData:
            *os << "DataType::GraphData";
            break;
          case sdk::DataType::DetectorRoi:
            *os << "DataType::DetectorRoi";
            break;
          case sdk::DataType::PreprocessorInfo:
            *os << "DataType::PreprocessorInfo";
            break;
          case sdk::DataType::DetectorInfo:
            *os << "DataType::DetectorInfo";
            break;
          case sdk::DataType::PerFrameMetadata:
            *os << "DataType::PerFrameMetadata";
            break;
          case sdk::DataType::CustomMetadata:
            *os << "DataType::CustomMetadata";
            break;
          case sdk::DataType::DebugMetadata:
            *os << "DataType::DebugMetadata";
            break;
           default:
            *os << "UNKNOWN_ENUM_VALUE";
            break;
       }
}

   void PrintTo(sdk::DeviceAccess e, std::ostream* os) {
    switch (e) {
          case sdk::DeviceAccess::ReadOnly:
            *os << "DeviceAccess::ReadOnly";
            break;
          case sdk::DeviceAccess::Control:
            *os << "DeviceAccess::Control";
            break;
          case sdk::DeviceAccess::Exclusive:
            *os << "DeviceAccess::Exclusive";
            break;
           default:
            *os << "UNKNOWN_ENUM_VALUE";
            break;
       }
}

   void PrintTo(sdk::FlowSwitcherFlowId e, std::ostream* os) {
    switch (e) {
          case sdk::FlowSwitcherFlowId::Rgb:
            *os << "FlowSwitcherFlowId::Rgb";
            break;
          case sdk::FlowSwitcherFlowId::Mwir:
            *os << "FlowSwitcherFlowId::Mwir";
            break;
          case sdk::FlowSwitcherFlowId::Sot:
            *os << "FlowSwitcherFlowId::Sot";
            break;
           default:
            *os << "UNKNOWN_ENUM_VALUE";
            break;
       }
}

   void PrintTo(sdk::FrameIdType e, std::ostream* os) {
    switch (e) {
          case sdk::FrameIdType::Original:
            *os << "FrameIdType::Original";
            break;
          case sdk::FrameIdType::Timestamp:
            *os << "FrameIdType::Timestamp";
            break;
           default:
            *os << "UNKNOWN_ENUM_VALUE";
            break;
       }
}

   void PrintTo(sdk::GenicamMode e, std::ostream* os) {
    switch (e) {
          case sdk::GenicamMode::GigeVision:
            *os << "GenicamMode::GigeVision";
            break;
          case sdk::GenicamMode::Usb3Vision:
            *os << "GenicamMode::Usb3Vision";
            break;
           default:
            *os << "UNKNOWN_ENUM_VALUE";
            break;
       }
}

   void PrintTo(sdk::ImageFilter e, std::ostream* os) {
    switch (e) {
          case sdk::ImageFilter::AreaSizeFilter:
            *os << "ImageFilter::AreaSizeFilter";
            break;
          case sdk::ImageFilter::LaplacianFilter:
            *os << "ImageFilter::LaplacianFilter";
            break;
           default:
            *os << "UNKNOWN_ENUM_VALUE";
            break;
       }
}

   void PrintTo(sdk::InitScoreMetric e, std::ostream* os) {
    switch (e) {
          case sdk::InitScoreMetric::Average:
            *os << "InitScoreMetric::Average";
            break;
          case sdk::InitScoreMetric::Median:
            *os << "InitScoreMetric::Median";
            break;
           default:
            *os << "UNKNOWN_ENUM_VALUE";
            break;
       }
}

   void PrintTo(sdk::KlvFormat e, std::ostream* os) {
    switch (e) {
          case sdk::KlvFormat::Disabled:
            *os << "KlvFormat::Disabled";
            break;
          case sdk::KlvFormat::UasVmtiLs:
            *os << "KlvFormat::UasVmtiLs";
            break;
           default:
            *os << "UNKNOWN_ENUM_VALUE";
            break;
       }
}

   void PrintTo(sdk::NormalizationType e, std::ostream* os) {
    switch (e) {
          case sdk::NormalizationType::Disabled:
            *os << "NormalizationType::Disabled";
            break;
          case sdk::NormalizationType::HistogramEqualization:
            *os << "NormalizationType::HistogramEqualization";
            break;
          case sdk::NormalizationType::LinearTransform:
            *os << "NormalizationType::LinearTransform";
            break;
          case sdk::NormalizationType::MeanStdCrop:
            *os << "NormalizationType::MeanStdCrop";
            break;
           default:
            *os << "UNKNOWN_ENUM_VALUE";
            break;
       }
}

   void PrintTo(sdk::OsdValue e, std::ostream* os) {
    switch (e) {
          case sdk::OsdValue::Version:
            *os << "OsdValue::Version";
            break;
          case sdk::OsdValue::StreamId:
            *os << "OsdValue::StreamId";
            break;
          case sdk::OsdValue::InputDescription:
            *os << "OsdValue::InputDescription";
            break;
          case sdk::OsdValue::FrameId:
            *os << "OsdValue::FrameId";
            break;
          case sdk::OsdValue::Fps:
            *os << "OsdValue::Fps";
            break;
          case sdk::OsdValue::Pts:
            *os << "OsdValue::Pts";
            break;
          case sdk::OsdValue::Latency:
            *os << "OsdValue::Latency";
            break;
          case sdk::OsdValue::TelemetryPlatform:
            *os << "OsdValue::TelemetryPlatform";
            break;
          case sdk::OsdValue::TelemetryPayload:
            *os << "OsdValue::TelemetryPayload";
            break;
          case sdk::OsdValue::FrameRegistration:
            *os << "OsdValue::FrameRegistration";
            break;
           default:
            *os << "UNKNOWN_ENUM_VALUE";
            break;
       }
}

   void PrintTo(sdk::PayloadChannel e, std::ostream* os) {
    switch (e) {
          case sdk::PayloadChannel::Rgb:
            *os << "PayloadChannel::Rgb";
            break;
          case sdk::PayloadChannel::Ir:
            *os << "PayloadChannel::Ir";
            break;
           default:
            *os << "UNKNOWN_ENUM_VALUE";
            break;
       }
}

   void PrintTo(sdk::PayloadMode e, std::ostream* os) {
    switch (e) {
          case sdk::PayloadMode::Rate:
            *os << "PayloadMode::Rate";
            break;
          case sdk::PayloadMode::Bit:
            *os << "PayloadMode::Bit";
            break;
          case sdk::PayloadMode::Pilot:
            *os << "PayloadMode::Pilot";
            break;
          case sdk::PayloadMode::Stow:
            *os << "PayloadMode::Stow";
            break;
          case sdk::PayloadMode::Park:
            *os << "PayloadMode::Park";
            break;
          case sdk::PayloadMode::Center:
            *os << "PayloadMode::Center";
            break;
           default:
            *os << "UNKNOWN_ENUM_VALUE";
            break;
       }
}

   void PrintTo(sdk::PayloadOrientation e, std::ostream* os) {
    switch (e) {
          case sdk::PayloadOrientation::Horizontal:
            *os << "PayloadOrientation::Horizontal";
            break;
          case sdk::PayloadOrientation::Vertical:
            *os << "PayloadOrientation::Vertical";
            break;
           default:
            *os << "UNKNOWN_ENUM_VALUE";
            break;
       }
}

   void PrintTo(sdk::PayloadType e, std::ostream* os) {
    switch (e) {
          case sdk::PayloadType::Colibri:
            *os << "PayloadType::Colibri";
            break;
          case sdk::PayloadType::Static:
            *os << "PayloadType::Static";
            break;
          case sdk::PayloadType::Xr:
            *os << "PayloadType::Xr";
            break;
           default:
            *os << "UNKNOWN_ENUM_VALUE";
            break;
       }
}

   void PrintTo(sdk::PlatformType e, std::ostream* os) {
    switch (e) {
          case sdk::PlatformType::Static:
            *os << "PlatformType::Static";
            break;
           default:
            *os << "UNKNOWN_ENUM_VALUE";
            break;
       }
}

   void PrintTo(sdk::PublisherDataType e, std::ostream* os) {
    switch (e) {
          case sdk::PublisherDataType::Disabled:
            *os << "PublisherDataType::Disabled";
            break;
          case sdk::PublisherDataType::Detections:
            *os << "PublisherDataType::Detections";
            break;
          case sdk::PublisherDataType::Tracks:
            *os << "PublisherDataType::Tracks";
            break;
           default:
            *os << "UNKNOWN_ENUM_VALUE";
            break;
       }
}

   void PrintTo(sdk::RawSourceMode e, std::ostream* os) {
    switch (e) {
          case sdk::RawSourceMode::Stream:
            *os << "RawSourceMode::Stream";
            break;
          case sdk::RawSourceMode::SingleFrame:
            *os << "RawSourceMode::SingleFrame";
            break;
           default:
            *os << "UNKNOWN_ENUM_VALUE";
            break;
       }
}

   void PrintTo(sdk::ReidMode e, std::ostream* os) {
    switch (e) {
          case sdk::ReidMode::Automatic:
            *os << "ReidMode::Automatic";
            break;
          case sdk::ReidMode::Manual:
            *os << "ReidMode::Manual";
            break;
           default:
            *os << "UNKNOWN_ENUM_VALUE";
            break;
       }
}

   void PrintTo(sdk::VideoPassthroughFlow e, std::ostream* os) {
    switch (e) {
          case sdk::VideoPassthroughFlow::On:
            *os << "VideoPassthroughFlow::On";
            break;
          case sdk::VideoPassthroughFlow::Off:
            *os << "VideoPassthroughFlow::Off";
            break;
           default:
            *os << "UNKNOWN_ENUM_VALUE";
            break;
       }
}

}
