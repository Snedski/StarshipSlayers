// Fill out your copyright notice in the Description page of Project Settings.


#include "FadeSystem.h"
#include "../../MainGameMode.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "../../../Widgets/Fade/FadeWidget.h"

void AFadeSystem::BeginPlay()
{
	Super::BeginPlay();

	FadeWidget = CreateWidget<UFadeWidget>(GetWorld()->GetFirstPlayerController(), FadeWidgetClass);
	FadeWidget->AddToViewport(1000000.f);
}

void AFadeSystem::DoUpdateCamera(float DeltaTime)
{
	Super::DoUpdateCamera(DeltaTime);
	FadeWidget->UpdateFadeScreen(FadeAmount, FadeColor);
}

void AFadeSystem::StopCameraFade()
{
	Super::StopCameraFade();

	if(FadeAmount > 0.f)
	{
		OnFadeIn.Broadcast();
	}
	else
	{
		OnFadeOut.Broadcast();
	}
}

AFadeSystem* AFadeSystem::GetInstance()
{
	return Cast<AFadeSystem>(UGameplayStatics::GetPlayerCameraManager(AMainGameMode::MainGameModeInstance->GetWorld(), 0));
}

void AFadeSystem::FadeIn(FFadeData data)
{
	if(FadeAmount > 0.f)
	{
		data.Color = FadeColor;
	}

	float durationFromCurrentFadeAmount = data.Duration - (FadeAmount * data.Duration);

	if(durationFromCurrentFadeAmount < 0.1f)
	{
		SetManualCameraFade(1.f, data.Color, false);
		OnFadeIn.Broadcast();
	}
	else
	{
		StartCameraFade(FadeAmount, 1.f, durationFromCurrentFadeAmount, data.Color);
	}
}

void AFadeSystem::FadeOut(FFadeData data)
{
	if(FadeAmount > 0.f)
	{
		data.Color = FadeColor;
	}

	float durationFromCurrentFadeAmount = data.Duration - ((1.f - FadeAmount) * data.Duration);

	if(durationFromCurrentFadeAmount < 0.1f)
	{
		SetManualCameraFade(0.f, data.Color, false);
		OnFadeOut.Broadcast();
	}
	else
	{
		StartCameraFade(FadeAmount, 0.f, durationFromCurrentFadeAmount, data.Color);
	}
}

void AFadeSystem::FadeInOut(FFadeData data)
{
	FadeInOutData = data;
	OnFadeIn.AddUniqueDynamic(this, &AFadeSystem::OnAutoFadeIn);
	OnFadeOut.AddUniqueDynamic(this, &AFadeSystem::OnAutoFadeOut);

	FadeIn(data);
}

void AFadeSystem::OnAutoFadeIn()
{
	OnFadeIn.RemoveDynamic(this, &AFadeSystem::OnAutoFadeIn);
	FadeOut(FadeInOutData);
}

void AFadeSystem::OnAutoFadeOut()
{
	OnFadeOut.RemoveDynamic(this, &AFadeSystem::OnAutoFadeOut);
	FadeInOutData = FFadeData();
}
