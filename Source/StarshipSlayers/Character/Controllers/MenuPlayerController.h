// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainPlayerController.h"
#include "MenuPlayerController.generated.h"

UCLASS()
class STARSHIPSLAYERS_API AMenuPlayerController : public AMainPlayerController
{
	GENERATED_BODY()
	
protected:
	void BeginPlay() override;
};
