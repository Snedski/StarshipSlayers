// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../GameMode/Systems/Interaction/InteractableInterface.h"
#include "ToggleSwitch.generated.h"

class AToggleLight;

UCLASS()
class STARSHIPSLAYERS_API AToggleSwitch : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UStaticMeshComponent* ToggleSwitchMesh = nullptr;

	UPROPERTY(EditInstanceOnly, Category = "_Settings")
	FGuid SwitchGUID = FGuid();

public:	
	AToggleSwitch();

	void Interact_Implementation() override;

	void Focus_Implementation(bool bFocus) override;
};
