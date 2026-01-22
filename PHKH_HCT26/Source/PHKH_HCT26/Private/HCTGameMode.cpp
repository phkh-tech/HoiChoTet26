// Fill out your copyright notice in the Description page of Project Settings.


#include "PHKH_HCT26/Public/HCTGameMode.h"

AHCTGameMode::AHCTGameMode()
{
}

void AHCTGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("Start Game Mode"));
}
