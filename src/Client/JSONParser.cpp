#include "JSONParser.h"
#include <cctype>

using namespace std;

static string escapeJson(const string& s) {
    string out;
    for (char c : s) {
        if (c == '\\') out += "\\\\";
        else if (c == '"') out += "\\\"";
        else if (c == '\n') out += "\\n";
        else if (c == '\r') {}
        else out += c;
    }
    return out;
}

static string trim(const string& s) {
    size_t start = 0;
    while (start < s.size() && isspace((unsigned char)s[start])) start++;

    size_t end = s.size();
    while (end > start && isspace((unsigned char)s[end - 1])) end--;

    return s.substr(start, end - start);
}

string JSONParser::getValue(const string& json, const string& key) {
    string pattern = "\"" + key + "\"";
    size_t pos = json.find(pattern);
    if (pos == string::npos) return "";

    pos = json.find(':', pos);
    if (pos == string::npos) return "";

    pos++;
    while (pos < json.size() && isspace((unsigned char)json[pos])) pos++;
    if (pos >= json.size()) return "";

    if (json[pos] == '"') {
        pos++;
        size_t end = pos;
        string value;
        while (end < json.size()) {
            if (json[end] == '"' && json[end - 1] != '\\') break;
            value += json[end];
            end++;
        }
        return value;
    }

    size_t end = pos;
    while (end < json.size() && json[end] != ',' && json[end] != '}' && json[end] != ']') {
        end++;
    }

    return trim(json.substr(pos, end - pos));
}

string JSONParser::error(const string& message) {
    return string("{\"status\":\"ERROR\",\"message\":\"") + escapeJson(message) + "\"}";
}

string JSONParser::success(const string& message) {
    return string("{\"status\":\"OK\",\"message\":\"") + escapeJson(message) + "\"}";
}