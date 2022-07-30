#include "utils.hpp"

namespace utils {
/**
 * Saves a JSON
 * @param json to be saved
 * @param path to save the json
 */
void saveJson(const nlohmann::json& json, std::filesystem::path path)
{
    std::filesystem::create_directory(path);

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

// got it from https://thispointer.com/find-and-replace-all-occurrences-of-a-sub-string-in-c/
void findReplace(std::string& data, std::string const& toSearch, std::string const& replaceStr)
{
    // Get the first occurrence
    size_t pos = data.find(toSearch);
    // Repeat till end is reached
    while (pos != std::string::npos) {
        // Replace this occurrence of Sub String
        data.replace(pos, toSearch.size(), replaceStr);
        // Get the next occurrence from the current position
        pos = data.find(toSearch, pos + replaceStr.size());
    }
}

void formatBIPS(std::string& message)
{
    findReplace(message, "\\", "");
    findReplace(message, "\"{", "{");
    findReplace(message, "}\"", "}");
    findReplace(message, "(", "[");
    findReplace(message, ")", "]");
}
} // namespace utils
