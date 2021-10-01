#include "message-buffer.hpp"

MessagesBuffer::MessagesBuffer(int delay) {
    m_thread =
        std::make_unique<std::thread>(&MessagesBuffer::read, this, delay);
    m_thread->detach();
}

void MessagesBuffer::read(int delay) {
    auto it = m_messages.begin();
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(delay));

        std::unique_lock<std::timed_mutex> l(m_mutex, std::defer_lock);
        l.try_lock_for(std::chrono::milliseconds(30));

        if (it != m_messages.end()) {
            std::cout << "leu: " << it->first << " => " << it->second
                      << std::endl;
            it = m_messages.erase(it);
        } else {
            it = m_messages.begin();
        }
    }
}

void MessagesBuffer::write(std::string IP, std::string message) {
    std::unique_lock<std::timed_mutex> l(m_mutex, std::defer_lock);
    l.try_lock_for(std::chrono::milliseconds(30));

    m_messages[IP] = message;
    std::cout << "Escreveu: " << IP << " => " << message << std::endl;
}
