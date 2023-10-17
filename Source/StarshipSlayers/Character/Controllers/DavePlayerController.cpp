// Fill out your copyright notice in the Description page of Project Settings.


#include "DavePlayerController.h"

void ADavePlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameOnly());
}