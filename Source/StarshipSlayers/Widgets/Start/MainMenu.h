// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

UCLASS()
class STARSHIPSLAYERS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable)
	void OnPlay();

	UFUNCTION(BlueprintCallable)
	void OnQuit();

	UFUNCTION()
	void OnPlayFadeIn();
};
