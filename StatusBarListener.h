#ifndef STATUS_BAR_LISTENER_H
#define STATUS_BAR_LISTENER_H

#include "gtest/gtest.h"
#include <iostream>

class StatusBarListener : public ::testing::EmptyTestEventListener {
public:
    StatusBarListener();

    void OnTestProgramStart(const ::testing::UnitTest& unit_test) override;
    void OnTestEnd(const ::testing::TestInfo& test_info) override;
    void OnTestProgramEnd(const ::testing::UnitTest& unit_test) override;

private:
    int test_count_;
    int tests_passed_;
    int tests_failed_;
    int tests_skipped_;

    void UpdateStatusBar();
    static const int kStatusBarLength = 50; // Status bar length set to 50
};

#endif // STATUS_BAR_LISTENER_H
