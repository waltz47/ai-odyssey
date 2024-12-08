// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "api_call.generated.h"

UCLASS()
class AIODYSSEY_API Aapi_call : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Aapi_call();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="API_CALL")
	void CallAPI(FString Data);

private:
	void RunPyScript(const FString& CmdLine);

};
