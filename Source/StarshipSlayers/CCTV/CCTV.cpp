// Fill out your copyright notice in the Description page of Project Settings.


#include "CCTV.h"
#include "Runtime/Engine/Classes/Components/SceneCaptureComponent2D.h"

ACCTV::ACCTV()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	CameraMesh = CreateDefaultSubobject<UStaticMeshComponent>("Camera");
	CameraMesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>("Scene Capture");
	SceneCapture->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
}

void ACCTV::BeginPlay()
{
	Super::BeginPlay();

	// The camera don't move if no curve is provided
	if(!IsValid(MovementCurve))
	{
		SetActorTickEnabled(false);
		return;
	}

	float minTime = 0.f;
	MovementCurve->GetTimeRange(minTime, MaxTime);
}

// Called every frame
void ACCTV::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentMovementTime += DeltaTime;
	CurrentMovementTime = FMath::Fmod(CurrentMovementTime, MaxTime);

	Root->AddWorldRotation(FRotator(0.f, MovementCurve->GetFloatValue(CurrentMovementTime), 0.f));
}

