// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseSystem.h"
#include "../../../Widgets/Pause/PauseMenu.h"

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
	APlayerController* controller = GetWorld()->GetFirstPlayerController();

	bPauseMenuOpen = !bPauseMenuOpen;

	PauseMenu->SetVisibility(bPauseMenuOpen ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	controller->SetPause(bPauseMenuOpen);
	controller->bShowMouseCursor = bPauseMenuOpen;

	if(bPauseMenuOpen)
	{
		controller->SetInputMode(FInputModeGameAndUI());
	}
	else
	{
		controller->SetInputMode(FInputModeGameOnly());
	}
}

bool UPauseSystem::IsPauseMenuOpen()
{
	return bPauseMenuOpen;
}
