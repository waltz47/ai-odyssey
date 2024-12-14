// Fill out your copyright notice in the Description page of Project Settings.


#include "llm_fn.h"
#include "api_call.h"
#include <vector>
#include "json_parser.h"

FString Ullm_fn::GetLLMResponse(std::vector<std::pair<std::string, std::string>>& history) {
    
	FString history_to_string = JsonParser::MapToJSONString(history);

	UE_LOG(LogTemp, Warning, TEXT("History: %s"), *history_to_string);
	FString response = Uapi_call::CallAPI(history_to_string);
	UE_LOG(LogTemp, Warning, TEXT("Response from LLM is: %s"), *response);
	JsonParser parser;
	parser.parse(TCHAR_TO_UTF8(*response));
	response =  FString(parser.getFunctionArguments()["dialogue"].c_str());
	UE_LOG(LogTemp, Warning, TEXT("Response after parsing fn: %s"), *response);
	return response;
}