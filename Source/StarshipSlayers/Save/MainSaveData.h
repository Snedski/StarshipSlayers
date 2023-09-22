// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainSaveData.generated.h"

USTRUCT(BlueprintType)
struct FPlayerSaveData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FVector PlayerLocation = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite)
	FRotator PlayerRotation = FRotator::ZeroRotator;
};