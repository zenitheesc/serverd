#include "../../src/message-buffer.hpp"
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

template <typename T>
void testInput(T value)
{
    Message message(26);
    nlohmann::json json = { { "value", value } };

    message << json;
    nlohmann::json result;

    message >> result;
    std::vector<std::uint8_t> vector = result;
    T resultConverted;
    std::memcpy(&resultConverted, vector.data(), sizeof(T));

    EXPECT_EQ(resultConverted, value);
}

template <>
void testInput<std::string>(std::string value)
{
    Message message(26);
    nlohmann::json json = { { "value", value } };

    message << json;
    nlohmann::json result;

    message >> result;
    std::vector<std::uint8_t> vector = result;

    std::string resultConverted;
    resultConverted.resize(vector.size());
    std::memcpy(resultConverted.data(), vector.data(), vector.size());

    EXPECT_EQ(resultConverted, value);
}

TEST(Message, Bool)
{
    testInput(true);
}

TEST(Message, Int)
{
    testInput(42);
}

TEST(Message, Float)
{
    testInput(420.69f);
}

TEST(Message, String)
{
    testInput<std::string>("batata");
}
