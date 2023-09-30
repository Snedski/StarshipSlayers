// Fill out your copyright notice in the Description page of Project Settings.


#include "ToggleLight.h"
#include "Runtime/Engine/Classes/Components/SpotLightComponent.h"

AToggleLight::AToggleLight()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	ConeLightEffect = CreateDefaultSubobject<UStaticMeshComponent>("Cone Light Effect");
	ConeLightEffect->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	SpotLight = CreateDefaultSubobject<USpotLightComponent>("Spot Light");
	SpotLight->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	NeonMesh = CreateDefaultSubobject<UStaticMeshComponent>("Neon Mesh");
	NeonMesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

void AToggleLight::BeginPlay()
{
	Super::BeginPlay();

	DefaultSpotLightIntensity = SpotLight->Intensity;
	NeonMeshGlowMaterial = NeonMesh->CreateDynamicMaterialInstance(1);
	NeonMeshGlowMaterial->GetScalarParameterValue(FMaterialParameterInfo("Glow"), DefaultNeonMeshGlowValue);
	Activate(bOn, true);
}

void AToggleLight::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(bOn)
	{
		CurrentTransitionTime += DeltaSeconds;

		if(CurrentTransitionTime >= TransitionTime)
		{
			CurrentTransitionTime = TransitionTime;
			SetActorTickEnabled(false);
		}
	}
	else
	{
		CurrentTransitionTime -= DeltaSeconds;

		if(CurrentTransitionTime <= 0.f)
		{
			CurrentTransitionTime = 0.f;
			SetActorTickEnabled(false);
		}
	}

	float alpha = CurrentTransitionTime / TransitionTime;
	SpotLight->SetIntensity(FMath::Lerp(0.f, DefaultSpotLightIntensity, alpha));
	NeonMeshGlowMaterial->SetScalarParameterValue("Glow", FMath::Lerp(0.f, DefaultNeonMeshGlowValue, alpha));
}

void AToggleLight::Toggle()
{
	bOn = !bOn;
	Activate(bOn);
}

void AToggleLight::Activate(bool bActivate, bool bInstant)
{
	ConeLightEffect->SetVisibility(bActivate);

	if(bInstant)
	{
		SpotLight->SetIntensity(bActivate ? DefaultSpotLightIntensity : 0.f);
		NeonMeshGlowMaterial->SetScalarParameterValue("Glow", bActivate ? DefaultNeonMeshGlowValue : 0.f);
		CurrentTransitionTime = bActivate ? TransitionTime : 0.f;
	}
	else
	{
		SetActorTickEnabled(true);
	}
}
