// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomUtility.h"
#include "CustomCheatManager.h"
#include "../Character/DaveCharacter.h"

TArray<FString> UCustomUtility::ActiveDebugTags = {};

void UCustomUtility::CustomPrintString(const FString& inStr, const FString& tag, FLinearColor color, float duration)
{
	if(tag != "" && !ActiveDebugTags.Contains(tag))
	{
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("%s"), *inStr);

	if(GAreScreenMessagesEnabled)
	{
		if(duration < 0.f)
		{
			duration = 0.f;
		}

		GEngine->AddOnScreenDebugMessage((uint64) - 1, duration, color.ToFColor(true), inStr);
	}
}

ADaveCharacter* UCustomUtility::GetDaveCharacter(UObject* worldContext)
{
	UWorld* world = GEngine->GetWorldFromContextObject(worldContext, EGetWorldErrorMode::ReturnNull);
	return (ADaveCharacter*) world->GetFirstPlayerController()->GetPawn();
}
