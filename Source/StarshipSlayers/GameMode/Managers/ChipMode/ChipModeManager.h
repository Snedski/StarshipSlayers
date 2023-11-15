// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Main/MainManager.h"
#include "ChipModeManager.generated.h"

class UChipModeData;
class UChipModeSelection;

UCLASS()
class STARSHIPSLAYERS_API UChipModeManager : public UMainManager
{
	GENERATED_BODY()
	
protected:
	static UChipModeManager* GetInstance();

	UPROPERTY(EditAnywhere, Category = "_Settings")
	UChipModeData* DefaultMode = nullptr;

	UPROPERTY(EditAnywhere, Category = "_Settings")
	TArray<UChipModeData*> ChipModeDatas = {};

	UPROPERTY(EditAnywhere, Category = "_Settings\|Debug")
	TSoftClassPtr<UChipModeSelection> ChipModeSelectionSoft = nullptr;

	UPROPERTY()
	UChipModeSelection* ChipModeSelection = nullptr;

	UPROPERTY()
	UChipModeData* ChipModeToLoad = nullptr;

	bool bChipModeSelectionActive = false;
	bool bInProcess = false;

protected:
	void InitManager() override;

	void ShowChipModeSelectionWidget();

	UFUNCTION()
	void OnChipModeFadeIn();

	UFUNCTION()
	void OnChipModeFadeOut();

public:
	static void ActivateChipModeSelection(bool bActive);

	UFUNCTION(BlueprintPure, DisplayName = "ChipModeManager - GetChipModeNameList")
	static TArray<FString> GetChipModeNameList();

	UFUNCTION(BlueprintCallable, DisplayName = "ChipModeManager - AccessChipMode")
	static void AccessChipMode(UChipModeData* chipModeData);

	UFUNCTION(BlueprintCallable, DisplayName = "ChipModeManager - AccessChipModeByName")
	static void AccessChipModeByName(FString chipModeName);
};
