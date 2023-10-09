// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "Managers/Save/SaveManager.h"
#include "../Widgets/HUD/MainHUD.h"
#include "Systems/Fade/FadeSystem.h"

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

	MainHUD = CreateWidget<UMainHUD>(GetWorld(), MainHUDClass, "HUD");
	MainHUD->AddToViewport();
}

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	AFadeSystem::GetInstance()->FadeIn(FFadeData(0.f, FLinearColor::Black));
	AFadeSystem::GetInstance()->FadeOut(FFadeData(1.f, FLinearColor::Black));
}

void AMainGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	MainGameModeInstance = nullptr;

	Super::EndPlay(EndPlayReason);
}

UMainHUD* AMainGameMode::GetHUD()
{
	return MainGameModeInstance->MainHUD;
}
