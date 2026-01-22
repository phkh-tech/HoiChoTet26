// Fill out your copyright notice in the Description page of Project Settings.


#include "PHKH_HCT26/Public/HCT_HUD.h"
#include "Blueprint/UserWidget.h" 

AHCT_HUD::AHCT_HUD()
{
	// Initialize pointer
	HUDWidgetInstance = nullptr;
}

void AHCT_HUD::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("Start HCT_HUD"));


	if (WBP_HCT26)
	{
		if (UWorld* World = GetWorld())
		{
			HUDWidgetInstance = CreateWidget<UUserWidget>(World, WBP_HCT26);
			if (HUDWidgetInstance)
			{
				HUDWidgetInstance->AddToViewport();
			}
		}
	}
}
