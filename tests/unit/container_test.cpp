#include <gtest/gtest.h>

#include <list>
#include <string>
#include <vector>

#include "print_ip.h"

TEST(PrintIp_Container_Test, VectorInt) {
    testing::internal::CaptureStdout();
    ip::print_ip(std::vector<int>{100, 200, 300, 400});
    const std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "100.200.300.400\n");
}

TEST(PrintIp_Container_Test, ListShort) {
    testing::internal::CaptureStdout();
    ip::print_ip(std::list<short>{400, 300, 200, 100});
    const std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "400.300.200.100\n");
}