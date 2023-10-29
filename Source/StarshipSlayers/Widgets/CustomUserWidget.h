// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CustomUserWidget.generated.h"

class AMainPlayerController;

UCLASS()
class STARSHIPSLAYERS_API UCustomUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	AMainPlayerController* MainPlayerController = nullptr;

protected:
	void NativeConstruct() override;

	void NativeOnInitialized() override;

	UFUNCTION()
	void OnControllerTypeChanged(bool bUseGamepad);
};
