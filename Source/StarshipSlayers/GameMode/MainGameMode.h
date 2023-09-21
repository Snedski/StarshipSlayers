// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

class USaveManager;

UCLASS()
class STARSHIPSLAYERS_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	friend class USaveManager;

public:
	static AMainGameMode* MainGameModeInstance;

protected:
	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	USaveManager* SaveManager = nullptr;

public:
	AMainGameMode();

protected:
	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
