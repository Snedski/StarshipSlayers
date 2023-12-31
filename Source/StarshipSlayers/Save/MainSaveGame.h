// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MainSaveData.h"
#include "MainSaveGame.generated.h"

UCLASS()
class STARSHIPSLAYERS_API UMainSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	FPlayerSaveData PlayerSaveData = FPlayerSaveData();

	UPROPERTY(BlueprintReadWrite)
	FChipModeSaveData ChipModeSaveData = FChipModeSaveData();
};
