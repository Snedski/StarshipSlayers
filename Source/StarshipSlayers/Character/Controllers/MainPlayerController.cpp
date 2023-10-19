// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"

AMainPlayerController::AMainPlayerController()
{
	PrimaryActorTick.bTickEvenWhenPaused = true;
	bShouldPerformFullTickWhenPaused = false;
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ULocalPlayer* localPlayer = Cast<ULocalPlayer>(Player);
	UEnhancedInputLocalPlayerSubsystem* inputSystem = localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	inputSystem->AddMappingContext(InputMapping, 0);
}

void AMainPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(GetWorld()->IsPaused())
	{
		UpdateCameraManager(DeltaSeconds);
	}
}

void AMainPlayerController::DetectAnyKey(FKey key)
{
	DetectController(key.IsGamepadKey());
}

void AMainPlayerController::DetectController(bool bUseController)
{
	bIsUsingController = bUseController;
	
	if(bUseController)
	{
		bShowMouseCursor = false;
	}
	else
	{
		bShowMouseCursor = bShowMouseCursorBuffer;
	}
}

void AMainPlayerController::ChangeMouseCursorVisibility(bool bVisible)
{
	bShowMouseCursorBuffer = bVisible;

	if(!bIsUsingController)
	{
		bShowMouseCursor = bVisible;
	}
}
