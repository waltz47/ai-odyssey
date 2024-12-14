// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <map>
#include <string>
#include <vector>
#include "Async/Async.h"
#include "llm_fn.h"
#include "json_parser.h"
#include "worldcharacter.generated.h"

using std::map;
using std::string;
using std::vector;

UCLASS()
class AIODYSSEY_API Aworldcharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	Aworldcharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void DisplayDialogue(); //display dialogue on screen via UI

	virtual FString Interact();
	void GetRecordedChar(FString&);
	void EnableRecording() { isrecording = true; }
	void ResetRecording() { isrecording = false; recording = FString(""); }
	void OnRecordingAccept();

	UFUNCTION(BlueprintCallable)
	FString GetDialogueToDisplay();

	std::vector<std::pair<std::string, std::string>> history; //message history
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString lastDialogue;

	FString recording;
	bool isrecording = false;

	TFuture<FString> Future;

};
