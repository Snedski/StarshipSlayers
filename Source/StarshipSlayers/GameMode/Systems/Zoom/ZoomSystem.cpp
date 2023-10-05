// Fill out your copyright notice in the Description page of Project Settings.


#include "ZoomSystem.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"

UZoomSystem::UZoomSystem()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UZoomSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(bOn)
	{
		CurrentZoomTime += DeltaTime;

		if(CurrentZoomTime >= ZoomTime)
		{
			CurrentZoomTime = ZoomTime;
			SetComponentTickEnabled(false);
		}
	}
	else
	{
		CurrentZoomTime -= DeltaTime;

		if(CurrentZoomTime <= 0.f)
		{
			CurrentZoomTime = 0.f;
			SetComponentTickEnabled(false);
		}
	}

	float alpha = CurrentZoomTime / ZoomTime;
	float smoothAlpha = SmoothCurve->GetFloatValue(alpha);
	OriginCamera->SetFieldOfView(FMath::Lerp(DefaultFOV, TargetFOV, smoothAlpha));
}

void UZoomSystem::SetupSystem(UCameraComponent* camera)
{
	OriginCamera = camera;
	DefaultFOV = OriginCamera->FieldOfView;
}

void UZoomSystem::EnableZoom(bool bEnable)
{
	bOn = bEnable;
	SetComponentTickEnabled(true);
}

