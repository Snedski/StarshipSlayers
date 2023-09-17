// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CCTV.generated.h"

class USceneCaptureComponent2D;

UCLASS()
class STARSHIPSLAYERS_API ACCTV : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	USceneComponent* Root = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UStaticMeshComponent* CameraMesh = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	USceneCaptureComponent2D* SceneCapture = nullptr;

	UPROPERTY(EditAnywhere, Category = "_Settings")
	UCurveFloat* MovementCurve = nullptr;

	float MaxTime = 0.f;
	float CurrentMovementTime = 0.f;

public:	
	ACCTV();

	void BeginPlay() override;
	void Tick(float DeltaTime) override;

};
