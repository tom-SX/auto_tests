#pragma once

#include "PipelineInterface_exports.h"

#include <memory>
#include <stdexcept>

/// All methods throw std::exception-derived class in case of an error

namespace sightx
{
class WebProxy;

namespace sdk
{
/// Logger interface
struct Logger
{
    /// Initializes logger callbacks
    /// \param a_Callbacks log level to report and a message callback
    /// \param a_eMinLogLevel minimum log level to report in OnMessage callback
    /// \param a_bEnableDDSLogs true to enable client DDS logs
    static void init(
        const LoggerCallbacks& a_Callbacks      = {},
        LogLevel               a_eMinLogLevel   = LogLevel::Error,
        bool                   a_bEnableDDSLogs = false);
};

class Stream;

/// Main pipeline interface
class Pipeline
{
public:
    Pipeline(
        const Pipeline&) = delete;

    Pipeline& operator=(
        const Pipeline&) = delete;

    ~Pipeline();

    /// Discovers servers available on the network
    /// \param a_nDiscoveryTimeoutInMs timeout for servers discovery, should be at least 1 sec
    /// \param a_bOnlyCompatible return only servers compatible with current client, if false - returns all available
    ///                          servers
    /// \return list of discovered servers
    static Vector<ServerInfo> discover(
        uint32_t a_nDiscoveryTimeoutInMs = 1000,
        bool     a_bOnlyCompatible       = true);

    /// Creates Pipeline instance; only one Pipeline instance can be created
    /// \param a_GrpcSettings grpc settings
    /// \param a_DdsSettings dds settings
    /// \param a_RawStreamSettings raw stream settings
    /// \param a_Callbacks sdk callbacks
    /// \return Pipeline instance
    static std::shared_ptr<Pipeline> create(
        const GrpcSettings&      a_GrpcSettings,
        const DDSSettings&       a_DdsSettings,
        const RawStreamSettings& a_RawStreamSettings,
        const Callbacks&         a_Callbacks);

    /// Creates start stream configuration object with default pipeline configuration; this object can be edited and
    /// used in startStream() method
    /// \param a_strCustomPreset optional preset file; if exists - StartStreamConfiguration will be initialized
    ///                          to values defined inside it instead of the default pipeline configuration
    /// \return StartStreamConfiguration instance filled with default pipeline configuration
    StartStreamConfiguration createStartStreamConfiguration(
        const String& a_strCustomPreset = "stream_settings.bin");

    /// Starts a new stream; d'tor of Stream object closes the remote stream
    /// \param a_Configuration stream configuration object created using createStartStreamConfiguration() and filled
    /// with requested parameters
    /// \return Stream object
    std::shared_ptr<Stream> startStream(
        const StartStreamConfiguration& a_Configuration);

    /// Wraps an existing stream known by its stream id; unlike startStream(), d'tor of Stream object doesn't close the stream.
    /// It's not allowed to wrap a stream that was created with startStream() in the same process.
    /// Note: this function is intended for internal usage most of the time and is not very useful otherwise
    /// \param a_strStreamId existing stream id
    /// \return Stream object
    std::shared_ptr<Stream> wrapStream(
        const String& a_strStreamId);

    /// \return pipeline information
    PipelineInfo getPipelineInfo();

    /// Returns full default stream configuration object
    /// Full configuration contains all optional (grouped) entries
    /// \return full default configuration
    FullStreamConfiguration getDefaultConfiguration();

    /// Shuts down pipeline service (should be used in case the service seems stuck)
    /// \param a_bForce true to shut down immediately
    void shutdown(
        bool a_bForce = false);

private:
    Pipeline(
        const GrpcSettings&,
        const DDSSettings&,
        const RawStreamSettings&,
        const Callbacks&);

    detail::PipelineImpl* m_pImpl;

    Callbacks m_Callbacks;
};

/// %Stream interface
class Stream : public ModuleFunctions
{
public:
    Stream(
        const Stream&) = delete;

    Stream& operator=(
        const Stream&) = delete;

    ~Stream();

    /// \return stream id
    String getId() const;

    /// \return true if Stream was created with Pipeline::wrapStream()
    bool isWrapped() const;

    /// Returns full current stream configuration object for the stream
    /// Full configuration contains all configuration fields including non-updatable ones
    /// \param a_strModuleAlias if not empty only return configuration for a specified module, otherwise return all
    /// modules
    /// \return full stream configuration
    FullStreamConfiguration getFullConfiguration(
        const String& a_strModuleAlias = "");

    /// Returns current stream configuration object for the stream
    /// To update stream configuration, this configuration should be edited and then update() should be called
    /// \return current stream configuration
    UpdateStreamConfiguration& getConfiguration();

    /// Updates current stream with configuration edited through getConfiguration()
    void update();

    /// Pushes raw frame to the service, this function can only be used with streams that use raw sources; the source
    /// should be open in Stream mode
    /// \param a_eRawSource raw source to push into, this source has to be selected during startStream
    /// \param a_pData raw image pointer
    /// \param a_nWidth raw image width or data size for compressed data
    /// \param a_nHeight raw image height or 1 for compressed data
    /// \param a_ePixelFormat pixel format of the raw image
    /// \param a_nStep length of image line in bytes, if 0 - assumed to be a_nWidth * sizeof(pixel)
    /// \param a_nFrameId frame id of the pushed frame, if -1 - running number will be used; this frame id is used in reported tracks
    /// \param a_nTimestampMs timestamp of the frame in ms, if -1 - current time is used
    /// \param a_bBlock true to block when sending the frame
    void pushRawFrame(
        RawSourceId a_eRawSource,
        const void* a_pData,
        uint32_t    a_nWidth,
        uint32_t    a_nHeight,
        PixelFormat a_ePixelFormat,
        uint32_t    a_nStep        = 0,
        uint64_t    a_nFrameId     = static_cast<uint64_t>(-1),
        uint64_t    a_nTimestampMs = static_cast<uint64_t>(-1),
        bool        a_bBlock       = false);

    /// Processes single frame; this function can only be used with streams that use raw sources; the source should be
    /// open in SingleFrame mode
    /// \param a_eRawSource raw source to push into, this source has to be selected during startStream
    /// \param a_nOutput desired output, several outputs can be selected by or'ing the bits
    /// \param a_pData raw image pointer
    /// \param a_nWidth raw image width or data size for compressed data
    /// \param a_nHeight raw image height or 1 for compressed data
    /// \param a_ePixelFormat pixel format of the raw image
    /// \param a_nStep length of image line in bytes, if 0 - assumed to be \p a_nWidth * sizeof(pixel)
    /// \return list of requested outputs
    SingleFrameOutputs processSingleFrame(
        RawSourceId                 a_eRawSource,
        SingleFrameOutputType::Type a_nOutput,
        const void*                 a_pData,
        uint32_t                    a_nWidth,
        uint32_t                    a_nHeight,
        PixelFormat                 a_ePixelFormat,
        uint32_t                    a_nStep = 0);

    /// Processes list of crops; this function can only be used with streams that use raw sources; the source should be
    /// open in SingleFrame mode; pipeline should contain modules responsible for crop processing (for example,
    /// classifier)
    /// \param a_eRawSource raw source to push into, this source has to be selected during startStream
    /// \param a_nOutput desired output, several outputs can be selected by or'ing the bits
    /// \param a_pCrops vector of crops
    /// \param a_nCropCount number of crops in \p a_pCrops
    /// \return list of per-crop metadata, each entry in the output corresponds to an entry in \p a_pCrops
    SingleFrameOutputs processCrops(
        RawSourceId                 a_eRawSource,
        SingleFrameOutputType::Type a_nOutput,
        const Crop*                 a_pCrops,
        uint32_t                    a_nCropCount);

    /// Updates telemetry for stream
    /// \param a_Telemetry telemetry
    /// \param a_nTimestampMs timestamp of the telemetry sample in ms, if -1 - current time is used
    void updateTelemetry(
        const TelemetryInfo& a_Telemetry,
        uint64_t             a_nTimestampMs = static_cast<uint64_t>(-1));

    /// \return stream information
    StreamInfo getStreamInfo();

private:
    friend Pipeline;
    friend ::sightx::WebProxy;

    Stream(
        detail::StreamImpl*);

    detail::StreamImpl* m_pImpl;
};


///////////////////// Implementation details

namespace cross_compile_detail
{
struct ExceptionHelper
{
    [[noreturn]] static void onThrow(
        const char* a_strMessage)
    {
        throw std::runtime_error(
            a_strMessage);
    }
};

struct CallbackHelper
{
    static void onMessageCallback(
        LoggerCallbacks*  a_pCallbacks,
        const MessageLog& a_MessageLog)
    {
        if (a_pCallbacks->OnMessage)
        {
            a_pCallbacks->OnMessage(
                a_MessageLog);
        }
    }

    static void onFrameResultsCallback(
        Callbacks*          a_pCallbacks,
        const FrameResults& a_vResults)
    {
        if (a_pCallbacks->OnFrameResults)
        {
            a_pCallbacks->OnFrameResults(
                a_vResults);
        }
    }

    static void onStreamEventCallback(
        Callbacks*       a_pCallbacks,
        const StreamLog& a_StreamLog)
    {
        if (a_pCallbacks->OnStreamEvent)
        {
            a_pCallbacks->OnStreamEvent(
                a_StreamLog);
        }
    }

    static void onServerStateChangeCallback(
        Callbacks*  a_pCallbacks,
        ServerState a_ServerState)
    {
        if (a_pCallbacks->OnServerStateChange)
        {
            a_pCallbacks->OnServerStateChange(
                a_ServerState);
        }
    }
};
} // namespace cross_compile_detail

/////////////// Logger

inline void Logger::init(
    const LoggerCallbacks& a_Callbacks,
    LogLevel               a_eMinLogLevel,
    bool                   a_bEnableDDSLogs)
{
    static LoggerCallbacks callbacks;
    callbacks = a_Callbacks;

    detail::sxLoggerInit(
        a_eMinLogLevel,
        a_bEnableDDSLogs,
        &callbacks,
        static_cast<bool>(
            a_Callbacks.OnMessage),
        &cross_compile_detail::ExceptionHelper::onThrow,
        &cross_compile_detail::CallbackHelper::onMessageCallback);
}

/////////////// Pipeline

inline Vector<ServerInfo> Pipeline::discover(
    uint32_t a_nDiscoveryTimeoutInMs,
    bool     a_bOnlyCompatible)
{
    Vector<ServerInfo> vRes;

    detail::sxDiscoverServers(
        vRes,
        a_nDiscoveryTimeoutInMs,
        a_bOnlyCompatible);

    return vRes;
}

inline std::shared_ptr<Pipeline> Pipeline::create(
    const GrpcSettings&      a_GrpcSettings,
    const DDSSettings&       a_DdsSettings,
    const RawStreamSettings& a_RawStreamSettings,
    const Callbacks&         a_Callbacks)
{
    return std::shared_ptr<Pipeline>(
        new Pipeline(
            a_GrpcSettings,
            a_DdsSettings,
            a_RawStreamSettings,
            a_Callbacks));
}

inline StartStreamConfiguration Pipeline::createStartStreamConfiguration(
    const String& a_strCustomPreset)
{
    StartStreamConfiguration res;

    detail::sxCreateStartStreamConfiguration(
        m_pImpl,
        a_strCustomPreset,
        res);

    return res;
}

inline std::shared_ptr<Stream> Pipeline::startStream(
    const StartStreamConfiguration& a_Configuration)
{
    return std::shared_ptr<Stream>(
        new Stream(
            detail::sxStartStream(
                m_pImpl,
                a_Configuration)));
}

inline std::shared_ptr<Stream> Pipeline::wrapStream(
    const String& a_strStreamId)
{
    return std::shared_ptr<Stream>(
        new Stream(
            detail::sxWrapStream(
                m_pImpl,
                a_strStreamId)));
}

inline PipelineInfo Pipeline::getPipelineInfo()
{
    PipelineInfo res;

    detail::sxGetPipelineInfo(
        m_pImpl,
        res);

    return res;
}

inline FullStreamConfiguration Pipeline::getDefaultConfiguration()
{
    FullStreamConfiguration res;

    detail::sxGetDefaultStreamConfiguration(
        m_pImpl,
        res);

    return res;
}

inline void Pipeline::shutdown(
    bool a_bForce)
{
    detail::sxShutdownPipeline(
        m_pImpl,
        a_bForce);
}

inline Pipeline::Pipeline(
    const GrpcSettings&      a_GrpcSettings,
    const DDSSettings&       a_DdsSettings,
    const RawStreamSettings& a_RawStreamSettings,
    const Callbacks&         a_Callbacks) :
        m_Callbacks(
            a_Callbacks)
{
    m_pImpl = detail::sxCreatePipeline(
        a_GrpcSettings,
        a_DdsSettings,
        a_RawStreamSettings,
        &m_Callbacks,
        static_cast<bool>(
            m_Callbacks.OnFrameResults),
        &cross_compile_detail::CallbackHelper::onFrameResultsCallback,
        &cross_compile_detail::CallbackHelper::onStreamEventCallback,
        &cross_compile_detail::CallbackHelper::onServerStateChangeCallback);
}

inline Pipeline::~Pipeline()
{
    detail::sxDestroyPipeline(
        m_pImpl);
}

/////////////// Stream

inline String Stream::getId() const
{
    String strRes;

    detail::sxGetStreamId(
        m_pImpl,
        strRes);

    return strRes;
}

inline bool Stream::isWrapped() const
{
    return detail::sxIsWrapped(
        m_pImpl);
}

inline FullStreamConfiguration Stream::getFullConfiguration(
    const String& a_strModuleAlias)
{
    FullStreamConfiguration res;

    detail::sxGetFullStreamConfiguration(
        m_pImpl,
        a_strModuleAlias,
        res);

    return res;
}

inline UpdateStreamConfiguration& Stream::getConfiguration()
{
    UpdateStreamConfiguration* pRes;

    detail::sxGetStreamConfiguration(
        m_pImpl,
        pRes);

    return *pRes;
}

inline void Stream::update()
{
    detail::sxUpdateStreamConfiguration(
        m_pImpl);
}

inline void Stream::pushRawFrame(
    RawSourceId a_eRawSource,
    const void* a_pData,
    uint32_t    a_nWidth,
    uint32_t    a_nHeight,
    PixelFormat a_ePixelFormat,
    uint32_t    a_nStep,
    uint64_t    a_nFrameId,
    uint64_t    a_nTimestampMs,
    bool        a_bBlock)
{
    detail::sxPushRawFrame(
        m_pImpl,
        a_eRawSource,
        a_pData,
        a_nWidth,
        a_nHeight,
        a_ePixelFormat,
        a_nStep,
        a_nFrameId,
        a_nTimestampMs,
        a_bBlock);
}

inline SingleFrameOutputs Stream::processSingleFrame(
    RawSourceId                 a_eRawSource,
    SingleFrameOutputType::Type a_nOutput,
    const void*                 a_pData,
    uint32_t                    a_nWidth,
    uint32_t                    a_nHeight,
    PixelFormat                 a_ePixelFormat,
    uint32_t                    a_nStep)
{
    SingleFrameOutputs res;

    detail::sxProcessSingleFrame(
        m_pImpl,
        a_eRawSource,
        a_nOutput,
        a_pData,
        a_nWidth,
        a_nHeight,
        a_ePixelFormat,
        a_nStep,
        res);

    return res;
}

inline SingleFrameOutputs Stream::processCrops(
    RawSourceId                 a_eRawSource,
    SingleFrameOutputType::Type a_nOutput,
    const Crop*                 a_pCrops,
    uint32_t                    a_nCropCount)
{
    SingleFrameOutputs res;

    detail::sxProcessCrops(
        m_pImpl,
        a_eRawSource,
        a_nOutput,
        a_pCrops,
        a_nCropCount,
        res);

    return res;
}

inline void Stream::updateTelemetry(
    const TelemetryInfo& a_Telemetry,
    uint64_t             a_nTimestampMs)
{
    detail::sxUpdateTelemetry(
        m_pImpl,
        a_Telemetry,
        a_nTimestampMs);
}

inline StreamInfo Stream::getStreamInfo()
{
    StreamInfo res;

    detail::sxGetStreamInfo(
        m_pImpl,
        res);

    return res;
}

inline Stream::Stream(
    detail::StreamImpl* a_pImpl) :
        ModuleFunctions(
            a_pImpl),
        m_pImpl(
            a_pImpl)
{
}

inline Stream::~Stream()
{
    detail::sxDestroyStream(
        m_pImpl);
}
} // namespace sdk
} // namespace sightx
