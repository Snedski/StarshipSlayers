// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "../../Dev/CustomCheatManager.h"
#include "../../Dev/CustomUtility.h"

AMainPlayerController::AMainPlayerController()
{
	PrimaryActorTick.bTickEvenWhenPaused = true;
	bShouldPerformFullTickWhenPaused = false;

	CheatClass = UCustomCheatManager::StaticClass();
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

	PrintUsingController();
	PrintCurrentInputMode();
	PrintKeyboardInputMode();
	PrintCursorVisibility();
	PrintCursorVisibilityBuffer();
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

void AMainPlayerController::PrintUsingController()
{
	if(bIsUsingController)
	{
		UCustomUtility::CustomPrintString("USE CONTROLLER", "InputMode", FLinearColor::Green, 0.f);
	}
	else
	{
		UCustomUtility::CustomPrintString("USE KEYBOARD", "InputMode", FLinearColor::Red, 0.f);
	}
}

void AMainPlayerController::PrintCurrentInputMode()
{
	ECurrentInputMode inputMode = bIsUsingController ? ECurrentInputMode::CIM_GAME : KeyboardInputMode;

	switch(inputMode)
	{
		case CIM_GAME:
		{
			UCustomUtility::CustomPrintString("CURRENT INPUT MODE : GAME ONLY", "InputMode", FLinearColor::Blue, 0.f);
			break;
		}

		case CIM_GAME_UI:
		{
			UCustomUtility::CustomPrintString("CURRENT INPUT MODE : GAME AND UI", "InputMode", FLinearColor::Blue, 0.f);
			break;
		}

		case CIM_UI:
		{
			UCustomUtility::CustomPrintString("CURRENT INPUT MODE : UI ONLY", "InputMode", FLinearColor::Blue, 0.f);
			break;
		}
	}
}

void AMainPlayerController::PrintKeyboardInputMode()
{
	switch(KeyboardInputMode)
	{
		case CIM_GAME:
		{
			UCustomUtility::CustomPrintString("KEYBOARD INPUT MODE : GAME ONLY", "InputMode", FLinearColor::Yellow, 0.f);
			break;
		}

		case CIM_GAME_UI:
		{
			UCustomUtility::CustomPrintString("KEYBOARD INPUT MODE : GAME AND UI", "InputMode", FLinearColor::Yellow, 0.f);
			break;
		}

		case CIM_UI:
		{
			UCustomUtility::CustomPrintString("KEYBOARD INPUT MODE : UI ONLY", "InputMode", FLinearColor::Yellow, 0.f);
			break;
		}
	}
}

void AMainPlayerController::PrintCursorVisibility()
{
	if(bShowMouseCursor)
	{
		UCustomUtility::CustomPrintString("MOUSE CURSOR VISIBLE", "InputMode", FLinearColor::Green, 0.f);
	}
	else
	{
		UCustomUtility::CustomPrintString("MOUSE CURSOR NOT VISIBLE", "InputMode", FLinearColor::Red, 0.f);
	}
}

void AMainPlayerController::PrintCursorVisibilityBuffer()
{
	if(bShowMouseCursorBuffer)
	{
		UCustomUtility::CustomPrintString("MOUSE CURSOR BUFFER VISIBLE", "InputMode", FLinearColor::Green, 0.f);
	}
	else
	{
		UCustomUtility::CustomPrintString("MOUSE CURSOR BUFFER NOT VISIBLE", "InputMode", FLinearColor::Red, 0.f);
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
