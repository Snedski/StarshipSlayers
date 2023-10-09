// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

class USaveManager;
class UMainHUD;
class AFadeSystem;

UCLASS()
class STARSHIPSLAYERS_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	friend USaveManager;
	friend AFadeSystem;

public:
	static AMainGameMode* MainGameModeInstance;

protected:
	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	USaveManager* SaveManager = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings")
	TSubclassOf<UMainHUD> MainHUDClass;

	UPROPERTY()
	UMainHUD* MainHUD = nullptr;

public:
	AMainGameMode();

protected:
	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	void BeginPlay() override;

	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UFUNCTION(BlueprintPure, DisplayName = "MainGameMode - GetHUD")
	static UMainHUD* GetHUD();
};
