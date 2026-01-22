// Fill out your copyright notice in the Description page of Project Settings.


#include "PHKH_HCT26/Public/HCT_HUD.h"

AHCT_HUD::AHCT_HUD()
{
}

void AHCT_HUD::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("Start HCT_HUD"));
}
