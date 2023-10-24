// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CustomUtility.generated.h"

class UCustomCheatManager;

UCLASS()
class STARSHIPSLAYERS_API UCustomUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	friend UCustomCheatManager;
	
protected:
	static TArray<FString> ActiveDebugTags;

public:
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "worldContext", CallableWithoutWorldContext, AdvancedDisplay = 1, DevelopmentOnly))
	static void CustomPrintString(const FString& inStr, const FString& tag = "", FLinearColor color = FLinearColor(0.0, 0.66, 1.0), float duration = 2.f);
};
