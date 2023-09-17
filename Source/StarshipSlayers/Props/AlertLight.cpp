// Fill out your copyright notice in the Description page of Project Settings.


#include "AlertLight.h"
#include "Runtime/Engine/Classes/Components/SpotLightComponent.h"
#include "Runtime/Engine/Classes/Components/PointLightComponent.h"
#include "Runtime/Engine/Classes/GameFramework/RotatingMovementComponent.h"

AAlertLight::AAlertLight()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;

	SpotLight_00 = CreateDefaultSubobject<USpotLightComponent>("Spot Light A");
	SpotLight_00->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	SpotLight_01 = CreateDefaultSubobject<USpotLightComponent>("Spot Light B");
	SpotLight_01->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	SpotLightMesh = CreateDefaultSubobject<UStaticMeshComponent>("Spot Light Sphere");
	SpotLightMesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	LeftCacheMesh = CreateDefaultSubobject<UStaticMeshComponent>("Left Cache");
	LeftCacheMesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	RightCacheMesh = CreateDefaultSubobject<UStaticMeshComponent>("Right Cache");
	RightCacheMesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	PointLight = CreateDefaultSubobject<UPointLightComponent>("Point Light");
	PointLight->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);

	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>("Rotate Light Component");
}