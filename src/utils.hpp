#pragma once

#include <nlohmann/json.hpp>
#include <sstream>
#include <string>

namespace utils {
auto concat(nlohmann::json json_parse) -> std::string;
auto parse(nlohmann::json json_parse, int max_size) -> std::string;
}
