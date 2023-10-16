// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameMode.h"
#include "DaveGameMode.generated.h"

class UMainHUD;

UCLASS()
class STARSHIPSLAYERS_API ADaveGameMode : public AMainGameMode
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "_Settings")
	TSubclassOf<UMainHUD> MainHUDClass;

	UPROPERTY()
	UMainHUD* MainHUD = nullptr;

protected:
	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

public:
	UFUNCTION(BlueprintPure, DisplayName = "DaveGameMode - GetHUD")
	static UMainHUD* GetHUD();
};
