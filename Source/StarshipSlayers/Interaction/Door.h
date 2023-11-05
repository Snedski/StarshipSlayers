// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class UBoxComponent;
class UAudioComponent;

UCLASS()
class STARSHIPSLAYERS_API ADoor : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	USceneComponent* Root = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UBoxComponent* TriggerBox = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UStaticMeshComponent* DoorMesh = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UAudioComponent* DoorOpenSound = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UAudioComponent* DoorCloseSound = nullptr;

	UPROPERTY(EditAnywhere, Category = "_Settings")
	float AnimationTime = 1.f;

	float CurrentTransitionTime = 0.f;
	bool bOpen = false;

public:	
	ADoor();

	void Tick( float DeltaSeconds ) override;

protected:
	UFUNCTION()
	void OnEnterZone(UPrimitiveComponent* comp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyID, bool bFromSweep, const FHitResult& sweepResult);

	UFUNCTION()
	void OnExitZone(UPrimitiveComponent* comp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 OtherBodyID);
};
