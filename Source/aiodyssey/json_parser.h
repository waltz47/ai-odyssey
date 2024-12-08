#pragma once

#include <string>
#include <map>
#include "rapidjson/document.h"

class JsonParser {
public:
    JsonParser();
    ~JsonParser() = default;

    // Parse a new JSON string
    void parse(const std::string& jsonString);

    // Returns the name of the function from the JSON
    std::string getFunctionName() const;

    // Returns a map of the function arguments where the key is the argument name and value is its value
    std::map<std::string, std::string> getFunctionArguments() const;

    static FString MapToJSONString(std::map<std::string, std::string>& history);
    

private:
    rapidjson::Document document;
};