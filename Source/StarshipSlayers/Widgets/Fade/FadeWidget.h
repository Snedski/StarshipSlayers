// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CustomUserWidget.h"
#include "FadeWidget.generated.h"

UCLASS()
class STARSHIPSLAYERS_API UFadeWidget : public UCustomUserWidget
{
	GENERATED_BODY()

friend AFadeSystem;
	
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateFadeScreen(float inDuration, FLinearColor inColor);
};
