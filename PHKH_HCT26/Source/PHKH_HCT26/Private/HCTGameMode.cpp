// Fill out your copyright notice in the Description page of Project Settings.


#include "PHKH_HCT26/Public/HCTGameMode.h"
#include "HCTPawn.h"
#include "PHKH_HCT26/PHKH_HCT26.h"

AHCTGameMode::AHCTGameMode()
{
	DefaultPawnClass = AHCTPawn::StaticClass();
}

void AHCTGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogHCT2026, Warning, TEXT("Start Game Mode"));
}
