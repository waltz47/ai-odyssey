#include "json_parser.h"
#include <sstream>
#include "Serialization/JsonSerializer.h"
#include "Dom/JsonObject.h"

JsonParser::JsonParser() : document() {
    // Constructor initializes document
}

void JsonParser::parse(const std::string& jsonString) {
    document.Parse(jsonString.c_str());
    if (document.HasParseError()) {
        throw std::runtime_error("JSON parsing error");
    }
}

std::string JsonParser::getFunctionName() const {
    if (document.HasMember("function") && document["function"].IsObject() &&
        document["function"].HasMember("name") && document["function"]["name"].IsString()) {
        return document["function"]["name"].GetString();
    }
    return "";
}

std::map<std::string, std::string> JsonParser::getFunctionArguments() const {
    std::map<std::string, std::string> args;

    if (document.HasMember("function") && document["function"].IsObject() &&
        document["function"].HasMember("arguments") && document["function"]["arguments"].IsObject()) {

        const rapidjson::Value& arguments = document["function"]["arguments"];
        for (rapidjson::Value::ConstMemberIterator itr = arguments.MemberBegin(); itr != arguments.MemberEnd(); ++itr) {
            if (itr->value.IsString()) { // only add string type arguments for now TODO: fix this
                args[itr->name.GetString()] = itr->value.GetString();
            }
        }
    }

    return args;
}
FString JsonParser::MapToJSONString(std::map<std::string, std::string>& history)
{
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

    TArray<TSharedPtr<FJsonValue>> HistoryArray;
    for (const auto& entry : history)
    {
        TSharedPtr<FJsonObject> Message = MakeShareable(new FJsonObject);
        Message->SetStringField("role", ANSI_TO_TCHAR(entry.first.c_str()));
        Message->SetStringField("content", ANSI_TO_TCHAR(entry.second.c_str()));
        HistoryArray.Add(MakeShareable(new FJsonValueObject(Message)));
    }

    JsonObject->SetArrayField("history", HistoryArray);

    FString OutputString;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

    return OutputString;
}