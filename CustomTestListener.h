#ifndef CUSTOM_TEST_LISTENER_H_
#define CUSTOM_TEST_LISTENER_H_

#include "gtest/gtest.h"
#include <json/json.h>
#include <fstream>
#include <iostream>
#include <regex>

class CustomTestListener : public ::testing::EmptyTestEventListener {
public:
    explicit CustomTestListener(const std::string& output_file) : output_file_(output_file) {}

    void OnTestPartResult(const ::testing::TestPartResult& test_part_result) override {
        if (test_part_result.failed()) {
            std::string message = test_part_result.message();
            std::smatch match;
            std::regex regex1(R"(Expected equality of these values:\n  (.*)\n    Which is: (.*)\n  (.*)\n    Which is: (.*))");
            std::regex regex2(R"(Expected equality of these values:\n  (.*)\n    Which is: (.*)\n  (.*))");
            std::regex regex3(R"(Expected: (.*) (.*) (.*), actual: (.*) vs (.*)\n)");
            std::regex regex4(R"(Duplicated egde: (.*))");

            if (std::regex_search(message, match, regex1) && match.size() == 5) {
                current_failure_["actual_value"] = match.str(2);
                current_failure_["expected_value"] = match.str(4);
            } else if (std::regex_search(message, match, regex2) && match.size() == 4) {
                current_failure_["actual_value"] = match.str(2);
                current_failure_["expected_value"] = match.str(3);
            } else if (std::regex_search(message, match, regex3) && match.size() == 6) {
                current_failure_["actual_value"] = match.str(4);
                current_failure_["expected_value"] = match.str(2) + " " + match.str(5);
            } else if (std::regex_search(message, match, regex4) && match.size() == 2) {
                current_failure_["actual_value"] = "Edge --> " + match.str(1) + " duplicated";
                current_failure_["expected_value"] = "No duplicated edges.";
            } else {
                current_failure_["actual_value"] = "";
                current_failure_["expected_value"] = "";
            }
            current_failure_["description"] = message;
            failures_.append(current_failure_);
        }
    }

    void OnTestEnd(const ::testing::TestInfo& test_info) override {
        if (test_info.result()->Failed()) {
            Json::Value failed_test;
            failed_test["name"] = test_info.test_case_name();
            failed_test["test"] = test_info.name();
            failed_test["status"] = "FAILED";
            if (!failures_.isNull()) {
                failed_test["failures"] = failures_;
            }
            failed_tests_.append(failed_test);
            std::cout << "Test failed: " << test_info.test_case_name() << "." << test_info.name() << std::endl;
        }
        // Clear the failures for the next test
        failures_.clear();
    }

    void OnTestProgramEnd(const ::testing::UnitTest& /*unit_test*/) override {
        Json::StreamWriterBuilder writer;
        std::ofstream output_file(output_file_);
        output_file << Json::writeString(writer, failed_tests_);
        output_file.close();
        std::cout << "Failed tests written to " << output_file_ << std::endl;
    }

private:
    std::string output_file_;
    Json::Value failed_tests_;
    Json::Value failures_; // To store failures of the current test
    Json::Value current_failure_; // To store the current failure details
};

#endif  // CUSTOM_TEST_LISTENER_H_
