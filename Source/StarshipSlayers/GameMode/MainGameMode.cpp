// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "Managers/SaveManager.h"

AMainGameMode* AMainGameMode::MainGameModeInstance = nullptr;

AMainGameMode::AMainGameMode()
{
	PrimaryActorTick.bCanEverTick = false;

	SaveManager = CreateDefaultSubobject<USaveManager>("Save Manager");
}

void AMainGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	MainGameModeInstance = this;
}

void AMainGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	MainGameModeInstance = nullptr;

	Super::EndPlay(EndPlayReason);
}
