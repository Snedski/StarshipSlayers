// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUD.h"

void UMainHUD::ShowInteractionPopup(bool bShow)
{
	if(bShow != bInteractionPopupShown)
	{
		bInteractionPopupShown = bShow;
		PlayInteractionPopupFadeAnimation(bInteractionPopupShown);
	}
}
