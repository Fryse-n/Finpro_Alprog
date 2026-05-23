#pragma once
#include <string>

class JSONParser {
public:
    static std::string getValue(const std::string& json, const std::string& key);
    static std::string error(const std::string& message);
    static std::string success(const std::string& message);
};