// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AlertLight.generated.h"

class USpotLightComponent;
class UPointLightComponent;
class URotatingMovementComponent;

UCLASS()
class STARSHIPSLAYERS_API AAlertLight : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	USceneComponent* Root = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	USpotLightComponent* SpotLight_00 = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	USpotLightComponent* SpotLight_01 = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UStaticMeshComponent* SpotLightMesh = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UStaticMeshComponent* LeftCacheMesh = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UStaticMeshComponent* RightCacheMesh = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	URotatingMovementComponent* RotatingMovementComponent = nullptr;

public:	
	AAlertLight();
};
