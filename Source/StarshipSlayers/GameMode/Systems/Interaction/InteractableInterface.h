// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/CoreUObject/Public/UObject/NoExportTypes.h"
#include "InteractableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

class STARSHIPSLAYERS_API IInteractableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Interact();
	virtual void Interact_Implementation() {};

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Focus(bool bFocus);
	virtual void Focus_Implementation(bool bFocus) {};
};