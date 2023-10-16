// Fill out your copyright notice in the Description page of Project Settings.


#include "DaveGameMode.h"
#include "../Widgets/HUD/MainHUD.h"

void ADaveGameMode::BeginPlay()
{
	Super::BeginPlay();

	MainHUD = CreateWidget<UMainHUD>(GetWorld()->GetFirstPlayerController(), MainHUDClass, "HUD");
	MainHUD->AddToViewport();
}

UMainHUD* ADaveGameMode::GetHUD()
{
	return Cast<ADaveGameMode>(MainGameModeInstance)->MainHUD;
}
