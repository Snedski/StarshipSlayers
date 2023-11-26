// Fill out your copyright notice in the Description page of Project Settings.


#include "ChipModeInteractable.h"
#include "../GameMode/Managers/ChipMode/ChipModeData.h"
#include "../GameMode/Managers/ChipMode/ChipModeManager.h"

AChipModeInteractable::AChipModeInteractable()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
}

void AChipModeInteractable::Focus_Implementation(bool bFocus)
{
	Mesh->SetRenderCustomDepth(bFocus);
}

void AChipModeInteractable::Interact_Implementation()
{
	UChipModeManager::AccessChipMode(ChipModeTriggered);
}
