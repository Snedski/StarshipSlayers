// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseSystem.h"
#include "../../../Widgets/Pause/PauseMenu.h"
#include "../../../Character/Controllers/MainPlayerController.h"
#include "Framework/Application/SlateApplication.h"

UPauseSystem::UPauseSystem()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPauseSystem::SetupSystem()
{
	PauseMenu = CreateWidget<UPauseMenu>(GetWorld()->GetFirstPlayerController(), PauseMenuClass);
	PauseMenu->AddToViewport(1);
	PauseMenu->SetVisibility(ESlateVisibility::Hidden);
	PauseMenu->InitPauseMenu(this);
}

void UPauseSystem::TogglePauseMenu()
{
	AMainPlayerController* controller = (AMainPlayerController*) GetWorld()->GetFirstPlayerController();

	bPauseMenuOpen = !bPauseMenuOpen;

	PauseMenu->SetVisibility(bPauseMenuOpen ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	controller->SetPause(bPauseMenuOpen);

	if(bPauseMenuOpen)
	{
		controller->SetInputMode(FInputModeGameAndUI());
		PauseMenu->SetFocus();
	}
	else
	{
		controller->SetInputMode(FInputModeGameOnly());
		FSlateApplication::Get().SetAllUserFocusToGameViewport();
	}
}

bool UPauseSystem::IsPauseMenuOpen()
{
	return bPauseMenuOpen;
}
