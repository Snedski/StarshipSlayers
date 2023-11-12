// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CustomUtility.generated.h"

class UCustomCheatManager;
class ADaveCharacter;

UCLASS()
class STARSHIPSLAYERS_API UCustomUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	friend UCustomCheatManager;
	
protected:
	static TArray<FString> ActiveDebugTags;

public:
	UFUNCTION(BlueprintCallable, meta = (AdvancedDisplay = 1, DevelopmentOnly))
	static void CustomPrintString(const FString& inStr, const FString& tag = "", FLinearColor color = FLinearColor(0.0, 0.66, 1.0), float duration = 2.f);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "worldContext"))
	static ADaveCharacter* GetDaveCharacter(UObject* worldContext);
};
