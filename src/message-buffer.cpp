#include "message-buffer.hpp"

MessagesBuffer::MessagesBuffer(int delay) {
    this->delay = delay;
    m_thread =
        std::make_unique<std::thread>(&MessagesBuffer::read, this);
    m_thread->detach();
}

void MessagesBuffer::read() {
    auto it = m_messages.begin();
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(delay));

        std::unique_lock<std::timed_mutex> l(m_mutex, std::defer_lock);
        l.try_lock_for(std::chrono::milliseconds(30));

        if (it != m_messages.end()) {
            //mostrar conteudo
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
}
