// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainGameMode.h"
#include "MenuGameMode.generated.h"

class UMainMenu;

UCLASS()
class STARSHIPSLAYERS_API AMenuGameMode : public AMainGameMode
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "_Settings")
	TSubclassOf<UMainMenu> MainMenuClass = nullptr;

	UPROPERTY()
	UMainMenu* MainMenu = nullptr;

protected:
	void BeginPlay() override;
};
