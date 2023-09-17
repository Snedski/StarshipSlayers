// Fill out your copyright notice in the Description page of Project Settings.


#include "GearProps.h"
#include "Runtime/Engine/Classes/GameFramework/RotatingMovementComponent.h"

AGearProps::AGearProps()
{
	PrimaryActorTick.bCanEverTick = true;

	GearMesh = CreateDefaultSubobject<UStaticMeshComponent>("Gear Mesh");
	RootComponent = GearMesh;

	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>("Rotate Gear Component");
}