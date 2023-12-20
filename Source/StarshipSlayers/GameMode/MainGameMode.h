// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../Data/FadeData.h"
#include "MainGameMode.generated.h"

class USaveManager;
class AFadeSystem;
class UChipModeManager;
class UObjectLinkManager;

UCLASS()
class STARSHIPSLAYERS_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	friend USaveManager;
	friend AFadeSystem;
	friend UChipModeManager;
	friend UObjectLinkManager;

public:
	static AMainGameMode* MainGameModeInstance;

protected:
	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	USaveManager* SaveManager = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UChipModeManager* ChipModeManager = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UObjectLinkManager* ObjectLinkManager = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings")
	float TimeBeforeFadeOut = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings")
	FFadeData StartingFade = FFadeData();

	float ElapsedBeforeFadeOut = 0.f;

public:
	AMainGameMode();

protected:
	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	void BeginPlay() override;

	void Tick( float DeltaSeconds ) override;

	void FinishDestroy() override;
};
