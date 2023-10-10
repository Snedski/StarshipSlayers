// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FadeData.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FFadeData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor Color = FLinearColor::Black;

public:
	FFadeData() {};

	FFadeData(float inDuration, FLinearColor inColor)
	{
		Duration = inDuration;
		Color = inColor;
	}
};
