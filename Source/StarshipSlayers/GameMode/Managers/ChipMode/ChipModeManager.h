// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Main/MainManager.h"
#include "ChipModeManager.generated.h"

UCLASS()
class STARSHIPSLAYERS_API UChipModeManager : public UMainManager
{
	GENERATED_BODY()
	
protected:
	static UChipModeManager* GetInstance();
};
