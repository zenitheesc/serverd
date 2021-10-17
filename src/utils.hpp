#pragma once

#include <array>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>
#include <string>

namespace utils {
auto concat(nlohmann::json json_parse) -> std::string;
auto parse(nlohmann::json json_parse, int max_size) -> std::string;
void saveJson(const nlohmann::json& json, std::filesystem::path path = std::filesystem::current_path());
}
