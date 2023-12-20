// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Main/MainManager.h"
#include "ChipModeManager.generated.h"

class UChipModeData;
class UChipModeSelection;
class UChipModeStartingPosRegistration;

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

	bool bChipModeSelectionActive = false;
	bool bInProcess = false;

protected:
	UChipModeManager();

	void InitManager() override;

	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void ShowChipModeSelectionWidget();

	UFUNCTION()
	void OnChipModeFadeIn();

	UFUNCTION()
	void OnChipModeFadeOut();

public:
	UFUNCTION(BlueprintCallable, DisplayName = "ChipModeManager - ActivateChipModeSelection")
	static void ActivateChipModeSelection(bool bActive);

	UFUNCTION(BlueprintPure, DisplayName = "ChipModeManager - GetChipModeNameList")
	static TArray<FString> GetChipModeNameList();

	UFUNCTION(BlueprintCallable, DisplayName = "ChipModeManager - AccessChipMode")
	static void AccessChipMode(UChipModeData* chipModeData);

	UFUNCTION(BlueprintCallable, DisplayName = "ChipModeManager - AccessChipModeByName")
	static void AccessChipModeByName(FString chipModeName);

protected:
	UChipModeData* GetChipModeByName(FString chipModeName);

	UChipModeData* GetCurrentChipMode();

#if WITH_EDITORONLY_DATA

protected:
	UPROPERTY(EditAnywhere, Category = "_Settings\|Debug")
	TSoftClassPtr<UChipModeStartingPosRegistration> ChipModeStartingPosRegistrationSoft = nullptr;

	UPROPERTY()
	UChipModeStartingPosRegistration* ChipModeStartingPosRegistration = nullptr;

protected:
	void ShowChipModeStartingPosRegistrationWidget();

public:
	static void LoadChipModeStartingPosRegistrationWidget();

	static void RegisterChipModeStartingPosition(FString chipModeName);

#endif
};
