// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHUD.generated.h"

UCLASS()
class STARSHIPSLAYERS_API UMainHUD : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	bool bInteractionPopupShown = false;

public:
	UFUNCTION(BlueprintCallable)
	void ShowInteractionPopup(bool bShow);

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void PlayInteractionPopupFadeAnimation(bool bShow);
};
