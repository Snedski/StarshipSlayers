// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevitatingChair.generated.h"

class UNiagaraComponent;

UCLASS()
class STARSHIPSLAYERS_API ALevitatingChair : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	USceneComponent* Root = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (Hidden))
	UStaticMeshComponent* ChairMesh = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UNiagaraComponent* ChairEffect = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings")
	float LevitatingSpeed = 50.f;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings")
	float LevitatingPower = 6.f;

	float BaseLocationZ = 0.f;
	float CurveValue = 0.f;

public:	
	ALevitatingChair();

	void BeginPlay() override;

	void Tick( float DeltaSeconds ) override;
};