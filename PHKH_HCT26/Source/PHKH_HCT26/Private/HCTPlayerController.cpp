// Fill out your copyright notice in the Description page of Project Settings.


#include "PHKH_HCT26/Public/HCTPlayerController.h"

AHCTPlayerController::AHCTPlayerController()
{
}

void AHCTPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Start HCTPlayerController"));
}
