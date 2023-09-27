// Fill out your copyright notice in the Description page of Project Settings.


#include "ToggleLight.h"
#include "Runtime/Engine/Classes/Components/RectLightComponent.h"

AToggleLight::AToggleLight()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	ToggleLightMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	ToggleLightMesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	ToggleRectLight = CreateDefaultSubobject<URectLightComponent>("Light");
	ToggleRectLight->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	ConeLightEffect = CreateDefaultSubobject<UStaticMeshComponent>("Cone Light Effect");
	ConeLightEffect->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

void AToggleLight::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	Activate(bOn);
}

void AToggleLight::Toggle()
{
	Activate(!bOn);
	bOn = !bOn;
}

void AToggleLight::Activate(bool bActivate)
{
	Root->SetVisibility(bActivate, true);
}
