#include <gtest/gtest.h>

#include <string>

#include "print_ip.h"

TEST(PrintIp_String_Test, StdString) {
    testing::internal::CaptureStdout();
    ip::print_ip(std::string{"Hello, World!"});
    const std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Hello, World!\n");
}