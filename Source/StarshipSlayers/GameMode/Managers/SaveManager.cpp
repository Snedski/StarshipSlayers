// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveManager.h"
#include "../MainGameMode.h"

USaveManager::USaveManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}

USaveManager* USaveManager::GetInstance()
{
	return AMainGameMode::MainGameModeInstance->SaveManager;
}
