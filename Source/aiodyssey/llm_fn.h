// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include <map>
#include <string>
#include "llm_fn.generated.h"

using std::map;
using std::string;

UCLASS()
class AIODYSSEY_API Ullm_fn : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	FString GetLLMResponse(std::map<std::string, std::string>& history); //get response and append to history. only called by ai chars
	
};
