// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChipModeStartingPosRegistration.generated.h"

UCLASS()
class STARSHIPSLAYERS_API UChipModeStartingPosRegistration : public UUserWidget
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	void OnSaveButtonClicked(FString selectedOption);
};
