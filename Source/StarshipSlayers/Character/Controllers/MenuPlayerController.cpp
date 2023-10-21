// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuPlayerController.h"

void AMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ChangeMouseCursorVisibility(true);
	SetInputMode(FInputModeGameAndUI());
}
