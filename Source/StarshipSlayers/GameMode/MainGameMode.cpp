// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "Managers/Save/SaveManager.h"
#include "Managers/ChipMode/ChipModeManager.h"
#include "Systems/Fade/FadeSystem.h"

AMainGameMode* AMainGameMode::MainGameModeInstance = nullptr;

AMainGameMode::AMainGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	SaveManager = CreateDefaultSubobject<USaveManager>("Save Manager");
	ChipModeManager = CreateDefaultSubobject<UChipModeManager>("ChipMode Manager");
}

void AMainGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	MainGameModeInstance = this;

	TArray<UMainManager*> managerComponents = {};
	GetComponents(managerComponents);

	for(UMainManager* manager : managerComponents)
	{
		if(manager->bEnable)
		{
			manager->InitManager();
		}
	}
}

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	AFadeSystem::GetInstance()->FadeIn(FFadeData(0.f, StartingFade.Color));
	SetActorTickEnabled(true);
}

void AMainGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ElapsedBeforeFadeOut += DeltaSeconds;

	if(ElapsedBeforeFadeOut >= TimeBeforeFadeOut)
	{
		AFadeSystem::GetInstance()->FadeOut(StartingFade);
		SetActorTickEnabled(false);
	}
}

void AMainGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	MainGameModeInstance = nullptr;

	Super::EndPlay(EndPlayReason);
}