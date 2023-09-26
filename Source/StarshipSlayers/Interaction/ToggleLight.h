// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ToggleLight.generated.h"

class URectLightComponent;

UCLASS()
class STARSHIPSLAYERS_API AToggleLight : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	USceneComponent* Root = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UStaticMeshComponent* ToggleLightMesh = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	URectLightComponent* ToggleRectLight = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UStaticMeshComponent* ConeLightEffect = nullptr;

	UPROPERTY(EditInstanceOnly, Category = "_Settings")
	bool bOn = true;

public:	
	AToggleLight();

	void OnConstruction(const FTransform& Transform) override;

	void Toggle();

protected:
	void Activate(bool bActivate);
};
