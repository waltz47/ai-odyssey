// Fill out your copyright notice in the Description page of Project Settings.


#include "worldcharacter.h"

// Sets default values
Aworldcharacter::Aworldcharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Aworldcharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void Aworldcharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Future.IsValid() && Future.IsReady()) {
		FString response = Future.Get();
		if (response.IsEmpty()) return;
		lastDialogue = response;
		UE_LOG(LogTemp, Warning, TEXT("Final Response: %s"), *lastDialogue);
		history.push_back(std::make_pair("assistant", std::string(TCHAR_TO_UTF8(*lastDialogue))));
		//GEngine->AddOnScreenDebugMessage(-1, 3.0, FColor::Red, lastDialogue);
		DisplayDialogue();
		Future = TFuture<FString>();
	}
}

FString Aworldcharacter::Interact() {
	FString response = Ullm_fn::GetLLMResponse(history);
	return response;
}

void Aworldcharacter::GetRecordedChar(FString& f) {
	if (isrecording) {
		recording.Append(f);
	}
}

void Aworldcharacter::OnRecordingAccept() {
	history.push_back(std::make_pair("user", std::string(TCHAR_TO_UTF8(*recording))));
	Future = Async(EAsyncExecution::Thread, [this]() -> FString {
		FString resp = Interact();
		return resp;
	});

	ResetRecording();
}

FString Aworldcharacter::GetDialogueToDisplay() {
	FString ret = lastDialogue;
	return ret;
}