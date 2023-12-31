// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ChipModeData.generated.h"

UCLASS()
class STARSHIPSLAYERS_API UChipModeData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	FString ChipModeName = "Default_ChipMode_Name";

	UPROPERTY(EditDefaultsOnly)
	TArray<UDataLayerAsset*> LoadedLayers = {};

	UPROPERTY(VisibleAnywhere)
	FVector StartLocation = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere)
	FRotator StartRotation = FRotator::ZeroRotator;

#if WITH_EDITOR
public:
	UChipModeData()
	{
		if(ChipModeName == "Default_ChipMode_Name")
		{
			ChipModeName = GetName();
			MarkPackageDirty();
		}
	}
#endif
};
