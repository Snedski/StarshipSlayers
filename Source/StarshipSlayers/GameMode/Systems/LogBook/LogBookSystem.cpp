// Fill out your copyright notice in the Description page of Project Settings.


#include "LogBookSystem.h"
#include "../../../Widgets/LogBook/LogBook.h"
#include "../Fade/FadeSystem.h"

ULogBookSystem::ULogBookSystem()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void ULogBookSystem::SetupSystem()
{
	LogBook = CreateWidget<ULogBook>(GetWorld(), LogBookClass);
	LogBook->AddToViewport(1);
	LogBook->SetVisibility(ESlateVisibility::Hidden);
}

void ULogBookSystem::ToggleLogBook()
{
	if(bTransitionDone)
	{
		bTransitionDone = false;

		AFadeSystem::GetInstance()->OnFadeIn.AddUniqueDynamic(this, &ULogBookSystem::OnToggleFadeIn);
		AFadeSystem::GetInstance()->OnFadeOut.AddUniqueDynamic(this, &ULogBookSystem::OnToggleFadeOut);
		AFadeSystem::GetInstance()->FadeInOut(FadeTransitionSettings);
	}
}

void ULogBookSystem::OnToggleFadeIn()
{
	AFadeSystem::GetInstance()->OnFadeIn.RemoveDynamic(this, &ULogBookSystem::OnToggleFadeIn);

	bool bOpenLogBook = LogBook->GetVisibility() == ESlateVisibility::Hidden;

	LogBook->SetVisibility(bOpenLogBook ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	GetWorld()->GetFirstPlayerController()->SetPause(bOpenLogBook);
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = bOpenLogBook;

	if(bOpenLogBook)
	{
		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameAndUI());
	}
	else
	{
		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
	}
}

void ULogBookSystem::OnToggleFadeOut()
{
	AFadeSystem::GetInstance()->OnFadeOut.RemoveDynamic(this, &ULogBookSystem::OnToggleFadeOut);
	bTransitionDone = true;
}
