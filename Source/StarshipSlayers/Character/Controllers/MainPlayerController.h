// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

class UInputMappingContext;

enum ECurrentInputMode : uint8
{
	CIM_GAME,
	CIM_GAME_UI,
	CIM_UI
};

UCLASS()
class STARSHIPSLAYERS_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "_Settings")
	UInputMappingContext* InputMapping = nullptr;

	bool bIsUsingController = false;
	bool bShowMouseCursorBuffer = false;
	bool bOverrideKeyboardInputMode = true;

	FVector2D PreviousMousePosition = FVector2D();

	ECurrentInputMode KeyboardInputMode = ECurrentInputMode::CIM_GAME;

protected:
	AMainPlayerController();

	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void DetectAnyKey(FKey key);

	void DetectController(bool bUseController);

	void PrintUsingController();

	void PrintCurrentInputMode();

	void PrintKeyboardInputMode();

	void PrintCursorVisibility();

	void PrintCursorVisibilityBuffer();

public:
	void SetInputMode(const FInputModeDataBase& InData) override;

	void ChangeMouseCursorVisibility(bool bVisible);
};
