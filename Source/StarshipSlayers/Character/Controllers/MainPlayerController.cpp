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

	GetMousePosition(PreviousMousePosition.X, PreviousMousePosition.Y);
}

void AMainPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(GetWorld()->IsPaused())
	{
		UpdateCameraManager(DeltaSeconds);
	}

	FVector2D currentMousePosition = FVector2D();
	GetMousePosition(currentMousePosition.X, currentMousePosition.Y);

	if(currentMousePosition != PreviousMousePosition)
	{
		PreviousMousePosition = currentMousePosition;
		DetectController(false);
	}

	PrintUsingGamepad();
	PrintCursorVisibility();
	PrintCursorVisibilityBuffer();
}

void AMainPlayerController::DetectAnyKey(FKey key)
{
	DetectController(key.IsGamepadKey());
}

void AMainPlayerController::DetectController(bool bUseGamepad)
{
	if(bIsUsingGamepad != bUseGamepad)
	{
		bIsUsingGamepad = bUseGamepad;
	
		if(bIsUsingGamepad)
		{
			bShowMouseCursor = false;
		}
		else
		{
			bShowMouseCursor = bShowMouseCursorBuffer;
		}

		OnControllerTypeChanged.Broadcast(bIsUsingGamepad);
		SetMouseLocation(PreviousMousePosition.X, PreviousMousePosition.Y);
	}
}

void AMainPlayerController::PrintUsingGamepad()
{
	if(bIsUsingGamepad)
	{
		UCustomUtility::CustomPrintString("USE GAMEPAD", "InputMode", FLinearColor::Green, 0.f);
	}
	else
	{
		UCustomUtility::CustomPrintString("USE KEYBOARD", "InputMode", FLinearColor::Red, 0.f);
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

	UGameViewportClient* viewport = GetWorld()->GetGameViewport();

	if(viewport->IgnoreInput())
	{
		bShowMouseCursorBuffer = true;
	}
	else
	{
		if(viewport->GetMouseCaptureMode() == EMouseCaptureMode::CaptureDuringMouseDown)
		{
			bShowMouseCursorBuffer = true;
		}
		else
		{
			bShowMouseCursorBuffer = false;
		}
	}

	if(!bIsUsingGamepad)
	{
		bShowMouseCursor = bShowMouseCursorBuffer;
	}
}

bool AMainPlayerController::IsUsingGamepad()
{
	return bIsUsingGamepad;
}