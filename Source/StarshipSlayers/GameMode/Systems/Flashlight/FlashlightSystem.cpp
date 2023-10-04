// Fill out your copyright notice in the Description page of Project Settings.


#include "FlashlightSystem.h"
#include "Runtime/Engine/Classes/Components/SpotLightComponent.h"

UFlashlightSystem::UFlashlightSystem()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UFlashlightSystem::SetupSystem(USpotLightComponent* spotlight)
{
	Flashlight = spotlight;
	ActivateFlashlight(bOn);
}

void UFlashlightSystem::ToggleFlashlight()
{
	bOn = !bOn;
	ActivateFlashlight(bOn);
}

void UFlashlightSystem::ActivateFlashlight(bool bActivate)
{
	Flashlight->SetVisibility(bActivate);
}
