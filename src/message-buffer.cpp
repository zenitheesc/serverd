#include "message-buffer.hpp"

Message::Message(std::size_t maxSize)
    : m_maxSize(maxSize)
    , m_currSize(0)
{
    m_message.resize(m_maxSize);
}

template <typename T>
void Message::save(const nlohmann::json& json)
{
    if (m_currSize + sizeof(T) > m_maxSize) {
        return;
    }
    T value = json;
    std::memcpy(m_message.data() + m_currSize, &value, sizeof(T));
    m_currSize += sizeof(T);
}

template <>
void Message::save<std::string>(const nlohmann::json& json)
{
    std::string value = json;
    if (m_currSize + value.size() > m_maxSize) {
        return;
    }
    std::memcpy(m_message.data() + m_currSize, value.data(), value.size());
    m_currSize += value.size();
}

void Message::write(const nlohmann::json& json)
{
    switch (json.type()) {
    case nlohmann::detail::value_t::number_integer: {
        save<std::int16_t>(json);
        break;
    }
    case nlohmann::detail::value_t::number_float: {
        save<float>(json);
        break;
    }
    case nlohmann::detail::value_t::number_unsigned: {
        save<std::uint16_t>(json);
        break;
    }
    case nlohmann::detail::value_t::boolean: {
        save<bool>(json);
        break;
    }
    case nlohmann::detail::value_t::string: {
        save<std::string>(json);
        break;
    }
    }
}

void Message::operator<<(const nlohmann::json& json)
{
    for (auto it : json) {
        if (it.is_structured()) {
            operator<<(it);
        } else {
            write(it);
        }
    }
}

void Message::operator>>(nlohmann::json& json)
{
    json = m_message;
}

MessagesBuffer::MessagesBuffer(int m_delay)
    : delay { m_delay }
{
    m_thread = std::make_unique<std::thread>(&MessagesBuffer::read, this);
    m_thread->detach();
}

void MessagesBuffer::read()
{
    auto it = m_messages.begin();
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(delay));

        std::unique_lock<std::timed_mutex> l(m_mutex, std::defer_lock);
        l.try_lock_for(std::chrono::milliseconds(30));

        if (it != m_messages.end()) {
            //mostrar conteudo
            nlohmann::json jsonVector;
            it->second >> jsonVector;
            std::cout << static_cast<int>(it->first) << " : " << jsonVector << std::endl;

            it = m_messages.erase(it);
        } else {
            it = m_messages.begin();
        }
    }
}

void MessagesBuffer::write(std::uint8_t id, const nlohmann::json& message)
{
    std::unique_lock<std::timed_mutex> l(m_mutex, std::defer_lock);
    l.try_lock_for(std::chrono::milliseconds(30));
    Message messageObj(26);
    messageObj << message;
    m_messages.insert(std::make_pair(id, messageObj));
}
