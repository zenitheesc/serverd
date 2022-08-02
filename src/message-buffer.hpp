#pragma once
#include <chrono>
#include <cstddef>
#include <deque>
#include <iostream>
#include <mutex>
#include <nlohmann/json.hpp>
#include <string>
#include <thread>
#include <vector>

class Message {
private:
    std::vector<std::uint8_t> m_message;
    std::size_t m_maxSize;
    std::size_t m_currSize;

    void write(const nlohmann::json& json);

public:
    explicit Message(std::size_t maxSize);
    Message() = default;

    template <typename T>
    void save(const nlohmann::json& json);

    void operator<<(const nlohmann::json& json);
    void operator>>(nlohmann::json& json);
};

class MessagesBuffer {
private:
    std::timed_mutex m_mutex;

    static constexpr int MAX_ID = 256;
    std::array<Message, MAX_ID> m_messages;
    std::deque<std::uint8_t> m_currIndex;

    std::size_t m_numBytes;

public:
    explicit MessagesBuffer(std::size_t numBytes);

    auto getCurrMessage() -> nlohmann::json;
    void write(std::uint8_t id, const nlohmann::json& message);
};
