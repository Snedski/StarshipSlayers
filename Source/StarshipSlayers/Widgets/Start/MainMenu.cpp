// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "../../GameMode/Systems/Fade/FadeSystem.h"
#include "../../Data/FadeData.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void UMainMenu::OnPlay()
{
	AFadeSystem::GetInstance()->OnFadeIn.AddUniqueDynamic(this, &UMainMenu::OnPlayFadeIn);
	AFadeSystem::GetInstance()->FadeIn(FFadeData());
}

void UMainMenu::OnQuit()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}

void UMainMenu::OnPlayFadeIn()
{
	AFadeSystem::GetInstance()->OnFadeIn.RemoveDynamic(this, &UMainMenu::OnPlayFadeIn);
	UGameplayStatics::OpenLevel(GetWorld(), FName("FirstPersonMap"));
}
