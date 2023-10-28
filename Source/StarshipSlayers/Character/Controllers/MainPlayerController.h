// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FControllerTypeEvent, bool, bUseGamepad);

class UInputMappingContext;

UCLASS()
class STARSHIPSLAYERS_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "_Settings")
	UInputMappingContext* InputMapping = nullptr;

	bool bIsUsingGamepad = false;
	bool bShowMouseCursorBuffer = false;

	FVector2D PreviousMousePosition = FVector2D();

public:
	FControllerTypeEvent OnControllerTypeChanged;

protected:
	AMainPlayerController();

	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void DetectAnyKey(FKey key);

	void PrintUsingGamepad();

	void PrintCursorVisibility();

	void PrintCursorVisibilityBuffer();

public:
	void SetInputMode(const FInputModeDataBase& InData) override;

	void DetectController(bool bUseGamepad);

	bool IsUsingGamepad();
};
