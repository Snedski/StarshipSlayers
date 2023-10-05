// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZoomSystem.generated.h"

class UCameraComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STARSHIPSLAYERS_API UZoomSystem : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "_Settings")
	float TargetFOV = 50.f;

	UPROPERTY(EditAnywhere, Category = "_Settings")
	float ZoomTime = 0.5f;

	UPROPERTY(EditAnywhere, Category = "_Settings")
	UCurveFloat* SmoothCurve = nullptr;

	UPROPERTY()
	UCameraComponent* OriginCamera = nullptr;

	bool bOn = false;
	float DefaultFOV = 0.f;
	float CurrentZoomTime = 0.f;

public:	
	UZoomSystem();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetupSystem(UCameraComponent* camera);

	UFUNCTION(BlueprintCallable)
	void EnableZoom(bool bEnable);
};
