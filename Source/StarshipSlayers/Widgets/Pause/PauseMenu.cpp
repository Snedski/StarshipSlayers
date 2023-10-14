// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"
#include "../../GameMode/Systems/Pause/PauseSystem.h"

void UPauseMenu::OnContinue()
{
	PauseSystem->TogglePauseMenu();
}

void UPauseMenu::OnQuit()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}

void UPauseMenu::InitPauseMenu(UPauseSystem* inPauseSystem)
{
	PauseSystem = inPauseSystem;
}
