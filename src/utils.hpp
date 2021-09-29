#pragma once
#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>
#include <string>


namespace utils {
std::string concat(nlohmann::json json_parse);
std::string parse(nlohmann::json json_parse, int maxSize);
}