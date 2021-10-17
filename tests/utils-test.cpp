#include "../src/utils.hpp"
#include <gtest/gtest.h>

TEST(Utils, ParseIP)
{
    EXPECT_EQ(255, utils::parseIP("192.168.255"));
}
