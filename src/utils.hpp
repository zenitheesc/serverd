#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <nlohmann/json.hpp>
#define SYMBOL '#'

namespace utils{
    std::string concat (nlohmann::json json_parse);
    std::string parse (nlohmann::json json_parse, int maxsize);
}