// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../GameMode/Systems/Interaction/InteractableInterface.h"
#include "ChipModeInteractable.generated.h"

class UChipModeData;

UCLASS()
class STARSHIPSLAYERS_API AChipModeInteractable : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "_Settings")
	UChipModeData* ChipModeTriggered = nullptr;

public:	
	AChipModeInteractable();

	void Interact_Implementation() override;

	void Focus_Implementation(bool bFocus) override;
};
