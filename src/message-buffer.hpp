#pragma once
#include <chrono>
#include <iostream>
#include <map>
#include <mutex>
#include <string>
#include <thread>

class MessagesBuffer {
private:
    std::timed_mutex m_mutex;
    std::unique_ptr<std::thread> m_thread;
    std::map<std::uint8_t, std::string> m_messages;
    int delay;

    void read();

public:
    MessagesBuffer(int m_delay);

    void write(std::uint8_t IP, std::string message);
};
