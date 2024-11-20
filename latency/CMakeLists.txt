project(sdk_samples)
cmake_minimum_required(VERSION 3.10)

find_package(OpenCV REQUIRED)
find_package(Iconv)



add_executable(sdk_sample_raw_frames
    sdk_sample_raw_frames.cpp
)

target_include_directories(sdk_sample_raw_frames
    PRIVATE
    /usr/local/Merlin/include
)

target_link_libraries(sdk_sample_raw_frames
    PRIVATE
    /usr/local/Merlin/lib/libsightx_sdk.so

    ${OpenCV_LIBRARIES}
)
