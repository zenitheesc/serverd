#include "message-buffer.hpp"
#include <algorithm>

Message::Message(std::size_t maxSize)
    : m_maxSize(maxSize)
    , m_currSize(0)
{
    m_message.resize(m_maxSize);
}

template <typename T>
void Message::save(const nlohmann::json& json)
{
    T value = json;
    if (m_currSize + sizeof(T) <= m_maxSize) {
        std::memcpy(m_message.data() + m_currSize, &value, sizeof(T));
        m_currSize += sizeof(T);
    }
}

template <>
void Message::save<std::string>(const nlohmann::json& json)
{
    std::string value = json;
    if (m_currSize + value.size() <= m_maxSize) {
        std::memcpy(m_message.data() + m_currSize, value.data(), value.size() + 1);
        m_currSize += value.size() + 1;
    }
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
    default:
        break;
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

void MessagesBuffer::write(std::uint8_t id, const nlohmann::json& message)
{
    std::unique_lock<std::timed_mutex> l(m_mutex, std::defer_lock);
    l.try_lock_for(std::chrono::milliseconds(30));

    constexpr int numBytes = 90;
    Message messageObj(numBytes);

    messageObj.save<std::int8_t>(id);
    messageObj << message;

    m_messages[id] = messageObj;

    if (std::find(std::begin(m_currIndex), std::end(m_currIndex), id) == std::end(m_currIndex)) {
        m_currIndex.push_back(id);
    }
}

auto MessagesBuffer::getCurrMessage() -> nlohmann::json
{
    std::unique_lock<std::timed_mutex> l { m_mutex, std::defer_lock };
    l.try_lock_for(std::chrono::milliseconds(30));

    nlohmann::json json;
    if (m_currIndex.empty()) {
        json["data"];
        return json;
    }

    nlohmann::json jsonVector;
    m_messages[m_currIndex.front()] >> jsonVector;

    json["data"] = jsonVector;

    std::cout << "sent message with id " << static_cast<int>(m_currIndex.front()) <<  std::endl;

    m_currIndex.pop_front();
    return json;
}
