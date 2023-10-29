// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CustomUserWidget.generated.h"

class AMainPlayerController;
class UButton;

UCLASS()
class STARSHIPSLAYERS_API UCustomUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	AMainPlayerController* MainPlayerController = nullptr;
	
	UPROPERTY()
	TArray<UButton*> FocusButton = {}; 

	UPROPERTY()
	UButton* PreviousFocusedButton = nullptr;

protected:
	void NativeConstruct() override;

	void NativeOnInitialized() override;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
	void OnControllerTypeChanged(bool bUseGamepad);

	UFUNCTION(BlueprintImplementableEvent)
	TArray<UButton*> GetAllButtons();

	UFUNCTION(BlueprintImplementableEvent)
	void OnFocusChanged(UButton* newButton, UButton* previousButton);
};
