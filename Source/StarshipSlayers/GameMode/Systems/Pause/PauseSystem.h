// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PauseSystem.generated.h"

class UPauseMenu;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STARSHIPSLAYERS_API UPauseSystem : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "_Settings")
	TSubclassOf<UPauseMenu> PauseMenuClass = nullptr;

	UPROPERTY()
	UPauseMenu* PauseMenu = nullptr;

	bool bPauseMenuOpen = false;

public:	
	UPauseSystem();	

	void SetupSystem();

	void TogglePauseMenu();

	bool IsPauseMenuOpen();
};
