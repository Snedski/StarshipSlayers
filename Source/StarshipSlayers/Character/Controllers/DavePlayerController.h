// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainPlayerController.h"
#include "DavePlayerController.generated.h"

UCLASS()
class STARSHIPSLAYERS_API ADavePlayerController : public AMainPlayerController
{
	GENERATED_BODY()
	
protected:
	void BeginPlay() override;
};
