#pragma once

#include <nlohmann/json.hpp>
#include <sstream>
#include <string>

namespace utils
{
    std::string concat(nlohmann::json json_parse);
    std::string parse(nlohmann::json json_parse, int max_size);
}
