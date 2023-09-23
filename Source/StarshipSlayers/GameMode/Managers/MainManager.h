// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MainManager.generated.h"


UCLASS()
class STARSHIPSLAYERS_API UMainManager : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "_Settings")
	bool bEnable = true;

public:	
	UMainManager();	
};
