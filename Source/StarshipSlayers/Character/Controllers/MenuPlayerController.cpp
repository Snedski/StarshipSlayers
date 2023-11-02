// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuPlayerController.h"

void AMenuPlayerController::SetInputMode(const FInputModeDataBase& InData)
{
	Super::SetInputMode(FInputModeGameAndUI());
}
