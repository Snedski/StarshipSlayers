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

	SetInputMode(FInputModeGameOnly());
}

void AMainPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(GetWorld()->IsPaused())
	{
		UpdateCameraManager(DeltaSeconds);
	}

	PrintUsingController(bIsUsingController);
	PrintCurrentInputMode(bIsUsingController ? ECurrentInputMode::CIM_GAME : KeyboardInputMode);
	PrintKeyboardInputMode(KeyboardInputMode);
}

void AMainPlayerController::DetectAnyKey(FKey key)
{
	DetectController(key.IsGamepadKey());
}

void AMainPlayerController::DetectController(bool bUseController)
{
	if(bIsUsingController != bUseController)
	{
		bIsUsingController = bUseController;
	
		if(bUseController)
		{
			bShowMouseCursor = false;
			bOverrideKeyboardInputMode = false;
			SetInputMode(FInputModeGameOnly());
			bOverrideKeyboardInputMode = true;
		}
		else
		{
			bShowMouseCursor = bShowMouseCursorBuffer;

			switch(KeyboardInputMode)
			{
				case ECurrentInputMode::CIM_GAME:
				{
					SetInputMode(FInputModeGameOnly());
					break;
				}

				case ECurrentInputMode::CIM_GAME_UI:
				{
					SetInputMode(FInputModeGameAndUI());
					break;
				}

				case ECurrentInputMode::CIM_UI:
				{
					SetInputMode(FInputModeUIOnly());
					break;
				}
			}
		}
	}
}

void AMainPlayerController::SetInputMode(const FInputModeDataBase& InData)
{
	Super::SetInputMode(InData);

	if(bOverrideKeyboardInputMode)
	{
		UGameViewportClient* viewport = GetWorld()->GetGameViewport();

		if(viewport->IgnoreInput())
		{
			KeyboardInputMode = ECurrentInputMode::CIM_UI;
		}
		else
		{
			if(viewport->GetMouseCaptureMode() == EMouseCaptureMode::CaptureDuringMouseDown)
			{
				KeyboardInputMode = ECurrentInputMode::CIM_GAME_UI;
			}
			else
			{
				KeyboardInputMode = ECurrentInputMode::CIM_GAME;
			}
		}
	}

	if(bIsUsingController)
	{
		Super::SetInputMode(FInputModeGameOnly());
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
