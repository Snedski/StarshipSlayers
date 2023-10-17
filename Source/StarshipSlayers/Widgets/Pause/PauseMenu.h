// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

class UPauseSystem;

UCLASS()
class STARSHIPSLAYERS_API UPauseMenu : public UUserWidget
{
	friend UPauseSystem;

	GENERATED_BODY()
	
protected:
	UPROPERTY()
	UPauseSystem* PauseSystem = nullptr;

protected:
	UFUNCTION(BlueprintCallable)
	void OnContinue();

	UFUNCTION(BlueprintCallable)
	void OnQuit();

	void InitPauseMenu(UPauseSystem* inPauseSystem);
};
