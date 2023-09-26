// Fill out your copyright notice in the Description page of Project Settings.


#include "ToggleSwitch.h"
#include "ToggleLight.h"

AToggleSwitch::AToggleSwitch()
{
	PrimaryActorTick.bCanEverTick = false;

	ToggleSwitchMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = ToggleSwitchMesh;
}

void AToggleSwitch::Interact_Implementation()
{
	for(AToggleLight* light : ToggleLights)
	{
		light->Toggle();
	}
}

void AToggleSwitch::Focus_Implementation(bool bFocus)
{
z	ToggleSwitchMesh->SetRenderCustomDepth(bFocus);
}