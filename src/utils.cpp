#include "utils.hpp"

namespace utils {
/** 
     * Concatenate json values with a comma separator
     * @param json_parse json to be parsed
     * @return parsed value
     */
auto concat(nlohmann::json json_parse) -> std::string
{
    std::stringstream parsed;
    for (auto& el : json_parse) {
        if (el.is_structured()) {
            parsed << concat(el);
        } else {
            parsed << el << ",";
        }
    }
    return parsed.str();
}

/**
     * Parse a json to a string in a fixed size
     * @param json_parse json to be parsed
     * @param max_size sized to be delimitated
     */
auto parse(nlohmann::json json_parse, int max_size) -> std::string
{
    std::string response = concat(json_parse);
    response.pop_back();

    int position = 0;
    while ((position = response.find('"')) != std::string::npos) {
        response.erase(position, 1);
    }

    if (response.size() > max_size) {
        response.resize(max_size);
        int count = max_size - 1;
        while (response[count] != ',') {
            response.pop_back();
            count--;
        }
        response.pop_back();
    }

    return response;
}

/**
 * Saves a JSON
 * @param json to be saved
 * @param path to save the json
 */
void saveJson(const nlohmann::json& json, std::filesystem::path path)
{
    if (!std::filesystem::is_directory(path)) {
        throw std::invalid_argument("Path is not a directory");
    }

    time_t rawtime;
    struct tm* timeinfo;

    constexpr int bufferSize(80);
    std::array<char, bufferSize> buffer;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer.data(), bufferSize, "%F-%H-%M-%S", timeinfo);

    path /= buffer.data();
    path += ".json";

    std::ofstream file(path);
    std::cout << "Wrote file: " << path << std::endl;
    file << json;
    file.close();
}

/**
 * Takes the last byte from a IP
 * @param ip string contaning the IP
 * @return last byte from the IP
 */
auto parseIP(const std::string& ip) -> uint8_t
{
    return std::stoi(ip.substr(ip.rfind(".") + 1, 3));
}

} // namespace utils
