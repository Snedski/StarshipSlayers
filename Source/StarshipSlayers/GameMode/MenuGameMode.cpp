// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuGameMode.h"
#include "../Widgets/Start/MainMenu.h"

void AMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameAndUI());
	MainMenu = CreateWidget<UMainMenu>(GetWorld()->GetFirstPlayerController(), MainMenuClass, "Main Menu");
	MainMenu->AddToViewport();
}
