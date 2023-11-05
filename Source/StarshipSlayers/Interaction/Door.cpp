// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Components/BoxComponent.h"
#include "../Character/DaveCharacter.h"

ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>("Trigger Box");
	TriggerBox->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>("Door");
	DoorMesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	TriggerBox->OnComponentBeginOverlap.RemoveAll(this);
	TriggerBox->OnComponentEndOverlap.RemoveAll(this);
	TriggerBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ADoor::OnEnterZone);
	TriggerBox->OnComponentEndOverlap.AddUniqueDynamic(this, &ADoor::OnExitZone);

}

void ADoor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(bOpen)
	{
		CurrentTransitionTime += DeltaSeconds;

		if(CurrentTransitionTime >= AnimationTime)
		{
			CurrentTransitionTime = AnimationTime;
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

	float alpha = CurrentTransitionTime / AnimationTime;
	DoorMesh->SetRelativeLocation(FVector(0., 0.f, FMath::Lerp(0.f, 450.f, alpha)));
}

void ADoor::OnEnterZone(UPrimitiveComponent* comp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyID, bool bFromSweep, const FHitResult& sweepResult)
{
	if(otherActor->GetClass()->IsChildOf(ADaveCharacter::StaticClass()))
	{
		bOpen = true;
		SetActorTickEnabled(true);
	}
}

void ADoor::OnExitZone(UPrimitiveComponent* comp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 OtherBodyID)
{
	if(otherActor->GetClass()->IsChildOf(ADaveCharacter::StaticClass()))
	{
		bOpen = false;
		SetActorTickEnabled(true);
	}
}
