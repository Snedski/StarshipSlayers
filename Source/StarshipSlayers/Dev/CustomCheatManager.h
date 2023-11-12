// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "CustomCheatManager.generated.h"

UCLASS()
class STARSHIPSLAYERS_API UCustomCheatManager : public UCheatManager
{
	GENERATED_BODY()
	
public:
	UFUNCTION(exec)
	void UpdateDebugTagVisiblity(FString tag, bool bVisible);

	UFUNCTION(exec)
	void ActivateChipModeSelection(bool bActive);
};
