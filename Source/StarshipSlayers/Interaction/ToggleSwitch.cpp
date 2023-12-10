// Fill out your copyright notice in the Description page of Project Settings.


#include "ToggleSwitch.h"
#include "ToggleLight.h"
#include "../GameMode/Managers/ObjectLink/ObjectLinkManager.h"

AToggleSwitch::AToggleSwitch()
{
	PrimaryActorTick.bCanEverTick = false;

	ToggleSwitchMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = ToggleSwitchMesh;
}

void AToggleSwitch::Interact_Implementation()
{
	TArray<AToggleLight*> toggleLights = UObjectLinkManager::GetObjectListFromGUID<AToggleLight>(SwitchGUID);

	for(AToggleLight* light : toggleLights)
	{
		light->Toggle();
	}
}

void AToggleSwitch::Focus_Implementation(bool bFocus)
{
	ToggleSwitchMesh->SetRenderCustomDepth(bFocus);
}