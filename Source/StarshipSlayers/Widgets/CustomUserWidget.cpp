// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomUserWidget.h"
#include "../Character/Controllers/MainPlayerController.h"

void UCustomUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetIsFocusable(true);
}

void UCustomUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	MainPlayerController = (AMainPlayerController*) GetWorld()->GetFirstPlayerController();

	SetCursor(MainPlayerController->IsUsingGamepad() ? EMouseCursor::None : EMouseCursor::Default);
	MainPlayerController->OnControllerTypeChanged.AddUniqueDynamic(this, &UCustomUserWidget::OnControllerTypeChanged);
}

void UCustomUserWidget::OnControllerTypeChanged(bool bUseGamepad)
{
	SetCursor(bUseGamepad ? EMouseCursor::None : EMouseCursor::Default);
}