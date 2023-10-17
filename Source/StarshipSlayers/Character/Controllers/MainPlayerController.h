// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

class UInputMappingContext;

UCLASS()
class STARSHIPSLAYERS_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "_Settings")
	UInputMappingContext* InputMapping = nullptr;

	bool bIsUsingController = false;
	bool bShowMouseCursorBuffer = false;

protected:
	AMainPlayerController();

	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void DetectAnyKey(FKey key);

	UFUNCTION(BlueprintCallable)
	void DetectMouseMovement(FVector movement);

	void DetectController(bool bUseController);

public:
	void ChangeMouseCursorVisibility(bool bVisible);
};
