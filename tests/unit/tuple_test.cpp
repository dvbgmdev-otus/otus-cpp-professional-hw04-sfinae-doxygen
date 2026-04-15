#include <gtest/gtest.h>

#include <string>
#include <tuple>

#include "print_ip.h"

TEST(PrintIp_Tuple_Test, HomogeneousTupleInt) {
    testing::internal::CaptureStdout();
    ip::print_ip(std::make_tuple(123, 456, 789, 0));
    const std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "123.456.789.0\n");
}