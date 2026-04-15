#include <gtest/gtest.h>

#include <cstdint>
#include <string>

#include "print_ip.h"

TEST(PrintIp_Int_Test, Int8) {
    testing::internal::CaptureStdout();
    ip::print_ip(int8_t{ -1 });
    const std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "255\n");
}

TEST(PrintIp_Int_Test, Int16) {
    testing::internal::CaptureStdout();
    ip::print_ip(int16_t{ 0 });
    const std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "0.0\n");
}

TEST(PrintIp_Int_Test, Int32) {
    testing::internal::CaptureStdout();
    ip::print_ip(int32_t{ 2130706433 });
    const std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "127.0.0.1\n");
}

TEST(PrintIp_Int_Test, Int64) {
    testing::internal::CaptureStdout();
    ip::print_ip(int64_t{ 8875824491850138409 });
    const std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "123.45.67.89.101.112.131.41\n");
}
