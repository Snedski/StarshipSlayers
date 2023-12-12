// Fill out your copyright notice in the Description page of Project Settings.


#include "ChipModeStartingPosRegistration.h"
#include "../../GameMode/Managers/ChipMode/ChipModeManager.h"

void UChipModeStartingPosRegistration::OnSaveButtonClicked(FString selectedOption)
{
#if WITH_EDITORONLY_DATA
	UChipModeManager::RegisterChipModeStartingPosition(selectedOption);
#endif
}
