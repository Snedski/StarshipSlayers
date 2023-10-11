// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DaveCharacter.generated.h"

class UInteractionSystem;
class UFlashlightSystem;
class UZoomSystem;
class ULogBookSystem;
class UInputMappingContext;
class USpringArmComponent;
class UCameraComponent;
class USpotLightComponent;

UCLASS()
class STARSHIPSLAYERS_API ADaveCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "_Settings")
	UInputMappingContext* InputMapping = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UCameraComponent* Camera = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	USpotLightComponent* SpotLight = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (Hidden))
	UInteractionSystem* InteractionSystem = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (Hidden))
	UFlashlightSystem* FlashlightSystem = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (Hidden))
	UZoomSystem* ZoomSystem = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (Hidden))
	ULogBookSystem* LogBookSystem = nullptr;

public:
	ADaveCharacter();

	void BeginPlay() override;

	void Tick( float DeltaSeconds ) override;

protected:
	UFUNCTION(BlueprintCallable)
	void OnMove(FVector2D input);

	UFUNCTION(BlueprintCallable)
	void OnLook(FVector2D input);

	UFUNCTION(BlueprintCallable)
	void OnSave();

	UFUNCTION(BlueprintCallable)
	void OnLoad();

	UFUNCTION(BlueprintCallable)
	void OnUse();

	UFUNCTION(BlueprintCallable)
	void OnFlashlight();

	UFUNCTION(BlueprintCallable)
	void OnZoom(bool value);

	UFUNCTION(BlueprintCallable)
	void OnLogBook();
};
