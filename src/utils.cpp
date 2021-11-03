#include "utils.hpp"

namespace utils {
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
} // namespace utils
