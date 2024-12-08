// Fill out your copyright notice in the Description page of Project Settings.

#include "api_call.h"

// Sets default values
Aapi_call::Aapi_call()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void Aapi_call::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void Aapi_call::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void Aapi_call::CallAPI(FString Data) {

	FString InFilePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir() / TEXT("Saved") / TEXT("in_data.txt")); //TODO: FIX
	FString OutFilePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir() / TEXT("Saved") / TEXT("out_data.txt"));

	if (!FFileHelper::SaveStringToFile(Data, *InFilePath))
	{
		UE_LOG(LogTemp, Error, TEXT("Write to InFile Failed"));
		// destroy here?
		return;
	}

	FString Script = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir() / TEXT("Scripts") / TEXT("helloworld.py"));
	FString CommandLine = FString::Printf(TEXT("python \"%s\" \"%s\" \"%s\""), *Script, *InFilePath, *OutFilePath);
	UE_LOG(LogTemp, Warning, TEXT("Running cmdline: %s"), *CommandLine);
	RunPyScript(CommandLine);

	FString OutFileContent;
	if (FFileHelper::LoadFileToString(OutFileContent, *OutFilePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("OutFile Content: %s"), *OutFileContent);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Outfile Read Failed."));
	}
}

void Aapi_call::RunPyScript(const FString& CommandLine) {

	void* PipeRead = nullptr;
	void* PipeWrite = nullptr;

	if (FPlatformProcess::CreatePipe(PipeRead, PipeWrite)) {
		// Split the command line into executable and arguments
		int32 SeparatorIndex;
		CommandLine.FindChar(' ', SeparatorIndex);
		FString Executable = CommandLine.Left(SeparatorIndex);
		FString Arguments = CommandLine.Mid(SeparatorIndex + 1);

		FProcHandle ProcessHandle = FPlatformProcess::CreateProc(*Executable, *Arguments, true, true, true, nullptr, 0, nullptr, PipeWrite, PipeRead);

		if (ProcessHandle.IsValid()) {
			FString Output;
			while (FPlatformProcess::IsProcRunning(ProcessHandle)) {
				FString PipeOutput = FPlatformProcess::ReadPipe(PipeRead);
				if (!PipeOutput.IsEmpty()) {
					Output += PipeOutput;
				}
			}

			FPlatformProcess::ClosePipe(PipeRead, PipeWrite);
			FPlatformProcess::WaitForProc(ProcessHandle);

			UE_LOG(LogTemp, Warning, TEXT("PyScript text: %s"), *Output);
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("PyScript Process Failed."));
		}
	}
}
