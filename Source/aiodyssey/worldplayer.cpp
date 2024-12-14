// Fill out your copyright notice in the Description page of Project Settings.

#include "worldplayer.h"
#include "worldcharacter.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "InputCoreTypes.h"

// Sets default values
Aworldplayer::Aworldplayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void Aworldplayer::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void Aworldplayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void Aworldplayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind movement functions
	PlayerInputComponent->BindAxis("MoveForward", this, &Aworldplayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &Aworldplayer::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &Aworldplayer::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &Aworldplayer::Turn);

	// Bind action functions
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &Aworldplayer::Interact);

	PlayerInputComponent->BindKey(EKeys::AnyKey, IE_Pressed, this, &Aworldplayer::OnAnyKeyPressed);
}

void Aworldplayer::MoveForward(float Value)
{
	if (interacting) return;
	AddMovementInput(GetActorForwardVector(), Value);
}

void Aworldplayer::MoveRight(float Value)
{
	if (interacting) return;
	AddMovementInput(GetActorRightVector(), Value);
}

void Aworldplayer::LookUp(float Value)
{
	if (interacting) return;
	AddControllerPitchInput(Value);
}

void Aworldplayer::Turn(float Value)
{
	if (interacting) return;
	AddControllerYawInput(Value);
}

void Aworldplayer::Interact()
{
	if (interacting) return;
	FHitResult HitResult;
	FVector location;
	FRotator rotation;
	GetActorEyesViewPoint(location, rotation);
	FVector Start = location;
	FVector End = Start + (rotation.Vector() * 500.0f);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Pawn, CollisionParams);

	if (bHit && HitResult.GetActor()->IsA(Aworldcharacter::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Interacted with a world character!"));
		Aworldcharacter* character = Cast<Aworldcharacter>(HitResult.GetActor());
		character->EnableRecording();
		npc = character;
		interacting = true;
		lastinteractingat = GetGameTimeSinceCreation();
	}
	else {
		interacting = false;
	}

	// Draw debug line for visualization
	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);
}

void Aworldplayer::OnAnyKeyPressed(FKey Key)
{
	if ((GetGameTimeSinceCreation() - lastinteractingat) <= 0.1f) return;
	if (IsValid(npc) && npc->isrecording) {
		FString keyname = Key.ToString();
		if (keyname == "Esc") {
			npc->ResetRecording();
		}
		else if (keyname == "Enter") {
			interacting = false;
			npc->OnRecordingAccept();
			npc = nullptr;
		}
		else if (keyname == "SpaceBar") {
			keyname = " ";
		}
		else if (keyname == "Period") {
			keyname = ".";
		}

		keyname = keyname.ToLower();
		UE_LOG(LogTemp, Warning, TEXT("Key pressed: %s"), *keyname);
		if ((keyname.Len() > 1)) {
			return;
		}
		
		npc->GetRecordedChar(keyname);

	}
}