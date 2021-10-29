#pragma once
#include <chrono>
#include <iostream>
#include <map>
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
    template <typename T>
    void save(const nlohmann::json& json);

public:
    explicit Message(std::size_t maxSize);
    void operator<<(const nlohmann::json& json);
    void operator>>(nlohmann::json& json);
};

class MessagesBuffer {
private:
    std::timed_mutex m_mutex;
    std::unique_ptr<std::thread> m_thread;
    std::map<std::uint8_t, Message> m_messages;
    int delay;

    void read();

public:
    explicit MessagesBuffer(int m_delay);

    void write(std::uint8_t id, const nlohmann::json& message);
};
