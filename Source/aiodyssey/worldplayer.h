// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "worldplayer.generated.h"

UCLASS()
class AIODYSSEY_API Aworldplayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	Aworldplayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// Movement functions
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void Turn(float Value);
	void Interact();
	UFUNCTION()
	void OnAnyKeyPressed(FKey key);

	bool interacting = false;
	float lastinteractingat = 0.f;

	UPROPERTY()
		class Aworldcharacter* npc = nullptr; //TODO: fix this. super hacky

};
