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

	UFUNCTION(BlueprintPure, DisplayName = "SaveManager - GetSaveFromSlot")
	static UMainSaveGame* GetSaveFromSlot(FString slotName);

	UFUNCTION(BlueprintCallable, DisplayName = "SaveManager - SaveSlot")
	static void SaveSlot(FString slotName);

	UFUNCTION(BlueprintPure, DisplayName = "SaveManager - LoadFromSlot")
	static UMainSaveGame* LoadFromSlot(FString slotName);

	UFUNCTION(BlueprintPure, DisplayName = "SaveManager - DoesSaveExist")
	static bool DoesSaveExist(FString slotName);

protected:
	static USaveManager* GetInstance();

	void CheckExistingSave(FString slotName);
};
