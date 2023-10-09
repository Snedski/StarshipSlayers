// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "../../../Data/FadeData.h"
#include "FadeSystem.generated.h"

class UFadeWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFadeSystemEvent);

UCLASS()
class STARSHIPSLAYERS_API AFadeSystem : public APlayerCameraManager
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "_Settings")
	TSubclassOf<UFadeWidget> FadeWidgetClass;

	UPROPERTY()
	UFadeWidget* FadeWidget = nullptr;

	FFadeData FadeInOutData = FFadeData();

public:
	UPROPERTY(BlueprintAssignable)
	FFadeSystemEvent OnFadeIn;

	UPROPERTY(BlueprintAssignable)
	FFadeSystemEvent OnFadeOut;

protected:
	void BeginPlay() override;

	void DoUpdateCamera(float DeltaTime) override;

	void StopCameraFade() override;

public:
	UFUNCTION(BlueprintPure, DisplayName = "Get FadeSystem")
	static AFadeSystem* GetInstance();

	UFUNCTION(BlueprintCallable)
	void FadeIn(FFadeData data);

	UFUNCTION(BlueprintCallable)
	void FadeOut(FFadeData data);

	UFUNCTION(BlueprintCallable)
	void FadeInOut(FFadeData data);

protected:
	UFUNCTION()
	void OnAutoFadeIn();

	UFUNCTION()
	void OnAutoFadeOut();
};
