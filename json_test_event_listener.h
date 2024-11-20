#pragma once
#include <gtest/gtest.h>
#include <fstream>
#include <string>

class JsonTestEventListener : public testing::TestEventListener {
public:
    explicit JsonTestEventListener(const std::string& output_file) : output_file_(output_file) {
        output_stream_.open(output_file);
    }
    
    ~JsonTestEventListener() override {
        if (output_stream_.is_open()) {
            output_stream_.close();
        }
    }

    void OnTestProgramStart(const testing::UnitTest& unit_test) override {}
    void OnTestIterationStart(const testing::UnitTest& unit_test, int iteration) override {}
    void OnEnvironmentsSetUpStart(const testing::UnitTest& unit_test) override {}
    void OnEnvironmentsSetUpEnd(const testing::UnitTest& unit_test) override {}
    void OnTestStart(const testing::TestInfo& test_info) override {}
    void OnTestPartResult(const testing::TestPartResult& result) override {}
    void OnTestEnd(const testing::TestInfo& test_info) override {}
    void OnEnvironmentsTearDownStart(const testing::UnitTest& unit_test) override {}
    void OnEnvironmentsTearDownEnd(const testing::UnitTest& unit_test) override {}
    void OnTestIterationEnd(const testing::UnitTest& unit_test, int iteration) override {}
    void OnTestProgramEnd(const testing::UnitTest& unit_test) override {}

private:
    std::ofstream output_stream_;
    std::string output_file_;
};
