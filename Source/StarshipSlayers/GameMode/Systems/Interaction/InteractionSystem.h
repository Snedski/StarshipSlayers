// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionSystem.generated.h"

class UCameraComponent;

UCLASS()
class STARSHIPSLAYERS_API UInteractionSystem : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "_Settings")
	float InteractionDistance = 300.f;

	UPROPERTY(EditAnywhere, Category = "_Settings")
	float InteractionRadius = 20.f;

	UPROPERTY()
	UCameraComponent* CameraOrigin = nullptr;

	UPROPERTY()
	AActor* FocusedInteractable = nullptr;

public:	
	UInteractionSystem();

	UFUNCTION(BlueprintCallable)
	void SetupSystem(UCameraComponent* camera);

	UFUNCTION(BlueprintCallable)
	void Interact();

protected:
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	AActor* ChooseBestInteractable(TArray<FHitResult> hitResults);
};
