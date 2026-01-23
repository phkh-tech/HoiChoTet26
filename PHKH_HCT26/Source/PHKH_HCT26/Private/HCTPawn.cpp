// Fill out your copyright notice in the Description page of Project Settings.


#include "PHKH_HCT26/Public/HCTPawn.h"

#include "PHKH_HCT26/PHKH_HCT26.h"


// Sets default values
AHCTPawn::AHCTPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHCTPawn::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LOGHCT2026, Warning, TEXT("Start HCTPawn"));
	
}

// Called every frame
void AHCTPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AHCTPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

