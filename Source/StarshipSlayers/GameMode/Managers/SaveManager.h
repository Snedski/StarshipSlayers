// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SaveManager.generated.h"

class UMainSaveGame;

UCLASS()
class STARSHIPSLAYERS_API USaveManager : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	UMainSaveGame* CurrentSaveGame = nullptr;

	FString CurrentSlotName = "";

public:	
	USaveManager();

	UFUNCTION(BlueprintPure, DisplayName = "Save Manager Get Save From Slot")
	static UMainSaveGame* GetSaveFromSlot(FString slotName);

	UFUNCTION(BlueprintCallable, DisplayName = "Save Manager Save Slot")
	static void SaveSlot(FString slotName);

protected:
	static USaveManager* GetInstance();

	void CheckExistingSave(FString slotName);
};
