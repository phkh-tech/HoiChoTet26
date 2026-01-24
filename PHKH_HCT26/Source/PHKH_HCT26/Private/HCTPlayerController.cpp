// Fill out your copyright notice in the Description page of Project Settings.


#include "PHKH_HCT26/Public/HCTPlayerController.h"

#include "PHKH_HCT26/PHKH_HCT26.h"

AHCTPlayerController::AHCTPlayerController()
{
}

void AHCTPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogHCT2026, Warning, TEXT("Start HCTPlayerController"));
}
