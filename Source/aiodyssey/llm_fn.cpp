// Fill out your copyright notice in the Description page of Project Settings.


#include "llm_fn.h"
#include "api_call.h"
#include "json_parser.h"

FString Ullm_fn::GetLLMResponse(std::map<std::string, std::string>& history) {
    
	FString history_to_string = JsonParser::MapToJSONString(history);
	FString response = Uapi_call::CallAPI(history_to_string);
	UE_LOG(LogTemp, Warning, TEXT("Response from LLM is: %s"), *response);
	return response;
}