project(sdk_samples)
cmake_minimum_required(VERSION 3.10)
set(CMAKE_BUILD_TYPE Debug)

# Find and include Google Test
find_package(GTest REQUIRED)
include_directories(${GTest_INCLUDE_DIRS})

find_package(jsoncpp CONFIG REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Iconv)

add_executable(sdk_sample_raw_frames
    sdk_sample_raw_frames.cpp
    merlin_generated_tests.cpp
    merlin_print_enums.cpp
    helper.cpp
    StatusBarListener.cpp
    update_tests_flag.cpp
    general_tests.cpp
)

target_include_directories(sdk_sample_raw_frames
    PRIVATE
    /usr/local/Merlin/include
)

target_link_libraries(sdk_sample_raw_frames
    PRIVATE
    /usr/local/Merlin/lib/libsightx_sdk.so
    ${OpenCV_LIBRARIES}
    ${GTest_LIBRARIES}
    gtest
    gtest_main
    pthread
    jsoncpp_lib
)

