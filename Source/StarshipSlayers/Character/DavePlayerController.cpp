// Fill out your copyright notice in the Description page of Project Settings.


#include "DavePlayerController.h"

ADavePlayerController::ADavePlayerController()
{
	PrimaryActorTick.bTickEvenWhenPaused = true;
	bShouldPerformFullTickWhenPaused = false;
}

void ADavePlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameOnly());
}

void ADavePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(GetWorld()->IsPaused())
	{
		UpdateCameraManager(DeltaSeconds);
	}
}
