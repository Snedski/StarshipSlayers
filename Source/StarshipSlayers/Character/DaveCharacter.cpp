// Fill out your copyright notice in the Description page of Project Settings.


#include "DaveCharacter.h"
#include "../GameMode/Systems/Interaction/InteractionSystem.h"
#include "../GameMode/Systems/Flashlight/FlashlightSystem.h"
#include "../GameMode/Systems/Zoom/ZoomSystem.h"

ADaveCharacter::ADaveCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	InteractionSystem = CreateDefaultSubobject<UInteractionSystem>("Interaction System");
	FlashlightSystem = CreateDefaultSubobject<UFlashlightSystem>("Flashlight System");
	ZoomSystem = CreateDefaultSubobject<UZoomSystem>("Zoom System");
}

void ADaveCharacter::BeginPlay()
{
	Super::BeginPlay();
}
