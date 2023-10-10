// Fill out your copyright notice in the Description page of Project Settings.


#include "DavePlayerController.h"

ADavePlayerController::ADavePlayerController()
{
	PrimaryActorTick.bTickEvenWhenPaused = true;
	bShouldPerformFullTickWhenPaused = true;
}
