// Fill out your copyright notice in the Description page of Project Settings.


#include "ChipModeManager.h"
#include "../../MainGameMode.h"
#include "ChipModeData.h"
#include "WorldPartition/DataLayer/WorldDataLayers.h"
#include "WorldPartition/DataLayer/DataLayerInstance.h"
#include "WorldPartition/DataLayer/DataLayerManager.h"
#include "../../../Widgets/Debug/ChipModeSelection.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "../../Systems/Fade/FadeSystem.h"

UChipModeManager* UChipModeManager::GetInstance()
{
	return AMainGameMode::MainGameModeInstance->ChipModeManager;
}

void UChipModeManager::InitManager()
{
	Super::InitManager();

	AWorldDataLayers* dataLayers = GetWorld()->GetWorldDataLayers();
	UDataLayerManager* dataLayerManager = GetWorld()->GetDataLayerManager();

	for(UDataLayerAsset* dataLayerAsset : DefaultMode->LoadedLayers)
	{
		dataLayerManager->SetDataLayerRuntimeState(dataLayerAsset, EDataLayerRuntimeState::Activated);
	}
}

void UChipModeManager::ShowChipModeSelectionWidget()
{
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

	dataLayers->ForEachDataLayer([dataLayerManager](UDataLayerInstance* dataLayerInstance)
	{
		const UDataLayerAsset* dataLayerAsset = dataLayerInstance->GetAsset();
		dataLayerManager->SetDataLayerRuntimeState(dataLayerAsset, EDataLayerRuntimeState::Unloaded);
		return true;
	});

	for(UDataLayerAsset* dataLayerAsset : ChipModeToLoad->LoadedLayers)
	{
		dataLayerManager->SetDataLayerRuntimeState(dataLayerAsset, EDataLayerRuntimeState::Activated);
	}

	ChipModeToLoad = nullptr;
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
		if(bActive && !IsValid(inst->ChipModeSelection))
		{
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
		result.Add(inst->DefaultMode->ChipModeName);

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
			inst->ChipModeToLoad = chipModeData;
			inst->bInProcess = true;

			AFadeSystem::GetInstance()->OnFadeIn.AddUniqueDynamic(inst, &UChipModeManager::OnChipModeFadeIn);
			AFadeSystem::GetInstance()->OnFadeOut.AddUniqueDynamic(inst, &UChipModeManager::OnChipModeFadeOut);
			AFadeSystem::GetInstance()->FadeInOut(FFadeData());
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

		for(UChipModeData* chipModeData : inst->ChipModeDatas)
		{
			if(chipModeName == chipModeData->ChipModeName)
			{
				AccessChipMode(chipModeData);
				return;
			}
		}
	}
}
