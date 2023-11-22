// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCheatManager.h"
#include "CustomUtility.h"
#include "../GameMode/Managers/ChipMode/ChipModeManager.h"

void UCustomCheatManager::UpdateDebugTagVisiblity(FString tag, bool bVisible)
{
	bool bContains = UCustomUtility::ActiveDebugTags.Contains(tag);

	if(bVisible && !bContains)
	{
		UCustomUtility::ActiveDebugTags.Add(tag);
	}
	else if(!bVisible && bContains)
	{
		UCustomUtility::ActiveDebugTags.Remove(tag);
	}
}

void UCustomCheatManager::ActivateChipModeSelection(bool bActive)
{
	UChipModeManager::ActivateChipModeSelection(bActive);
}

void UCustomCheatManager::RegisterChipModeStartingPosition()
{
	UChipModeManager::LoadChipModeStartingPosRegistrationWidget();
}
