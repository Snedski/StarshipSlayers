// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SaveManager.generated.h"


UCLASS()
class STARSHIPSLAYERS_API USaveManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	USaveManager();

protected:
	static USaveManager* GetInstance();
};
