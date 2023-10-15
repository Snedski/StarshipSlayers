// Fill out your copyright notice in the Description page of Project Settings.


#include "LevitatingChair.h"
#include "NiagaraComponent.h"

ALevitatingChair::ALevitatingChair()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	ChairMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	ChairMesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	ChairEffect = CreateDefaultSubobject<UNiagaraComponent>("Effect");
	ChairEffect->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

void ALevitatingChair::BeginPlay()
{
	Super::BeginPlay();

	BaseLocationZ = ChairMesh->GetComponentLocation().Z;
}

void ALevitatingChair::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CurveValue = (CurveValue + (DeltaSeconds * LevitatingSpeed));
	CurveValue = FMath::Fmod(CurveValue, 360.f);

	float newLocationZ = BaseLocationZ + (FMath::Sin(CurveValue) * LevitatingPower);
	ChairMesh->SetWorldLocation(FVector(ChairMesh->GetComponentLocation().X, ChairMesh->GetComponentLocation().Y, newLocationZ));
}
