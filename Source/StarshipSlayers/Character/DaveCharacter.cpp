// Fill out your copyright notice in the Description page of Project Settings.


#include "DaveCharacter.h"
#include "../GameMode/Systems/Interaction/InteractionSystem.h"
#include "../GameMode/Systems/Flashlight/FlashlightSystem.h"
#include "../GameMode/Systems/Zoom/ZoomSystem.h"
#include "../GameMode/Systems/LogBook/LogBookSystem.h"
#include "../GameMode/Managers/Save/SaveManager.h"
#include "../Save/MainSaveData.h"
#include "../Save/MainSaveGame.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/Components/SpotLightComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "../GameMode/Systems/Pause/PauseSystem.h"

ADaveCharacter::ADaveCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->AttachToComponent(Camera, FAttachmentTransformRules::KeepRelativeTransform);

	SpotLight = CreateDefaultSubobject<USpotLightComponent>("SpotLight");
	SpotLight->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);

	InteractionSystem = CreateDefaultSubobject<UInteractionSystem>("Interaction System");
	FlashlightSystem = CreateDefaultSubobject<UFlashlightSystem>("Flashlight System");
	ZoomSystem = CreateDefaultSubobject<UZoomSystem>("Zoom System");
	LogBookSystem = CreateDefaultSubobject<ULogBookSystem>("LogBook System");
	PauseSystem = CreateDefaultSubobject<UPauseSystem>("Pause System");
}

void ADaveCharacter::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* controller = GetWorld()->GetFirstPlayerController();

	if(USaveManager::DoesSaveExist("SaveSlot_0"))
	{
		UMainSaveGame* saveGame = USaveManager::GetSaveFromSlot("SaveSlot_0");
		FPlayerSaveData saveData = saveGame->PlayerSaveData;

		SetActorLocation(saveData.PlayerLocation);
		SetActorRotation(saveData.PlayerRotation);
		controller->SetControlRotation(GetActorRotation());
	}

	InteractionSystem->SetupSystem(Camera);
	FlashlightSystem->SetupSystem(SpringArm);
	ZoomSystem->SetupSystem(Camera);
	LogBookSystem->SetupSystem();
	PauseSystem->SetupSystem();
}

void ADaveCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UMainSaveGame* saveGame = USaveManager::GetSaveFromSlot("SaveSlot_0");
	saveGame->PlayerSaveData.PlayerLocation = GetActorLocation();
	saveGame->PlayerSaveData.PlayerRotation = GetControlRotation();
}

void ADaveCharacter::OnMove(FVector2D input)
{
	AddMovementInput(GetActorRightVector(), input.X);
	AddMovementInput(GetActorForwardVector(), input.Y);
}

void ADaveCharacter::OnLook(FVector2D input)
{
	AddControllerYawInput(input.X);
	AddControllerPitchInput(input.Y);
}

void ADaveCharacter::OnSave()
{
	USaveManager::SaveSlot("SaveSlot_0");
}

void ADaveCharacter::OnLoad()
{
	UWorld* world = GetWorld();
	UGameplayStatics::OpenLevel(world, FName(UGameplayStatics::GetCurrentLevelName(world)));
}

void ADaveCharacter::OnUse()
{
	InteractionSystem->Interact();
}

void ADaveCharacter::OnFlashlight()
{
	FlashlightSystem->ToggleFlashlight();
}

void ADaveCharacter::OnZoom(bool value)
{
	ZoomSystem->EnableZoom(value);
}

void ADaveCharacter::OnLogBook()
{
	if(!PauseSystem->IsPauseMenuOpen())
	{
		LogBookSystem->ToggleLogBook();
	}
}

void ADaveCharacter::OnPause()
{
	if(!LogBookSystem->IsLogBookOpen() && !LogBookSystem->InTransition())
	{
		PauseSystem->TogglePauseMenu();
	}
}
