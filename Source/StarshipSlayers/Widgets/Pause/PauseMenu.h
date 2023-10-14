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

public:
	UFUNCTION(BlueprintCallable)
	void OnContinue();

	UFUNCTION(BlueprintCallable)
	void OnQuit();

protected:
	void InitPauseMenu(UPauseSystem* inPauseSystem);
};
