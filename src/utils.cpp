#include "utils.hpp"

namespace utils {
/** 
     * Concatenate json values with a comma separator
     * @param json_parse json to be parsed
     * @return parsed value
     */
std::string concat(nlohmann::json json_parse)
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
std::string parse(nlohmann::json json_parse, int max_size)
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
}