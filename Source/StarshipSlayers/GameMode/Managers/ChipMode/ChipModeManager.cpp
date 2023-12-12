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
	CurrentChipMode = DefaultMode;

	for(UDataLayerAsset* dataLayerAsset : DefaultMode->LoadedLayers)
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

	dataLayers->ForEachDataLayer([dataLayerManager](UDataLayerInstance* dataLayerInstance)
	{
		const UDataLayerAsset* dataLayerAsset = dataLayerInstance->GetAsset();
		dataLayerManager->SetDataLayerRuntimeState(dataLayerAsset, EDataLayerRuntimeState::Unloaded);
		return true;
	});

	for(UDataLayerAsset* dataLayerAsset : CurrentChipMode->LoadedLayers)
	{
		dataLayerManager->SetDataLayerRuntimeState(dataLayerAsset, EDataLayerRuntimeState::Activated);
	}

	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	APawn* pawn = controller->GetPawn();
	SetComponentTickEnabled(true);

	if(CurrentChipMode == DefaultMode)
	{
		pawn->SetActorLocation(LatestLocation);
		pawn->SetActorRotation(LatestRotation);
		controller->SetControlRotation(LatestRotation);
	}
	else
	{
		LatestLocation = pawn->GetActorLocation();
		LatestRotation = pawn->GetControlRotation();

		if(CurrentChipMode->StartLocation != FVector::ZeroVector && CurrentChipMode->StartRotation != FRotator::ZeroRotator)
		{
			pawn->SetActorLocation(CurrentChipMode->StartLocation);
			pawn->SetActorRotation(CurrentChipMode->StartRotation);
			controller->SetControlRotation(CurrentChipMode->StartRotation);
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
			inst->CurrentChipMode = chipModeData;
			inst->bInProcess = true;

			UWorld* world = inst->GetWorld();
			AWorldDataLayers* dataLayers = world->GetWorldDataLayers();
			UDataLayerManager* dataLayerManager = world->GetDataLayerManager();

			for(UDataLayerAsset* dataLayerAsset : inst->CurrentChipMode->LoadedLayers)
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