// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Main/MainManager.h"
#include "ChipModeManager.generated.h"

class UChipModeData;

UCLASS()
class STARSHIPSLAYERS_API UChipModeManager : public UMainManager
{
	GENERATED_BODY()
	
protected:
	static UChipModeManager* GetInstance();

	UPROPERTY(EditAnywhere, Category = "_Settings")
	UChipModeData* DefaultMode = nullptr;

	UPROPERTY(EditAnywhere, Category = "_Settings")
	TArray<UChipModeData*> ChipModeDatas = {};

protected:
	void InitManager() override;
};
