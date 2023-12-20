// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveManager.h"
#include "../../MainGameMode.h"
#include "../../../Save/MainSaveGame.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

UMainSaveGame* USaveManager::GetSaveFromSlot(FString slotName)
{
	USaveManager* inst = GetInstance();
	inst->CheckExistingSave(slotName);
	return inst->CurrentSaveGame;
}

void USaveManager::SaveSlot(FString slotName)
{
	USaveManager* inst = GetInstance();

	if(inst->bEnable)
	{
		inst->CheckExistingSave(slotName);
		UGameplayStatics::SaveGameToSlot(inst->CurrentSaveGame, slotName, 0);
	}
}

bool USaveManager::DoesSaveExist(FString slotName)
{
	USaveManager* inst = GetInstance();

	if(inst->bEnable)
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
