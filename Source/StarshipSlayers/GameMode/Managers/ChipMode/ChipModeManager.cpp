// Fill out your copyright notice in the Description page of Project Settings.


#include "ChipModeManager.h"
#include "../../MainGameMode.h"
#include "ChipModeData.h"
#include "WorldPartition/DataLayer/WorldDataLayers.h"
#include "WorldPartition/DataLayer/DataLayerInstance.h"
#include "WorldPartition/DataLayer/DataLayerManager.h"
#include "../../../Widgets/Debug/ChipModeSelection.h"
#include "../../../Widgets/Debug/ChipModeStartingPosRegistration.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "../../Systems/Fade/FadeSystem.h"
#include "WorldPartition/WorldPartitionSubsystem.h"
#include "WorldPartition/DataLayer/DataLayerAsset.h"
#include "../Save/SaveManager.h"
#include "../../../Save/MainSaveData.h"
#include "../../../Save/MainSaveGame.h"

UChipModeManager* UChipModeManager::GetInstance()
{
	return AMainGameMode::MainGameModeInstance->ChipModeManager;
}

UChipModeManager::UChipModeManager()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UChipModeManager::InitManager()
{
	Super::InitManager();

	AWorldDataLayers* dataLayers = GetWorld()->GetWorldDataLayers();
	UDataLayerManager* dataLayerManager = GetWorld()->GetDataLayerManager();
	UChipModeData* current = GetCurrentChipMode();

	for(UDataLayerAsset* dataLayerAsset : current->LoadedLayers)
	{
		dataLayerManager->SetDataLayerRuntimeState(dataLayerAsset, EDataLayerRuntimeState::Activated);
	}
}

void UChipModeManager::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UWorldPartitionSubsystem* worldPartition = UWorld::GetSubsystem<UWorldPartitionSubsystem>(GetWorld());

	if(worldPartition->IsAllStreamingCompleted())
	{
		SetComponentTickEnabled(false);
		AFadeSystem::GetInstance()->FadeOut(FFadeData());
	}
}

void UChipModeManager::ShowChipModeSelectionWidget()
{
	bInProcess = false;
	ChipModeSelection = CreateWidget<UChipModeSelection>(GetWorld()->GetFirstPlayerController(), ChipModeSelectionSoft.Get());
	ChipModeSelection->AddToViewport(1);

	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	controller->SetInputMode(FInputModeGameAndUI());
}

void UChipModeManager::OnChipModeFadeIn()
{
	AFadeSystem::GetInstance()->OnFadeIn.RemoveDynamic(this, &UChipModeManager::OnChipModeFadeIn);

	AWorldDataLayers* dataLayers = GetWorld()->GetWorldDataLayers();
	UDataLayerManager* dataLayerManager = GetWorld()->GetDataLayerManager();
	UChipModeData* current = GetCurrentChipMode();

	dataLayers->ForEachDataLayer([dataLayerManager](UDataLayerInstance* dataLayerInstance)
	{
		const UDataLayerAsset* dataLayerAsset = dataLayerInstance->GetAsset();
		dataLayerManager->SetDataLayerRuntimeState(dataLayerAsset, EDataLayerRuntimeState::Unloaded);
		return true;
	});

	for(UDataLayerAsset* dataLayerAsset : current->LoadedLayers)
	{
		dataLayerManager->SetDataLayerRuntimeState(dataLayerAsset, EDataLayerRuntimeState::Activated);
	}

	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	APawn* pawn = controller->GetPawn();
	SetComponentTickEnabled(true);

	UMainSaveGame* saveGame = USaveManager::GetSaveFromSlot("SaveSlot_0");

	if(current == DefaultMode)
	{
		FChipModeSaveData saveData = saveGame->ChipModeSaveData;

		pawn->SetActorLocation(saveData.LastPlayerLocation);
		pawn->SetActorRotation(saveData.LastPlayerRotation);
		controller->SetControlRotation(saveData.LastPlayerRotation);
	}
	else
	{
		saveGame->ChipModeSaveData.LastPlayerLocation = pawn->GetActorLocation();
		saveGame->ChipModeSaveData.LastPlayerRotation = pawn->GetControlRotation();

		if(current->StartLocation != FVector::ZeroVector && current->StartRotation != FRotator::ZeroRotator)
		{
			pawn->SetActorLocation(current->StartLocation);
			pawn->SetActorRotation(current->StartRotation);
			controller->SetControlRotation(current->StartRotation);
		}
	}
}

void UChipModeManager::OnChipModeFadeOut()
{
	AFadeSystem::GetInstance()->OnFadeOut.RemoveDynamic(this, &UChipModeManager::OnChipModeFadeOut);
	bInProcess = false;
}

void UChipModeManager::ActivateChipModeSelection(bool bActive)
{
	UChipModeManager* inst = GetInstance();

	if(inst->bEnable)
	{
		if(bActive && !IsValid(inst->ChipModeSelection) && !inst->bInProcess)
		{
			inst->bInProcess = true;
			const FSoftObjectPath& path = inst->ChipModeSelectionSoft.ToSoftObjectPath();
			FStreamableDelegate del = FStreamableDelegate::CreateUObject(inst, &UChipModeManager::ShowChipModeSelectionWidget);

			UAssetManager::GetStreamableManager().RequestAsyncLoad(path, del);
		}
		else if(!bActive && IsValid(inst->ChipModeSelection))
		{
			inst->ChipModeSelection->RemoveFromParent();
			inst->ChipModeSelection = nullptr;
			
			APlayerController* controller = inst->GetWorld()->GetFirstPlayerController();
			controller->SetInputMode(FInputModeGameOnly());
		}
	}
}

TArray<FString> UChipModeManager::GetChipModeNameList()
{
	UChipModeManager* inst = GetInstance();

	if(inst->bEnable)
	{
		TArray<FString> result = {};
		result.Add("Default");

		for(UChipModeData* data : inst->ChipModeDatas)
		{
			result.Add(data->ChipModeName);
		}

		return result;
	}

	return {};
}

void UChipModeManager::AccessChipMode(UChipModeData* chipModeData)
{
	UChipModeManager* inst = GetInstance();

	if(inst->bEnable)
	{
		if(!inst->bInProcess)
		{
			UMainSaveGame* saveGame = USaveManager::GetSaveFromSlot("SaveSlot_0");
			saveGame->ChipModeSaveData.CurrentChipModeName = chipModeData->ChipModeName;
			inst->bInProcess = true;

			UWorld* world = inst->GetWorld();
			AWorldDataLayers* dataLayers = world->GetWorldDataLayers();
			UDataLayerManager* dataLayerManager = world->GetDataLayerManager();

			for(UDataLayerAsset* dataLayerAsset : chipModeData->LoadedLayers)
			{
				const UDataLayerInstance* dataLayerInstance = dataLayerManager->GetDataLayerInstanceFromAsset(dataLayerAsset);
				EDataLayerRuntimeState currentState = dataLayerManager->GetDataLayerInstanceRuntimeState(dataLayerInstance);

				if(currentState == EDataLayerRuntimeState::Unloaded)
				{
					dataLayerManager->SetDataLayerRuntimeState(dataLayerAsset, EDataLayerRuntimeState::Loaded);
				}
			}

			AFadeSystem::GetInstance()->OnFadeIn.AddUniqueDynamic(inst, &UChipModeManager::OnChipModeFadeIn);
			AFadeSystem::GetInstance()->OnFadeOut.AddUniqueDynamic(inst, &UChipModeManager::OnChipModeFadeOut);
			AFadeSystem::GetInstance()->FadeIn(FFadeData());
		}
	}
}

void UChipModeManager::AccessChipModeByName(FString chipModeName)
{
	UChipModeManager* inst = GetInstance();

	if(inst->bEnable)
	{
		if(chipModeName == inst->DefaultMode->ChipModeName)
		{
			AccessChipMode(inst->DefaultMode);
			return;
		}

		if(UChipModeData* chipModeData = inst->GetChipModeByName(chipModeName))
		{
			AccessChipMode(chipModeData);
		}
	}
}

UChipModeData* UChipModeManager::GetChipModeByName(FString chipModeName)
{
	for(UChipModeData* chipModeData : ChipModeDatas)
	{
		if(chipModeName == chipModeData->ChipModeName)
		{
			return chipModeData;
		}
	}

	return DefaultMode;
}

UChipModeData* UChipModeManager::GetCurrentChipMode()
{
	UMainSaveGame* saveGame = USaveManager::GetSaveFromSlot("SaveSlot_0");
	FChipModeSaveData saveData = saveGame->ChipModeSaveData;
	return GetChipModeByName(saveData.CurrentChipModeName);
}

#if WITH_EDITORONLY_DATA

void UChipModeManager::ShowChipModeStartingPosRegistrationWidget()
{
	bInProcess = false;
	ChipModeStartingPosRegistration = CreateWidget<UChipModeStartingPosRegistration>(GetWorld()->GetFirstPlayerController(), ChipModeStartingPosRegistrationSoft.Get());
	ChipModeStartingPosRegistration->AddToViewport(1);

	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	controller->SetInputMode(FInputModeGameAndUI());
}

void UChipModeManager::LoadChipModeStartingPosRegistrationWidget()
{
	UChipModeManager* inst = GetInstance();

	if(inst->bEnable && !IsValid(inst->ChipModeStartingPosRegistration) && !inst->bInProcess)
	{
		inst->bInProcess = true;

		APlayerController* controller = inst->GetWorld()->GetFirstPlayerController();
		controller->SetPause(true);

		const FSoftObjectPath& path = inst->ChipModeStartingPosRegistrationSoft.ToSoftObjectPath();
		FStreamableDelegate del = FStreamableDelegate::CreateUObject(inst, &UChipModeManager::ShowChipModeStartingPosRegistrationWidget);

		UAssetManager::GetStreamableManager().RequestAsyncLoad(path, del);
	}
}

void UChipModeManager::RegisterChipModeStartingPosition(FString chipModeName)
{
	UChipModeManager* inst = GetInstance();

	if(inst->bEnable)
	{
		APlayerController* controller = inst->GetWorld()->GetFirstPlayerController();

		if(chipModeName != inst->DefaultMode->ChipModeName)
		{
			for(UChipModeData* chipModeData : inst->ChipModeDatas)
			{
				if(chipModeName == chipModeData->ChipModeName)
				{
					APawn* pawn = controller->GetPawn();
					chipModeData->StartLocation = pawn->GetActorLocation();
					chipModeData->StartRotation = pawn->GetControlRotation();

					if(!chipModeData->GetPackage()->IsDirty())
					{
						chipModeData->GetPackage()->SetDirtyFlag(true);
					}
				}
			}
		}

		inst->ChipModeStartingPosRegistration->RemoveFromParent();
		inst->ChipModeStartingPosRegistration = nullptr;
		controller->SetInputMode(FInputModeGameOnly());
		controller->SetPause(false);
	}
}

#endif