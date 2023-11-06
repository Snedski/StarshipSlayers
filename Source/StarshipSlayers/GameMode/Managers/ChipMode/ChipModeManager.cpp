// Fill out your copyright notice in the Description page of Project Settings.


#include "ChipModeManager.h"
#include "../../MainGameMode.h"

UChipModeManager* UChipModeManager::GetInstance()
{
	return AMainGameMode::MainGameModeInstance->ChipModeManager;
}
