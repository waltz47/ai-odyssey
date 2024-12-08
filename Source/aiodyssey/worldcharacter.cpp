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

}

// Called to bind functionality to input
void Aworldcharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

