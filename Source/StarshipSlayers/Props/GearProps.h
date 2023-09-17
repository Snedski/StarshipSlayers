// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GearProps.generated.h"

class URotatingMovementComponent;

UCLASS()
class STARSHIPSLAYERS_API AGearProps : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UStaticMeshComponent* GearMesh = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	URotatingMovementComponent* RotatingMovementComponent = nullptr;

public:	
	AGearProps();
};
