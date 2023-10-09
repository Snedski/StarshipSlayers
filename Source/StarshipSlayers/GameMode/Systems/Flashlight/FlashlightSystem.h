// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FlashlightSystem.generated.h"

class USpotLightComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STARSHIPSLAYERS_API UFlashlightSystem : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "_Settings")
	bool bOn = false;

	UPROPERTY()
	USceneComponent* FlashlightsRoot = nullptr;

public:	
	UFlashlightSystem();

	UFUNCTION(BlueprintCallable)
	void SetupSystem(USceneComponent* spotlightsRoot);

	UFUNCTION(BlueprintCallable)
	void ToggleFlashlight();

protected:
	void ActivateFlashlight(bool bActivate);
};
