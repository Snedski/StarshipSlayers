// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveManager.h"
#include "../MainGameMode.h"
#include "../../Save/MainSaveGame.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

USaveManager::USaveManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}

UMainSaveGame* USaveManager::GetSaveFromSlot(FString slotName)
{
	GetInstance()->CheckExistingSave(slotName);
	return GetInstance()->CurrentSaveGame;
}

void USaveManager::SaveSlot(FString slotName)
{
	GetInstance()->CheckExistingSave(slotName);
	UGameplayStatics::SaveGameToSlot(GetInstance()->CurrentSaveGame, slotName, 0);
}

USaveManager* USaveManager::GetInstance()
{
	return AMainGameMode::MainGameModeInstance->SaveManager;
}

void USaveManager::CheckExistingSave(FString slotName)
{
	if(!IsValid(CurrentSaveGame) || CurrentSlotName != slotName)
	{
		CurrentSlotName = slotName;

		if(UGameplayStatics::DoesSaveGameExist(slotName, 0))
		{
			CurrentSaveGame = Cast<UMainSaveGame>(UGameplayStatics::LoadGameFromSlot(slotName, 0));
		}
		else
		{
			CurrentSaveGame = NewObject<UMainSaveGame>();
		}
	}
}
