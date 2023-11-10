// Fill out your copyright notice in the Description page of Project Settings.


#include "ChipModeManager.h"
#include "../../MainGameMode.h"
#include "ChipModeData.h"
#include "WorldPartition/DataLayer/WorldDataLayers.h"
#include "WorldPartition/DataLayer/DataLayerInstance.h"
#include "WorldPartition/DataLayer/DataLayerManager.h"

UChipModeManager* UChipModeManager::GetInstance()
{
	return AMainGameMode::MainGameModeInstance->ChipModeManager;
}

void UChipModeManager::InitManager()
{
	Super::InitManager();

	AWorldDataLayers* dataLayers = GetWorld()->GetWorldDataLayers();
	UDataLayerManager* dataLayerManager = GetWorld()->GetDataLayerManager();

	/*dataLayers->ForEachDataLayer([dataLayerManager](UDataLayerInstance* dataLayerInstance) 
	{
		const UDataLayerAsset* dataLayerAsset = dataLayerInstance->GetAsset();
		dataLayerManager->SetDataLayerRuntimeState(dataLayerAsset, EDataLayerRuntimeState::Unloaded);
		return true;
	});*/

	for(UDataLayerAsset* dataLayerAsset : DefaultMode->LoadedLayers)
	{
		dataLayerManager->SetDataLayerRuntimeState(dataLayerAsset, EDataLayerRuntimeState::Activated);
	}
}
