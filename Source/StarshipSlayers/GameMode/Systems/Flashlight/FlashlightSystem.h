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
	USpotLightComponent* Flashlight = nullptr;

public:	
	UFlashlightSystem();

	UFUNCTION(BlueprintCallable)
	void SetupSystem(USpotLightComponent* spotlight);

	UFUNCTION(BlueprintCallable)
	void ToggleFlashlight();

protected:
	void ActivateFlashlight(bool bActivate);
};
