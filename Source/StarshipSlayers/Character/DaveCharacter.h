// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DaveCharacter.generated.h"

class UInteractionSystem;
class UFlashlightSystem;
class UZoomSystem;
class ULogBookSystem;

UCLASS()
class STARSHIPSLAYERS_API ADaveCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
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
};
