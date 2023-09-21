// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DaveCharacter.generated.h"

UCLASS()
class STARSHIPSLAYERS_API ADaveCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADaveCharacter();

	void BeginPlay() override;
};
