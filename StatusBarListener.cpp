#include "StatusBarListener.h"

StatusBarListener::StatusBarListener() : test_count_(0), tests_passed_(0), tests_failed_(0), tests_skipped_(0) {}

void StatusBarListener::OnTestProgramStart(const ::testing::UnitTest& unit_test) {
    test_count_ = unit_test.test_to_run_count();
    std::cout << "Running " << test_count_ << " tests..." << std::endl;
}

void StatusBarListener::OnTestEnd(const ::testing::TestInfo& test_info) {
    if (test_info.result()->Passed()) {
        tests_passed_++;
    }
    else if (test_info.result()->Skipped()) {
        tests_skipped_++;
    } 
    else {
        tests_failed_++;
    }
    UpdateStatusBar();
}

void StatusBarListener::OnTestProgramEnd(const ::testing::UnitTest& unit_test) {
    std::cout << "\nTesting completed.\n";
    std::cout << "Total tests: " << test_count_ << "\n";
    std::cout << "Passed: " << tests_passed_ << "\n";
    std::cout << "Failed: " << tests_failed_ << "\n";
    std::cout << "Skipped: " << tests_skipped_ << "\n";
}

void StatusBarListener::UpdateStatusBar() {
    std::cout << "\rProgress: [";
    int progress = (tests_passed_ + tests_failed_ + tests_skipped_) * kStatusBarLength / test_count_;
    for (int i = 0; i < progress; ++i) {
        std::cout << "#";
    }
    for (int i = progress; i < kStatusBarLength; ++i) {
        std::cout << " ";
    }
    std::cout << "] " << (tests_passed_ + tests_failed_ + tests_skipped_) * 100 / test_count_ << "%";
    std::cout.flush();
}
