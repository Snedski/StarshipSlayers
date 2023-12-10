// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ToggleLight.generated.h"

class USpotLightComponent;

UCLASS()
class STARSHIPSLAYERS_API AToggleLight : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	USceneComponent* Root = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UStaticMeshComponent* ConeLightEffect = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	USpotLightComponent* SpotLight = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UStaticMeshComponent* NeonMesh = nullptr;

	UPROPERTY(EditInstanceOnly, Category = "_Settings")
	FGuid SwitchGUID = FGuid();

	UPROPERTY(EditDefaultsOnly, Category = "_Settings")
	float TransitionTime = 0.5f;

	UPROPERTY(EditInstanceOnly, Category = "_Settings")
	bool bOn = true;

	UPROPERTY()
	UMaterialInstanceDynamic* NeonMeshGlowMaterial = nullptr;

	float DefaultSpotLightIntensity = 0.f;
	float DefaultNeonMeshGlowValue = 0.f;
	float CurrentTransitionTime = 0.f;

public:	
	AToggleLight();

	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;

	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void Toggle();

protected:
	void Activate(bool bActivate, bool bInstant = false);
};
