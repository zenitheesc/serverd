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
    std::map<std::string, std::string> m_messages;

    void read(int delay);

   public:
    MessagesBuffer(int delay);

    void write(std::string IP, std::string message);
};
