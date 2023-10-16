// Fill out your copyright notice in the Description page of Project Settings.


#include "DaveGameMode.h"
#include "../Widgets/HUD/MainHUD.h"

void ADaveGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	MainHUD = CreateWidget<UMainHUD>(GetWorld(), MainHUDClass, "HUD");
	MainHUD->AddToViewport();
}

UMainHUD* ADaveGameMode::GetHUD()
{
	return Cast<ADaveGameMode>(MainGameModeInstance)->MainHUD;
}
