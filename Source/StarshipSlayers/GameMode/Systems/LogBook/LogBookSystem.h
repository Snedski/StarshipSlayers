// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LogBookSystem.generated.h"

class ULogBook;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STARSHIPSLAYERS_API ULogBookSystem : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "_Settings")
	TSubclassOf<ULogBook> LogBookClass = nullptr;

	UPROPERTY(EditAnywhere, Category = "_Settings")
	FFadeData FadeTransitionSettings = FFadeData();

	UPROPERTY()
	ULogBook* LogBook = nullptr;

	bool bTransitionDone = true;

public:	
	ULogBookSystem();

	UFUNCTION(BlueprintCallable)
	void SetupSystem();

	UFUNCTION(BlueprintCallable)
	void ToggleLogBook();

protected:
	UFUNCTION()
	void OnToggleFadeIn();

	UFUNCTION()
	void OnToggleFadeOut();
};
