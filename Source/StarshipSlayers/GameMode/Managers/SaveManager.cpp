// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveManager.h"
#include "../MainGameMode.h"
#include "../../Save/MainSaveGame.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

UMainSaveGame* USaveManager::GetSaveFromSlot(FString slotName)
{
	GetInstance()->CheckExistingSave(slotName);
	return GetInstance()->CurrentSaveGame;
}

void USaveManager::SaveSlot(FString slotName)
{
	if(GetInstance()->bEnable)
	{
		GetInstance()->CheckExistingSave(slotName);
		UGameplayStatics::SaveGameToSlot(GetInstance()->CurrentSaveGame, slotName, 0);
	}
}

bool USaveManager::DoesSaveExist(FString slotName)
{
	if(GetInstance()->bEnable)
	{
		return UGameplayStatics::DoesSaveGameExist(slotName, 0);
	}

	return false;
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
		
		if(bEnable && UGameplayStatics::DoesSaveGameExist(slotName, 0))
		{
			CurrentSaveGame = Cast<UMainSaveGame>(UGameplayStatics::LoadGameFromSlot(slotName, 0));
		}
		else
		{
			CurrentSaveGame = NewObject<UMainSaveGame>();
		}
	}
}
