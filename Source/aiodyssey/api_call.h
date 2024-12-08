// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "api_call.generated.h"

UCLASS(Blueprintable)
class AIODYSSEY_API Uapi_call : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
    static FString CallAPI(FString Data);

private:
    static void RunPyScript(const FString& CmdLine);
};