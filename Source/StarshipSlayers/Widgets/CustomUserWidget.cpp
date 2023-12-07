// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomUserWidget.h"
#include "../Character/Controllers/MainPlayerController.h"
#include "Components/Button.h"

void UCustomUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//SetIsFocusable(true);
}

void UCustomUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	MainPlayerController = (AMainPlayerController*) GetWorld()->GetFirstPlayerController();
	FocusButton = GetAllButtons();

	SetCursor(MainPlayerController->IsUsingGamepad() ? EMouseCursor::None : EMouseCursor::Default);
	MainPlayerController->OnControllerTypeChanged.AddUniqueDynamic(this, &UCustomUserWidget::OnControllerTypeChanged);
}

void UCustomUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(IsVisible() && FocusButton.Num() > 0)
	{
		UButton* currentFocusButton = PreviousFocusedButton;

		for(UButton* button : FocusButton)
		{
			if(button->HasUserFocus(MainPlayerController))
			{
				if(currentFocusButton != button)
				{
					OnFocusChanged(button, currentFocusButton);
					PreviousFocusedButton = button;
				}

				return;
			}
		}

		if(currentFocusButton != nullptr)
		{
			currentFocusButton->SetFocus();
		}
		else
		{
			FocusButton[0]->SetFocus();
		}
	}
}

FReply UCustomUserWidget::NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	MainPlayerController->DetectController(InKeyEvent.GetKey().IsGamepadKey());

	return FReply::Unhandled();
}

void UCustomUserWidget::OnControllerTypeChanged(bool bUseGamepad)
{
	SetCursor(bUseGamepad ? EMouseCursor::None : EMouseCursor::Default);
}