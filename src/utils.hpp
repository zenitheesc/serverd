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
void saveJson(const nlohmann::json& json, std::filesystem::path path = std::filesystem::current_path());
}
