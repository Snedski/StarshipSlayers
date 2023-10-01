// Fill out your copyright notice in the Description page of Project Settings.


#include "DaveCharacter.h"
#include "../GameMode/Systems/Interaction/InteractionSystem.h"

ADaveCharacter::ADaveCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	InteractionSystem = CreateDefaultSubobject<UInteractionSystem>("Interaction System");
}

void ADaveCharacter::BeginPlay()
{
	Super::BeginPlay();
}
