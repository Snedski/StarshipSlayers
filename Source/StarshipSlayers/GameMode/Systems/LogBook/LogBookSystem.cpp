// Fill out your copyright notice in the Description page of Project Settings.


#include "LogBookSystem.h"
#include "../../../Widgets/LogBook/LogBook.h"
#include "../Fade/FadeSystem.h"
#include "../../../Character/Controllers/MainPlayerController.h"

ULogBookSystem::ULogBookSystem()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void ULogBookSystem::SetupSystem()
{
	LogBook = CreateWidget<ULogBook>(GetWorld()->GetFirstPlayerController(), LogBookClass);
	LogBook->AddToViewport(1);
	LogBook->SetVisibility(ESlateVisibility::Hidden);
}

void ULogBookSystem::ToggleLogBook()
{
	if(bTransitionDone)
	{
		bTransitionDone = false;
		bLogBookOpen = !bLogBookOpen;

		AFadeSystem::GetInstance()->OnFadeIn.AddUniqueDynamic(this, &ULogBookSystem::OnToggleFadeIn);
		AFadeSystem::GetInstance()->OnFadeOut.AddUniqueDynamic(this, &ULogBookSystem::OnToggleFadeOut);
		AFadeSystem::GetInstance()->FadeInOut(FadeTransitionSettings);
	}
}

bool ULogBookSystem::IsLogBookOpen()
{
	return bLogBookOpen;
}

bool ULogBookSystem::InTransition()
{
	return !bTransitionDone;
}

void ULogBookSystem::OnToggleFadeIn()
{
	AFadeSystem::GetInstance()->OnFadeIn.RemoveDynamic(this, &ULogBookSystem::OnToggleFadeIn);
	AMainPlayerController* controller = (AMainPlayerController*) GetWorld()->GetFirstPlayerController();

	LogBook->SetVisibility(bLogBookOpen ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	controller->SetPause(bLogBookOpen);

	if(bLogBookOpen)
	{
		controller->SetInputMode(FInputModeGameAndUI());
	}
	else
	{
		controller->SetInputMode(FInputModeGameOnly());
	}
}

void ULogBookSystem::OnToggleFadeOut()
{
	AFadeSystem::GetInstance()->OnFadeOut.RemoveDynamic(this, &ULogBookSystem::OnToggleFadeOut);
	bTransitionDone = true;
}
