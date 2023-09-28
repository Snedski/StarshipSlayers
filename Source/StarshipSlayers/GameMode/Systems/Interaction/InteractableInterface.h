// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/CoreUObject/Public/UObject/NoExportTypes.h"
#include "InteractableInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

class STARSHIPSLAYERS_API IInteractableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, DisplayName = "Interactable - Interact")
	void Interact();
	virtual void Interact_Implementation() {};

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, DisplayName = "Interactable - Focus")
	void Focus(bool bFocus);
	virtual void Focus_Implementation(bool bFocus) {};
};